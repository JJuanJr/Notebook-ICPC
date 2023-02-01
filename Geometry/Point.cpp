typedef int T;
struct pt{
    T x, y;
    pt(): x(0), y(0) {}
    pt(T _x, T _y): x(_x), y(_y) {}
    pt operator+(pt p) {return {x+p.x, y+p.y};}
    pt operator-(pt p) {return {x-p.x, y-p.y};}
    pt operator*(T d) {return {x*d, y*d};}
    pt operator/(T d) {return {x/d, y/d};}
    bool operator==(pt b) {return x == b.x && y == b.y;}
    bool operator!=(pt b) {return x != b.x || y != b.y;}
    bool operator<(pt b) {return x == b.x? y < b.y : x < b.x;}
};
const double M_PI = acos(-1);
double DEG_TO_RAD(double n){ return n*M_PI/180.0; }
double RAD_TO_DEG(double n){ return n*180.0/M_PI; }
T sq(pt p) {return p.x*p.x + p.y*p.y;}
double abs(pt p) {return sqrt(sq(p));}
//Transformaciones
pt translate(pt v, pt p) {return p+v;}
pt scale(pt c, double factor, pt p) { return c + (p-c)*factor; }
pt rot(pt p, double ang) { return {p.x*cos(ang) - p.y*sin(ang), p.x*sin(ang) + p.y*cos(ang)}; }
pt perp(pt p) {return {-p.y, p.x};}
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) { return fp + (r-p) * (fq-fp) / (q-p); }
T dot(pt v, pt w) {return v.x*w.x + v.y*w.y;}
bool isPerp(pt v, pt w) {return dot(v,w) == 0;}
double angle(pt v, pt w) {
    double cosTheta = dot(v,w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}
T cross(pt v, pt w) {return v.x*w.y - v.y*w.x;}
T orient(pt a, pt b, pt c) {return cross(b-a,c-a);} // colinear == 0, left > 0, right < 0
bool inAngle(pt a, pt b, pt c, pt p) { //Si un pt se encuentra dentro del angulo ABC
    assert(orient(a,b,c) != 0);
    if (orient(a,b,c) < 0) swap(b,c);
    return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}
double orientedAngle(pt a, pt b, pt c) {
    if (orient(a,b,c) >= 0) return angle(b-a, c-a);
    return 2*M_PI - angle(b-a, c-a);
}
bool isConvex(vector<pt> p) {
    bool hasPos=false, hasNeg=false;
    for (int i=0, n=p.size(); i<n; i++) {
        int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}
//polar sort
pt v = {/* whatever you want except 0,0 */};
bool half(pt p) { // true if in blue half
    assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
    //inclinar la zona azul de orden
    return cross(v,p) < 0 || (cross(v,p) == 0 && dot(v,p) < 0);
}
pt o = {1,1};
bool polarSort(pt v, pt w) {
    return make_tuple(half(v), 0) < make_tuple(half(w), cross(v,w));
    //Desempate por magnitud
    return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v,w), sq(w));
    //Ordenar alrededor de un punto diferente a (0,0)
    return make_tuple(half(v-o), 0) < make_tuple(half(w-o), cross(v-o, w-o));
}
//Complex stl 
typedef double T; // long long abs and arg cast to int
typedef complex<T> pt; // abs(pt p), arg(pt p)
#define x real()
#define y imag()
T dot(pt v, pt w) {return (conj(v)*w).x;} //Complex stl
T cross(pt v, pt w) {return (conj(v)*w).y;} //Complex stl
pt rot(pt p, double ang) {return p * polar(1.0, ang);} //Complex stl