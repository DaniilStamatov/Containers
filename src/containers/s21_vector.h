#pragma once

#include <initializer_list>
#include <iostream>
#include <string>
#include <typeinfo>

namespace s21 {
template <typename T>
class vector {
 public:
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
  vector();  // default constructor, creates empty vector
  explicit vector(
      size_type n);  // parameterized constructor, creates the vector of size n
  vector(std::initializer_list<value_type> const
             &items);       // initializer list constructor, creates vector
                            // initizialized using std::initializer_list
  vector(const vector &v);  // copy constructor
  vector(vector &&v);       // move constructor
  ~vector();                // destructor
  vector &operator=(
      std::initializer_list<value_type> const
          &items);  // assignment operator overload for copying object
  vector &operator=(
      vector &v);  // assignment operator overload for copying object
  vector &operator=(
      vector &&v);  // assignment operator overload for moving object

  reference at(size_type pos);  // access specified element with bounds checking
  reference operator[](size_type pos);  // access specified element
  const_reference front();              // access the first element
  const_reference back();               // access the last element
  value_type *data();                   // direct access to the underlying array
  iterator begin();                     // returns an iterator to the beginning
  iterator end();                       // returns an iterator to the end
  bool empty();                         // checks whether the container is empty
  size_type size();                     // returns the number of elements
  size_type max_size();  // returns the maximum possible number of elements
  void reserve(
      size_type size);   // allocate storage of size elements and copies current
                         // array elements to a newely allocated array
  size_type capacity();  // returns the number of elements that can be held in
                         // currently allocated storage
  void shrink_to_fit();  // reduces memory usage by freeing unused memory
  void clear();          // clears the contents
  iterator insert(
      iterator pos,
      const_reference value);  // inserts elements into concrete pos and returns
                               // the iterator that points to the new element
  void erase(iterator pos);    // erases element at pos
  void push_back(const_reference value);  // adds an element to the end
  void pop_back();                        // removes the last element
  void swap(vector &other);               // swaps the contents
};
}  // namespace s21

/*********************************************************************/

template <typename T>
s21::vector<T>::vector() : m_size_(0), m_capacity_(0), arr_(nullptr) {}

template <typename T>
s21::vector<T>::vector(size_type n) : m_size_(n), m_capacity_(n) {
  if (n > this->max_size())  // подача отрицательного n - переполнение
    throw std::length_error("cannot create s21::vector larger than max_size()");
  if (typeid(value_type) ==
      typeid(bool &))  // bool выделяет блоками по 64 байта
    m_capacity_ = n / 64 * 64 + ((n % 64) > 0 ? 64 : 0);
  arr_ = new value_type[m_capacity_]{};
}

template <typename T>
s21::vector<T>::vector(std::initializer_list<value_type> const &items)
    : m_size_(items.size()),
      m_capacity_(items.size()),
      arr_(new T[items.size()]{}) {
  for (size_t i = 0; i < m_size_; i++) {
    arr_[i] = items.begin()[i];
  }
}

template <typename T>
s21::vector<T>::vector(const vector &v)
    : m_size_(v.m_size_),
      m_capacity_(v.m_capacity_),
      arr_(new T[v.m_capacity_]{}) {
  for (size_t i = 0; i < m_size_; i++) {
    arr_[i] = v.arr_[i];
  }
}

template <typename T>
s21::vector<T>::vector(vector &&v)
    : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr_(v.arr_) {
  v.arr_ = nullptr;
  v.m_size_ = 0;
  v.m_capacity_ = 0;
}

template <typename T>
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
template <typename T>
typename s21::vector<T> &s21::vector<T>::operator=(
    std::initializer_list<value_type> const &items) {
  m_size_ = items.size();
  if (m_capacity_ <= items.size()) {  // if capacity of vector is < than list,
                                      // than alloc new memory
    delete[] arr_;
    m_capacity_ = items.size();
    arr_ = new T[m_capacity_]{};
  }
  for (size_t i = 0; i < m_size_; i++) {
    arr_[i] = items.begin()[i];
  }
  return *this;
}

template <typename T>
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
template <typename T>
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

template <typename T>
typename s21::vector<T>::reference s21::vector<T>::at(size_type pos) {
  if (pos > m_capacity_) {
    throw std::out_of_range("Index pos >= this->size()");
  }
  // else if (pos < 0) {
  //   throw std::out_of_range("Index pos <= 0");
  // }
  return arr_[pos];
}

template <typename T>
typename s21::vector<T>::reference s21::vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T>
typename s21::vector<T>::const_reference s21::vector<T>::front() {
  return arr_[0];
}

template <typename T>
typename s21::vector<T>::const_reference s21::vector<T>::back() {
  return arr_[m_size_ - 1];
}

template <typename T>
typename s21::vector<T>::value_type *s21::vector<T>::data() {
  return arr_;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::begin() {
  return arr_;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::end() {
  return &(arr_[this->size()]);
}

template <typename T>
bool s21::vector<T>::empty() {
  return (m_size_ == 0) ? true : false;
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::size() {
  return m_size_;
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::max_size() {
  auto pow = [](size_type x) {
    size_type out = 2;
    for (size_type i = 1; i < x; i++) out *= 2;
    return out;
  };
  return pow(sizeof(void *) * 8 - 1) / (sizeof(T) * 8) * 8 - 1;
}

template <typename T>
void s21::vector<T>::reserve(size_type size) {
  if (size > this->max_size())  // подача отрицательного n - переполнение
    throw std::length_error("vector::reserve");

  // увеличиваем, только если подали больше т.к. иначе нет смысла
  if (size >= this->m_capacity_) {
    s21::vector<value_type> temp(size);
    temp.m_size_ = 0;
    for (size_type i = 0; i < m_size_; i++, temp.m_size_++) {
      temp[i] = this->arr_[i];
    }
    this->swap(temp);
  }
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::capacity() {
  return m_capacity_;
}

template <typename T>
void s21::vector<T>::shrink_to_fit() {
  s21::vector<value_type> temp(m_size_);
  for (size_type i = 0; i < m_size_; i++) {
    temp[i] = this->arr_[i];
  }
  this->swap(temp);
}

template <typename T>
void s21::vector<T>::clear() {
  if (typeid(value_type) == typeid(bool &))
    m_capacity_ = m_size_ / 64 * 64 + ((m_size_ % 64) > 0 ? 64 : 0);
  m_size_ = 0;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::insert(
    iterator pos, const_reference value) {
  m_size_++;
}

template <typename T>
void s21::vector<T>::erase(iterator pos) {
  m_size_--;
}

template <typename T>
void s21::vector<T>::push_back(const_reference value) {
  m_size_++;
}

template <typename T>
void s21::vector<T>::pop_back() {
  m_size_--;
}

template <typename T>
void s21::vector<T>::swap(vector &other) {
  s21::vector<value_type> temp(*this);
  *this = std::move(other);
  other = std::move(temp);
}