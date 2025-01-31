#include <algorithm>
#include <iomanip>
#include <iostream>
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
  struct rbtree_node {
    rbtree_node(const value_type& value)
        : value_(value),
          right_(nullptr),
          left_(nullptr),
          parent_(nullptr),
          mColor('R') {}
    value_type value_;
    rbtree_node* right_;
    rbtree_node* left_;
    rbtree_node* parent_;
    char mColor;
  };

  using node = rbtree_node;

  struct rbtree_iterator {
   public:
    rbtree_iterator() noexcept;
    rbtree_iterator(node* node) noexcept;
    reference operator*() const;
    pointer operator->() const;
    rbtree_iterator& operator++();
    rbtree_iterator operator++(int);
    rbtree_iterator& operator--();
    rbtree_iterator operator--(int);
    bool operator==(const rbtree_iterator& lhs);
    bool operator!=(const rbtree_iterator& lhs);

   private:
    friend class rbtree;
    node* current_;
  };

  using iterator = rbtree_iterator;

  rbtree() noexcept;
  rbtree(node* node);
  rbtree(const std::initializer_list<value_type>& items);
  rbtree(const rbtree& other) noexcept;
  rbtree(rbtree&& other) noexcept;
  void swap(rbtree<K, T>&& other);
  void swap(rbtree<K, T>& other);
  ~rbtree();

  rbtree& operator=(const rbtree& other) noexcept;
  rbtree& operator=(rbtree&& other) noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;

  std::pair<iterator, bool> insert(const value_type& value) noexcept;
  std::pair<iterator, bool> insert(const K& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const K& key, const T& obj);
  void erase(const value_type& value);
  void merge(rbtree& other);
  T& at(const K& key);
  T& operator[](const K& key);
  bool contains(const K& key);
  size_type size();
  void print_tree() { print_tree(m_root, 0); }
  void clear();

 private:
  void rotate_left(node* pos);
  void rotate_right(node* pos);
  void insert(const value_type& value, iterator& iter, bool& inserted);
  void insert_node(node* temp, iterator& iter, bool& inserted);
  node* find_node(const K& key);
  void clear(node* node);
  node* copy_tree(node* node);
  void transfer_node(node* deleted_node, node* inserted_node) noexcept;
  bool is_leaf(node* n);
  void set_new_grandfather(node* parent, node* uncle, node* grandfather,
                           node*& pos);
  node* minimum(node* n);
  node* maximum(node* n);
  node* sibling(node* n);
  void fix_insertion(node* pos);
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
    print_tree(current->right_, depth + 1);
    std::cout << std::setw(depth * 4) << "";
    std::cout << (current->mColor == 'R' ? "R" : "B") << current->value_.first
              << std::endl;
    print_tree(current->left_, depth + 1);
  }

 private:
  node* m_root;
  size_type m_size;
};

template <typename K, typename T>
inline rbtree<K, T>::rbtree_iterator::rbtree_iterator() noexcept
    : current_(nullptr) {}

template <typename K, typename T>
inline rbtree<K, T>::rbtree_iterator::rbtree_iterator(node* node) noexcept
    : current_(node) {}

template <typename K, typename T>
inline typename rbtree<K, T>::reference
rbtree<K, T>::rbtree_iterator::operator*() const {
  return current_->value_;
}

template <typename K, typename T>
inline typename rbtree<K, T>::pointer
rbtree<K, T>::rbtree_iterator::operator->() const {
  return &(current_->value_);
}

template <typename K, typename T>
inline typename rbtree<K, T>::rbtree_iterator&
rbtree<K, T>::rbtree_iterator::operator++() {
  if (current_ != nullptr) {
    if (current_->right_) {
      current_ = current_->right_;
      while (current_->left_) {
        current_ = current_->left_;
      }
    } else {
      node* temp = current_->parent_;
      while (temp != nullptr && current_ == temp->right_) {
        current_ = temp;
        temp = temp->parent_;
      }
      current_ = temp;
    }
  }
  return *this;
}

