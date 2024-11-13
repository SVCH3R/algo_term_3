#include <iostream>
#include <string>
#include <random>

struct Node {
  Node* left;
  Node* right;
  int64_t size;
  int64_t key;
  int64_t priority;
  int64_t sum;

  explicit Node(const int64_t& ckey) : left(nullptr), right(nullptr), size(1), key(ckey), priority(rand()), sum(ckey){};
};

struct Treap {
 private:
  Node* root_;

  Node* Insert(Node* root, Node* node) {
    if (root == nullptr) {
      return node;
    }
    auto p = Split(root, node->key);
    return Merge(Merge(p.first, node), p.second);
  }

  int64_t Size(Node* root) {
    return !root ? 0 : root->size;
  }

  int64_t Sum(Node* root) {
    return !root ? 0 : root->sum;
  }

  void Update(Node* root) {
    if (root == nullptr) {
      return;
    }
    root->sum = root->key + Sum(root->left) + Sum(root->right);
    root->size = Size(root->left) + Size(root->right) + 1;
  }

  Node* Find(Node* root, int64_t key) {
    if (root == nullptr) {
      return nullptr;
    }
    if (root->key == key) {
      return root;
    }
    if (root->key < key) {
      return Find(root->right, key);
    }
    return Find(root->left, key);
  }

  Node* Erase(Node* root, const int64_t& key) {
    if (root == nullptr) {
      return nullptr;
    }
    if (root->key == key) {
      auto res = Merge(root->left, root->right);
      delete root;
      return res;
    }
    if (root->key < key) {
      root->right = Erase(root->right, key);
      Update(root);
      return root;
    }
    root->left = Erase(root->left, key);
    Update(root);
    return root;
  }

  Node* Kth(Node* root, const int64_t& k) {
    if (root == nullptr) {
      return nullptr;
    }
    if (k < 0) {
      return nullptr;
    }
    int64_t leftsize = Size(root->left);
    if (k == leftsize) {
      return root;
    }
    if (leftsize >= k) {
      return Kth(root->left, k);
    }
    return Kth(root->right, k - 1 - leftsize);
  }

  Node* Next(Node*& root, int64_t key) {
    if (root == nullptr) {
      return nullptr;
    }
    auto p = Split(root, key);
    if (!p.second) {
      return nullptr;
    }
    auto lb = p.second;
    while (lb->left) {
      lb = lb->left;
    }
    root = Merge(p.first, p.second);
    return lb;
  }

  Node* Prev(Node*& root, const int64_t& key) {
    if (root == nullptr) {
      return nullptr;
    }
    auto p = Split(root, key);
    if (!p.first) {
      return nullptr;
    }
    auto lb = p.first;
    while (lb->right) {
      lb = lb->right;
    }
    root = Merge(p.first, p.second);
    return lb;
  }

  Node* Merge(Node* t1, Node* t2) {
    if (t1 == nullptr) {
      return t2;
    }
    if (t2 == nullptr) {
      return t1;
    }
    if (t1->priority < t2->priority) {
      t1->right = Merge(t1->right, t2);
      Update(t1);
      return t1;
    }
    t2->left = Merge(t1, t2->left);
    Update(t2);
    return t2;
  }

  std::pair<Node*, Node*> Split(Node*& root, const int64_t& key) {
    if (root == nullptr) {
      return {nullptr, nullptr};
    }
    if (root->key < key) {
      auto t12 = Split(root->right, key);
      auto t1 = t12.first;
      auto t2 = t12.second;
      root->right = t1;
      Update(root);
      return {root, t2};
    }
    auto t12 = Split(root->left, key);
    auto t1 = t12.first;
    auto t2 = t12.second;
    root->left = t2;
    Update(root);
    return {t1, root};
  }
  void Delete(Node* node) {
    if (!node) {
      return;
    }
    Delete(node->left);
    Delete(node->right);
    delete node;
  }

  // int64_t Query(int64_t a, int64_t b, int64_t left, int64_t right) {
  //   if (a >= left && b <= right) {
  //     return Sum(root_);
  //   }
  //   if (b < left || a > right) {
  //     return 0;
  //   }
  //   return Query(a, (a + b) / 2, left, right) + Query((a + b) / 2 + 1, b, left, right);
  // }

 public:
  Treap() : root_(nullptr) {
  }

  Node* Find(const int64_t& key) {
    return Find(root_, key);
  }

  void Insert(Node* node) {
    root_ = Insert(root_, node);
  }

  void Erase(const int64_t& key) {
    root_ = Erase(root_, key);
  }

  Node* Kth(const int64_t& key) {
    return Kth(root_, key);
  }

  Node* Next(const int64_t& key) {
    return Next(root_, key);
  }

  Node* Prev(const int64_t& key) {
    return Prev(root_, key);
  }
  ~Treap() {
    Delete(root_);
  }

  int64_t Query(const int64_t& l, const int64_t& r) {
    auto splitted12 = Split(root_, l);
    auto splitted23 = Split(splitted12.second, r + 1);
    int64_t res = Sum(splitted23.first);
    Merge(splitted12.first, Merge(splitted23.first, splitted23.second));
    return res;
  }
};

int main() {
  Treap ct;
  char cmd = 0;
  int64_t n = 0;
  int64_t l = 0;
  int64_t r = 0;
  int64_t key = 0;
  std::cin >> n;
  while (n--) {
    std::cin >> cmd;
    if (cmd == '+') {
      std::cin >> key;
      if (!ct.Find(key)) {
        auto node = new Node(key);
        ct.Insert(node);
      }
    } else {
      std::cin >> l >> r;
      std::cout << ct.Query(l, r) << '\n';
    }
  }
}