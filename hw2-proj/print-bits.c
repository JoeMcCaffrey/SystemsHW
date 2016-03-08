#include <stdio.h> 


int main() {



unsigned char first = 181 ;

signed char second = -75;

unsigned char b,c,d,e,f,g,h;
unsigned char bb,cc,dd,ee,ff,gg,hh,a;

signed char i,j,k,l,m,n,o,p;
signed char ii,jj,kk,ll,mm,nn,oo,pp; 

a = first >> 7;

b= first << 1 ;
bb = b >> 7;

c = first << 2;
cc= c >> 7 ;


d= first << 3 ;
dd = d >> 7 ;

e = first << 4 ;
ee = e >> 7;

f = first << 5;
ff = f >> 7 ;

g = first << 6 ;
gg = g >> 7;

h = first << 7;
hh = h >> 7 ;

i= second >>7 ;

j= second << 1 ;
jj= j >> 7;

k = second <<2 ;
kk = k >>7 ;

l = second << 3 ;
ll = l >> 7 ;

m = second <<4 ;
mm = m >> 7 ;

n = second << 5; 
nn = n >>7 ;

o = second << 6 ;
oo = o >> 7 ;

p = second << 7 ;
pp = p >> 7 ;


printf("%i%i%i%i%i%i%i%i\n", a, bb, cc,dd,ee,ff,gg,hh) ;

printf("%d%d%d%d%d%d%d%d\n",!!(i),!!(jj),!!(kk),!!(ll),!!(mm),!!(nn),!!(oo),!!(pp));

}
