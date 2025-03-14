#pragma once
#include <initializer_list>
#include <stdexcept>
namespace s21 {
template <typename T>
class list {
 private:
  struct Node {
    Node() = default;
    Node(const T &value, Node *next = nullptr, Node *prev = nullptr)
        : value_(value), next_(next), prev_(prev) {}

    T value_;
    Node *next_ = nullptr;
    Node *prev_ = nullptr;
  };

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class ListIterator {
   public:
    ListIterator() noexcept;
    ListIterator(Node *node) noexcept;

    reference operator*() const;
    ListIterator &operator++();
    ListIterator operator++(int);
    ListIterator &operator--();
    ListIterator operator--(int);
    bool operator==(const ListIterator &other) const;
    bool operator!=(const ListIterator &other) const;

   protected:
    friend class list;
    Node *current_;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(ListIterator other) : ListIterator(other) {}
    const_reference operator*() const;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;

  list() noexcept;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &other) noexcept;
  list(list &&other) noexcept;
  ~list();
  void update_end();

  size_type size() const noexcept;
  size_type max_size() const noexcept;

  bool empty();
  void copy(const list &l);
  void swap(list &l);
  list &operator=(const list &l) noexcept;
  list &operator=(list &&l) noexcept;

  void clear();
  iterator insert(iterator pos, const_reference value);
  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);
  void push_back(const_reference data) noexcept;
  void pop_back();
  void push_front(const_reference value) noexcept;
  void pop_front();
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void sort();
  void reverse() noexcept;
  void unique();
  void erase(iterator pos);
  const_reference front();
  const_reference back();

 private:
  Node *m_head;
  Node *m_tail;
  size_type m_size;
  Node *m_end;
};
}  // namespace s21

template <typename T>
s21::list<T>::ListIterator::ListIterator() noexcept : current_(nullptr) {}

template <typename T>
s21::list<T>::ListIterator::ListIterator(Node *node) noexcept
    : current_(node) {}

template <typename T>
typename s21::list<T>::reference s21::list<T>::ListIterator::operator*() const {
  return current_->value_;
};

template <typename T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator++() {
  current_ = current_->next_;
  return *this;
}

template <typename T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator++(
    int) {
  ListIterator temp(current_);
  current_ = current_->next_;
  return temp;
}

template <typename T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator--() {
  current_ = current_->prev_;
  return *this;
}

template <typename T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator--(
    int) {
  ListIterator temp(current_);
  current_ = current_->prev_;
  return temp;
}

template <typename T>
bool s21::list<T>::ListIterator::operator==(
    const s21::list<T>::ListIterator &other) const {
  return current_ == other.current_;
}

template <typename T>
bool s21::list<T>::ListIterator::operator!=(const ListIterator &other) const {
  return !(*this == other);
}

