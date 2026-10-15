// The level description language: compiler and evaluator.
#include "script.h"

Script g_script;
char g_levelBuiltinsAdded;


// @ 0x405012
void skipWhitespace(char **p)
{
    while (**p == ' ' || **p == '\t' || **p == '\r' || **p == '\n')
        ++*p;
}

// @ 0x40515d
int isIdentifierStart(char c)
{
    if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && c != '_')
        return 0;
    return 1;
}

// @ 0x40522e
int isIdentifierChar(char c)
{
    if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && c != '_' && (c < '0' || c > '9'))
        return 0;
    return 1;
}

// @ 0x405326
int isDigit(char c)
{
    if (c < '0' || c > '9')
        return 0;
    return 1;
}

void Script::fail(const char *message)
{
    if (!failed) {
        failed = 1;
        error = message;
    }
}

// @ 0x404ba1
Vec3 *Script::makeNumber(Vec3 *out, double v)
{
    float f = (float)v;
    *out = V3(f, f, f);
    return out;
}

// @ 0x405cf2
Script::Script()
{
    // @ 0x4053ba: the containers start empty
    program = ArrayList<ScriptOp>();
    code = ArrayList<ScriptInstr>();
    builtins = ArrayList<ScriptBuiltin>();
    functions = nullptr;
    maxPriority = 0;
    operators = ArrayList<ScriptOperator>();
    regInfo = ArrayList<ScriptRegInfo>();
    init();
}

// @ 0x40540b
Script::~Script()
{
    regInfo.release();
    operators.release();
    builtins.release();
    code.release();
    program.release();
}

// @ 0x405ca7
void Script::init()
{
    reset(0.0f, 0.0f, 0.0f);
    addOperators(5, kOperators);
    addBuiltins(12, kMathBuiltins);
}

// @ 0x405d28
void scriptInitLevelBuiltins()
{
    if (!g_levelBuiltinsAdded) {
        g_script.init();
        g_script.addBuiltins(6, kLevelBuiltins);
        g_levelBuiltinsAdded = 1;
    }
}

// @ 0x404fb1
ScriptVar *Script::newVariable()
{
    ScriptVar *v = (ScriptVar *)malloc(sizeof(ScriptVar));
    v->prev = nullptr;
    v->next = vars;
    if (vars)
        vars->prev = v;
    vars = v;
    v->isConst = 0;
    v->value.reg = -1;
    v->value.value = defaultValue;
    v->name[0] = 0;
    return v;
}

// @ 0x4054df
void Script::reset(float x, float y, float z)
{
    vars = nullptr;
    if (failed)
        failed = 0;
    program.last = program.first;
    code.last = code.first;
    invalid.reg = -1;
    defaultValue = V3(x, y, z);
    invalid.value = V3(x, y, z);
    maxPriority = 0;
    regCount = 0;
    ans = newVariable();
    ans->isConst = 1;
    strcpy(ans->name, "ans");
    ans->value.reg = -1;
    ans->value.value = defaultValue;
}

// @ 0x40547a
void Script::clearVariables()
{
    vars = nullptr;
    if (failed)
        failed = 0;
    program.last = program.first;
    code.last = code.first;
    regCount = 0;
    ans = newVariable();
    ans->isConst = 1;
    strcpy(ans->name, "ans");
    ans->value.reg = -1;
    ans->value.value = defaultValue;
}

// @ 0x40544b
void Script::addConstant(const char *name, float x, float y, float z)
{
    ScriptVar *v = newVariable();
    v->isConst = 1;
    strcpy(v->name, name);
    v->value.reg = -1;
    v->value.value = V3(x, y, z);
}

// @ 0x4057d0
void Script::addMathConstants()
{
    Vec3 pi = V3(3.14159274f);
    addConstant("pi", pi.x, pi.y, pi.z);
    Vec3 e = V3((float)fp::exp(1.0));
    addConstant("_e", e.x, e.y, e.z);
}

// @ 0x40583a
void Script::addBuiltins(int count, const ScriptBuiltin *table)
{
    for (; count > 0; --count)
        builtins.push_back(*table++);
}

// @ 0x405863
void Script::addOperators(int count, const ScriptOperator *table)
{
    for (; count > 0; --count, ++table) {
        if (maxPriority < table->priority)
            maxPriority = table->priority;
        operators.push_back(*table);
    }
}

