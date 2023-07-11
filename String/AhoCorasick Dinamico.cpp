const int MX = 300005, SIG = 26, LMX = 20;
 
struct aho_corasick {
	struct Node {
		Node *sig[SIG], *fail;
		int finish, cnt;
 
		Node () : fail(this), finish(0), cnt(0) {
			for (int i = 0; i < SIG; i++)
				sig[i] = this;
		}
 
		Node (Node *root) : fail(root), finish(0), cnt(0) {
			for (int i = 0; i < SIG; i++)
				sig[i] = root;
		}
	};
 
	Node *root;
 
	aho_corasick() { reset(); }
 
	void reset () {
		root = new Node;
	}
 
	void insert (string &s, int ind) {
		Node *u = root;
 
		for (char c : s) {
			c -= 'a';
 
			if (u->sig[c] == root) {
				u->sig[c] = new Node(root);
				u->sig[c]->finish = -1;
			}
 
			u = u->sig[c];
		}
 
		u->finish = ind;
		u->cnt++;
	}
 
	Node* getFail (Node *u, int c) {
		while (u != root && u->sig[c] == root)
			u = u->fail;
		return u->sig[c];
	}
 
	void build () {
		queue<Node*> q;
		
		for (int i = 0; i < SIG; i++)
			if (root->sig[i] != root)
				q.push(root->sig[i]);
 
		while (q.size()) {
			Node *u = q.front();
			q.pop();
 
			for (int i = 0; i < SIG; i++) {
				Node *v = u->sig[i];
 
				if (v != root) {
					v->fail = getFail(u->fail, i);
					v->cnt += v->fail->cnt;
					q.push(v);
				}
			}
		}
	}
 
	int match (string &t) {
		Node *u = root;
		int res = 0;
 
		for (int i = 0; i < t.size(); i++) {
			char c = t[i] - 'a';
			
			if (u->sig[c] != root)
				u = u->sig[c];
			else
				u = getFail(u->fail, c);
			res += u->cnt;
		}
 
		return res;
	}
};
 
typedef vector<string*> vs;
 
struct dynamic_aho_corasick {
	aho_corasick ac[LMX];
	vs s[LMX];
	int exi;
 
	dynamic_aho_corasick () : exi(0) {}
 
	void insert (string &str) {
		int j = 0;
		while (exi & (1 << j)) j++;
		s[j].push_back(new string(str));
 
		for (int i = 0; i < j; i++) {
			for (string *t : s[i]) s[j].push_back(t);
			s[i].clear();
			ac[i].reset();
		}
 
		for (string *t : s[j])
			ac[j].insert(*t, 1);
		ac[j].build();
 
		exi++;
	}
 
	int match (string &t) {
		int res = 0;
 
		for (int i = 0; i < LMX; i++)
			if (exi & (1 << i))
				res += ac[i].match(t);
 
		return res;
	}
};


Otra implementacion


const int N = 3 * int(1e5) + 9;
struct aho_corasick_static {
  int cnt[N], link[N], psz;
  map<char, int> to[N];
 
  void clear() {
    for(int i = 0; i < psz; i++)
      cnt[i] = 0, link[i] = -1, to[i].clear();
 
    psz = 1;
    link[0] = -1;
    cnt[0] = 0;
  }
 
  aho_corasick_static() {
    psz = N - 2;
    clear();
  }
 
  void add_word(string s) {
    int u = 0;
    for(char c : s) {
      if(!to[u].count(c)) to[u][c] = psz++;
      u = to[u][c];
    }
 
    cnt[u]++;
  }
 
  void push_links() {
    queue<int> Q;
    int u, v, j;
    char c;
 
    Q.push(0);
    link[0] = -1;
 
    while(!Q.empty()) {
      u = Q.front();
      Q.pop();
 
      for(auto it : to[u]) {
        v = it.second;
        c = it.first;
        j = link[u];
 
        while(j != -1 && !to[j].count(c)) j = link[j];
        if(j != -1) link[v] = to[j][c];
        else link[v] = 0;
 
        cnt[v] += cnt[link[v]];
        Q.push(v);
      }
    }
  }
 
  int get_count(string p) {
    int u = 0, ans = 0;
    for(char c : p) {
      while(u != -1 && !to[u].count(c)) u = link[u];
      if(u == -1) u = 0;
      else u = to[u][c];
      ans += cnt[u];
    }
 
    return ans;
  }
};
 
struct aho_corasick {
  vector<string> li[20];
  aho_corasick_static ac[20];
 
  void clear() {
    for(int i = 0; i < 20; i++) {
      li[i].clear();
      ac[i].clear();
    }
  }
 
  aho_corasick() {
    clear();
  }
 
  void add_word(string s) {
    int pos = 0;
    for(int l = 0; l < 20; l++)
      if(li[l].empty()) {
        pos = l;
        break;
      }
 
    li[pos].push_back(s);
    ac[pos].add_word(s);
 
    for(int bef = 0; bef < pos; bef++) {
      ac[bef].clear();
      for(string s2 : li[bef]) {
        li[pos].push_back(s2);
        ac[pos].add_word(s2);
      }
 
      li[bef].clear();
    }
 
    ac[pos].push_links();
  }
  //sum of occurrences of all patterns in this string
  int get_count(string s) {
    int ans = 0;
    for(int l = 0; l < 20; l++)
      ans += ac[l].get_count(s);
 
    return ans;
  }
};