template <typename T>
typename s21::list<T>::const_reference
s21::list<T>::ListConstIterator::operator*() const {
  return this->current_->value_;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() noexcept {
  return iterator(m_head ? this->m_head : this->m_end);
}

template <typename T>
typename s21::list<T>::const_iterator s21::list<T>::cbegin() const noexcept {
  return const_iterator(m_head ? this->m_head : this->m_end);
}

template <class T>
typename s21::list<T>::iterator s21::list<T>::end() noexcept {
  return iterator(m_end);
}

template <typename T>
typename s21::list<T>::const_iterator s21::list<T>::cend() const noexcept {
  return const_iterator(m_end);
}

template <typename T>
s21::list<T>::list() noexcept : m_head(nullptr), m_tail(nullptr), m_size(0) {
  m_end = new Node(T());
  update_end();
}

template <typename T>
s21::list<T>::list(size_type n) : m_head(nullptr), m_tail(nullptr), m_size(n) {
  if (n == 0) throw std::out_of_range("Size must be greater than zero");
  m_end = new Node(T());
  for (size_type i = 0; i < n; i++) {
    push_back(value_type());
  }
  update_end();
}

template <typename T>
s21::list<T>::list(std::initializer_list<value_type> const &items)
    : m_head(nullptr), m_tail(nullptr), m_size(0) {
  m_end = new Node(T());
  for (value_type item : items) {
    push_back(item);
  }
  update_end();
}

template <typename T>
s21::list<T>::list(const list &other) noexcept
    : m_head(nullptr), m_tail(nullptr), m_size(0) {
  copy(other);
}

template <typename T>
s21::list<T>::list(list &&other) noexcept
    : m_head(nullptr), m_tail(nullptr), m_size(0), m_end(nullptr) {
  swap(other);
}

template <typename T>
void s21::list<T>::clear() {
  while (size() > 0) {
    pop_back();
  }
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
  Node *node = nullptr;
  Node *position = pos.current_;
  if (empty()) {
    node = new Node(value);
    m_head = node;
    m_tail = node;
    node->next_ = nullptr;
    node->prev_ = nullptr;
    ++m_size;
  } else {
    if (pos == begin()) {
      push_front(value);
    } else if (pos == end()) {
      push_back(value);
    } else {
      node = new Node(value);
      node->next_ = position;
      node->prev_ = position->prev_;
      if (position->prev_ != nullptr) {
        position->prev_->next_ = node;
      }
      position->prev_ = node;
      ++m_size;
    }
  }
  update_end();
  return iterator(node);
}

template <typename T>
void s21::list<T>::copy(const list &l) {
  Node *temp = l.m_head;
  while (temp) {
    push_back(temp->value_);
    temp = temp->next_;
  }
  update_end();
}

template <typename T>
bool s21::list<T>::empty() {
  return m_size == 0;
}

template <typename T>
s21::list<T>::~list() {
  clear();
  delete m_end;
}

template <typename T>
void s21::list<T>::update_end() {
  if (m_end) {
    if (m_tail) {
      m_end->prev_ = m_tail;
      m_tail->next_ = m_end;
    }
  }
}

template <typename value_type>
void s21::list<value_type>::swap(list &l) {
  std::swap(m_head, l.m_head);
  std::swap(m_tail, l.m_tail);
  std::swap(m_size, l.m_size);
  std::swap(m_end, l.m_end);
}

template <typename T>
s21::list<T> &s21::list<T>::operator=(const list &l) noexcept {
  if (this != &l) {
    list<T> temp(l);
    clear();
    swap(temp);
  }
  return *this;
}

template <typename T>
s21::list<T> &s21::list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::size() const noexcept {
  return m_size;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

template <typename T>
void s21::list<T>::push_back(const_reference data) noexcept {
  Node *node = new Node(data, nullptr, m_tail);
  if (m_tail) {
    m_tail->next_ = node;
  }
  m_tail = node;
  if (!m_head) {
    m_head = node;
  }
  update_end();
  ++m_size;
}

template <typename T>
void s21::list<T>::pop_back() {
  if (size() == 0) throw std::out_of_range("Empty list!");
  Node *last_node = m_tail;
  if (m_size == 1) {
    m_head = nullptr;
    m_tail = nullptr;
  } else {
    m_tail = last_node->prev_;
    m_tail->next_ = nullptr;
  }
  delete last_node;
  m_size--;
  update_end();
}

template <typename T>
void s21::list<T>::push_front(const_reference value) noexcept {
  Node *data = new Node(value, m_head, nullptr);
  if (m_head) {
    m_head->prev_ = data;
  } else {
    m_tail = data;
  }
  m_head = data;
  update_end();
  ++m_size;
}

template <typename T>
void s21::list<T>::pop_front() {
  if (m_head == nullptr) throw std::out_of_range("Empty list!");
  Node *temp = m_head->next_;
  delete m_head;
  m_head = temp;
  if (m_head) {
    m_head->prev_ = nullptr;
  } else {
    m_end = nullptr;
  }
  --m_size;
}

template <typename T>
void s21::list<T>::merge(list &other) {
  if (this != &other) {
    if (!empty() && !other.empty()) {
      iterator first(begin());
      iterator firstX(other.begin());
      const iterator last(end());
      const iterator lastX(other.end());
      while ((first != last) && (firstX != lastX)) {
        if (*firstX < *first) {
          insert(first, *firstX++);
        } else
          ++first;
      }
      while (firstX != lastX) insert(first, *firstX++);
    } else if (this->empty() && !other.empty()) {
      this->copy(other);
    }
    other.clear();
  }
}

template <typename T>
void s21::list<T>::splice(const_iterator pos, list &other) {
  iterator first = other.begin();
  while (first != other.end()) {
    insert(pos, *first++);
  }
  other.clear();
}

template <typename T>
void s21::list<T>::sort() {
  if (m_size > 1) {
    bool swapped;
    do {
      swapped = false;
      iterator it = begin();
      while (it != end()) {
        iterator next = it;
        ++next;
        if (next != end() && *it > *next) {
          std::swap(*it, *next);
          swapped = true;
        }
        ++it;
      }
    } while (swapped);
  }
}

template <typename T>
void s21::list<T>::reverse() noexcept {
  if (!empty()) {
    iterator first = begin();
    iterator last = --end();
    bool flag = false;
    while (first != last && !flag) {
      std::swap(*first, *last);
      ++first;
      if (first == last) {
        flag = true;
      }
      --last;
    }
  }
}

template <typename T>
void s21::list<T>::unique() {
  iterator it = begin();
  while (it != end()) {
    iterator next = it;
    ++next;
    if (next != end() && it.current_->value_ == next.current_->value_) {
      erase(next);
    } else {
      it = next;
    }
  }
}

template <typename T>
void s21::list<T>::erase(iterator pos) {
  Node *node = pos.current_;
  if (!empty() && node != m_end) {
    if (node == m_head) {
      pop_front();
    } else if (node == m_tail) {
      pop_back();
    } else {
      node->prev_->next_ = node->next_;
      node->next_->prev_ = node->prev_;
      delete node;
      --m_size;
    }
  }
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::front() {
  return m_head ? m_head->value_ : m_end->value_;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::back() {
  return m_tail ? m_tail->value_ : m_end->value_;
}

template <class T>
template <class... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(const_iterator pos,
                                                          Args &&...args) {
  for (const auto &arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <class T>
template <class... Args>
void s21::list<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}

template <class T>
template <class... Args>
void s21::list<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_front(arg);
  }
}