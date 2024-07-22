#include "s21_list.h"

using namespace s21;

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {
  Initvirtual_();
}

template <typename T>
list<T>::list(list::size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  if (n <= 0) throw std::out_of_range("Index out of range");
  Initvirtual_();
  while (n-- > 0) push_back(T());
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  Initvirtual_();
  for (value_type i : items) {
    push_back(i);
  }
}

template <typename T>
list<T>::list(const list &other) : head_(nullptr), tail_(nullptr), size_(0) {
  Initvirtual_();
  *this = other;
}

template <typename T>
list<T>::list(list &&other) {
  if (this != &other) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    virtual_ = other.virtual_;
    other.size_ = 0;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.virtual_ = nullptr;
    other.Initvirtual_();
  }
}

template <typename T>
list<T>::~list() {
  clear();
  delete virtual_;
}

template <typename T>
void list<T>::push_front(const_reference data) {
  auto *new_ptr = new Node_(data);
  if (!head_) {
    head_ = new_ptr;
    head_->ptr_prev_ = virtual_;
    head_->ptr_next_ = virtual_;
    virtual_->ptr_next_ = head_;
    virtual_->ptr_prev_ = head_;
  } else if (!tail_) {
    tail_ = head_;
    tail_->ptr_next_ = virtual_;
    tail_->ptr_prev_ = new_ptr;
    virtual_->ptr_prev_ = tail_;
    virtual_->ptr_next_ = new_ptr;
    new_ptr->ptr_next_ = tail_;
    head_ = new_ptr;
  } else {
    new_ptr->ptr_next_ = head_;
    head_ = new_ptr;
    virtual_->ptr_next_ = head_;
    head_->ptr_prev_ = virtual_;
  }
  ++size_;
  virtual_->value_ = size_;
}

template <typename T>
void list<T>::push_back(const_reference data) {
  auto *new_ptr = new Node_(data);
  if (!head_) {
    head_ = new_ptr;
    head_->ptr_next_ = virtual_;
    head_->ptr_prev_ = virtual_;
    virtual_->ptr_prev_ = head_;
    virtual_->ptr_next_ = head_;
  } else if (!tail_) {
    tail_ = new_ptr;
    tail_->ptr_next_ = virtual_;
    tail_->ptr_prev_ = head_;
    virtual_->ptr_prev_ = tail_;
    head_->ptr_next_ = tail_;
  } else {
    new_ptr->ptr_prev_ = tail_;
    tail_->ptr_next_ = new_ptr;
    tail_ = new_ptr;
    virtual_->ptr_prev_ = tail_;
    tail_->ptr_next_ = virtual_;
  }
  ++size_;
  virtual_->value_ = size_;
}

template <typename T>
void list<T>::pop_front() {
  if (head_) {
    Node_ *head_rm = head_;
    if (head_->ptr_next_ != virtual_) {
      head_ = head_->ptr_next_;
    } else {
      head_ = nullptr;
    }

    if (head_rm->ptr_next_) delete head_rm;

    if (size_ == 2) {
      head_ = tail_;
      virtual_->ptr_next_ = head_;
      virtual_->ptr_prev_ = head_;
      head_->ptr_next_ = virtual_;
      head_->ptr_prev_ = virtual_;
      tail_ = nullptr;
    }
    --size_;
    virtual_->value_ = size_;
  }
}

template <typename T>
void list<T>::pop_back() {
  if (tail_) {
    Node_ *tail_rm = tail_;
    if (tail_->ptr_prev_ != virtual_) {
      tail_ = tail_->ptr_prev_;
    } else {
      tail_ = nullptr;
    }

    if (tail_rm->ptr_prev_) delete tail_rm;

    if (size_ == 2) {
      virtual_->ptr_next_ = head_;
      virtual_->ptr_prev_ = head_;
      head_->ptr_next_ = virtual_;
      head_->ptr_prev_ = virtual_;
      tail_ = nullptr;
    }
    --size_;
    virtual_->value_ = size_;
  }
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return head_ ? head_->value_ : virtual_->value_;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  return tail_ ? tail_->value_ : front();
}

template <typename T>
void list<T>::swap(list &other) {
  Node_ *tmp_head = head_;
  Node_ *tmp_tail = tail_;
  Node_ *tmp_virtual = virtual_;
  size_t tmp_size = other.size_;
  if (other.head_ || head_) {
    head_ = other.head_;
    other.head_ = tmp_head;
  }
  if (other.tail_ || tail_) {
    tail_ = other.tail_;
    other.tail_ = tmp_tail;
  }
  virtual_ = other.virtual_;
  other.virtual_ = tmp_virtual;
  other.size_ = size_;
  size_ = tmp_size;
}

template <typename T>
void list<T>::sort() {
  if (size_ <= 1) return;

  list<T> left, right;
  int n = size_ / 2;

  for (int i = 0; i < n; i++) {
    auto left_iter = begin() + i;
    left.push_back(*left_iter);
  }
  for (int j = n; j < (int)size_; j++) {
    auto right_iter = begin() + j;
    right.push_back(*right_iter);
  }

  left.sort();
  right.sort();

  MergeSort_(left, right, *this);
}

