#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <cmath>
#include <initializer_list>
#include <typeinfo>

namespace s21 {
template <class T>
class vector {
 public:
  /*---------- VECTOR MEMBER TYPE ----------*/
  using value_type = T;   // type of an element (T is template parameter)
  using reference = T &;  // type of the reference to an element
  using const_reference = const T &;  // type of the constant reference
  using iterator = T *;  // type for iterating through the container
  using const_iterator =
      const T *;  // constant type for iterating through the container
  using size_type =
      size_t;  // type of the container size (standard type is size_t)

 private:
  size_type m_size_;
  size_type m_capacity_;
  value_type *arr_;

 public:
  /*---------- VECTOR MEMBER FUNCTIONS ----------*/
  // default constructor, creates empty vector
  vector();
  // parameterized constructor, creates the vector of size n
  explicit vector(size_type n);
  /* initializer list constructor, creates vector initizialized using
  std::initializer_list */
  // cppcheck ругается на отсутствие explicit
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);  // copy constructor
  vector(vector &&v);       // move constructor
  ~vector();                // destructor
  // assignment operator overload for copying object
  vector &operator=(std::initializer_list<value_type> const &items);
  // assignment operator overload for copying object
  vector &operator=(vector &v);
  // assignment operator overload for moving object
  vector &operator=(vector &&v);

  /*---------- VECTOR ELEMENT ACCESS ----------*/
  reference at(size_type pos);  // access specified element with bounds checking
  reference operator[](size_type pos);  // access specified element
  const_reference front();              // access the first element
  const_reference back();               // access the last element
  value_type *data();                   // direct access to the underlying array

  /*---------- VECTOR ITERATORS ----------*/
  iterator begin();  // returns an iterator to the beginning
  iterator end();    // returns an iterator to the end

  /*---------- VECTOR CAPACITY ----------*/
  bool empty();          // checks whether the container is empty
  size_type size();      // returns the number of elements
  size_type max_size();  // returns the maximum possible number of elements
  /* allocate storage of size elements and copies current array elements to a
  newely allocated array */
  void reserve(size_type size);
  /* returns the number of elements that can be held in currently allocated
  storage */
  size_type capacity();
  void shrink_to_fit();  // reduces memory usage by freeing unused memory

  /*---------- VECTOR MODIFIERS ----------*/
  void clear();  // clears the contents
  /* inserts elements into concrete pos and returns the iterator that points to
  the new element */
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);               // erases element at pos
  void push_back(const_reference value);  // adds an element to the end
  void pop_back();                        // removes the last element
  void swap(vector &other);               // swaps the contents

  /*---------- VECTOR ITERATORS ----------*/
  // Inserts new elements into the container directly before pos.
  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  // Appends new elements to the end of the container.
  template <class... Args>
  void insert_many_back(Args &&...args);
};
}  // namespace s21

/*********************************************************************/

template <class T>
s21::vector<T>::vector() : m_size_(0), m_capacity_(0), arr_(nullptr) {}

template <class T>
s21::vector<T>::vector(size_type n) : m_size_(n), m_capacity_(n) {
  if (n > this->max_size())  // подача отрицательного n - переполнение
    throw std::length_error("cannot create s21::vector larger than max_size()");
  if (typeid(value_type) ==
      typeid(
          bool &))  // bool выделяет блоками, кратными машинному слову системы
    m_capacity_ =
        n / __WORDSIZE * __WORDSIZE + ((n % __WORDSIZE) > 0 ? __WORDSIZE : 0);
  arr_ = new value_type[m_capacity_]{};
}

template <class T>
s21::vector<T>::vector(std::initializer_list<value_type> const &items)
    : m_size_(items.size()), m_capacity_(items.size()) {
  if (typeid(value_type) ==
      typeid(
          bool &))  // bool выделяет блоками, кратными машинному слову системы
    m_capacity_ = m_size_ / __WORDSIZE * __WORDSIZE +
                  ((m_size_ % __WORDSIZE) > 0 ? __WORDSIZE : 0);
  arr_ = new value_type[m_capacity_]{};
  for (size_type i = 0; i < m_size_; ++i) {
    arr_[i] = items.begin()[i];
  }
}