template <typename K, typename T>
inline typename rbtree<K, T>::rbtree_iterator
rbtree<K, T>::rbtree_iterator::operator++(int) {
  rbtree_iterator temp(current_);
  ++(*this);
  return temp;
}

template <typename K, typename T>
inline typename rbtree<K, T>::rbtree_iterator&
rbtree<K, T>::rbtree_iterator::operator--() {
  if (current_ != nullptr) {
    if (current_->left_) {
      current_ = current_->left_;
      while (current_->right_) {
        current_ = current_->right_;
      }
    } else {
      node* temp = current_->parent_;
      while (temp != nullptr && current_ == temp->left_) {
        current_ = temp;
        temp = temp->parent_;
      }
      current_ = temp;
    }
  }
  return *this;
}

template <typename K, typename T>
inline typename rbtree<K, T>::rbtree_iterator
rbtree<K, T>::rbtree_iterator::operator--(int) {
  rbtree_iterator temp(current_);
  --(*this);
  return temp;
}

template <typename K, typename T>
inline bool rbtree<K, T>::rbtree_iterator::operator==(
    const rbtree_iterator& lhs) {
  return this->current_ == lhs.current_;
}

template <typename K, typename T>
inline bool rbtree<K, T>::rbtree_iterator::operator!=(
    const rbtree_iterator& lhs) {
  return this->current_ != lhs.current_;
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
    : m_root(copy_tree(other.m_root)), m_size(other.m_size) {}

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
  if (node != nullptr) {
    clear(node->left_);
    clear(node->right_);
    delete node;
  }
}

