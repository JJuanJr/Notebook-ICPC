/* Expandir pila de memoria C++ 11 */
#include <sys/resource.h>
rlimit rl;
getrlimit(RLIMIT_STACK, &rl);
rl.rlim_cur=1024L*1024L*256L;//256mb
setrlimit(RLIMIT_STACK, &rl);

/* iterar mascara de bits */
for(int i=n; i; i^=i&-i)

/* funciones sobre bits */
x = __builtin_popcount(n);//bits encendidos en n
x = __builtin_ctz(n);//ceros a la derecha de n
x = __builtin_clz(n);//ceros a la izquierda de n
x = __builtin_ffs(n);//primera posicion en 1
x = __builtin_ctzll((ll) n);//para 64b agregars ll al nombre
x = (n&(-n));//least significant bit en 1

/* resultado de & en el rango [l, r] */
ll rangeAND(ll l, ll r) {
  ll ans = 0;
  rforn (i, 63) {
    if ((l & (1ll << i)) != (r & (1ll << i))) break;
    ans |= (l & (1ll << i));
  }
  return ans;
}

/* Expresiones Regulares */
string expresion = "(take|love|know|like)s*";
string cadena = "likes knows";
regex reg(expresion);
bool match = regex_match(cadena,reg);//Existe?

smatch matches;
while(regex_search(cadena, matches, reg)){
    cadena = matches.suffix();//Recorrer los match
    cout << cadena << endl;
}

/*Rotar una matriz 90 grados*/
int n;
vii rotar(vii &a) {
	vii v(n, vi(n));
	forn(i,n)
    forn(j, n)
      v[i][j] = a[n - 1 - j][i];
	return v;
}