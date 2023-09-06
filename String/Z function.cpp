Dada una string s, devuelve un vector Z donde Z[i] representa el prefijo
de mayor longitud  de s, que tambien es prefijo del sufijo de s que inicia
en i.
         01234567
Ejemplo: aabzaaba "aab" es un prefijo de s y "aaba" es un sufijo de s, Z[4] = 3.

Otra definicion: Dado un string s retorna un vector z donde z[i] es igual al mayor
numero de caracteres desde s[i] que coinciden con los caracteres desde s[0]

Complejidad: O(|n|)
vector<int> z_function (string &s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, x = 0, y = 0; i < n; i++) {
        z[i] = max(0, min(z[i-x], y-i+1));
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            x = i, y = i+z[i], z[i]++;
        }
    }
    return z;
}