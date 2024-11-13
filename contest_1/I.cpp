#include <iostream>
#include <vector>

struct Node {
  int key;
  int priority;
  Node* parent;
  Node* left;
  Node* right;

  Node(const int& ckey, const int& cpriority)
      : key(ckey), priority(cpriority), parent(nullptr), left(nullptr), right(nullptr) {
  }
};

struct CartesianTree {
  Node* root;
  CartesianTree() = default;
  explicit CartesianTree(Node* node) : root(node) {
  }

  ~CartesianTree() {
    Delete(root);
  }

  void Delete(Node* node) {
    if (!node) {
      return;
    }
    Delete(node->left);
    Delete(node->right);
    delete node;
  }

  void Build(std::vector<std::pair<int, int>> array, const int& n) {
    Node* last = nullptr;
    for (int i = 0; i < n; ++i) {
      int key = array[i].first;
      int priority = array[i].second;
      Node* cur = last;
      while ((cur != nullptr) && (cur->priority >= priority)) {
        cur = cur->parent;
      }
      Node* new_node(new Node(key, priority));
      if (cur == nullptr) {
        new_node->left = root;
        if (root) {
          root->parent = new_node;
        }
        root = new_node;
      } else {
        new_node->left = cur->right;
        if (cur->right) {
          cur->right->parent = new_node;
        }
        cur->right = new_node;
        new_node->parent = cur;
      }
      last = new_node;
    }
  }

  void Inorder(Node* root) {
    if (root != nullptr) {
      Inorder(root->left);
      std::cout << (root->parent ? root->parent->key : 0) << ' ' << (root->left ? root->left->key : 0) << ' '
                << (root->right ? root->right->key : 0) << '\n';
      Inorder(root->right);
    }
  }

  void Inorder() {
    Inorder(root);
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  CartesianTree ct(nullptr);
  int inp1 = 0;
  std::vector<std::pair<int, int>> array(n);
  for (int i = 0; i < n; ++i) {
    array[i].first = i + 1;
    std::cin >> inp1 >> array[i].second;
  }
  ct.Build(array, n);
  std::cout << "YES\n";
  ct.Inorder();
  return 0;
}
