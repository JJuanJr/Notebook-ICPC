int extEuclid(int a, int b, int &x, int &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    int xi, yi;
    int g = extEuclid(b, a%b, xi, yi);
    x = yi;
    y = xi-yi*(a/b);
    return g;
}
