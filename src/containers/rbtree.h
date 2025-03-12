#include <algorithm>
#include <iomanip>
#include <iostream>
#include "s21_vector.h"
template <typename K, typename T>
class rbtree {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using pointer = value_type*;

 protected:
  enum class NodeColor : int8_t { Black = 0, Red = 1 };
  struct node {
    node(const value_type& value)
        : m_value(value),
          m_right(nullptr),
          m_left(nullptr),
          m_parent(nullptr),
          m_color(NodeColor::Red) {}
    value_type m_value;
    node* m_right;
    node* m_left;
    node* m_parent;
    NodeColor m_color;
  };

 protected:
  struct rbtree_iterator {
   public:
    rbtree_iterator() noexcept;
    rbtree_iterator(node* node) noexcept;
    rbtree_iterator(const rbtree_iterator& other)
        : m_current(other.m_current) {};
    reference operator*() const;
    pointer operator->() const;
    rbtree_iterator& operator++();
    rbtree_iterator operator++(int);
    rbtree_iterator& operator--();
    rbtree_iterator operator--(int);
    bool operator==(const rbtree_iterator& lhs);
    rbtree_iterator& operator=(const rbtree_iterator& other) {
      if (this != &other) {
        m_current = other.m_current;
      }
      return *this;
    }
    bool operator!=(const rbtree_iterator& lhs);

   private:
    friend class rbtree;
    node* m_current;
  };

  struct rbtree_const_iterator {
   public:
    rbtree_const_iterator() noexcept : rbtree_iterator() {};
    const_reference operator*() const { return rbtree_iterator::operator*(); };
  };

  using iterator = rbtree_iterator;
  using const_iterator = rbtree_const_iterator;

 protected:
  rbtree() noexcept;
  rbtree(node* node);
  rbtree(const std::initializer_list<value_type>& items);
  rbtree(const rbtree& other) noexcept;
  rbtree(rbtree&& other) noexcept;
  void swap(rbtree<K, T>&& other);
  void swap(rbtree<K, T>& other);
  virtual ~rbtree();

  rbtree& operator=(const rbtree& other) noexcept;
  rbtree& operator=(rbtree&& other) noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;

  std::pair<iterator, bool> insert(const value_type& value) noexcept;
  std::pair<iterator, bool> insert(const K& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const K& key, const T& obj);
  void erase(iterator pos);
  void erase(const value_type& value);
  void merge(rbtree& other);
  T& at(const K& key);
  T& operator[](const K& key);
  bool contains(const K& key);
  size_type size();
  void print_tree() { print_tree(m_root, 0); }
  void clear();

  node* get_min(node* n);
  node* find_node(const K& key);

 private:
  void rotate_left(node* pos);
  void rotate_right(node* pos);
  void insert(const value_type& value, iterator& iter, bool& inserted);
  void insert_node(node* temp, iterator& iter, bool& inserted);
  void clear(node* node);
  node* copy(node* node);
  void transfer_node(node* deleted_node, node* inserted_node) noexcept;
  bool is_leaf(node* n);
  void set_grandfather(node* parent, node* uncle, node* grandfather,
                       node*& pos);
  node* get_max(node* n);
  node* get_sibling(node* n);
  void balance_insertion(node* pos);
  void replace_node(node* n, node* child) noexcept;
  void delete_case1(node* n);
  void delete_case2(node* n);
  void delete_case3(node* n);
  void delete_case4(node* n);
  void delete_case5(node* n);
  void delete_case6(node* n);

  void print_tree(node* current, int depth) {
    if (current == nullptr) {
      return;
    }
    print_tree(current->m_right, depth + 1);
    std::cout << std::setw(depth * 4) << "";
    std::cout << (current->m_color == NodeColor::Red ? "R" : "B")
              << current->m_value.first << std::endl;
    print_tree(current->m_left, depth + 1);
  }

 private:
  node* m_root;
  size_type m_size;
};

template <typename K, typename T>
inline rbtree<K, T>::rbtree_iterator::rbtree_iterator() noexcept
    : m_current(nullptr) {}

template <typename K, typename T>
inline rbtree<K, T>::rbtree_iterator::rbtree_iterator(node* node) noexcept
    : m_current(node) {}

template <typename K, typename T>
inline typename rbtree<K, T>::reference
rbtree<K, T>::rbtree_iterator::operator*() const {
  return m_current->m_value;
}

template <typename K, typename T>
inline typename rbtree<K, T>::pointer
rbtree<K, T>::rbtree_iterator::operator->() const {
  if (!m_current) {
    throw std::runtime_error("Attempt to access value via invalid iterator");
  }
  return std::addressof(m_current->m_value);
}

