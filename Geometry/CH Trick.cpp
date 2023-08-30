typedef ll tc;
struct Line{tc m,h;};
struct CHT {
	vector<Line> c;
	int pos=0;
	tc in(Line a, Line b){
		tc x=b.h-a.h,y=a.m-b.m;
		return x/y+(x%y?!((x>0)^(y>0)):0);
	}
	void add(tc m, tc h){
		Line l=(Line){m,h};
		if(c.size()&&m==c.back().m){
			l.h=min(h,c.back().h);c.pop_back();if(pos)pos--;
		}
		while(c.size()>1&&in(c.back(),l)<=in(c[c.size()-2],c.back())){
			c.pop_back();if(pos)pos--;
		}
		c.pb(l);
	}
	inline bool fbin(tc x, int m){return in(c[m],c[m+1])>x;}
	
	tc eval(tc x){
		while(pos>0&&fbin(x,pos-1))pos--;
		while(pos<c.size()-1&&!fbin(x,pos))pos++;
		return c[pos].m*x+c[pos].h;
	}
};


//Ejemplo de uso: codeforces.com/gym/104252/problem/B

#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

typedef ll tc;
struct Line{tc m,h;};
struct CHT {
	vector<Line> c;
	int pos=0;
	tc in(Line a, Line b){
		tc x=b.h-a.h,y=a.m-b.m;
		return x/y+(x%y?!((x>0)^(y>0)):0);
	}
	void add(tc m, tc h){
		Line l=(Line){m,h};
		if(c.size()&&m==c.back().m){
			l.h=min(h,c.back().h);c.pop_back();if(pos)pos--;
		}
		while(c.size()>1&&in(c.back(),l)<=in(c[c.size()-2],c.back())){
			c.pop_back();if(pos)pos--;
		}
		c.pb(l);
	}
	inline bool fbin(tc x, int m){return in(c[m],c[m+1])>x;}
	
	tc eval(tc x){
		while(pos>0&&fbin(x,pos-1))pos--;
		while(pos<c.size()-1&&!fbin(x,pos))pos++;
		return c[pos].m*x+c[pos].h;
	}
};

struct STree{
	vector<CHT> st;int n;
	STree(int n): st(4*n+5), n(n) {}
	void upd(int k, int s, int e, int p, ii now){
		st[k].add(-now.fst,-now.snd);
		if(s+1==e)return;
		int m=(s+e)/2;
		if(p<m) upd(2*k,s,m,p,now);
		else upd(2*k+1,m,e,p,now);
	}
	int get(int k, int s, int e, ii val){
		if(val.snd >= -st[k].eval(val.fst)) return -1;
		if(s+1==e) return s;
		int m=(s+e)/2;
		int ans=get(2*k,s,m,val);
		if(ans<0) ans=get(2*k+1,m,e,val);
		return ans;
	}
	
	void upd(int p, ii now){upd(1,0,n,p,now);}
	int get(ii val){return get(1,0,n,val);}
};

int main(){FIN;
	int n; cin>>n;
	vector<pair<ii,int>> a(n);
	fore(i,0,n) cin>>a[i].fst.fst>>a[i].fst.snd,a[i].snd=i;
	
	int q; cin>>q;
	vector<pair<ii,int>> qs(q);
	fore(i,0,q) cin>>qs[i].fst.fst>>qs[i].fst.snd,qs[i].snd=i;
	
	sort(ALL(a)); sort(ALL(qs));
	
	STree st(q);
	fore(i,0,q) st.upd(qs[i].snd,qs[i].fst);
	
	vector<vector<int>> ans(q);
	
	fore(i,0,n){
		int now=st.get(a[i].fst);
		if(now!=-1) ans[now].pb(a[i].snd);
	}
	
	fore(i,0,q){
		int k=SZ(ans[i]);
		sort(ALL(ans[i]));
		ans[i].insert(ans[i].begin(),k-1);
		fore(j,0,SZ(ans[i]))cout<<ans[i][j]+1<<" \n"[j+1==SZ(ans[i])];
	}
}