#ifndef S21_VECTOR
#define S21_VECTOR

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {
template <class T>
class vector {
  // private attributes
 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;
  // public attribures
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  // private method
 private:
  void reserve_more_capacity(size_type size);
  // public methods
 public:
  // default constructor (simplified syntax for assigning values to attributes)
  vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}
  // parametrized constructor for fixed size vector (explicit was used in order
  // to avoid automatic type conversion)
  explicit vector(size_type n)
      : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}
  // initializer list constructor (allows creating lists with initializer lists,
  // see main.cpp)
  vector(std::initializer_list<value_type> const &items);
  // copy constructor with simplified syntax
  vector(const vector &v)
      : m_size(v.m_size), m_capacity(v.m_capacity), arr(new T[v.m_size]) {
    std::copy(v.arr, v.arr + v.m_size, arr);
  };
  // move constructor with simplified syntax
  vector(vector &&v) {
    m_size = std::exchange(v.m_size, 0);
    m_capacity = std::exchange(v.m_capacity, 0);
    arr = std::exchange(v.arr, nullptr);
  }

  // destructor
  ~vector() { delete[] arr; }

  //assignment operator overload for moving object
  vector &operator=(vector &&other) noexcept;

  // some method examples
  // size getter
  size_type size() { return m_size; }
  const size_type size() const { return m_size; }
  bool empty() { return m_size == 0; }

  // element accessor
  value_type at(size_type i);
  value_type operator[](size_type i);
  value_type operator[](size_type i) const;

  // append new element
  void push_back(value_type v);
  void pop_back();
  void swap(vector &other);
  void clear() { delete[] arr, arr = nullptr, m_size = 0, m_capacity = 0; }

  T &front() {
    if (m_size == 0) throw std::out_of_range("Vector is empty");
    return arr[0];
  }

  const T &front() const {
    if (m_size == 0) throw std::out_of_range("Vector is empty");
    return arr[0];
  }

  // Метод доступа к последнему элементу
  T &back() {
    if (m_size == 0) throw std::out_of_range("Vector is empty");
    return arr[m_size - 1];
  }

  const T &back() const {
    if (m_size == 0) throw std::out_of_range("Vector is empty");
    return arr[m_size - 1];
  }

  class iterator {
   private:
    T *ptr;

   public:
    iterator(T *ptr) : ptr(ptr) {}
    T &operator*() { return *ptr; }
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    iterator operator+(int n) { return ptr + n; }
    iterator operator-(int n) { return ptr - n; }

    bool operator==(const iterator &other) const { return ptr == other.ptr; }
    bool operator!=(const iterator &other) const { return ptr != other.ptr; }
  };

  class const_iterator {
   private:
    const T *ptr;

   public:
    const_iterator(const T *ptr) : ptr(ptr) {}
    const T &operator*() { return *ptr; }
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    const_iterator operator--(int);
    const_iterator operator+(int n) { return ptr + n; }
    const_iterator operator-(int n) { return ptr - n; }

    bool operator==(const const_iterator &other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const const_iterator &other) const {
      return ptr != other.ptr;
    }
  };

  iterator begin() { return iterator(arr); }
  iterator end() { return iterator(arr + m_size); }

  const_iterator cbegin() const { return const_iterator(arr); }
  const_iterator cend() const { return const_iterator(arr + m_size); }
};
}  // namespace s21

#include "s21_vector.cpp"

#endif