// @ 0x40517f
// Parameters of the function being expanded shadow the variables.
ScriptVar *Script::findVariable(const char *name)
{
    for (ScriptVar *v = locals; v; v = v->next) {
        if (strcmp(name, v->name) == 0)
            return v;
    }
    for (ScriptVar *v = vars; v; v = v->next) {
        if (strcmp(name, v->name) == 0)
            return v;
    }
    return nullptr;
}

// @ 0x405773
ScriptVar *Script::findVariableAt(char *p)
{
    char name[16];
    readIdentifier(p, name);
    return findVariable(name);
}

// @ 0x405258
ScriptFunction *Script::findFunction(const char *name)
{
    for (ScriptFunction *f = functions; f; f = f->next) {
        if (strcmp(f->names[0], name) == 0)
            return f;
    }
    return nullptr;
}

// @ 0x4056e8
ScriptFunction *Script::newFunction()
{
    ScriptFunction *f = (ScriptFunction *)malloc(sizeof(ScriptFunction));
    f->next = functions;
    f->prev = nullptr;
    if (functions)
        functions->prev = f;
    functions = f;
    f->paramCount = 0;
    f->names[0][0] = 0;
    f->body.first = nullptr;
    f->body.last = nullptr;
    f->body.capacityEnd = nullptr;
    return f;
}

// @ 0x405734
int Script::findOperator(char c)
{
    for (int i = 0; i < operators.size(); ++i) {
        if (c == operators.at(i).symbol)
            return i;
    }
    return -1;
}

// @ 0x40560b
// Reads an identifier of at most 15 characters; out may be null to skip it.
char *Script::readIdentifier(char *p, char *out)
{
    if (!out) {
        if (isIdentifierStart(*p)) {
            int left = 14;
            for (;;) {
                ++p;
                if (!isIdentifierChar(*p))
                    break;
                if (left == 0) {
                    fail("identifier too long");
                    return p;
                }
                --left;
            }
        }
        return p;
    }

    char c = *p;
    if (isIdentifierStart(c)) {
        *out = c;
        int left = 14;
        for (;;) {
            ++p;
            ++out;
            c = *p;
            if (!isIdentifierChar(c))
                break;
            if (left == 0) {
                *out = 0;
                fail("identifier too long");
                return p;
            }
            *out = c;
            --left;
        }
    }
    *out = 0;
    return p;
}

// @ 0x4051cc
// Statements up to the closing '}' of a repeat block.
char *Script::parseBlock(char *p)
{
    if (!p)
        return nullptr;
    while (p && *p == ';')
        ++p;
    for (;;) {
        if (!p)
            return nullptr;
        if (*p == '}' || *p == 0)
            return p;
        if (failed)
            return p;
        char *q = statement(p);
        if (failed)
            return nullptr;
        while (q && *q == ';')
            ++q;
        skipWhitespace(&q);
        p = q;
    }
}

// @ 0x40652f
void Script::compile(const char *text)
{
    char *p = (char *)text;
    if (!p)
        return;
    while (p && *p == ';')
        ++p;
    while (p && *p && !failed) {
        char *q = statement(p);
        if (failed)
            break;
        while (q && *q == ';')
            ++q;
        skipWhitespace(&q);
        p = q;
    }
}

// @ 0x4059f9
// name(a, b, ...) = { body }
char *Script::defineFunction(const char *name, char *params, char *body)
{
    for (int i = 0; i < builtins.size(); ++i) {
        if (strcmp(name, builtins.at(i).name) == 0) {
            if (failed)
                return nullptr;
            error = "Default function cannot be overriden";
            failed = 1;
            return nullptr;
        }
    }

    ScriptFunction *f = findFunction(name);
    if (!f)
        f = newFunction();
    strcpy(f->names[0], name);
    skipWhitespace(&params);
    f->paramCount = 0;

    char *p = params;
    for (;;) {
        if (*p == ')' || *p == 0) {
            skipWhitespace(&body);
            if (*body != '{') {
                if (failed)
                    return nullptr;
                error = "{ expected to define function";
                failed = 1;
                return nullptr;
            }
            ++body;
            skipWhitespace(&body);
            char *s = body;
            f->body.last = f->body.first;
            int depth = 0;
            char c = *s;
            while (c != 0 && (c != '}' || depth != 0)) {
                if (c == '{')
                    ++depth;
                if (c == '}')
                    --depth;
                f->body.push_back(*s);
                ++s;
                c = *s;
            }
            f->body.push_back('\0');
            if (*s != 0)
                return s + 1;
            if (failed)
                return nullptr;
            error = "function definition not closed by }";
            failed = 1;
            return nullptr;
        }

        int index = ++f->paramCount;
        params = readIdentifier(p, f->names[index]);
        skipWhitespace(&params);
        char c = *params;
        if ((c != ')' && c != ',') || f->names[f->paramCount][0] == 0) {
            f->paramCount = 0;
            f->body.last = f->body.first;
            if (failed)
                return nullptr;
            error = "Parameter variables exlected";
            failed = 1;
            return nullptr;
        }
        p = params;
        if (c == ',')
            p = params + 1;
    }
}