template <typename K, typename T>
inline typename rbtree<K, T>::node* rbtree<K, T>::copy_tree(node* node) {
  rbtree_node* temp = nullptr;
  if (node != nullptr) {
    temp = new rbtree_node(node->value_);
    temp->mColor = node->mColor;
    temp->left_ = copy_tree(node->left_);
    temp->right_ = copy_tree(node->right_);
    temp->parent_ = node->parent_;
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
  return iterator(minimum(m_root));
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
    if (current->value_.first == key) {
      flag = true;
    } else if (key < current->value_.first) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  return current;
}

template <typename K, typename T>
inline void rbtree<K, T>::rotate_left(node* pos) {
  node* pivot = pos->right_;

  if (pos->parent_ != nullptr) {
    pivot->parent_ = pos->parent_;

    if (pos->parent_->left_ == pos)
      pos->parent_->left_ = pivot;
    else
      pos->parent_->right_ = pivot;
  } else {
    m_root = pivot;
    pivot->parent_ = nullptr;
  }

  pos->right_ = pivot->left_;
  if (pivot->left_ != nullptr) pivot->left_->parent_ = pos;

  pos->parent_ = pivot;
  pivot->left_ = pos;
}

template <typename K, typename T>
inline void rbtree<K, T>::rotate_right(node* pos) {
  node* pivot = pos->left_;

  if (pos->parent_ != nullptr) {
    pivot->parent_ = pos->parent_;
    if (pos->parent_->left_ == pos) {
      pos->parent_->left_ = pivot;
    } else {
      pos->parent_->right_ = pivot;
    }
  } else {
    m_root = pivot;
    pivot->parent_ = nullptr;
  }

  pos->left_ = pivot->right_;
  if (pivot->right_ != nullptr) {
    pivot->right_->parent_ = pos;
  }

  pos->parent_ = pivot;
  pivot->right_ = pos;
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
    n->value_.second = obj;
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
    if (temp->value_.first < begin->value_.first) {
      begin = begin->left_;
    } else if (temp->value_.first > begin->value_.first) {
      begin = begin->right_;
    } else if (temp->value_.first == begin->value_.first) {
      inserted = false;
      iter = iterator(begin);
      flag = true;
    }
  }
  if (!flag) {
    temp->parent_ = begin_parent;
    if (temp->value_.first < begin_parent->value_.first) {
      std::cout << temp->parent_->value_.first << std::endl;

      begin_parent->left_ = temp;
    } else {
      begin_parent->right_ = temp;
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
    temp->parent_ = nullptr;
    iter = iterator(temp);
    inserted = true;
  } else {
    insert_node(temp, iter, inserted);
  }
  if (inserted) {
    fix_insertion(temp);
    ++m_size;
  } else {
    delete temp;
  }
}

template <typename K, typename T>
inline typename rbtree<K, T>::node* rbtree<K, T>::sibling(node* n) {
  node* parent = n->parent_;
  node* sibling = nullptr;
  if (n == parent->left_) {
    sibling = parent->right_;
  } else {
    sibling = parent->left_;
  }
  return sibling;
}

template <typename K, typename T>
inline void rbtree<K, T>::erase(const value_type& value) {
  node* find = find_node(value.first);
  node* child = nullptr;
  node* successor = find;
  if (find->left_) {
    successor = maximum(find->left_);
  } else if (find->right_) {
    successor = minimum(find->right_);
  }
  if (successor != find) {
    transfer_node(find, successor);
    if (!successor->parent_) {
      m_root = successor;
      m_root->mColor = 'B';
    }
    successor = find;
  }
  child = (successor->left_ != nullptr) ? successor->left_ : successor->right_;
  if (successor->mColor == 'B') {
    if (!child) {
      delete_case1(successor);
    } else {
      child->parent_ = successor->parent_;
      if (successor->parent_->left_ == successor) {
        successor->parent_->left_ = child;
      } else {
        successor->parent_->right_ = child;
      }
      printf("here\n");
      if (child->mColor == 'R') {
        child->mColor = 'B';
      } else {
        delete_case1(child);
      }
    }
  }
  if (successor->parent_) {
    if (successor->parent_->left_ == successor) {
      successor->parent_->left_ = nullptr;
    } else {
      successor->parent_->right_ = nullptr;
    }
    successor->parent_ = nullptr;
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
  char tmpColor = source->mColor;
  source->mColor = target->mColor;
  target->mColor = tmpColor;

  node* tempNode = source->left_;
  source->left_ = target->left_;
  if (target->left_) {
    target->left_->parent_ = source;
  }
  target->left_ = tempNode;
  if (tempNode) {
    tempNode->parent_ = target;
  }
  tempNode = source->right_;
  source->right_ = target->right_;
  if (target->right_) {
    target->right_->parent_ = source;
  }
  target->right_ = tempNode;
  if (tempNode) {
    tempNode->parent_ = target;
  }

  if (source->parent_) {
    if (source->parent_->left_ == source) {
      source->parent_->left_ = target;
    } else {
      source->parent_->right_ = target;
    }
  }

  if (target->parent_) {
    if (target->parent_->left_ == target) {
      target->parent_->left_ = source;
    } else {
      target->parent_->right_ = source;
    }
  }

  tempNode = source->parent_;
  source->parent_ = target->parent_;
  target->parent_ = tempNode;
}

template <typename K, typename T>
inline void rbtree<K, T>::replace_node(node* old_node,
                                       node* new_node) noexcept {
  if (new_node) {
    new_node->parent_ = old_node->parent_;
  }

  if (old_node == old_node->parent_->left_) {
    old_node->parent_->left_ = new_node;
  } else {
    old_node->parent_->right_ = new_node;
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case1(node* n) {
  if (n->parent_) {
    delete_case2(n);
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case2(node* find) {
  node* s = sibling(find);
  if (s && s->mColor == 'R') {
    find->parent_->mColor = 'R';
    s->mColor = 'B';
    if (find == find->parent_->left_) {
      rotate_left(find->parent_);
    } else {
      rotate_right(find->parent_);
    }
  }
  delete_case3(find);
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case3(node* find) {
  node* s = sibling(find);
  if (s && find->parent_->mColor == 'B' && s->mColor == 'B' &&
      (!s->left_ || s->left_->mColor == 'B') &&
      (!s->right_ || s->right_->mColor == 'B')) {
    s->mColor = 'R';
    delete_case1(find->parent_);
  } else {
    delete_case4(find);
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case4(node* n) {
  node* s = sibling(n);
  if (s && n->parent_->mColor == 'R' && (s->mColor == 'B') &&
      (!s->left_ || s->left_->mColor == 'B') &&
      (!s->right_ || s->right_->mColor == 'B')) {
    s->mColor = 'R';
    n->parent_->mColor = 'B';
  } else {
    delete_case5(n);
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case5(node* n) {
  node* s = sibling(n);

  if (s && s->mColor == 'B') {
    if ((n == n->parent_->left_) && (!s->right_ || s->right_->mColor == 'B') &&
        (!s->left_ || s->left_->mColor == 'R')) {
      s->mColor = 'R';
      s->left_->mColor = 'B';
      rotate_right(s);
    } else if ((n == n->parent_->right_) && (s->left_->mColor == 'B') &&
               (s->right_->mColor == 'R')) {
      s->mColor = 'R';
      s->right_->mColor = 'B';
      rotate_left(s);
    }
  }
  delete_case6(n);
}

template <typename K, typename T>
inline void rbtree<K, T>::delete_case6(node* n) {
  node* s = sibling(n);
  s->mColor = n->parent_->mColor;
  n->parent_->mColor = 'B';
  if (n == n->parent_->left_) {
    s->right_->mColor = 'B';
    rotate_left(n->parent_);
  } else {
    s->left_->mColor = 'B';
    rotate_right(n->parent_);
  }
}

template <typename K, typename T>
inline bool rbtree<K, T>::is_leaf(node* n) {
  return (n != nullptr && n->left_ == nullptr && n->right_ == nullptr);
}

template <typename K, typename T>
typename rbtree<K, T>::node* rbtree<K, T>::minimum(node* n) {
  if (n != nullptr) {
    while (n->left_ != nullptr) {
      n = n->left_;
    }
  }
  return n;
}

template <typename K, typename T>
inline typename rbtree<K, T>::node* rbtree<K, T>::maximum(node* n) {
  while (n->right_) {
    n = n->right_;
  }
  return n;
}

template <typename K, typename T>
inline void rbtree<K, T>::fix_insertion(node* pos) {
  if (pos == m_root) {
    pos->mColor = 'B';
  } else {
    node* parent = pos->parent_;

    while (parent->mColor == 'R') {
      node* grandfather = parent->parent_;
      if (parent == grandfather->left_) {
        node* uncle = grandfather->right_;
        if (uncle != nullptr && uncle->mColor == 'R') {
          set_new_grandfather(parent, uncle, grandfather, pos);
        } else {
          if (pos == parent->right_) {
            pos = parent;
            rotate_left(pos);
          }
          parent->mColor = 'B';
          grandfather->mColor = 'R';
          rotate_right(grandfather);
        }
      } else {  // if father is right child
        node* uncle = grandfather->left_;
        if (uncle != nullptr && uncle->mColor == 'R') {
          set_new_grandfather(parent, uncle, grandfather, pos);
        } else {
          if (pos == parent->left_) {
            pos = parent;
            rotate_right(pos);
          }
          parent->mColor = 'B';
          grandfather->mColor = 'B';
          rotate_left(grandfather);
        }
      }
    }
    m_root->mColor = 'B';
  }
}

template <typename K, typename T>
inline void rbtree<K, T>::set_new_grandfather(rbtree<K, T>::node* parent,
                                              rbtree<K, T>::node* uncle,
                                              rbtree<K, T>::node* grandfather,
                                              rbtree<K, T>::node*& pos) {
  parent->mColor = 'B';
  uncle->mColor = 'B';
  grandfather->mColor = 'R';
  pos = grandfather;
}

template <typename K, typename T>
inline T& rbtree<K, T>::at(const K& key) {
  node* node = find_node(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found in the tree");
  }
  return node->value_.second;
}

template <typename K, typename T>
inline T& rbtree<K, T>::operator[](const K& key) {
  node* node = find_node(key);
  if (node == nullptr) {
    insert(key, T());
    node = find_node(key);
  }
  return node->value_.second;
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