template <typename T>
void list<T>::merge(list &other) {
  if (this != &other) {
    list<T> tmp;
    tmp = *this;
    MergeSort_(tmp, other, *this);
    other.clear();
  }
}

template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node_ tmp_head = *head_;
    Node_ tmp_tail = *tail_;
    Node_ *head_ptr = head_;
    Node_ *tail_ptr = tail_;
    for (size_t i = 0; i < size_ / 2; i++) {
      head_ptr->value_ = tmp_tail.value_;
      tail_ptr->value_ = tmp_head.value_;
      head_ptr = head_ptr->ptr_next_;
      tail_ptr = tail_ptr->ptr_prev_;
      tmp_head = *head_ptr;
      tmp_tail = *tail_ptr;
    }
  }
}

template <typename T>
void list<T>::unique() {
  if (size_ == 0 || size_ == 1) return;
  auto it = begin();
  auto it_next = it + 1;
  list<T> tmp_lst;
  while (it != end()) {
    if (*it == *it_next) {
      ++it;
      ++it_next;
      continue;
    } else
      tmp_lst.push_back(*it);
    ++it_next;
    ++it;
  }
  *this = std::move(tmp_lst);
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return (std::numeric_limits<std::size_t>::max() / sizeof(Node_) / 2);
}

template <typename T>
bool list<T>::empty() const {
  return size_ == 0;
}

template <typename T>
void list<T>::clear() {
  while (size_ != 0) {
    pop_front();
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(list::iterator pos,
                                           const_reference value) {
  Node_ *cur_node = GetiteratorNode_(pos);
  auto *new_node_ = new Node_(value);
  if (size_ <= 1) {
    if (cur_node == virtual_)
      push_back(value);
    else if (cur_node == head_)
      push_front(value);
    delete new_node_;
    new_node_ = nullptr;
    return iterator(head_);
  } else {
    Node_ *prev_node = cur_node->ptr_prev_;
    new_node_->ptr_prev_ = prev_node;
    new_node_->ptr_next_ = cur_node;
    cur_node->ptr_prev_ = new_node_;
    prev_node->ptr_next_ = new_node_;
    if (cur_node == virtual_)
      tail_ = new_node_;
    else if (cur_node == head_)
      head_ = new_node_;
    ++size_;
  }
  return iterator(new_node_);
}

template <typename T>
void list<T>::erase(list::iterator pos) {
  Node_ *ptr = GetiteratorNode_(pos);
  if (ptr == virtual_) return;
  if (ptr == head_) {
    pop_front();
  } else if (ptr == tail_) {
    pop_back();
  } else {
    Node_ *prev = ptr->ptr_prev_;
    Node_ *next = ptr->ptr_next_;
    prev->ptr_next_ = next;
    next->ptr_prev_ = prev;
    delete ptr;
    --size_;
  }
}

template <typename T>
void list<T>::splice(list::iterator pos, list &other) {
  if (this != &other) {
    for (auto itr = other.begin(); itr != other.end(); ++itr) insert(pos, *itr);
    other.clear();
  }
}

template <typename T>
list<T> &list<T>::operator=(const list<T> &other) {
  if (this != &other) {
    clear();
    if (!virtual_) Initvirtual_();
    Node_ *tmp_node = other.head_;
    if (tmp_node) {
      while (tmp_node != other.virtual_) {
        push_back(tmp_node->value_);
        tmp_node = tmp_node->ptr_next_;
      }
    }
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&other) {
  if (this != &other) {
    list<T> tmp_lst(std::move(other));
    *this = tmp_lst;
  }
  return *this;
}

template <typename T>
void list<T>::Initvirtual_() {
  virtual_ = new Node_(T());
  virtual_->ptr_next_ = nullptr;
  virtual_->ptr_prev_ = nullptr;
}

template <typename T>
void list<T>::MergeSort_(list<T> &left, list<T> &right, list<T> &result) {
  list<T> merged;
  int left_index = 0, right_index = 0;
  s21::list<T>::const_iterator left_iter = left.begin();
  s21::list<T>::const_iterator right_iter = right.begin();

  while ((left_index < (int)left.size_) && (right_index < (int)right.size_)) {
    left_iter = left.begin() + left_index;
    right_iter = right.begin() + right_index;
    if (*left_iter <= *right_iter) {
      merged.push_back(*left_iter);
      ++left_index;
    } else {
      merged.push_back(*right_iter);
      ++right_index;
    }
  }

  while (left_index < (int)left.size_) {
    merged.push_back(*left_iter);
    ++left_iter;
    ++left_index;
  }

  while (right_index < (int)right.size_) {
    merged.push_back(*right_iter);
    ++right_iter;
    ++right_index;
  }

  result = merged;
}