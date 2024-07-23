#include "s21_avl_tree.h"

using namespace s21;

template <typename K, typename V>
Tree<K, V>::Tree()
    : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {}

template <typename K, typename V>
Tree<K, V>::Tree(const value_type &elem)
    : parent_(nullptr), left_(nullptr), right_(nullptr) {
  root_ = new Node_(elem);
}

template <typename K, typename V>
Tree<K, V>::~Tree() {
  clear();
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(Tree &&other) {
  if (this != &other) {
    parent_ = other.parent_;
    right_ = other.right_;
    left_ = other.left_;
    root_ = other.root_;
    other.parent_ = nullptr;
    other.right_ = nullptr;
    other.left_ = nullptr;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename K, typename V>
typename Tree<K, V>::size_type Tree<K, V>::size() const {
  int size = 0;
  Size_(size);
  return size;
}

template <typename K, typename V>
inline unsigned char Tree<K, V>::Height_(Tree *tr) {
  return (tr ? tr->root_ ? tr->root_->height_ : 0 : 0);
}

template <typename K, typename V>
inline int Tree<K, V>::BalanceFactor_() {
  return (Height_(right_) - Height_(left_));
}

template <typename K, typename V>
void Tree<K, V>::FixHeight_() {
  root_->height_ =
      (Height_(left_) > Height_(right_) ? Height_(left_) : Height_(right_)) + 1;
}

template <typename K, typename V>
void Tree<K, V>::RotateLeft_() {
  Tree *tmp_right = right_;
  Tree *tmp_parent = parent_;
  right_ = tmp_right->left_;
  ChangePointers_(tmp_right, true);
  FixHeight_();
  tmp_right->FixHeight_();
  *this = std::move(*tmp_right);
  parent_ = tmp_parent;
  left_->parent_ = this;
  if (right_) right_->parent_ = this;
  if (left_) {
    if (left_->right_) {
      if (!left_->right_->parent_->root_)
        left_->right_->parent_->root_ =
            new Node_(left_->right_->root_->element_);
      left_->right_->parent_ = left_;
    }
    if (left_->left_) {
      if (!left_->left_->parent_->root_)
        left_->left_->parent_->root_ = new Node_(left_->left_->root_->element_);
      left_->left_->parent_ = left_;
    }
  }
  delete tmp_right;
  tmp_right = nullptr;
}

template <typename K, typename V>
void Tree<K, V>::RotateRight_() {
  Tree *tmp_left = left_;
  Tree *tmp_parent = parent_;
  left_ = tmp_left->right_;
  ChangePointers_(tmp_left, false);
  FixHeight_();
  tmp_left->FixHeight_();
  *this = std::move(*tmp_left);
  parent_ = tmp_parent;
  right_->parent_ = this;

  if (left_) left_->parent_ = this;

  if (right_) {
    if (right_->left_) {
      if (!right_->left_->parent_->root_)
        right_->left_->parent_->root_ =
            new Node_(right_->left_->root_->element_);
      right_->left_->parent_ = right_;
    }
    if (right_->right_) {
      if (!right_->right_->parent_->root_)
        right_->right_->parent_->root_ =
            new Node_(right_->right_->root_->element_);
      right_->right_->parent_ = right_;
    }
  }

  delete tmp_left;
  tmp_left = nullptr;
}

template <typename K, typename V>
void Tree<K, V>::ChangePointers_(Tree *tmp, bool is_left) {
  auto *tmp_this = new Tree<K, V>();
  tmp_this->parent_ = parent_;
  tmp_this->left_ = left_;
  tmp_this->right_ = right_;
  tmp_this->root_ = root_;
  if (is_left)
    tmp->left_ = tmp_this;
  else
    tmp->right_ = tmp_this;
}

template <typename K, typename V>
void Tree<K, V>::Balance_() {
  FixHeight_();
  int balance = BalanceFactor_();
  if (balance == 2) {
    if (right_->BalanceFactor_() < 0) {
      right_->RotateRight_();
    }
    RotateLeft_();
  } else if (balance == -2) {
    if (left_->BalanceFactor_() > 0) left_->RotateLeft_();
    RotateRight_();
  }
}

template <typename K, typename V>
void Tree<K, V>::Insert_(const value_type &elem, Iterator &iter,
                         bool &is_inserted) {
  if (!root_) {
    root_ = new Node_(elem);
    iter.SetTree(this);
    is_inserted = true;
    return;
  }
  if (elem.first < root_->element_.first) {
    if (!left_) {
      left_ = new Tree;
      left_->parent_ = this;
    }
    left_->Insert_(elem, iter, is_inserted);
  } else if (elem.first > root_->element_.first) {
    if (!right_) {
      right_ = new Tree;
      right_->parent_ = this;
    }
    right_->Insert_(elem, iter, is_inserted);
  }
  Balance_();
}

template <typename K, typename V>
Tree<K, V> *Tree<K, V>::FindMin(const Tree *node) const {
  return (node->left_ && node->left_->root_ ? FindMin(node->left_)
                                            : (Tree<K, V> *)node);
}

template <typename K, typename V>
void Tree<K, V>::erase(Tree<K, V>::Iterator pos) {
  Tree<K, V> *current = GetTree_(pos);
  if (current == this) {
    RemoveThis_(current);
  } else {
    auto parent = current->parent_;
    if (!current->left_ && !current->right_) {
      RemoveEdge_(current, parent);
    } else {
      RemoveNode_(current, parent);
    }
  }
  if (root_) Balance_();
}

template <typename K, typename V>
void Tree<K, V>::Size_(int &size) const {
  if (root_) ++size;
  if (right_) right_->Size_(size);
  if (left_) left_->Size_(size);
}

template <typename K, typename V>
Tree<K, V> *Tree<K, V>::FindMax(const Tree *node) const {
  return (node->right_ && node->right_->root_ ? FindMax(node->right_)
                                              : (Tree<K, V> *)node);
}

template <typename K, typename V>
void Tree<K, V>::clear() {
  delete left_;
  delete right_;
  delete root_;
}

template <typename K, typename V>
void Tree<K, V>::Swap_(Tree<K, V> &other) {
  Node_ *tmp_root = root_;
  Tree<K, V> *tmp_left = left_;
  Tree<K, V> *tmp_right = right_;
  Tree<K, V> *tmp_parent = parent_;
  root_ = other.root_;
  left_ = other.left_;
  right_ = other.right_;
  parent_ = other.parent_;
  other.root_ = tmp_root;
  other.left_ = tmp_left;
  other.right_ = tmp_right;
  other.parent_ = tmp_parent;
}

template <typename K, typename V>
void Tree<K, V>::RemoveThis_(Tree<K, V> *current) {
  if (current->right_ || current->left_) {
    Tree<K, V> *min =
        FindMin(current->right_ ? current->right_ : current->left_);
    Tree<K, V> *min_parent = min->parent_;
    if (min_parent->left_ == min)
      min_parent->left_ = nullptr;
    else
      min_parent->right_ = nullptr;
    min->parent_ = nullptr;
    if (left_) {
      min->left_ = left_;
      left_ = nullptr;
    }
    if (right_) {
      min->right_ = right_;
      right_ = nullptr;
    }
    Swap_(*min);
    if (right_) right_->parent_ = this;
    delete min;
  } else {
    delete root_;
    root_ = nullptr;
  }
}

template <typename K, typename V>
void Tree<K, V>::RemoveEdge_(Tree<K, V> *current, Tree<K, V> *parent) {
  if (parent->left_ == current) {
    delete current;
    parent->left_ = nullptr;
  } else if (parent->right_ == current) {
    delete current;
    parent->right_ = nullptr;
  }
}

template <typename K, typename V>
void Tree<K, V>::RemoveNode_(Tree<K, V> *current, Tree<K, V> *parent) {
  Tree<K, V> *min = FindMin(current->right_ ? current->right_ : current->left_);
  Tree<K, V> *min_parent = min->parent_;
  if (min_parent->right_ == min)
    min_parent->right_ = nullptr;
  else
    min_parent->left_ = nullptr;
  if (parent->right_ == current)
    parent->right_ = min;
  else
    parent->left_ = min;
  min->left_ = current->left_;
  min->right_ = current->right_;
  min->parent_ = parent;
  if (min->left_) min->left_->parent_ = min;
  if (min->right_) min->right_->parent_ = min;
  current->left_ = nullptr;
  current->right_ = nullptr;
  current->parent_ = nullptr;
  delete current;
}

template <typename K, typename V>
bool Tree<K, V>::empty() const {
  return !root_;
}

template <typename K, typename V>
typename Tree<K, V>::size_type Tree<K, V>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Tree<V, V>) / 2;
}

template <typename K, typename V>
Tree<K, V>::Tree(const std::initializer_list<value_type> &items)
    : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {
  for (value_type i : items) insert(i);
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(const Tree &other) {
  if (this != &other) {
    auto it = other.begin();
    clear();
    root_ = nullptr;
    parent_ = nullptr;
    left_ = nullptr;
    right_ = nullptr;
    std::pair<K, V> el;
    el.first = it->first;
    el.second = it->second;
    insert(el);
    while (true) {
      if (it == other.end()) break;
      ++it;
      el.first = it->first;
      el.second = it->second;
      insert(el);
    }
  }
  return *this;
}

template <typename K, typename V>
Tree<K, V>::Tree(const Tree &other)
    : root_(nullptr), parent_(nullptr), left_(nullptr), right_(nullptr) {
  *this = other;
}

template <typename K, typename V>
Tree<K, V>::Tree(Tree &&other) {
  *this = std::move(other);
}

template <typename K, typename V>
void Tree<K, V>::merge(Tree<K, V> &other) {
  if (!other.root_) return;
  auto itr1 = other.begin();
  std::pair<K, V> sorry;
  for (; itr1 != other.end(); itr1++) {
    sorry.first = itr1->first;
    sorry.second = itr1->second;
    insert(sorry);
  }
  sorry.first = itr1->first;
  sorry.second = itr1->second;
  insert(sorry);
  other.clear();
  other.root_ = nullptr;
  other.right_ = nullptr;
  other.left_ = nullptr;
  other.parent_ = nullptr;
}

template <typename K, typename V>
void Tree<K, V>::swap(Tree &other) {
  Swap_(other);
}

template <typename K, typename V>
std::pair<typename Tree<K, V>::iterator, bool> Tree<K, V>::insert(
    const Tree::value_type &value) {
  iterator it;
  bool is_inserted = false;
  Insert_(value, it, is_inserted);
  std::pair<iterator, bool> res = {it, is_inserted};
  return res;
}

template <typename K, typename V>
bool Tree<K, V>::contains(const K &key) const {
  bool contains = true;
  Contains_(key, contains);
  return contains;
}

template <typename K, typename V>
void Tree<K, V>::Contains_(const K &key, bool &contains) const {
  if (!root_ || (!left_ && !right_ && root_->element_.first != key)) {
    contains = false;
  } else if (key < root_->element_.first) {
    if (left_)
      left_->Contains_(key, contains);
    else
      contains = false;
  } else if (key > root_->element_.first) {
    if (right_)
      right_->Contains_(key, contains);
    else
      contains = false;
  }
}

template <typename K, typename V>
void Tree<K, V>::const_iterator::OperationPlus_() {
  if (tree_->right_)
    tree_ = tree_->FindMin(tree_->right_);
  else if (!tree_->left_ && !tree_->right_) {
    if (tree_->parent_) {
      if (tree_->parent_->left_ == tree_)
        tree_ = tree_->parent_;
      else if (tree_->parent_->right_ == tree_)
        if (tree_->parent_ && tree_->parent_->parent_)
          tree_ = tree_->parent_->parent_;
    }
  } else if (tree_->parent_) {
    tree_ = tree_->parent_;
  }
}

template <typename K, typename V>
void Tree<K, V>::const_iterator::OperationMinus_() {
  if (tree_->left_)
    tree_ = tree_->FindMax(tree_->left_);
  else if (!tree_->left_ && !tree_->right_) {
    if (tree_->parent_) {
      if (tree_->parent_->right_ == tree_)
        tree_ = tree_->parent_;
      else if (tree_->parent_->left_ == tree_)
        if (tree_->parent_ && tree_->parent_->parent_)
          tree_ = tree_->parent_->parent_;
    }
  } else if (tree_->parent_) {
    tree_ = tree_->parent_;
  }
}
