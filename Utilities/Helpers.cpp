/* Expandir pila de memoria C++ 11 */
#include <sys/resource.h>
rlimit rl;
getrlimit(RLIMIT_STACK, &rl);
rl.rlim_cur=1024L*1024L*256L;//256mb
setrlimit(RLIMIT_STACK, &rl);

/* iterar mascara de bits */
for(int i=n; i; i=(i-1)&n) // Decreciente
for(int i=0; i=i-n&n; ) // creciente

/* funciones sobre bits */
x = __builtin_popcount(n);//bits encendidos en n
x = __builtin_ctz(n);//ceros a la derecha de n
x = __builtin_clz(n);//ceros a la izquierda de n
x = __builtin_ffs(n);//primera posicion en 1
x = __builtin_ctzll((ll) n);//para 64b agregars ll al nombre
x = (n&(-n));//least significant bit en 1

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
