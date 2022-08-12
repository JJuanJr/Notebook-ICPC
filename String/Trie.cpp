struct Node {
  int cont;
  Node* child[26];
};

struct Trie {
  Node* root;

  Trie() {
    root = new Node();
  }

  void insert(const string &s) {
    Node* curr = root;
    for (int i = 0; i < sz(s); ++i) {
      if (curr->child[s[i] - 'a'] == NULL) {
        curr->child[s[i] - 'a'] = new Node();
      }
      curr->child[s[i] - 'a']->cont++;
      curr = curr->child[s[i] - 'a'];
    }
  }

  pair<int, int> query(const string &s) {
    Node* curr = root;
    for (int i = 0; i < sz(s); ++i) {
      if (curr->child[s[i] - 'a'] == NULL) {
        return make_pair(i, curr->cont);
      }
      curr = curr->child[s[i] - 'a'];
    }
    return make_pair(sz(s), curr->cont);
  }
};
