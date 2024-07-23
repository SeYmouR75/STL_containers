#ifndef S21_QUEUE
#define S21_QUEUE

#include "../s21_list/s21_list.h"

namespace s21 {
template <typename T, typename ContainerT = s21::list<T>>
class queue {
 public:
  using value_type = typename ContainerT::value_type;
  using reference = typename ContainerT::reference;
  using const_reference = typename ContainerT::const_reference;
  using size_type = typename ContainerT::size_type;

  queue() : container() {}
  queue(std::initializer_list<value_type> const &items) : container(items) {}
  queue(const queue &other) : container(other.container) {}
  queue(queue &&other) : container(std::move(other.container)) {}
  ~queue() {}

  queue &operator=(queue &&other) {
    this->container = std::move(other.container);
    return *this;
  }

  const_reference front() { return container.front(); }
  const_reference back() { return container.back(); }

  bool empty() { return container.empty(); }
  size_type size() { return container.size(); }

  void push(const_reference value) { this->container.push_back(value); }
  void pop() { this->container.pop_front(); }
  void swap(queue &other) { this->container.swap(other.container); }

 private:
  ContainerT container;
};

}  // namespace s21

#endif