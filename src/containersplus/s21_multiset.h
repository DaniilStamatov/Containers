#pragma once
#include "../containers/rbtree.h"
namespace s21 {
template <typename K>
class multiset : protected rbtree<K, K> {
 public:
  /*---------- MULTISET MEMBER TYPE ----------*/
  using typename rbtree<K, K>::key_type;
  using typename rbtree<K, K>::mapped_type;
  using value_type = K;
  using typename rbtree<K, K>::size_type;
  using const_reference = const value_type&;
  using node = typename rbtree<K, K>::node;
  using tree_iterator = typename rbtree<K, K>::iterator;

  multiset() : rbtree<K, K>() {};
  multiset(const multiset& other) : rbtree<K, K>(other) {};
  multiset(std::initializer_list<value_type> const& items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
      rbtree<K, K>::insert(*i, K());
    }
  };
  multiset(multiset&& other) : rbtree<K, K>(std::move(other)) {};
  ~multiset() = default;

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
  multiset& operator=(multiset&& s) noexcept { return rbtree<K, K>::operator=(s); }

  iterator begin() noexcept { return iterator(rbtree<K, K>::begin()); }

  iterator end() noexcept { return iterator(nullptr); }

  void clear() noexcept { rbtree<K, K>::clear(); }

  std::pair<iterator, bool> insert(const value_type& value) noexcept {
    iterator it;
    bool is_inserted = rbtree<K, K>::insert(std::make_pair(value, K()), it, true);
    return {it, is_inserted};
  }

  template<class... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&& ...args) {
    s21::vector<std::pair<iterator,bool>> results;
    for(const auto& arg : {args...}) {
      results.push_back(insert(arg));
    }
    return results;
  }

  void print_tree() { rbtree<K, K>::print_tree(); }


  void erase(iterator pos) { rbtree<K, K>::erase(pos); }

  void swap(multiset& other) { rbtree<K, K>::swap(other); }

  void merge(multiset& other) { rbtree<K, K>::merge(other); }

  iterator find(const K& key) {
    return iterator(tree_iterator(rbtree<K, K>::find_node(key)));
  }
  bool contains(const K& key) noexcept { return rbtree<K, K>::contains(key); }

  size_type size() noexcept { return rbtree<K, K>::size(); }
};
}