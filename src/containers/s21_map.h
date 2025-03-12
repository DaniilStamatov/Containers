#pragma once
#include "rbtree.h"

template <typename K, typename T>
class map : protected rbtree<K, T> {
 public:
  using typename rbtree<K, T>::key_type;
  using typename rbtree<K, T>::mapped_type;
  using typename rbtree<K, T>::value_type;
  using typename rbtree<K, T>::iterator;
  using typename rbtree<K, T>::size_type;
  map() : rbtree<K, T>() {};
  map(const map& other) : rbtree<K, T>(other) {};
  map(const std::initializer_list<value_type>& items) : rbtree<K, T>(items) {};
  map(map&& other) : rbtree<K, T>(std::move(other)) {};
  ~map() = default;

  std::pair<iterator, bool> insert(const value_type& value) noexcept {
    return rbtree<K, T>::insert(value);
  }
  std::pair<iterator, bool> insert(const K& key, const T& obj) noexcept {
    return rbtree<K, T>::insert(key, obj);
  }
  std::pair<iterator, bool> insert_or_assign(const K& key, const T& obj) {
    return rbtree<K, T>::insert_or_assign(key, obj);
  }
  template<class... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&& ...args) {
    s21::vector<std::pair<iterator,bool>> results;
    for(const auto& arg : {args...}) {
      results.push_back(insert(arg));
    }
    return results;
  }

  void merge(map& other) { rbtree<K, T>::merge(other); }

  void erase(iterator pos) { rbtree<K, T>::erase(*pos); }

  size_type size() noexcept { return rbtree<K, T>::size(); }
  bool contains(const K& key) { return rbtree<K, T>::contains(key); }

  T& operator[](const K& key) { return rbtree<K, T>::operator[](key); }
  T& at(const K& key) { return rbtree<K, T>::at(key); }
  void swap(map<K, T>& other) { return rbtree<K, T>::swap(other); }
  iterator begin() noexcept { return rbtree<K, T>::begin(); }

  iterator end() noexcept { return rbtree<K, T>::end(); }
};