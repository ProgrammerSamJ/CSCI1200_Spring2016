#include <vector>
#include <iostream>
#include <string>
using namespace std;
void complete_squares(unsigned int n,unsigned int a[],unsigned int b[]){
	unsigned int *p;
	for ( p=a; p<a+n; ++p ) {
		*p = (p-a)*(p-a);
		*b = *p;
		cout << *b << endl;
	}	
}		
int main () {
	unsigned int m = 10;
	unsigned int c[m]; unsigned int d[m];
	complete_squares(m,&c[m],&d[m]);

	unsigned int n = 5;
	unsigned int e[n]; unsigned int f[n];
	complete_squares(n,&e[n],&f[n]);

	unsigned int o = 15;
	unsigned int g[o]; unsigned int h[o];
	complete_squares(o,&g[o],&h[o]);
}