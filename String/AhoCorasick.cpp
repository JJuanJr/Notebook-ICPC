Construye un arbol con patrones string, sirve para responder consultas
del tipo dado n patrones contar la cantidad de ocurrencias en un texto T.

const int M = 26;
struct node{
	vector<int> child;
	int p = -1;
	char c = 0;
	int suffixLink = -1, endLink = -1;
	int id = -1;
 
	node(int p = -1, char c = 0) : p(p), c(c){
		child.resize(M, -1);
	}
};
 
struct AhoCorasick{
	vector<node> t;
	vector<int> lenghts;
	int wordCount = 0;
 
	AhoCorasick(){
		t.emplace_back();
	}
 
	void add(const string & s){
		int u = 0;
		for(char c : s){
			if(t[u].child[c-'a'] == -1){
				t[u].child[c-'a'] = t.size();
				t.emplace_back(u, c);
			}
			u = t[u].child[c-'a'];
		}
		t[u].id = wordCount++;
		lenghts.push_back(s.size());
	}
 
	void link(int u){
		if(u == 0){
			t[u].suffixLink = 0;
			t[u].endLink = 0;
			return;
		}
		if(t[u].p == 0){
			t[u].suffixLink = 0;
			if(t[u].id != -1) t[u].endLink = u;
			else t[u].endLink = t[t[u].suffixLink].endLink;
			return;
		}
		int v = t[t[u].p].suffixLink;
		char c = t[u].c;
		while(true){
			if(t[v].child[c-'a'] != -1){
				t[u].suffixLink = t[v].child[c-'a'];
				break;
			}
			if(v == 0){
				t[u].suffixLink = 0;
				break;
			}
			v = t[v].suffixLink;
		}
		if(t[u].id != -1) t[u].endLink = u;
		else t[u].endLink = t[t[u].suffixLink].endLink;
	}
 
	void build(){
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()){
			int u = Q.front(); Q.pop();
			link(u);
			for(int v = 0; v < M; ++v)
				if(t[u].child[v] != -1)
					Q.push(t[u].child[v]);
		}
	}
 
	int match(const string & text){
		int u = 0;
		int ans = 0;
		for(int j = 0; j < text.size(); ++j){
			int i = text[j] - 'a';
			while(true){
				if(t[u].child[i] != -1){
					u = t[u].child[i];
					break;
				}
				if(u == 0) break;
				u = t[u].suffixLink;
			}
			int v = u;
			while(true){
				v = t[v].endLink;
				if(v == 0) break;
				++ans;
				int idx = j + 1 - lenghts[t[v].id];
				// cout << "Found word #" << t[v].id << " at position " << idx << "\n";
				v = t[v].suffixLink;
			}
		}
		return ans;
	}
};

Implementacion de UFPS

El trie (o prefix tree) guarda un diccionario de strings como un arbol enraizado.
Aho corasick permite encontrar las ocurrencias de todos los strings del trie en un string s.

const int alpha = 26; //cantidad de letras del lenguaje
const char L = 'a'; //primera letra del lenguaje

struct node {
    int next[alpha], end;
    //int link, exit, cnt; //para aho corasick
    int& operator[](int i) { return next[i]; }
};

vector<node> trie = {node()};

void add_str(string &s, int id = 1) {
    int u = 0;
    for (auto ch : s) {
        int c = ch-L;
        if (!trie[u][c]) {
            trie[u][c] = trie.size();
            trie.push_back(node());
        }
        u = trie[u][c];
    }
    trie[u].end = id; //con id > 0
    //trie[u].cnt++; //para aho corasick
}

// aho corasick
void build_ac() {
    queue<int> q; q.push(0);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int c = 0; c < alpha; ++c) {
            int v = trie[u][c];
            if (!v) trie[u][c] = trie[trie[u].link][c];
            else q.push(v);
            if (!u || !v) continue;
            trie[v].link = trie[trie[u].link][c];
			trie[v].exit = trie[trie[v].link].end ? trie[v].link : trie[trie[v].link].exit;
            trie[v].cnt += trie[trie[v].link].cnt;
        }
    }
}

vector<int> cnt; //cantidad de ocurrencias en s para cada patron

void run_ac(string &s) {
    int u = 0, sz = s.size();
    for (int i = 0; i < sz; ++i) {
        int c = s[i]-L;
        while (u && !trie[u][c]) u = trie[u].link;
        u = trie[u][c];
        int x = u;
        while (x) {
            int id = trie[x].end;
            if (id) cnt[id-1]++;
            x = trie[x].exit;
        }
    }
}
