// Built-in arenas (level scripts stored in the executable).
// Extracted verbatim from sumofull.exe; see script/script.h for the language.

// @ 0x42bd68 (1294 chars)
static const char kLevelKitchen[] =
    "mainbox()={addbox(vec(60,5,60),vec(0,-5,0),3,1);};"
    "chair0(pos)={\taddbox(vec(4,1,3),pos+vec(0,5,0),1,1); breakability(80);"
    "\taddbox(vec(1,3,3),pos+vec(3,9,0),1,0); breakability(80);"
    "\taddbox(vec(1,2,3),pos+vec(3,2,0),1,1); breakability(80);"
    "\taddbox(vec(1,2,3),pos+vec(-3,2,0),1,1); breakability(80);};"
    "chair2(pos)={\taddbox(vec(4,1,3),pos+vec(0,5,0),1,1); breakability(80);"
    "\taddbox(vec(1,3,3),pos+vec(-3,9,0),1,0); breakability(80);"
    "\taddbox(vec(1,2,3),pos+vec(3,2,0),1,1); breakability(80);"
    "\taddbox(vec(1,2,3),pos+vec(-3,2,0),1,1); breakability(80);};table(pos)={\tbr=100;"
    "\taddbox(vec(10,1,10),pos+vec(0,9,0),0,0); breakability(br);"
    "\taddbox(vec(1,4,1),pos+vec(9,4,-9 ),0,1); breakability(br);"
    "\taddbox(vec(1,4,1),pos+vec(9,4,9  ),0,1); breakability(br);"
    "\taddbox(vec(1,4,1),pos+vec(-9,4,-9),0,1); breakability(br);"
    "\taddbox(vec(1,4,1),pos+vec(-9,4,9 ),0,1); breakability(br);};walls()={\tbr=150;"
    "\taddbox(vec(55,8,1),vec(0,8,-56),2,1);breakability(br);"
    "\taddbox(vec(55,8,1),vec(0,8,56),2,1);breakability(br);"
    "\taddbox(vec(1,8,55),vec(-56,8,0),2,1);breakability(br);"
    "\taddbox(vec(1,8,55),vec(56,8,0),2,1);breakability(br);};walls();table(vec(0,0,0));"
    "chair2(vec(-15,0,0));chair0(vec(15,0,0));mainbox();man(vec(0,0,-25),vec(0,0,1),2);"
    "man(vec(0,0,25),vec(0,0,-1),3);man(vec(25,0,0),vec(-1,0,0),0);"
    "man(vec(-25,0,0),vec(1,0,0),1);";

// @ 0x42b8d0 (1171 chars)
static const char kLevelRoof[] =
    "mainbox()={\taddbox(vec(3,10.5,3),vec(0,0.5,0),5,1);"
    " \taddbox(vec(30,2,3),vec(0,12.98,0),5,1); \taddbox(vec(3,2,30),vec(0,13,0),5,1);};"
    " mainbox();table(pos)={\tbr=100;\taddbox(vec(10,1,10),pos+vec(0,9,0),0,0); breakability(br);"
    "\taddbox(vec(1,4,1),pos+vec(9,4,-9 ),0,1); breakability(br);"
    "\taddbox(vec(1,4,1),pos+vec(9,4,9  ),0,1); breakability(br);"
    "\taddbox(vec(1,4,1),pos+vec(-9,4,-9),0,1); breakability(br);"
    "\taddbox(vec(1,4,1),pos+vec(-9,4,9 ),0,1); breakability(br);};"
    "chair0(pos)={\taddbox(vec(4,1,3),pos+vec(0,5,0),1,1); breakability(80);"
    "\taddbox(vec(1,3,3),pos+vec(3,9,0),1,0); breakability(80);"
    "\taddbox(vec(1,2,3),pos+vec(3,2,0),1,1); breakability(80);"
    "\taddbox(vec(1,2,3),pos+vec(-3,2,0),1,1); breakability(80);};"
    "chair2(pos)={\taddbox(vec(4,1,3),pos+vec(0,5,0),1,1); breakability(80);"
    "\taddbox(vec(1,3,3),pos+vec(-3,9,0),1,0); breakability(80);"
    "\taddbox(vec(1,2,3),pos+vec(3,2,0),1,1); breakability(80);"
    "\taddbox(vec(1,2,3),pos+vec(-3,2,0),1,1); breakability(80);};table(vec(14,-10,20));"
    "table(vec(-14,-10,-20));chair0(vec(15,-10,-15));chair2(vec(-15,-10,15));"
    "man(vec(0,20,-20),vec(0,0,1),4);man(vec(0,20,20),vec(0,0,-1),5);"
    "man(vec(20,20,0),vec(-1,0,0),4);man(vec(-20,20,0),vec(1,0,0),5);";

