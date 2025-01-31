#pragma once
#include "rbtree/rbtree.h"

template <typename K, typename T>
class map : public rbtree<K, T> {
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

  std::pair<iterator, bool> insert(const value_type& value) noexcept {
    return rbtree<K, T>::insert(value);
  }
  std::pair<iterator, bool> insert(const K& key, const T& obj) noexcept {
    return rbtree<K, T>::insert(key, obj);
  }
  std::pair<iterator, bool> insert_or_assign(const K& key, const T& obj) {
    return rbtree<K, T>::insert_or_assign(key, obj);
  }
  void merge(map& other) { rbtree<K, T>::merge(other); }

  void erase(iterator pos) { rbtree<K, T>::erase(*pos); }

  size_type size() noexcept { return rbtree<K, T>::size(); }
};