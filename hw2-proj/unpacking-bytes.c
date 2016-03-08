

#include <stdio.h>


int main() {

unsigned int i1 = 1835098984u;

unsigned int i2 = 1768842611u;


char a,bb,cc,dd,ee,ff,gg,hh ;
int b,c,d,e,f,g,h;

a = i1 >>24 ;

b = i1 << 8 ;

bb = b >> 24 ;

c = i1 << 16 ;

cc = c >> 24;

d = i1 << 24;

dd = d >>  24 ;

e = i2 >> 24 ;

f = i2 << 8 ;

ff = f >> 24;

g = i2 << 16;

gg = g >> 24 ;

h = i2 << 24;

hh = h >> 24;
printf("%c%c%c%c%c%c%c%c\n",a,bb,cc,dd,e,ff,gg,hh);
}

