
#include <stdio.h>

int main() {

	float x = 10;
	float y = 13;

	int z = (int) x+y ;

	printf("x = %f\n", x );
	printf("y = %f\n", y);

	printf("size of signed float in bytes is %d.\n", sizeof(x));
	printf("size of signed float in bits is %d.\n", sizeof(x)*8);
	printf("%f + %f = %f.\n",x,y,x+y);
	printf("%f + %f = %d.\n",x,y,z);
	
}
	
