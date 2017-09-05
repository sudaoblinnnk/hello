#include <stdio.h>

typedef int jint;

int for_func() {

L3: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_0 = 0x00000001;
//LABEL               |  LL0: line 65
L0: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
jint v1_0 = 0x00000000;
//LABEL               |  LL2: line 66
L2: ;
//CONST               |     |v2=0x00000003  // int:3   float:0.000000
jint v2_0 = 101;
//IF_GE               |     |if (v0 >= v2) {  goto L4; }
if (v0_0 >= v2_0) {  goto L4; }
//LABEL               |  LL5: line 67
L5: ;
//ADD                 |     |v1 = v1 + v0;
v1_0 = v1_0 + v0_0;
//LABEL               |  LL6: line 66
L6: ;
//ADD_INT_LIT_X       |     |v0 = v0 + 1;
v0_0 = v0_0 + 1;
//GOTO                |     |goto L2;
goto L2;
//LABEL               |  LL4: line 69
L4: ;
//RETURN_VOID         |     |return

return v1_0;
//LABEL               |  LL1:
L1: ;


}

int switch_func(int v2)
{

L2: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_0 = 0x00000000;
//LABEL               |  LL0: line 127
L0: ;
//PACKED_SWITCH       |     |switch(v2)
//PACKED_SWITCH       |     |case 1: goto L3
//PACKED_SWITCH       |     |case 2: goto L4
//PACKED_SWITCH       |     |default: goto L5

switch(v2) {
case 1: goto L3;
case 2: goto L4;
default: goto L5;
}

//LABEL               |  LL5: line 135
L5: ;
//CONST               |     |v0=0x00000003  // int:3   float:0.000000
v0_0 = 0x00000003;
//LABEL               |  LL6: line 138
L6: ;
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL3: line 257
L3: ;
//CONST               |     |v0=0x00000001  // int:1   float:0.000000
v0_0 = 0x00000001;
//LABEL               |  LL7: line 258
L7: ;
//GOTO                |     |goto L6;
goto L6;
//LABEL               |  LL4: line 260
L4: ;
//CONST               |     |v0=0x00000002  // int:2   float:0.000000
v0_0 = 0x00000002;
L8: ;
//GOTO                |     |goto L6;
goto L6;
//LABEL               |  LL9: line 383
L9: ;
//LABEL               |  LL1:
L1: ;
}

int
main (void)
{
  printf ("for_func %d \n", for_func());
  printf ("switch_func %d \n", switch_func(3));
  return 0;
}
