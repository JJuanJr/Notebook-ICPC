
    Dado N puntos en el plano cartesiano, decir la cantidad
    maxima de puntos que cubre un circulo de radio R
    Complejidad: O(N^2 * log N)


typedef double T;
//En caso de TLE, cambiar la complex por la struct pt.
typedef complex<T> pt; 
const int MAXN = 500; //Maximo numero de puntos
bool cmp(pair<T, bool> angAlpha, pair<T, double> angBeta){
  return angAlpha.ff == angBeta.ff ? angAlpha.ss : angAlpha.ff < angBeta.ff;
}
struct maxInsidePtCircle{
  vector<pt> p;
  int n;
  T dist[MAXN][MAXN];
  maxInsidePtCircle() {}
  maxInsidePtCircle(vector<pt> &pts, int _n): p(pts), n(_n) {}
  void build(){ //precalcular distancias entre los puntos
    for (int i=0; i<n-1; i++)
      for (int j=i+1; j<n; j++)
        dist[i][j] = dist[j][i] = abs(p[i]-p[j]); //sqrt((x1 - x2)^2 + (y1 - y2)^2)
  }
  int getPtsInside(int i, T r){
    vector<pair<T, bool>> angles;
    forn(j, n){
      if(i != j && dist[i][j] <= 2 * r){
        T A = arg(p[j] - p[i]); // arctan -> atan2
        T B = acos(dist[i][j] / (2 * r));
        T alpha = A - B;
        T beta = A + B;
        angles.pb({alpha, 1});
        angles.pb({beta, 0});
      }
    }
    sort(all(angles), cmp);
    int cnt = 1, ans = 1;
    forn(i, sz(angles)){
      if(angles[i].ss) cnt++;
      else cnt--;
      ans = max(ans, cnt);
    }
    return ans;
  }
  int maxPoints(T radio){
    int ans = 0;
    forn(i, n)
      ans = max(ans, getPtsInside(i, radio));
    return ans;
  }
};