// @ 0x405bb3
// Calls a built-in.  With constant arguments it runs at once; otherwise an
// instruction is emitted and a new register receives the result.
ScriptOperand Script::call(ScriptFn fn, int argc, ScriptOperand *args, const char *name)
{
    Vec3 constants[5];
    Vec3 *ctx[6];
    Vec3 value;
    ScriptOperand result;

    int i = 0;
    for (; i < argc; ++i) {
        if (args[i].reg != -1)
            break;
        constants[i] = args[i].value;
        ctx[i + 1] = &constants[i];
    }
    ctx[0] = &value;

    if (i == argc) {
        result.reg = -1;
        fn(ctx);
    } else {
        ScriptInstr ins;
        ins.fn = fn;
        for (i = 0; i < argc; ++i) {
            int reg = args[i].reg;
            if (reg == -1) {
                reg = regCount;
                regs[reg] = args[i].value;
                ++regCount;
            }
            ins.args[i] = reg;
        }
        strcpy(ins.name, name);
        ins.argc = argc;
        result.reg = regCount;
        regs[regCount] = defaultValue;
        ++regCount;
        value = defaultValue;
        ins.out = result.reg;
        code.push_back(ins);
    }
    result.value = value;
    return result;
}

// @ 0x405fb5
// operand { operator operand } with priorities; depth > 0 inside ( ).
ScriptOperand Script::parseExpression(int depth)
{
    ScriptOperand values[64];
    char ops[64];
    int count = 0;
    char c;

    do {
        values[count] = parseOperand(depth);
        if (failed)
            return invalid;
        skipWhitespace(&cursor);
        c = *cursor;
        if (c != 0 && c != ';' && c != ')' && c != ',') {
            ++cursor;
            ops[count] = (char)findOperator(c);
            if (ops[count] == -1) {
                fail("Operator expected");
                return invalid;
            }
        }
        ++count;
    } while (!failed && (c = *cursor) != 0 && c != ';' && c != ')' && c != ',');

    if (*cursor == ')') {
        if (depth == 0) {
            fail("Unexpected )");
            return invalid;
        }
        ++cursor;
    } else if (depth != 0) {
        fail("Expected )");
        return invalid;
    }

    // reduce, highest priority first, left to right
    for (int priority = maxPriority; priority >= 0; --priority) {
        int w = 1;
        for (int r = 1; r < count; ++r) {
            int op = ops[r - 1];
            if (operators.at(op).priority == priority) {
                ScriptOperand pair[2] = {values[w - 1], values[r]};
                char name[4] = {'o', 'p', operators.at(op).symbol, 0};
                values[w - 1] = call(operators.at(op).fn, 2, pair, name);
                ops[w - 1] = ops[r];
            } else {
                ops[w] = ops[r];
                values[w] = values[r];
                ++w;
            }
        }
        count = w;
    }

    if (count != 1) {
        if (failed)
            return invalid;
        failed = 1;
        error = "Unknown Error";
    }
    if (failed)
        return invalid;
    return values[0];
}

// @ 0x406216
char *Script::expressionStatement(char *p)
{
    cursor = p;
    last = parseExpression(0);
    int reg = last.reg;
    if (reg == -1) {
        reg = regCount;
        regs[reg] = last.value;
        ++regCount;
    }
    resultReg = reg;
    return cursor;
}

// @ 0x406277
int Script::parseArguments(ScriptOperand *out, int count)
{
    int parsed = 0;
    for (;;) {
        --count;
        if (count < 1) {
            *out = parseExpression(1);
        } else {
            *out = parseExpression(0);
            if (*cursor != ',') {
                fail("More parameters expected");
                return 0;
            }
            ++cursor;
        }
        ++parsed;
        ++out;
        if (failed)
            return 0;
        if (count == 0)
            return parsed;
    }
}