// @ 0x42b6f8 (465 chars)
static const char kLevelSeesaw[] =
    "addbox( vec(20,2,50),vec(0,-8,0), 0,1);addbox( vec(3,4,8),vec(-7,-6,0), 10,1);"
    "addbox( vec(3,4,8),vec(7,-6,0), 10,1);addbox( vec(8,17,10),vec(0,0,0), 6,1);p=vec(0,1,0);"
    "repeat(33) {\tp=rot(p,vec(pi*2/33,0,0));\tcutplane( p, -6);};"
    "addbox( vec(6,1,30),vec(0,7,0), 0,0);addbox( vec(2,1,1),vec(3,10,0), 0,0);"
    "addbox( vec(2,1,1),vec(-3,10,0), 0,0);man(vec(0,8,-28),vec(0,0,1),2);"
    " man(vec(0,8,28),vec(0,0,-1),3); man(vec(0,8,-18),vec(0,0,1),0);"
    "man(vec(0,8,18),vec(0,0,-1),1); ";

// @ 0x42b560 (402 chars)
static const char kLevelStage[] =
    "addbox( vec(8,8,3), vec(0,-2,-33),10,1);addbox( vec(8,8,3), vec(0,-2,33),10,1);"
    "addbox( vec(6,1,35),vec(0,7,0), 0,1); breakability(210);"
    "addbox( vec(3,2,8), vec(33,-8,-0),10,1);addbox( vec(3,2,8), vec(-33,-8,0),10,1);"
    "addbox( vec(35,1.5,6),vec(0,-4.5,0), 0,0); breakability(270);"
    "man(vec(0,8,-20),vec(0,0,1),0);man(vec(0,8,20),vec(0,0,-1),1);"
    " man(vec(0,8,-30),vec(0,0,1),0);man(vec(0,8,30),vec(0,0,-1),1); ";

// @ 0x42b338 (548 chars)
static const char kLevelDownstairs[] =
    "p=vec(-50,-8,0);br=100000;repeat(13){\taddbox(vec(3,1,30),p,0,1); breakability(250);"
    "\taddbox(vec(5,1,30),p+vec(2,-2,0),10,1);\tp=p+vec(6,4,0);"
    "}addbox(vec(15,1,30),p+vec(12,-2,0),10,1);p=p+vec(6,4,0);p=p+vec(6,-4,0);"
    "addbox(vec(15,1,30),p,0,1);addbox(vec(1,7,28),p+vec(15,8,0),1,1); breakability(200);"
    "addbox(vec(15,7,1),p+vec(0,8,29),1,1); breakability(200);"
    "addbox(vec(15,7,1),p+vec(0,8,-29),1,1); breakability(200);"
    "man(vec(-11,8,-15)+p,vec(0,0,1),2);man(vec(-11,8,15)+p,vec(0,0,-1),3);"
    "man(vec(6,8,-15)+p,vec(-1,0,0),0);man(vec(6,8,15)+p,vec(-1,0,0),1);";
