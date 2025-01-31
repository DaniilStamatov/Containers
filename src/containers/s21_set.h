#pragma once

template <typename K>
class set : public rbtree<K, K> {
  using typename rbtree<K, T>::key_type;
  using typename rbtree<K, T>::mapped_type;
  using typename rbtree<K, T>::value_type;
  using typename rbtree<K, T>::iterator;
  using typename rbtree<K, T>::size_type;
};