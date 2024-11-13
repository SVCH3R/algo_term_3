#include <iostream>
#include <string>
#include <random>

struct Node {
  Node* left;
  Node* right;
  int64_t size;
  int64_t key;
  int64_t priority;
  int64_t min;

  explicit Node(const int64_t& ckey) : left(nullptr), right(nullptr), size(1), key(ckey), priority(rand()), min(ckey){};
};

struct Treap {
 private:
  Node* root_;
  Node* Insert(Node* root, Node* node, const int64_t& size) {
    if (root == nullptr) {
      return node;
    }
    auto p = Split(root, size);
    return Merge(p.first, Merge(node, p.second));
  }
  int64_t Size(Node* root) {
    return !root ? 0 : root->size;
  }

  int64_t Min(Node* root) {
    return !root ? INT64_MAX : root->min;
  }

  void Update(Node* root) {
    if (root == nullptr) {
      return;
    }
    root->min = std::min(std::min(root->key, Min(root->left)), Min(root->right));
    root->size = Size(root->left) + Size(root->right) + 1;
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

  std::pair<Node*, Node*> Split(Node* root, const int64_t& size) {
    if (!root) {
      return {nullptr, nullptr};
    }
    auto leftsize = Size(root->left);
    if (size <= leftsize) {
      auto splitted = Split(root->left, size);
      root->left = splitted.second;
      Update(root);
      return {splitted.first, root};
    }
    auto splitted = Split(root->right, size - 1 - leftsize);
    root->right = splitted.first;
    Update(root);
    return {root, splitted.second};
  }

  void Delete(Node* node) {
    if (!node) {
      return;
    }
    Delete(node->left);
    Delete(node->right);
    delete node;
  }

 public:
  Treap() : root_(nullptr) {
  }
  void Insert(Node* node, const int64_t& size) {
    root_ = Insert(root_, node, size);
  }
  ~Treap() {
    Delete(root_);
  }
  int64_t Query(const int64_t& l, const int64_t& r) {
    auto s1 = Split(root_, r);
    auto s2 = Split(s1.first, l - 1);
    int64_t res = Min(s2.second);
    root_ = Merge(Merge(s2.first, s2.second), s1.second);
    return res;
  }
};

int main() {
  Treap ct;
  char cmd = 0;
  int64_t n = 0;
  int64_t l = 0;
  int64_t r = 0;
  int64_t x = 0;
  int64_t i = 0;
  std::cin >> n;
  while (n--) {
    std::cin >> cmd;
    if (cmd == '+') {
      std::cin >> i >> x;
      auto node = new Node(x);
      ct.Insert(node, i);
    } else {
      std::cin >> l >> r;
      std::cout << ct.Query(l, r) << '\n';
    }
  }
}