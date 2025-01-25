#include "list.h"

template <typename T>
list<T>::ListConstIterator::ListConstIterator() noexcept : current_(nullptr) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(Node *node) noexcept: current_(node) {}

template <typename T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*() const {return current_->value_;};

template <typename T>
typename list<T>::ListConstIterator& list<T>::ListConstIterator::operator++()
{
    current_ = current_->next_;
    return *this;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++(int)
{
    ListConstIterator temp(current_);
    current_ = current_->next_;
    return temp;
}

template <typename T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator--()
{
    current_ = current_->prev_;
    return *this;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator--(int)
{
    ListConstIterator temp(current_);
    current_ = current_->prev_;
    return temp;
}

template <typename T>
bool list<T>::ListConstIterator::operator==(const list<T>::ListConstIterator& other) const 
{
    return current_ == other.current_;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(const ListConstIterator &other) const
{
    return !(*this == other);
}

template <typename T>
list<T>::ListIterator::ListIterator() noexcept : ListConstIterator()
{
}

template <typename T>
list<T>::ListIterator::ListIterator(Node *node) noexcept : ListConstIterator(node)
{
}

template <typename T>
typename list<T>::reference list<T>::ListIterator::operator*() const
{
    return this->current_->value_;
}

template <typename T> 
typename list<T>::iterator list<T>::begin() noexcept{
    return  iterator(m_head ? this->m_head : this->m_end);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const noexcept
{
    return const_iterator(m_head ? this->m_head : this->m_end);
}

template <class T>
typename list<T>::iterator list<T>::end() noexcept {
  return iterator(m_end);
}


template <typename T>
typename list<T>::const_iterator list<T>::cend() const noexcept
{
    return const_iterator(m_end);
}

template <typename T>
list<T>::list() noexcept : m_head(nullptr), m_tail(nullptr), m_size(0)
{
    m_end = new Node(T());
    update_end();
}

template <typename T>
list<T>::list(size_type n) : m_head(nullptr), m_tail(nullptr), m_size(n)
{
    if(n <= 0) throw std::out_of_range("Size must be greater than zero");
    m_end = new Node(T());
    for(size_type i = 0; i < n; i++) {
        push_back(value_type());
    }
    update_end();
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)  : m_head(nullptr), m_tail(nullptr), m_size(0)
{
    m_end = new Node(T());
    for(value_type item : items) {
        push_back(item);
    }   
    update_end();
}

template <typename T>
list<T>::list(const list &l) noexcept :  m_head(nullptr), m_tail(nullptr), m_size(0) 
{
    copy(l);
}

template <typename T>
list<T>::list(list &&l) noexcept :  m_head(nullptr), m_tail(nullptr), m_size(0), m_end(nullptr)
{
    swap(l);
}

template <typename T>
void list<T>::clear() {
    while (size() > 0)
    {
        pop_back();
    }
    
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference value)
{
    Node* node = new Node(value);
    Node* position = pos.current_;
    if(empty()) {
        m_head = node;
        m_tail = node;
        node->next_ = nullptr;
        node->prev_ = nullptr;
        ++m_size;
    } else{
        if(pos == begin()) {
            push_front(value);
        } else if(pos == end()) {
            push_back(value);
        }
        else {node->next_ = position;
        node->prev_ = position->prev_;
        position->prev_->next_ = node;
        position->prev_ = node;
        ++m_size;

        }
    }
    update_end();
    return pos;
}

template <typename T>
void list<T>::copy(const list &l) {
    Node* temp = l.m_head;
    while (temp) {
        push_back(temp->value_); 
        temp = temp->next_;
    }
    update_end();
}

template <typename T>
bool list<T>::empty()
{
    return m_size == 0;
}

template <typename T>
list<T>::~list()
{
   clear();
}

template <typename T>
void list<T>::update_end()
{
    m_end->prev_ = m_tail;
    if(m_tail) {
        m_tail->next_ = m_end;
    }
}


template <typename value_type>
void list<value_type>::swap(list& l) {
  std::swap(m_head, l.m_head);
  std::swap(m_tail, l.m_tail);
  std::swap(m_size, l.m_size);
  std::swap(m_end, l.m_end);
}

template <typename T>
list<T>& list<T>::operator=(const list &l) noexcept 
{
    if(this != &l){
        list<T> temp(l);
        clear();
        swap(temp);
    }
    return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& l) noexcept {
    if (this != &l) {
        clear();
        swap(l);
    }
    return *this;
}

template <typename T>
typename list<T>::size_type list<T>::size()
{
    return m_size;
}

template <typename T>
void list<T>::push_back(const_reference data) noexcept
{
    Node* node = new Node(data, nullptr, m_tail);
    if(m_tail) {
        m_tail->next_ = node;
    }
    m_tail = node;
    if(!m_head) {
        m_head = node;
    }
    update_end();
    ++m_size;
}

template <typename T>
void list<T>::pop_back() {
    if(size() == 0) throw std::out_of_range("Empty list!");
    Node* last_node = m_tail;
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
void list<T>::push_front(const_reference value) noexcept
{
    Node* data = new Node(value, m_head, nullptr);
    if(m_head) {
        m_head->prev_ = data;
    } else {
        m_tail = data;
    }
    m_head = data;
    update_end();
    ++m_size;
}

template <typename T>
void list<T>::pop_front() {
    if(m_head == nullptr) throw std::out_of_range("Empty list!");
    Node* temp = m_head->next_;
    delete m_head;
    m_head = temp;
    if(m_head) {
        m_head->prev_ = nullptr;
    } else {
        m_tail = nullptr;
    }
    --m_size;
    update_end();
}

