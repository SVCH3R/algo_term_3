#include <iostream>
#include <vector>
#include <random>
#include <string>

struct Node {
  Node* left;
  Node* right;
  int32_t size;
  int32_t min;
  int32_t value;
  int32_t priority;
  bool reverse;

  explicit Node(const int32_t& cval)
      : left(nullptr), right(nullptr), size(1), min(cval), value(cval), priority(rand() / 1000000){};

  Node() = default;
  ~Node() = default;
};

class Treap {
 private:
  Node* root_;

  void FixNode(Node* node) {
    if (node != nullptr) {
      node->size = 1 + Size(node->left) + Size(node->right);
      node->min = std::min(std::min(node->value, Min(node->left)), Min(node->right));
      if (node->reverse) {
        node->reverse = false;
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
        if (node->left != nullptr) {
          node->left->reverse = !node->left->reverse;
        }
        if (node->right != nullptr) {
          node->right->reverse = !node->right->reverse;
        }
      }
    }
  }

  int32_t Size(Node* node) {
    return node ? node->size : 0;
  }

  int32_t Min(Node* node) {
    return node ? node->min : INT32_MAX;
  }

  std::pair<Node*, Node*> Split(Node* root, const int32_t& k) {
    if (root == nullptr) {
      return std::make_pair(nullptr, nullptr);
    }
    FixNode(root);
    if (Size(root->left) < k) {
      auto [t1, t2] = Split(root->right, k - Size(root->left) - 1);
      root->right = t1;
      FixNode(root);
      return std::make_pair(root, t2);
    }
    auto [t1, t2] = Split(root->left, k);
    root->left = t2;
    FixNode(root);
    return std::make_pair(t1, root);
  }

  Node* Merge(Node* t1, Node* t2) {
    if (t1 == nullptr) {
      return t2;
    }
    if (t2 == nullptr) {
      return t1;
    }
    FixNode(t1);
    FixNode(t2);
    if (t1->priority < t2->priority) {
      t2->left = Merge(t1, t2->left);
      FixNode(t2);
      return t2;
    }
    t1->right = Merge(t1->right, t2);

    FixNode(t1);
    return t1;
  }

  void Clear(Node* node) {
    if (node != nullptr) {
      if (node->left) {
        Clear(node->left);
      }
      if (node->right) {
        Clear(node->right);
      }
    }
    delete node;
  }

 public:
  Treap() : root_(nullptr) {
  }

  void Insert(const int32_t& i, const int32_t& value) {
    auto [t1, t2] = Split(root_, i);
    Node* node = new Node(value);
    root_ = Merge(Merge(t1, node), t2);
  }

  int32_t Query(const int32_t& l, const int32_t& r) {
    auto [t1, t2] = Split(root_, l - 1);
    auto [t3, t4] = Split(t2, r - l + 1);
    FixNode(t3);
    int32_t res = Min(t3);
    root_ = Merge(Merge(t1, t3), t4);
    return res;
  }

  void Reverse(const int32_t& l, const int32_t& r) {
    auto [t1, t2] = Split(root_, l - 1);
    auto [t3, t4] = Split(t2, r - l + 1);
    t3->reverse = !t3->reverse;
    FixNode(t3);
    root_ = Merge(Merge(t1, t3), t4);
  }

  ~Treap() {
    Clear(root_);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  srand(time(nullptr));

  Treap ct;
  int32_t n = 0;
  int32_t m = 0;
  int32_t cmd = 0;
  int32_t value = 0;
  int32_t l = 0;
  int32_t r = 0;

  std::cin >> n >> m;

  for (int32_t i = 0; i < n; ++i) {
    std::cin >> value;
    ct.Insert(i, value);
  }

  while (m--) {
    std::cin >> cmd >> l >> r;
    if (cmd == 1) {
      ct.Reverse(l, r);
    } else {
      std::cout << ct.Query(l, r) << '\n';
    }
  }
}
