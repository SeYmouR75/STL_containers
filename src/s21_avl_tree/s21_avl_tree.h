#ifndef S21_AVL_TREE
#define S21_AVL_TREE

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace s21 {
template <typename K, typename V>
class Tree {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  Tree();

  explicit Tree(const value_type &elem);
  Tree(std::initializer_list<value_type> const &items);
  Tree(const Tree &other);
  Tree(Tree &&other);

  virtual ~Tree();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void clear();
  void merge(Tree<K, V> &other);
  void swap(Tree &other);
  bool contains(const K &key) const;

  Tree &operator=(const Tree &other);
  Tree &operator=(Tree &&other);

 protected:
  typedef struct Node_ {
    value_type element_;
    unsigned char height_;
    explicit Node_(const value_type &elem) : element_(elem), height_(1){};
  } Node_;

  Node_ *root_;
  Tree *parent_;
  Tree *left_;
  Tree *right_;

  class ConstIterator {
   public:
    ConstIterator() : tree_(nullptr) {}
    ConstIterator(const ConstIterator &other) { tree_ = other.tree_; }
    explicit ConstIterator(Tree<K, V> *tree) : tree_(tree) {}
    ~ConstIterator() = default;

    bool operator==(const ConstIterator &other) {
      return this->tree_ == other.tree_;
    }
    bool operator!=(const ConstIterator &other) {
      return this->tree_ != other.tree_;
    }
    const value_type *operator->() { return &(tree_->root_->element_); }
    ConstIterator operator++() {
      OperationPlus_();
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator tmp(*this);
      OperationPlus_();
      return tmp;
    }
    ConstIterator operator+=(size_type n) {
      while (n-- > 0) operator++();
      return *this;
    }
    ConstIterator operator--() {
      OperationMinus_();
      return *this;
    }
    ConstIterator operator--(int) {
      ConstIterator tmp(*this);
      OperationMinus_();
      return tmp;
    }
    ConstIterator operator-=(size_type n) {
      while (n-- > 0) operator--();
      return *this;
    }
    Tree<K, V> *GetTree() { return tree_; }
    Node_ *GetNode() { return tree_->root_; }
    void SetTree(Tree<K, V> *tr) { tree_ = tr; }

   protected:
    Tree<K, V> *tree_;
    void OperationPlus_();
    void OperationMinus_();
  };

  class Iterator : public ConstIterator {
   public:
    Iterator() : ConstIterator() {}
    explicit Iterator(Tree<K, V> *tree) : ConstIterator(tree) {}
    ~Iterator() = default;

    value_type *operator->() { return &(this->tree_->root_->element_); }
  };

  void Insert_(const value_type &elem, Iterator &iter, bool &is_inserted);

  Tree *FindMin(const Tree *node) const;
  Tree *FindMax(const Tree *node) const;

 private:
  unsigned char Height_(Tree *tr);
  int BalanceFactor_();
  void FixHeight_();
  void RotateLeft_();
  void RotateRight_();
  void ChangePointers_(Tree *tmp, bool is_left);
  void Balance_();
  void Size_(int &size) const;
  void Swap_(Tree<K, V> &other);
  void Contains_(const K &key, bool &contains) const;
  void RemoveThis_(Tree<K, V> *current);
  void RemoveEdge_(Tree<K, V> *current, Tree<K, V> *parent);
  void RemoveNode_(Tree<K, V> *current, Tree<K, V> *parent);

 public:
  using const_iterator = ConstIterator;
  using iterator = Iterator;

  iterator begin() const {
    if (!left_ && !right_ && !root_)
      throw std::out_of_range("Tree does not exist");
    const Tree<K, V> *tmp_this = this;
    Tree<K, V> *min_tr = FindMin(left_ ? left_ : tmp_this);
    return Iterator(min_tr);
  }

  iterator end() const {
    if (!left_ && !right_ && !root_)
      throw std::out_of_range("Tree does not exist");
    const Tree<K, V> *tmp_this = this;
    Tree<K, V> *max_tr = FindMax(right_ ? right_ : tmp_this);
    return Iterator(max_tr);
  }

  void erase(iterator pos);
  virtual std::pair<iterator, bool> insert(const value_type &value);

  Tree<K, V> *GetTree_(iterator pos) { return pos.GetTree(); }
  Node_ *GetNode_(iterator pos) { return pos.GetNode(); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res_vec;
    for (auto elem : {std::forward<Args>(args)...}) {
      res_vec.push_back(insert(elem));
    }
    return res_vec;
  }
};
}  // namespace s21

#include "s21_avl_tree.cpp"

#endif