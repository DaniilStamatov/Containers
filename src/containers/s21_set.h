#pragma once
#include "rbtree.h"
template <typename K>
class set : protected rbtree<K, K> {
 public:
  using typename rbtree<K, K>::key_type;
  using typename rbtree<K, K>::mapped_type;
  using value_type = K;
  using typename rbtree<K, K>::size_type;
  using const_reference = const value_type&;
  using node = typename rbtree<K, K>::node;
  using tree_iterator = typename rbtree<K, K>::iterator;

  set() : rbtree<K, K>() {};
  set(const set& other) : rbtree<K, K>(other) {};
  set(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
      rbtree<K, K>::insert(*i, K());
    }
  };
  set(set&& other) : rbtree<K, K>(std::move(other)) {};
  ~set() = default;

  struct iterator : public rbtree<K, K>::rbtree_iterator {
   public:
    iterator() : tree_iterator() {};
    iterator(node* node) : tree_iterator(node) {};
    iterator(const tree_iterator& it) : tree_iterator(it) {};
    K& operator*() {
      const auto& res = rbtree<K, K>::iterator::operator*();
      return const_cast<K&>(res.first);
    }
  };
  set& operator=(set&& s) noexcept { return rbtree<K, K>::operator=(s); }

  iterator begin() noexcept { return iterator(rbtree<K, K>::begin()); }

  iterator end() noexcept { return iterator(nullptr); }

  void clear() noexcept { rbtree<K, K>::clear(); }

  std::pair<iterator, bool> insert(const value_type& value) noexcept {
    auto result = rbtree<K, K>::insert(value, K());
    return std::make_pair(iterator(result.first), result.second);
  }

  void erase(iterator pos) { rbtree<K, K>::erase(pos); }

  void swap(set& other) { rbtree<K, K>::swap(other); }

  void merge(set& other) { rbtree<K, K>::merge(other); }

  iterator find(const K& key) {
    return iterator(tree_iterator(rbtree<K, K>::find_node(key)));
  }
  bool contains(const K& key) noexcept { return rbtree<K, K>::contains(key); }

  size_type size() noexcept { return rbtree<K, K>::size(); }
};