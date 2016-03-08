#include <stdio.h>

int main() {
 	char c = 'C';
	char a = 65;
	char f = 'F';
	char e = 'E';
	char b = 'B';
	
	printf("c = %c\n", c );
	printf("a = %c\n", a );
	printf("%c%c%c%c%c%c%c%c\n", c,a,f,e,b,a,b,e);
	printf("number of bytes: %d.\n",sizeof(c)+sizeof(a)+sizeof(f)+sizeof(e)+sizeof(b)+sizeof(a)+sizeof(b)+sizeof(e));
}

