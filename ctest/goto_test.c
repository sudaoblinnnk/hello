#include <stdio.h>

typedef int jint;

int gotofunc() {

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

int
main (void)
{
  printf ("Hello, world! %d \n", gotofunc());
  return 0;
}
