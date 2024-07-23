#include <initializer_list>
#include <iostream>
#include <utility>

#include "../s21_list/s21_list.h"
#include "../s21_vector/s21_vector.h"

namespace s21 {
template <typename Key, typename Value>
class UnorderedMap {
 private:
  class Pair {
   public:
    Key first;
    Value second;

    Pair() = default;

    Pair(const Key &key, const Value &value) : first(key), second(value) {}

    Pair(const Pair &other) = default;

    Pair(Pair &&other) noexcept = default;

    Pair &operator=(const Pair &other) = default;

    Pair &operator=(Pair &&other) noexcept = default;
  };

  std::vector<list<Pair>> table;
  size_t bucket_count;
  size_t size;

  size_t hash(const Key &key) const {
    return std::hash<Key>{}(key) % bucket_count;
  }

 public:
  using PairType = Pair;
  using BucketType = list<PairType>;
  using TableType = std::vector<BucketType>;

  class iterator {
   private:
    TableType *table_ptr;
    size_t bucket_index;
    typename BucketType::iterator list_it;

    void advance_to_valid() {
      while (bucket_index < table_ptr->size() &&
             list_it == (*table_ptr)[bucket_index].end()) {
        ++bucket_index;
        if (bucket_index < table_ptr->size()) {
          list_it = (*table_ptr)[bucket_index].begin();
        }
      }

      if (bucket_index >= table_ptr->size())
        list_it = typename BucketType::iterator();
    }

   public:
    iterator(TableType *table_ptr, size_t bucket_index,
             typename BucketType::iterator list_it)
        : table_ptr(table_ptr), bucket_index(bucket_index), list_it(list_it) {
      advance_to_valid();
    }

    PairType &operator*() { return *list_it; }

    PairType *operator->() { return &(*list_it); }

    iterator &operator++() {
      ++list_it;
      advance_to_valid();
      return *this;
    }

    bool operator==(const iterator &other) const {
      return table_ptr == other.table_ptr &&
             bucket_index == other.bucket_index && list_it == other.list_it;
    }

    bool operator!=(const iterator &other) const { return !(*this == other); }
  };

  UnorderedMap(size_t bucket_count = 10) : bucket_count(bucket_count), size(0) {
    table.resize(bucket_count);
  }

  UnorderedMap(const UnorderedMap &other)
      : bucket_count(other.bucket_count),
        size(other.size),
        table(other.table) {}

  UnorderedMap(UnorderedMap &&other) noexcept
      : bucket_count(other.bucket_count),
        size(other.size),
        table(std::move(other.table)) {
    other.bucket_count = 0;
    other.size = 0;
  }

  UnorderedMap(std::initializer_list<PairType> init_list)
      : UnorderedMap(init_list.size() * 2) {
    for (const auto &pair : init_list) {
      insert(pair.first, pair.second);
    }
  }

  UnorderedMap &operator=(const UnorderedMap &other) {
    if (this != &other) {
      bucket_count = other.bucket_count;
      size = other.size;
      table = other.table;
    }
    return *this;
  }

  UnorderedMap &operator=(UnorderedMap &&other) noexcept {
    if (this != &other) {
      bucket_count = other.bucket_count;
      size = other.size;
      table = std::move(other.table);
      other.bucket_count = 0;
      other.size = 0;
    }
    return *this;
  }

  bool insert(const Key &key, const Value &value) {
    size_t index = hash(key);
    for (auto &pair : table[index]) {
      if (pair.first == key) {
        pair.second = value;
        return false;
      }
    }
    table[index].emplace_back(key, value);
    ++size;
    return true;
  }

  iterator find(const Key &key) {
    size_t index = hash(key);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
      if (it->first == key) {
        return iterator(&table, index, it);
      }
    }
    return end();
  }

  iterator begin() {
    for (size_t index = 0; index < table.size(); ++index) {
      if (!table[index].empty()) {
        return iterator(&table, index, table[index].begin());
      }
    }
    return end();
  }

  iterator end() {
    return iterator(&table, table.size(), typename BucketType::iterator());
  }

  size_t get_size() const { return size; }
};

int main() {
  UnorderedMap<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  map.insert(4, "four");

  for (auto it = map.begin(); it != map.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
  }

  return 0;
}
}  // namespace s21