#ifndef S21_STACK_H
#define S21_STACK_H
#include "../s21_vector/s21_vector.h"

namespace s21 {
template <class T, class ContainerT = s21::vector<T>>
class stack {
 public:
  using value_type = typename ContainerT::value_type;
  using reference = typename ContainerT::reference;
  using const_reference = typename ContainerT::const_reference;
  using size_type = typename ContainerT::size_type;

  stack() : container() {}
  stack(std::initializer_list<value_type> const &items) : container(items) {}
  stack(const stack &other) : container(other.container) {}
  stack(stack &&other) : container(std::move(other.container)) {}
  ~stack() {}

  stack &operator=(stack &&other) {
    this->container = std::move(other.container);
    return *this;
  }

  const_reference top() { return container.back(); }

  bool empty() { return container.empty(); }
  size_type size() { return container.size(); }

  void push(const_reference value) { this->container.push_back(value); }
  void pop() { this->container.pop_back(); }
  void swap(stack &other) { this->container.swap(other.container); }

 private:

  ContainerT container;
};

}  //  namespace s21

#endif