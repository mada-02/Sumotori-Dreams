// The level description language of the MOD files and built-in arenas.
//
// A small expression language over 3D vectors: assignments, user functions
// (expanded inline at compile time), repeat loops and built-in functions.
// Statements are evaluated while they are compiled: calls whose arguments
// are all constants run immediately (that is how the level builders such as
// addbox() take effect), everything else is compiled into a register program
// that the editor can re-evaluate.
#pragma once

#include "../core/common.h"
#include "../core/vecmath.h"

// A built-in receives { out, arg0, arg1, ... }.
typedef void (*ScriptFn)(Vec3 **args);

// 16 bytes: an expression value, either a constant or a register.
struct ScriptOperand {
    int reg;                  // -1 = constant
    Vec3 value;
};

// 0x2c bytes
struct ScriptVar {
    char name[16];
    ScriptOperand value;      // +0x10
    int isConst;              // +0x20
    ScriptVar *next;          // +0x24
    ScriptVar *prev;          // +0x28
};

// 0x18 bytes, tables at 0x453420 and 0x453568
struct ScriptBuiltin {
    char name[16];
    int argc;
    ScriptFn fn;
};

// 8 bytes, table at 0x453540
struct ScriptOperator {
    char symbol;
    char priority;
    char pad[2];
    ScriptFn fn;
};

// 0x128 bytes: user function, expanded inline at every call
struct ScriptFunction {
    char names[17][16];       // [0] = function name, [1..] = parameters
    int paramCount;           // +0x110
    ArrayList<char> body;     // +0x114
    ScriptFunction *next;     // +0x120
    ScriptFunction *prev;     // +0x124
};

// 0x30 bytes: compiled instruction (virtual registers)
struct ScriptInstr {
    ScriptFn fn;
    int argc;
    int out;
    int args[5];
    char name[16];
};

// 0x1c bytes: linked instruction
struct ScriptOp {
    ScriptFn fn;
    Vec3 *out;
    Vec3 *args[5];
};

// 12 bytes: register lifetime used by the linker
struct ScriptRegInfo {
    int firstDef;
    int lastUse;
    int mapped;
};

enum { SCRIPT_MAX_REGS = 1024 };

class Script {
public:
    Script();                                                   // @ 0x405cf2 (base 0x4053ba)
    virtual Vec3 *makeNumber(Vec3 *out, double v);              // vtable 0x42c3c0[0]: @ 0x404ba1
    ~Script();                                                  // @ 0x40540b

    void init();                                                // @ 0x405ca7
    void reset(float x, float y, float z);                      // @ 0x4054df
    void clearVariables();                                      // @ 0x40547a
    void addConstant(const char *name, float x, float y, float z); // @ 0x40544b
    void addMathConstants();                                    // @ 0x4057d0
    void addBuiltins(int count, const ScriptBuiltin *table);    // @ 0x40583a
    void addOperators(int count, const ScriptOperator *table);  // @ 0x405863

    void compile(const char *text);                             // @ 0x40652f
    void link();                                                // @ 0x405d55
    void evaluate(Vec3 *out);                                   // @ 0x4058aa
    void dump(const char *fileName);                            // @ 0x4058f0

    // +0x04 ...
    char *cursor;
    const char *error;
    char failed;
    char pad0d[3];
    Vec3 defaultValue;        // +0x10
    ScriptOperand invalid;    // +0x1c
    int regCount;             // +0x2c
    Vec3 regs[SCRIPT_MAX_REGS]; // +0x30
    ArrayList<ScriptOp> program;   // +0x3030
    ArrayList<ScriptInstr> code;   // +0x303c
    int resultReg;            // +0x3048
    ScriptOperand last;       // +0x304c
    ScriptVar *vars;          // +0x305c
    ScriptVar *locals;        // +0x3060 parameters of the function being expanded
    ScriptVar *ans;           // +0x3064
    ArrayList<ScriptBuiltin> builtins;   // +0x3068
    ScriptFunction *functions;           // +0x3074
    int maxPriority;                     // +0x3078
    ArrayList<ScriptOperator> operators; // +0x307c
    ArrayList<ScriptRegInfo> regInfo;    // +0x3088

private:
    void fail(const char *message);
    ScriptVar *newVariable();                                   // @ 0x404fb1
    ScriptVar *findVariable(const char *name);                  // @ 0x40517f
    ScriptVar *findVariableAt(char *p);                         // @ 0x405773
    ScriptFunction *findFunction(const char *name);             // @ 0x405258
    ScriptFunction *newFunction();                              // @ 0x4056e8
    int findOperator(char c);                                   // @ 0x405734
    char *readIdentifier(char *p, char *out);                   // @ 0x40560b
    char *parseBlock(char *p);                                  // @ 0x4051cc
    char *defineFunction(const char *name, char *params, char *body); // @ 0x4059f9
    ScriptOperand call(ScriptFn fn, int argc, ScriptOperand *args, const char *name); // @ 0x405bb3
    ScriptOperand parseExpression(int depth);                   // @ 0x405fb5
    char *expressionStatement(char *p);                         // @ 0x406216
    int parseArguments(ScriptOperand *out, int count);          // @ 0x406277
    char *statement(char *p);                                   // @ 0x406306
    ScriptOperand parseOperand(int depth);                      // @ 0x406587
};

void skipWhitespace(char **p);                                  // @ 0x405012
int isIdentifierStart(char c);                                  // @ 0x40515d
int isIdentifierChar(char c);                                   // @ 0x40522e
int isDigit(char c);                                            // @ 0x405326

extern Script g_script;                   // @ 0x4e7bd8
extern char g_levelBuiltinsAdded;         // @ 0x4eac6c

// Built-in tables (defined in builtins.cpp)
extern const ScriptBuiltin kMathBuiltins[12];   // @ 0x453420 (builtins.cpp)
extern const ScriptBuiltin kLevelBuiltins[6];   // @ 0x453568
extern const ScriptOperator kOperators[5];      // @ 0x453540

void scriptInitLevelBuiltins();           // @ 0x405d28

// float helpers used by the built-ins
double fmodf2(float a, float b);          // @ 0x4046d0 (wrapper 0x404704)
double powSigned(float a, float b);       // @ 0x404ab9
