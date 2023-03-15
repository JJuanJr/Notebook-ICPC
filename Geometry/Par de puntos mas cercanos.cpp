#include <bits/stdc++.h>
#define forr(i,n) for(int i = 0; i < n; ++i)
#define forab(i,a,b) for(int i = a; i < b; ++i)
#define pb(x) push_back(x)

using namespace std;

struct punto{
    double x, y;
    int id;

    punto(){ x = y = id = 0; }
    punto(double _x, double _y){
        x = _x;  y = _y;  id = 0;
    }
};

bool cmp_x(const punto & a, const punto & b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool cmp_y(const punto & a, const punto & b) {
    return a.y < b.y;
}

vector<punto> a, t;
double mindist;
pair<int, int> best_pair;

void upd_ans(const punto & a, const punto & b) {
    double dist = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
    if (dist < mindist) {
        mindist = dist;
        best_pair = {a.id, b.id};
    }
}

void rec(int l, int r) {
    if (r - l <= 3) {
        for (int i = l; i < r; ++i)
        for (int j = i + 1; j < r; ++j)
            upd_ans(a[i], a[j]);
        sort(a.begin() + l, a.begin() + r, cmp_y);
        return;
    }

    int m = (l + r) >> 1, midx = a[m].x;
    rec(l, m);  rec(m, r);

    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, t.begin(), cmp_y);
    copy(t.begin(), t.begin() + r - l, a.begin() + l);
    int tsz = 0;
    for (int i = l; i < r; ++i) {
        if (abs(a[i].x - midx) < mindist) {
            for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < mindist; --j)
                upd_ans(a[i], t[j]);
            t[tsz++] = a[i];
        }
    }
}

double solve(){
    sort(a.begin(), a.end(), cmp_x);
    t.resize(a.size());
    mindist = 1E20;
    rec(0, a.size());
    return mindist;
}

int main(){
    int n, x, y;
    while(scanf("%d", &n) != EOF){
        a.clear();
        forr(i, n){
            scanf("%d %d", &x, &y);
            a.push_back(punto(x, y));
        }
        cout << solve() << endl;
    }

    return 0;
}