// @ 0x406306
char *Script::statement(char *p)
{
    if (*p == 0)
        return nullptr;
    skipWhitespace(&p);
    if (!isIdentifierStart(*p))
        return expressionStatement(p);

    char name[16];
    char *q = readIdentifier(p, name);
    skipWhitespace(&q);

    if (strcmp(name, "repeat") == 0) {
        if (*q != '(') {
            if (failed)
                return nullptr;
            error = "( expected after repeat";
            failed = 1;
            return nullptr;
        }
        ++q;
        skipWhitespace(&q);
        cursor = q;
        ScriptOperand times;
        parseArguments(&times, 1);
        if (times.reg != -1) {
            if (failed)
                return nullptr;
            error = "Parameter of repeat must be definit";
            failed = 1;
            return nullptr;
        }
        int n = fp::ftol(times.value.x);
        if (n < 0) {
            if (failed)
                return nullptr;
            error = "Parameter of repeat cannot be negative";
            failed = 1;
            return nullptr;
        }
        skipWhitespace(&cursor);
        if (*cursor != '{') {
            if (failed)
                return nullptr;
            error = "{ expected for repeat";
            failed = 1;
            return nullptr;
        }
        char *start = ++cursor;
        for (; n > 0; --n) {
            cursor = start;
            cursor = parseBlock(start);
        }
        if (*cursor == '}')
            return ++cursor;
        if (failed)
            return nullptr;
        error = "{ for repeat must be closed by }";
        failed = 1;
        return nullptr;
    }

    if (*q != '=') {
        if (*q == '(') {
            // name(params) = { ... } defines a function
            char *params = q + 1;
            char *s = params;
            for (char c = *s; c != 0 && c != '('; c = *++s) {
                if (c == ')')
                    break;
            }
            if (*s == ')') {
                char *t = s + 1;
                skipWhitespace(&t);
                if (*t == '=')
                    return defineFunction(name, params, t + 1);
            }
        }
        return expressionStatement(p);
    }

    ScriptVar *v = findVariable(name);
    if (!v) {
        v = newVariable();
        strcpy(v->name, name);
    }
    if (v->isConst & 1) {
        if (failed)
            return nullptr;
        error = "Constant cannot be modified";
        failed = 1;
        return nullptr;
    }
    cursor = q + 1;
    v->value = parseExpression(0);
    return cursor;
}

// @ 0x406587
// number | -operand | ( expression ) | builtin(args) | function(args) | variable
ScriptOperand Script::parseOperand(int depth)
{
    ScriptOperand result = invalid;
    char negate = 0;

    while (*cursor == ' ')
        ++cursor;
    char c = *cursor;
    if (c == '(') {
        ++cursor;
        return parseExpression(depth + 1);
    }
    while (c == '-') {
        negate ^= 1;
        ++cursor;
        skipWhitespace(&cursor);
        c = *cursor;
    }

    char *start = cursor;
    if (!isIdentifierStart(*start)) {
        if (!isDigit(*cursor)) {
            fail("Value or ( expected");
            return result;
        }
        double scale = 1.0;
        double v = 0.0;
        char *s;
        do {
            s = cursor;
            char d = *s;
            cursor = s + 1;
            v = v * 10.0 + (double)(d - '0');
        } while (isDigit(*cursor));
        if (s[1] == '.') {
            s += 2;
            cursor = s;
            while (isDigit(*cursor)) {
                char d = *s;
                scale = scale * 0.1;
                ++s;
                cursor = s;
                v = (double)(d - '0') * scale + v;
            }
        }
        if (negate)
            v = -v;
        result.reg = -1;
        makeNumber(&result.value, v);
        return result;
    }

    char name[16];
    char *after = readIdentifier(start, name);
    skipWhitespace(&after);
    if (*after != '(') {
        ScriptVar *v = findVariableAt(cursor);
        if (v) {
            cursor = readIdentifier(cursor, nullptr);
            return v->value;   // a leading minus is ignored here
        }
        fail("No such command or variable");
        return result;
    }

    cursor = after + 1;
    ScriptOperand args[16];
    for (int i = 0; i < builtins.size(); ++i) {
        if (strcmp(name, builtins.at(i).name) == 0) {
            parseArguments(args, builtins.at(i).argc);
            if (failed)
                return result;
            result = call(builtins.at(i).fn, builtins.at(i).argc, args, builtins.at(i).name);
            if (negate) {
                fail("minus not supported now");
                return invalid;
            }
            return result;
        }
    }

    ScriptFunction *f = findFunction(name);
    if (!f) {
        fail("Undefined Function");
        return result;
    }

    ScriptVar *savedLocals = locals;
    ScriptVar params[16];
    if (f->paramCount == 0) {
        skipWhitespace(&cursor);
        if (*cursor != ')') {
            fail("No parameter expected");
            locals = savedLocals;
            return result;
        }
        ++cursor;
    } else {
        parseArguments(args, f->paramCount);
        if (failed) {
            locals = savedLocals;
            return result;
        }
        int i = 0;
        for (; i < f->paramCount; ++i) {
            strcpy(params[i].name, f->names[i + 1]);
            params[i].isConst = 0;
            params[i].prev = nullptr;
            params[i].next = &params[i + 1];
            params[i].value = args[i];
        }
        params[i - 1].next = nullptr;
        locals = params;
    }

    // expand the body in place
    char *saved = cursor;
    cursor = &f->body.at(0);
    compile(cursor);
    cursor = saved;
    result = last;
    locals = savedLocals;
    if (negate) {
        fail("minus not supported now");
        return invalid;
    }
    return result;
}

