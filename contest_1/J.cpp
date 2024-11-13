#include <iostream>
#include <string>
#include <random>

struct Node {
  Node* left;
  Node* right;
  int size;
  int key;
  int priority;

  explicit Node(const int& ckey) : left(nullptr), right(nullptr), size(1), key(ckey), priority(rand()){};
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

  int Size(Node* root) {
    return root ? 0 : root->size;
  }

  void UpdateSize(Node* root) {
    if (root == nullptr) {
      return;
    }
    root->size = Size(root->left) + Size(root->right) + 1;
  }

  Node* Find(Node* root, int key) {
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

  Node* Erase(Node* root, const int& key) {
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
      UpdateSize(root);
      return root;
    }
    root->left = Erase(root->left, key);
    UpdateSize(root);
    return root;
  }

  Node* Kth(Node* root, const int& k) {
    if (root == nullptr) {
      return nullptr;
    }
    if (k < 0) {
      return nullptr;
    }
    int leftsize = Size(root->left);
    if (k == leftsize) {
      return root;
    }
    if (leftsize >= k) {
      return Kth(root->left, k);
    }
    return Kth(root->right, k - 1 - leftsize);
  }

  Node* Next(Node*& root, int key) {
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

  Node* Prev(Node*& root, const int& key) {
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
      UpdateSize(t1);
      return t1;
    }
    t2->left = Merge(t1, t2->left);
    UpdateSize(t2);
    return t2;
  }

  std::pair<Node*, Node*> Split(Node*& root, const int& key) {
    if (root == nullptr) {
      return {nullptr, nullptr};
    }
    if (root->key < key) {
      auto t12 = Split(root->right, key);
      auto t1 = t12.first;
      auto t2 = t12.second;
      root->right = t1;
      UpdateSize(root);
      return {root, t2};
    }
    auto t12 = Split(root->left, key);
    auto t1 = t12.first;
    auto t2 = t12.second;
    root->left = t2;
    UpdateSize(root);
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

 public:
  Treap() : root_(nullptr) {
  }

  Node* Find(const int& key) {
    return Find(root_, key);
  }

  void Insert(Node* node) {
    root_ = Insert(root_, node);
  }

  void Erase(const int& key) {
    root_ = Erase(root_, key);
  }

  Node* Kth(const int& key) {
    return Kth(root_, key);
  }

  Node* Next(const int& key) {
    return Next(root_, key);
  }

  Node* Prev(const int& key) {
    return Prev(root_, key);
  }
  ~Treap() {
    Delete(root_);
  }
};

int main() {
  Treap ct;
  std::string cmd;

  int key = 0;

  while (std::cin >> cmd >> key) {

    if (cmd == "insert") {
      if (!ct.Find(key)) {
        auto node = new Node(key);
        ct.Insert(node);
      }
    }
    if (cmd == "delete") {
      if (ct.Find(key)) {
        ct.Erase(key);
      }
    }
    if (cmd == "exists") {
      auto res = ct.Find(key);
      std::cout << (res ? "true\n" : "false\n");
    }
    if (cmd == "next") {
      auto res = ct.Next(key);
      if (res) {
        std::cout << res->key << '\n';
      } else {
        std::cout << "none\n";
      }
    }

    if (cmd == "prev") {
      auto res = ct.Prev(key);
      if (res) {
        std::cout << res->key << '\n';
      } else {
        std::cout << "none\n";
      }
    }

    if (cmd == "kth") {
      auto res = ct.Kth(key);
      if (res) {
        std::cout << res->key << '\n';
      } else {
        std::cout << "none\n";
      }
    }
  }
}