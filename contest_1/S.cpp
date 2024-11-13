#include <iostream>
#include <string>
#include <random>

struct Node {
  Node* left;
  Node* right;
  int64_t size;
  int64_t value;
  int64_t priority;
  int64_t min;
  bool promise;

  explicit Node(const int64_t& cval)
      : left(nullptr), right(nullptr), size(1), value(cval), priority(rand()), min(cval), promise(false){};
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

  void FixNode(Node* root) {
    if (root == nullptr) {
      return;
    }
    root->min = std::min(std::min(root->value, Min(root->left)), Min(root->right));
    root->size = Size(root->left) + Size(root->right) + 1;
  }

  void Push(Node* root) {
    if (!root) {
      return;
    }
    root->promise = !root->promise;
    std::swap(root->left, root->right);
    root->left->promise = !root->left->promise;
    root->right->promise = !root->right->promise;
  }

  Node* Merge(Node* t1, Node* t2) {
    if (t1 == nullptr) {
      return t2;
    }
    if (t2 == nullptr) {
      return t1;
    }
    if (t1->priority < t2->priority) {
      Push(t1);
      t1->right = Merge(t1->right, t2);
      FixNode(t1);
      return t1;
    }
    Push(t2);
    t2->left = Merge(t1, t2->left);
    FixNode(t2);
    return t2;
  }

  std::pair<Node*, Node*> Split(Node* t, const int64_t& x0) {
    if (!t) {
      return {nullptr, nullptr};
    }

    Push(t);
    if (t->value < x0) {
      auto [a, b] = Split(t->right, x0);
      t->right = a;
      FixNode(t);
      return {t, b};
    }
    auto [a, b] = Split(t->left, x0);
    t->left = b;
    FixNode(t);
    return {a, t};
  }

  void Delete(Node* node) {
    if (!node) {
      return;
    }
    Delete(node->left);
    Delete(node->right);
    delete node;
  }

  void Reverse(Node* t, const int& l, const int& r) {
    auto [t1, t2] = Split(root_, l);
    auto [t3, t4] = Split(t2, r);
    t3->promise = !t3->promise;
    Merge(Merge(t1, t3), t4);
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

  void Reverse(const int& l, const int& r) {
  }
};

int main() {
  Treap ct;
  int64_t n = 0;
  int64_t m = 0;

  int64_t value = 0;
  std::cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    std::cin >> value;
    auto node = new Node(value);
    ct.Insert(node, i);
  }
  int cmd, l, r;
  while (m--) {
    std::cin >> cmd >> l >> r;
    if (cmd == 1) {
      ct.Reverse(l, r);
    } else {
      ct.Query(l, r);
    }
  }
}