/*
Tecnica: Implementar convex hull y iterar sobre el ch.
*/
double distancia(vector<pt> pts){
    vector<pt> ch = convexhull(pts);
    T best = 0;
    for(int i = 0, j = 1, len = ch.size() ; i < len ; i++){
        while(sq(ch[j] - ch[i]) > sq(ch[j] - ch[(i+1)%len])){
            best = max(best, sq(ch[j]-ch[i]));
            j = (j+1)%len;
        }
    }
    return sqrtl(best);
}