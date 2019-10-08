#define EMIT(a) __asm __emit (a)
#define EM(a) __asm __emit (a)

#include<stdio.h>
#define X64_Start_with_CS(_cs) \
	{ \
		EMIT(0x6A) EMIT(_cs)                         /*  push   _cs             */ \
		EMIT(0xE8) EMIT(0) EMIT(0) EMIT(0) EMIT(0)   /*  call   $+5             */ \
		EMIT(0x83) EMIT(4) EMIT(0x24) EMIT(5)        /*  add    dword [esp], 5  */ \
		EMIT(0xCB)                                   /*  retf                   */ \
	}

#define X64_End_with_CS(_cs) \
	{ \
		EMIT(0xE8) EMIT(0) EMIT(0) EMIT(0) EMIT(0)                                 /*  call   $+5                   */ \
		EMIT(0xC7) EMIT(0x44) EMIT(0x24) EMIT(4) EMIT(_cs) EMIT(0) EMIT(0) EMIT(0) /*  mov    dword [rsp + 4], _cs  */ \
		EMIT(0x83) EMIT(4) EMIT(0x24) EMIT(0xD)                                    /*  add    dword [rsp], 0xD      */ \
		EMIT(0xCB)                                                                 /*  retf                         */ \
	}


#define X64_Start() X64_Start_with_CS(0x33)
#define X64_End() X64_End_with_CS(0x23)

#define __break() asm("int3")

int main(void)
{
	printf("Start\n");
	X64_Start();
	EM(0x48) EM(0x8D) EM(0x05) EM(0xF9) EM(0xFF) EM(0xFF) EM(0xFF)// lea rax, [$] ; rip-relative
	X64_End();
}