// @ 0x405d55
// Turns the instruction list into a directly callable program, folding
// virtual registers whose lifetimes do not overlap.  Writes asm.txt.
void Script::link()
{
    program.last = program.first;
    regInfo.last = regInfo.first;
    if (regCount == 0) {
        resultReg = 0;
        return;
    }

    for (int i = 0; i < regCount; ++i) {
        ScriptRegInfo info = {-1, -1, i};
        regInfo.push_back(info);
    }

    int t = 0;
    for (ScriptInstr *ins = code.first; ins < code.last; ++ins, ++t) {
        if (regInfo.at(ins->out).firstDef == -1)
            regInfo.at(ins->out).firstDef = t;
        for (int k = 0; k < ins->argc; ++k)
            regInfo.at(ins->args[k]).lastUse = t;
    }
    if (resultReg < regInfo.size())
        regInfo.at(resultReg).lastUse = t;
    else
        resultReg = 0;

    t = 0;
    for (ScriptInstr *ins = code.first; ins < code.last; ++ins, ++t) {
        ScriptOp op;
        op.fn = ins->fn;
        for (int k = 0; k < ins->argc; ++k) {
            ins->args[k] = regInfo.at(ins->args[k]).mapped;
            op.args[k] = &regs[ins->args[k]];
        }
        int mapped = regInfo.at(ins->out).mapped;
        for (int j = 0; j < regCount; ++j) {
            if (regInfo.at(j).lastUse <= t && regInfo.at(j).firstDef >= 0 && j != mapped &&
                regInfo.at(j).lastUse != -1) {
                regInfo.at(j) = regInfo.at(mapped);
                regInfo.at(mapped).mapped = j;
                j = regCount;
            }
        }
        ins->out = regInfo.at(ins->out).mapped;
        op.out = &regs[ins->out];
        program.push_back(op);
    }

    resultReg = regInfo.at(resultReg).mapped;
    dump("asm.txt");
}

// @ 0x4058aa
void Script::evaluate(Vec3 *out)
{
    Vec3 *result;
    if (regCount == 0) {
        result = &defaultValue;
    } else {
        for (ScriptOp *op = program.first; op < program.last; ++op)
            op->fn(&op->out);
        result = &regs[resultReg];
    }
    *out = *result;
}

// @ 0x4058f0
void Script::dump(const char *fileName)
{
    FILE *f = fopen(fileName, "w");
    for (int i = 0; i < regCount; ++i) {
        if (regInfo.at(i).firstDef == -1)
            fprintf(f, "Const: r%d = %g,%g,%g\n", i, (double)regs[i].x, (double)regs[i].y, (double)regs[i].z);
    }
    for (ScriptInstr *ins = code.first; ins < code.last; ++ins) {
        fprintf(f, "%s r%d, ", ins->name, ins->out);
        for (int k = 0; k < ins->argc; ++k) {
            fprintf(f, "r%d", ins->args[k]);
            if (k != ins->argc - 1)
                fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fprintf(f, "RESULT: r%d\n", resultReg);
    fclose(f);
}
