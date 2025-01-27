#include <algorithm>
template <typename T>
class rbtree {
 public:
  struct rbtree_node : {
    typedef rbtree_node this_type;

    rbtree_node(const T& value)
        : value_(value),
          node_right_(nullptr),
          node_left_(nullptr),
          node_parent_(nullptr),
          mColor('R') {}
    this_type* node_right_;
    this_type* node_left_;
    this_type* node_parent_;
    char mColor;
    T value_;
  };

  using node = rbtree_node;
  using reference = T&;
  using const_reference = const T&;

  struct rbtree_iterator {
   public:
    rbtree_iterator() noexcept;
    rbtree_iterator(node* node) noexcept;
    reference operator*() const;
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
  rbtree(const rbtree& other) noexcept;
  rbtree(rbtree&& other) noexcept;
  ~rbtree();
  void clear(node* node);
  node* copy_tree(node* node);
  rbtree& operator=(const rbtree& other) noexcept;
  rbtree& operator=(rbtree&& other) noexcept;

  void rotate_left(node* pos);
  void rotate_right(node* pos);
  void insert(const T& value);
  void remove(const T& value);
  void fix_insertion(node* pos);
  void fix_removing(node* pos);

 private:
  node* m_root;
};

template <typename T>
inline rbtree<T>::rbtree_iterator::rbtree_iterator() noexcept
    : current_(nullptr) {}

template <typename T>
inline rbtree<T>::rbtree_iterator::rbtree_iterator(node* node) noexcept
    : current_(node) {}

template <typename T>
inline rbtree<T>::reference rbtree<T>::rbtree_iterator::operator*() const {
  return current_->value;
}

template <typename T>
inline rbtree<T>::rbtree_iterator& rbtree<T>::rbtree_iterator::operator++() {
  if (current_ != nullptr) {
    if (current_->node_right_) {
      current_ = current_->node_right_;
      while (current_->node_left_) {
        current_ = current_->node_left_;
      }
    } else {
      node* temp = current_->node_parent_;
      while (current_ == temp->node_right_) {
        current_ = temp;
        temp = current_->node_parent_;
      }
      if (current_->node_right_ != temp) {
        current_ = temp;
      }
    }
  }
  return *this;
}

template <typename T>
inline rbtree<T>::rbtree_iterator rbtree<T>::rbtree_iterator::operator++(int) {
  rbtree_iterator temp(current_);
  ++(*this);
  return temp;
}

template <typename T>
inline rbtree<T>::rbtree_iterator& rbtree<T>::rbtree_iterator::operator--() {
  if (current_ != nullptr) {
    if (current_->node_left_) {
      current_ = current_->node_left_;
      while (current_->node_right_) {
        current_ = current_->node_right_;
      }
    } else {
      node* temp = current_->node_parent_;
      while (current_ == temp->node_left_) {
        current_ = temp;
        temp = current_->node_parent_;
      }
      current_ = temp;
    }
  }
  return *this;
}

template <typename T>
inline rbtree<T>::rbtree_iterator rbtree<T>::rbtree_iterator::operator--(int) {
  rbtree_iterator temp(current_);
  --(*this);
  return temp;
}

template <typename T>
inline bool rbtree<T>::rbtree_iterator::operator==(const rbtree_iterator& lhs) {
  return this->current_ == lhs.current_;
}

template <typename T>
inline bool rbtree<T>::rbtree_iterator::operator!=(const rbtree_iterator& lhs) {
  return this->current_ != lhs.current_;
}

template <typename T>
inline rbtree<T>::rbtree() noexcept : m_root(nullptr) {}

template <typename T>
inline rbtree<T>::rbtree(node* node) : m_root(node) {}

template <typename T>
inline rbtree<T>::rbtree(const rbtree& other) noexcept
    : m_root(copy_tree(other.m_root)) {}

template <typename T>
inline rbtree<T>::rbtree(rbtree&& other) noexcept : m_root(nullptr) {
  std::swap(m_root, other.m_root);
}

template <typename T>
inline rbtree<T>::~rbtree() {
  clear(m_root);
}

template <typename T>
inline void rbtree<T>::clear(node* node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename T>
inline rbtree<T>::node* rbtree<T>::copy_tree(node* node) {
  rbtree_node* temp = nullptr;
  if (node != nullptr) {
    temp = new rbtree_node(node->value_);
    temp->mColor = node->mColor;
    temp->node_left_ = copy_tree(node->node_left_);
    temp->node_right_ = copy_tree(node->node_right_);
    temp->node_parent_ = node->node_parent_;
  }
  return temp;
}

template <typename T>
inline rbtree<T>& rbtree<T>::operator=(const rbtree& other) noexcept {
  if (this != &other) {
    rbtree temp(other);
    clear(m_root);
    std::swap(this->m_root, temp.m_root);
  }
  return *this;
}

template <typename T>
inline rbtree<T>& rbtree<T>::operator=(rbtree&& other) noexcept {
  if (this != &other) {
    std::swap(m_root, other.m_root);
  }
  return *this;
}

template <typename T>
inline void rbtree<T>::rotate_left(node* pos) {
  node* pivot = pos->node_right_;

  pivot->node_parent_ = pos->node_parent_; /* при этом, возможно, pivot
                                              становится корнем дерева */
  if (pos->node_parent_ != nullptr) {
    if (pos->node_parent_->node_left_ == pos)
      pos->node_parent_->node_left_ = pivot;
    else
      pos->node_parent_->node_right_ = pivot;
  }

  pos->node_right_ = pivot->node_left_;
  if (pivot->node_left_ != nullptr) pivot->node_left_->node_parent_ = pos;

  pos->node_parent_ = pivot;
  pivot->node_left_ = pos;
}

template <typename T>
inline void rbtree<T>::rotate_right(node* pos) {
  node* pivot = pos->node_left_;
  pivot->node_parent_ = pos->node_parent_; /* при этом, возможно, pivot
                                              становится корнем дерева */
  if (pos->node_parent_ != nullptr) {
    if (pos->node_parent_->node_left_ == pos)
      pos->node_parent_->node_left_ = pivot;
    else
      pos->node_parent_->node_right_ = pivot;
  }

  pos->node_left_ = pivot->node_right_;
  if (pivot->node_right_ != nullptr) pivot->node_right_->node_parent_ = pos;

  pos->node_parent_ = pivot;
  pivot->node_right_ = pos;
}

template <typename T>
inline void rbtree<T>::insert(const T& value) {
  node* temp = new node(value);
  if (m_root == nullptr) {
    m_root = temp;
    temp->node_parent_ = nullptr;
  } else {
    node* begin = m_root;
    node* begin_parent = nullptr;
    while (begin != nullptr) {
      begin_parent = begin;
      if (begin->value_ < temp->value_) {
        begin = begin->node_right_;
      } else {
        begin = begin->node_left_;
      }
      begin->node_parent_ = begin_parent;
      if (begin_parent->value_ < temp->value_) {
        begin_parent->node_right_ = temp;
      } else {
        begin->node_left_ = temp;
      }
    }
  }
  fix_insertion(temp);
}

template <typename T>
inline void rbtree<T>::remove(const T& value) {
	
}

template <typename T>
inline void rbtree<T>::fix_insertion(node* pos) {
  if (pos == m_root) {
    pos->mColor = 'B';
  } else {
    while (pos->node_parent_->mColor == 'R') {
      node* parent = pos->node_parent_;
      node* grandfather = parent->node_parent_;
      if (pos->node_parent_ == grandfather->node_left_) {
        node* uncle = grandfather->node_right_;
        if (uncle != nullptr && uncle->mColor == 'R') {
          parent->mColor = 'B';
          uncle->mColor = 'B';
          grandfather->mColor = 'R';
          pos = grandfather;
        } else {
          if (pos == parent->node_right_) {
            pos = parent;
            rotate_left(pos);
          }
          parent->mColor = 'B';
          grandfather->mColor = 'R';
          rotate_right(grandfather);
        }
      } else {  // if father is right child
        node* uncle = grandfather->node_left_;
        if (uncle != nullptr && uncle->mColor == 'R') {
          parent->mColor = 'B';
          uncle->mColor = 'B';
          grandfather->mColor = 'R';
          pos = grandfather;
        } else {
          if (pos == parent->node_left_) {
            pos = parent;
            rotate_right(pos);
          }
          parent->mColor = 'B';
          grandfather->mColor = 'B';
          rotate_right(grandfather);
        }
      }
    }
    m_root->mColor = 'B';
  }
}