template <class T>
s21::vector<T>::vector(const vector &v)
    : m_size_(v.m_size_),
      m_capacity_(v.m_capacity_),
      arr_(new value_type[v.m_capacity_]{}) {
  for (size_type i = 0; i < m_size_; ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <class T>
s21::vector<T>::vector(vector &&v)
    : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr_(v.arr_) {
  v.arr_ = nullptr;
  v.m_size_ = 0;
  v.m_capacity_ = 0;
}

template <class T>
s21::vector<T>::~vector() {
  m_capacity_ = 0;
  m_size_ = 0;
  delete[] arr_;
  arr_ = nullptr;
}

/*
  Лист инициализации переопределяет размеры вектора. size меняется всегда под
  кол-во поданных элементов, а capacity изменяется в зависимости от того,
  хватает памяти или нет
*/
template <class T>
typename s21::vector<T> &s21::vector<T>::operator=(
    std::initializer_list<value_type> const &items) {
  m_size_ = items.size();
  if (m_capacity_ <= items.size()) {  // if capacity of vector is < than list,
                                      // then alloc new memory
    delete[] arr_;
    m_capacity_ = items.size();
    arr_ = new T[m_capacity_]{};
  }
  for (size_t i = 0; i < m_size_; i++) {
    arr_[i] = items.begin()[i];
  }
  return *this;
}

template <class T>
typename s21::vector<T> &s21::vector<T>::operator=(vector &v) {
  if (&v != this) {
    delete[] arr_;
    m_size_ = v.size();
    m_capacity_ = v.capacity();
    arr_ = new T[m_capacity_]{};
    for (size_t i = 0; i < m_size_; i++) {
      arr_[i] = v[i];
    }
  }
  return *this;
}

// idk what to write, it's 1:43 31st october 2024
// i finished it at 22:48 on 8th november 2024
template <class T>
typename s21::vector<T> &s21::vector<T>::operator=(vector &&v) {
  if (&v != this) {
    m_size_ = v.m_size_;
    m_capacity_ = v.m_capacity_;
    delete[] arr_;
    arr_ = v.arr_;

    v.arr_ = nullptr;
    v.m_capacity_ = 0;
    v.m_size_ = 0;
  }
  return *this;
}

template <class T>
typename s21::vector<T>::reference s21::vector<T>::at(size_type pos) {
  if (pos > m_size_) {
    throw std::out_of_range("Index pos >= this->size()");
  }
  return arr_[pos];
}

template <class T>
typename s21::vector<T>::reference s21::vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <class T>
typename s21::vector<T>::const_reference s21::vector<T>::front() {
  return arr_[0];
}

template <class T>
typename s21::vector<T>::const_reference s21::vector<T>::back() {
  return arr_[m_size_ - 1];
}

template <class T>
typename s21::vector<T>::value_type *s21::vector<T>::data() {
  return arr_;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::begin() {
  return (iterator)(arr_);
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::end() {
  return (iterator)(arr_ + m_size_);
}

template <class T>
bool s21::vector<T>::empty() {
  return (m_size_ == 0) ? true : false;
}

template <class T>
typename s21::vector<T>::size_type s21::vector<T>::size() {
  return m_size_;
}

template <class T>
typename s21::vector<T>::size_type s21::vector<T>::max_size() {
  size_type reserve_size = 1;
  if (typeid(value_type) == typeid(bool &)) reserve_size = 64;
  return (((powl(2, __WORDSIZE) / sizeof(value_type)) / 2 - reserve_size));
}

template <class T>
void s21::vector<T>::reserve(size_type size) {
  if (size > this->max_size())  // подача отрицательного n - переполнение
    throw std::length_error("vector::reserve");

  // увеличиваем, только если подали больше т.к. иначе нет смысла
  if (size >= this->m_capacity_) {
    s21::vector<value_type> temp(size);
    temp.m_size_ = 0;
    for (size_type i = 0; i < m_size_; ++i, ++temp.m_size_) {
      temp[i] = this->arr_[i];
    }
    this->swap(temp);
  }
}

template <class T>
typename s21::vector<T>::size_type s21::vector<T>::capacity() {
  return m_capacity_;
}

template <class T>
void s21::vector<T>::shrink_to_fit() {
  s21::vector<value_type> temp(m_size_);
  for (size_type i = 0; i < m_size_; ++i) {
    temp[i] = value_type(arr_[i]);
  }
  this->swap(temp);
}

template <class T>
void s21::vector<T>::clear() {
  if (typeid(value_type) == typeid(bool &))
    m_capacity_ = m_size_ / __WORDSIZE * __WORDSIZE +
                  ((m_size_ % __WORDSIZE) > 0 ? __WORDSIZE : 0);
  m_size_ = 0;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::insert(
    iterator pos, const_reference value) {
  size_type point = std::distance(begin(), pos);
  if (m_capacity_ == 0)
    reserve(1);
  else if (m_size_ == m_capacity_)
    reserve(m_capacity_ * 2);
  for (size_t i = m_size_; i > point; i--) {
    arr_[i] = arr_[i - 1];
  }
  arr_[point] = value;
  ++m_size_;
  return (iterator)(arr_ + point);
}

template <class T>
void s21::vector<T>::erase(iterator pos) {
  size_type point = std::distance(begin(), pos);
  for (size_type i = point; m_size_ > 0 && i < m_size_ - 1; ++i) {
    arr_[i] = arr_[i + 1];
  }
  --m_size_;
}

template <class T>
void s21::vector<T>::push_back(const_reference value) {
  this->insert(this->end(), value);
}

template <class T>
void s21::vector<T>::pop_back() {
  this->erase(this->end());
}

template <class T>
void s21::vector<T>::swap(vector &other) {
  s21::vector<value_type> temp(*this);
  *this = std::move(other);
  other = std::move(temp);
}

template <class T>
template <class... Args>
typename s21::vector<T>::iterator s21::vector<T>::insert_many(
    const_iterator pos, Args &&...args) {
  iterator iter = const_cast<iterator>(pos);
  size_type point = std::distance(begin(), iter);
  size_type i = 0;
  for (auto temp : {args...}) {
    insert(iter + i, temp);
    ++i;
    iter = this->begin() + point;
  }
  return iter;
}

template <class T>
template <class... Args>
void s21::vector<T>::insert_many_back(Args &&...args) {
  insert_many(this->end(), args...);
}

#endif