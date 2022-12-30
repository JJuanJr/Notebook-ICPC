bool find_any_solution(int a, int b, int c, int &x, int &y, int &g){
    g = extEuclid(a, b, x, y);
    if(c % g)
        return false;
    x *= (c/g);
    y *= (c/g);
    return true;
}

void find_all_solutions(int a, int b, int c){
    int x, y, g, x0, y0;
    if(!find_any_solution(a, b, c, x, y, g))
        return;
    form(i, -10, 10, 1){
        x0 = x + i*(b/g);
        y0 = y - i*(a/g);
        printf("%d*%d + %d*%d = %d\n", a,x0,b,y0,a*x0+b*y0);
    }
}