template <typename K, typename T>
inline typename rbtree<K, T>::rbtree_iterator&
rbtree<K, T>::rbtree_iterator::operator++() {
  if (m_current == nullptr) return *this;
  if (m_current->m_right) {
    m_current = m_current->m_right;
    while (m_current->m_left) {
      m_current = m_current->m_left;
    }
  } else {
    node* temp = m_current->m_parent;
    while (temp != nullptr && m_current == temp->m_right) {
      m_current = temp;
      temp = temp->m_parent;
    }
    m_current = temp;
  }
  return *this;
}

template <typename K, typename T>
inline typename rbtree<K, T>::rbtree_iterator
rbtree<K, T>::rbtree_iterator::operator++(int) {
  rbtree_iterator temp(m_current);
  ++(*this);
  return temp;
}

template <typename K, typename T>
inline typename rbtree<K, T>::rbtree_iterator&
rbtree<K, T>::rbtree_iterator::operator--() {
  if (m_current == nullptr) return *this;
  if (m_current->m_left) {
    m_current = m_current->m_left;
    while (m_current->m_right) {
      m_current = m_current->m_right;
    }
  } else {
    node* temp = m_current->m_parent;
    while (temp != nullptr && m_current == temp->m_left) {
      m_current = temp;
      temp = temp->m_parent;
    }
    m_current = temp;
  }
  return *this;
}

template <typename K, typename T>
inline typename rbtree<K, T>::rbtree_iterator
rbtree<K, T>::rbtree_iterator::operator--(int) {
  rbtree_iterator temp(m_current);
  --(*this);
  return temp;
}

template <typename K, typename T>
inline bool rbtree<K, T>::rbtree_iterator::operator==(
    const rbtree_iterator& lhs) {
  return this->m_current == lhs.m_current;
}

template <typename K, typename T>
inline bool rbtree<K, T>::rbtree_iterator::operator!=(
    const rbtree_iterator& lhs) {
  return this->m_current != lhs.m_current;
}

template <typename K, typename T>
inline rbtree<K, T>::rbtree() noexcept : m_root(nullptr), m_size(0) {}

template <typename K, typename T>
inline rbtree<K, T>::rbtree(node* node) : m_root(node), m_size(1) {}

template <typename K, typename T>
inline rbtree<K, T>::rbtree(const std::initializer_list<value_type>& items)
    : m_root(nullptr), m_size(0) {
  for (auto i : items) {
    insert(i);
  }
}

template <typename K, typename T>
inline rbtree<K, T>::rbtree(const rbtree& other) noexcept
    : m_root(copy(other.m_root)), m_size(other.m_size) {}

template <typename K, typename T>
inline rbtree<K, T>::rbtree(rbtree&& other) noexcept
    : m_root(nullptr), m_size(0) {
  swap(other);
}

template <typename K, typename T>
inline void rbtree<K, T>::swap(rbtree<K, T>&& other) {
  std::swap(m_root, other.m_root);
  std::swap(m_size, other.m_size);
}

template <typename K, typename T>
inline void rbtree<K, T>::swap(rbtree<K, T>& other) {
  if (this != &other) {
    std::swap(m_root, other.m_root);
    std::swap(m_size, other.m_size);
  }
}

template <typename K, typename T>
inline rbtree<K, T>::~rbtree() {
  clear(m_root);
}

template <typename K, typename T>
inline void rbtree<K, T>::clear(node* node) {
  if (node == nullptr) return;
  clear(node->m_left);
  clear(node->m_right);
  delete node;
}

template <typename K, typename T>
inline typename rbtree<K, T>::node* rbtree<K, T>::copy(node* n) {
  node* temp = nullptr;
  if (n != nullptr) {
    temp = new node(n->m_value);
    temp->m_color = n->m_color;
    temp->m_left = copy(n->m_left);
    temp->m_right = copy(n->m_right);
    temp->m_parent = n->m_parent;
  }
  return temp;
}

template <typename K, typename T>
inline rbtree<K, T>& rbtree<K, T>::operator=(const rbtree& other) noexcept {
  if (this != &other) {
    rbtree temp(other);
    clear(m_root);
    std::swap(this->m_root, temp.m_root);
  }
  return *this;
}

