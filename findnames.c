#include<stdio.h>
#include<string.h>
char line[100];
int y;
char flag = 0;
int stuff =0 ;
void process() {
	asm(".intel_syntax noprefix\n");
	asm("mov ecx, offset line\n");
	asm("mov edx, ecx\n");
	asm("mov cl, [edx]\n");
	asm("xor eax, eax\n");
	asm("jmp A\n");
	asm("A:\n");
	asm("test cl, cl\n");
	asm("jz B\n");
	asm("movsx ecx, cl\n");
	asm("rol eax, 7\n");
	asm("xor eax, ecx\n");
	asm("inc edx\n");
	asm("mov cl, [edx]\n");
	asm("jmp A\n");
	asm("B:\n");


	asm("mov ecx, offset stuff\n");
	asm("mov [ecx], eax\n");
}

int main() {

	FILE *fp = fopen("kernel32names", "r");
	int ch;
	int index = 0;
	while((ch=getc(fp))!=EOF) {
		if(ch == '\n') {
			flag = 0;
			line[index] = '\0';
			index = 0;
			y = 0xA48D6762;
			process();
			
			switch(stuff) {
				case 0xA48D6762: 
				case 0x6E72656B: 
				case 0x32336C65:
				case 0x6C6C642E:
				case 0x6A582465:
				case 0x20088E6A:
				case 0x6C64746E:
				case 0x4C44544E: 
					printf("stuff=%08x\t line=%s\n", stuff, line);
					break;
			}
			stuff = 0;
		}
		else {
			line[index] = ch;
			++index;
		}
	}
}