template <typename K, typename T>
inline rbtree<K, T>& rbtree<K, T>::operator=(rbtree&& other) noexcept {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

template <typename K, typename T>
inline typename rbtree<K, T>::iterator rbtree<K, T>::begin() noexcept {
  return iterator(get_min(m_root));
}

template <typename K, typename T>
inline typename rbtree<K, T>::iterator rbtree<K, T>::end() noexcept {
  return iterator(nullptr);
}

template <typename K, typename T>
inline typename rbtree<K, T>::node* rbtree<K, T>::find_node(const K& key) {
  node* current = m_root;
  bool flag = false;
  while (current != nullptr && !flag) {
    if (current->m_value.first == key) {
      flag = true;
    } else if (key < current->m_value.first) {
      current = current->m_left;
    } else {
      current = current->m_right;
    }
  }
  return current;
}

template <typename K, typename T>
inline void rbtree<K, T>::rotate_left(node* pos) {
  node* pivot = pos->m_right;

  if (pos->m_parent != nullptr) {
    pivot->m_parent = pos->m_parent;

    if (pos->m_parent->m_left == pos)
      pos->m_parent->m_left = pivot;
    else
      pos->m_parent->m_right = pivot;
  } else {
    m_root = pivot;
    pivot->m_parent = nullptr;
  }

  pos->m_right = pivot->m_left;
  if (pivot->m_left != nullptr) pivot->m_left->m_parent = pos;

  pos->m_parent = pivot;
  pivot->m_left = pos;
}

template <typename K, typename T>
inline void rbtree<K, T>::rotate_right(node* pos) {
  node* pivot = pos->m_left;

  if (pos->m_parent != nullptr) {
    pivot->m_parent = pos->m_parent;
    if (pos->m_parent->m_left == pos) {
      pos->m_parent->m_left = pivot;
    } else {
      pos->m_parent->m_right = pivot;
    }
  } else {
    m_root = pivot;
    pivot->m_parent = nullptr;
  }

  pos->m_left = pivot->m_right;
  if (pivot->m_right != nullptr) {
    pivot->m_right->m_parent = pos;
  }

  pos->m_parent = pivot;
  pivot->m_right = pos;
}

template <typename K, typename T>
std::pair<typename rbtree<K, T>::iterator, bool> rbtree<K, T>::insert(
    const value_type& value) noexcept {
  iterator it;
  bool is_inserted = false;
  insert(value, it, is_inserted);
  std::pair<iterator, bool> res = {it, is_inserted};
  return res;
}

template <typename K, typename T>
inline std::pair<typename rbtree<K, T>::iterator, bool> rbtree<K, T>::insert(
    const K& key, const T& obj) {
  return insert(std::make_pair(key, obj));
}

template <typename K, typename T>
inline std::pair<typename rbtree<K, T>::iterator, bool>
rbtree<K, T>::insert_or_assign(const K& key, const T& obj) {
  iterator it = begin();
  bool is_inserted = false;
  node* n = find_node(key);
  if (n == nullptr) {
    is_inserted = true;

    it = insert(key, obj).first;
  } else {
    it = iterator(n);
    n->m_value.second = obj;
  }
  return {it, is_inserted};
}

template <typename K, typename T>
void rbtree<K, T>::insert_node(node* temp, iterator& iter, bool& inserted) {
  node* begin = m_root;
  node* begin_parent = nullptr;
  bool flag = false;
  while (begin != nullptr && !flag) {
    begin_parent = begin;
    if (temp->m_value.first < begin->m_value.first) {
      begin = begin->m_left;
    } else if (temp->m_value.first > begin->m_value.first) {
      begin = begin->m_right;
    } else if (temp->m_value.first == begin->m_value.first) {
      inserted = false;
      iter = iterator(begin);
      flag = true;
    }
  }
  if (!flag) {
    temp->m_parent = begin_parent;
    if (temp->m_value.first < begin_parent->m_value.first) {
      std::cout << temp->m_parent->m_value.first << std::endl;

      begin_parent->m_left = temp;
    } else {
      begin_parent->m_right = temp;
    }
    inserted = true;
    iter = iterator(temp);
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::insert(const value_type& value, iterator& iter,
                                 bool& inserted) {
  node* temp = new node(value);

  if (m_root == nullptr) {
    m_root = temp;
    temp->m_parent = nullptr;
    iter = iterator(temp);
    inserted = true;
  } else {
    insert_node(temp, iter, inserted);
  }
  if (inserted) {
    balance_insertion(temp);
    ++m_size;
  } else {
    delete temp;
  }
}

template <typename K, typename T>
inline typename rbtree<K, T>::node* rbtree<K, T>::get_sibling(node* n) {
  node* parent = n->m_parent;
  node* sibling = nullptr;
  if (n == parent->m_left) {
    sibling = parent->m_right;
  } else {
    sibling = parent->m_left;
  }
  return sibling;
}

template <typename K, typename T>
inline void rbtree<K, T>::erase(iterator pos) {
  erase(*pos);
}
template <typename K, typename T>
inline void rbtree<K, T>::erase(const value_type& value) {
  node* find = find_node(value.first);
  node* child = nullptr;
  node* successor = find;
  if (find->m_left) {
    successor = get_max(find->m_left);
  } else if (find->m_right) {
    successor = get_min(find->m_right);
  }
  if (successor != find) {
    transfer_node(find, successor);
    if (!successor->m_parent) {
      m_root = successor;
      m_root->m_color = NodeColor::Black;
    }
    successor = find;
  }
  child =
      (successor->m_left != nullptr) ? successor->m_left : successor->m_right;
  if (successor->m_color == NodeColor::Black) {
    if (!child) {
      delete_case1(successor);
    } else {
      child->m_parent = successor->m_parent;
      if (successor->m_parent->m_left == successor) {
        successor->m_parent->m_left = child;
      } else {
        successor->m_parent->m_right = child;
      }
      printf("here\n");
      if (child->m_color == NodeColor::Red) {
        child->m_color = NodeColor::Black;
      } else {
        delete_case1(child);
      }
    }
  }
  if (successor->m_parent) {
    if (successor->m_parent->m_left == successor) {
      successor->m_parent->m_left = nullptr;
    } else {
      successor->m_parent->m_right = nullptr;
    }
    successor->m_parent = nullptr;
  }
  if (successor == m_root) {
    m_root = nullptr;
  }
  --m_size;

  delete find;
}

template <typename K, typename T>
inline void rbtree<K, T>::merge(rbtree& other) {
  for (iterator it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

template <typename K, typename T>
void rbtree<K, T>::transfer_node(node* source, node* target) noexcept {
  NodeColor tmpColor = source->m_color;
  source->m_color = target->m_color;
  target->m_color = tmpColor;

  node* tempNode = source->m_left;
  source->m_left = target->m_left;
  if (target->m_left) {
    target->m_left->m_parent = source;
  }
  target->m_left = tempNode;
  if (tempNode) {
    tempNode->m_parent = target;
  }
  tempNode = source->m_right;
  source->m_right = target->m_right;
  if (target->m_right) {
    target->m_right->m_parent = source;
  }
  target->m_right = tempNode;
  if (tempNode) {
    tempNode->m_parent = target;
  }

  if (source->m_parent) {
    if (source->m_parent->m_left == source) {
      source->m_parent->m_left = target;
    } else {
      source->m_parent->m_right = target;
    }
  }

  if (target->m_parent) {
    if (target->m_parent->m_left == target) {
      target->m_parent->m_left = source;
    } else {
      target->m_parent->m_right = source;
    }
  }

  tempNode = source->m_parent;
  source->m_parent = target->m_parent;
  target->m_parent = tempNode;
}

template <typename K, typename T>
inline void rbtree<K, T>::replace_node(node* old_node,
                                       node* new_node) noexcept {
  if (new_node) {
    new_node->m_parent = old_node->m_parent;
  }

  if (old_node == old_node->m_parent->m_left) {
    old_node->m_parent->m_left = new_node;
  } else {
    old_node->m_parent->m_right = new_node;
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case1(node* n) {
  if (n->m_parent) {
    delete_case2(n);
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case2(node* find) {
  node* s = get_sibling(find);
  if (s && s->m_color == NodeColor::Red) {
    find->m_parent->m_color = NodeColor::Red;
    s->m_color = NodeColor::Black;
    if (find == find->m_parent->m_left) {
      rotate_left(find->m_parent);
    } else {
      rotate_right(find->m_parent);
    }
  }
  delete_case3(find);
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case3(node* find) {
  node* s = get_sibling(find);
  if (s && find->m_parent->m_color == NodeColor::Black &&
      s->m_color == NodeColor::Black &&
      (!s->m_left || s->m_left->m_color == NodeColor::Black) &&
      (!s->m_right || s->m_right->m_color == NodeColor::Black)) {
    s->m_color = NodeColor::Red;
    delete_case1(find->m_parent);
  } else {
    delete_case4(find);
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case4(node* n) {
  node* s = get_sibling(n);
  if (s && n->m_parent->m_color == NodeColor::Red &&
      (s->m_color == NodeColor::Black) &&
      (!s->m_left || s->m_left->m_color == NodeColor::Black) &&
      (!s->m_right || s->m_right->m_color == NodeColor::Black)) {
    s->m_color = NodeColor::Red;
    n->m_parent->m_color = NodeColor::Black;
  } else {
    delete_case5(n);
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case5(node* n) {
  node* s = get_sibling(n);

  if (s && s->m_color == NodeColor::Black) {
    if ((n == n->m_parent->m_left) &&
        (!s->m_right || s->m_right->m_color == NodeColor::Black) &&
        (!s->m_left || s->m_left->m_color == NodeColor::Red)) {
      s->m_color = NodeColor::Red;
      s->m_left->m_color = NodeColor::Black;
      rotate_right(s);
    } else if ((n == n->m_parent->m_right) &&
               (s->m_left->m_color == NodeColor::Black) &&
               (s->m_right->m_color == NodeColor::Red)) {
      s->m_color = NodeColor::Red;
      s->m_right->m_color = NodeColor::Black;
      rotate_left(s);
    }
  }
  delete_case6(n);
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case6(node* n) {
  node* s = get_sibling(n);
  s->m_color = n->m_parent->m_color;
  n->m_parent->m_color = NodeColor::Black;
  if (n == n->m_parent->m_left) {
    s->m_right->m_color = NodeColor::Black;
    rotate_left(n->m_parent);
  } else {
    s->m_left->m_color = NodeColor::Black;
    rotate_right(n->m_parent);
  }
}

template <typename K, typename T>
inline bool rbtree<K, T>::is_leaf(node* n) {
  return (n != nullptr && n->m_left == nullptr && n->m_right == nullptr);
}

template <typename K, typename T>
typename rbtree<K, T>::node* rbtree<K, T>::get_min(node* n) {
  if (n != nullptr) {
    while (n->m_left != nullptr) {
      n = n->m_left;
    }
  }
  return n;
}

template <typename K, typename T>
inline typename rbtree<K, T>::node* rbtree<K, T>::get_max(node* n) {
  while (n->m_right) {
    n = n->m_right;
  }
  return n;
}

template <typename K, typename T>
inline void rbtree<K, T>::balance_insertion(node* pos) {
  if (pos == m_root) {
    pos->m_color = NodeColor::Black;
  } else {
    node* parent = pos->m_parent;

    while (parent->m_color == NodeColor::Red) {
      node* grandfather = parent->m_parent;
      if (parent == grandfather->m_left) {
        node* uncle = grandfather->m_right;
        if (uncle != nullptr && uncle->m_color == NodeColor::Red) {
          set_grandfather(parent, uncle, grandfather, pos);
        } else {
          if (pos == parent->m_right) {
            pos = parent;
            rotate_left(pos);
          }
          parent->m_color = NodeColor::Black;
          grandfather->m_color = NodeColor::Red;
          rotate_right(grandfather);
        }
      } else {  // if father is right child
        node* uncle = grandfather->m_left;
        if (uncle != nullptr && uncle->m_color == NodeColor::Red) {
          set_grandfather(parent, uncle, grandfather, pos);
        } else {
          if (pos == parent->m_left) {
            pos = parent;
            rotate_right(pos);
          }
          parent->m_color = NodeColor::Black;
          grandfather->m_color = NodeColor::Black;
          rotate_left(grandfather);
        }
      }
    }
    m_root->m_color = NodeColor::Black;
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::set_grandfather(rbtree<K, T>::node* parent,
                                          rbtree<K, T>::node* uncle,
                                          rbtree<K, T>::node* grandfather,
                                          rbtree<K, T>::node*& pos) {
  parent->m_color = NodeColor::Black;
  uncle->m_color = NodeColor::Black;
  grandfather->m_color = NodeColor::Red;
  pos = grandfather;
}

template <typename K, typename T>
inline T& rbtree<K, T>::at(const K& key) {
  node* node = find_node(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found in the tree");
  }
  return node->m_value.second;
}

template <typename K, typename T>
inline T& rbtree<K, T>::operator[](const K& key) {
  node* node = find_node(key);
  if (node == nullptr) {
    insert(key, T());
    node = find_node(key);
  }
  return node->m_value.second;
}

template <typename K, typename T>
inline bool rbtree<K, T>::contains(const K& key) {
  node* node = find_node(key);
  return node != nullptr;
}

template <typename K, typename T>
inline typename rbtree<K, T>::size_type rbtree<K, T>::size() {
  return m_size;
}

template <typename K, typename T>
inline void rbtree<K, T>::clear() {
  clear(m_root);
  m_size = 0;
}