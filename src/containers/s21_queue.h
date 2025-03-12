#ifndef QUEUE_H
#define QUEUE_H

#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node {
    Node() = default;
    Node(const T& value, Node* next = nullptr) : value_(value), next_(next) {}

    T value_;
    Node* next_ = nullptr;
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_type size_ = 0;

 public:
  queue() noexcept = default;

  queue(std::initializer_list<value_type> const& items) : queue() {
    for (const auto& item : items) {
      push(item);
    }
  }

  queue(const queue& other) : queue() {
    Node* temp = other.head_;
    while (temp) {
      push(temp->value_);
      temp = temp->next_;
    }
  }

  queue(queue&& other) noexcept
      : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  ~queue() {
    clear();
  }

  queue& operator=(queue&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  const_reference front() const {
    if (empty()) {
      throw std::out_of_range("Queue is empty!");
    }
    return head_->value_;
  }

  const_reference back() const {
    if (empty()) {
      throw std::out_of_range("Queue is empty!");
    }
    return tail_->value_;
  }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  void push(const_reference value) {
    Node* new_node = new Node(value);
    if (empty()) {
      head_ = new_node;
    } else {
      tail_->next_ = new_node;
    }
    tail_ = new_node;
    ++size_;
  }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Queue is empty!");
    }
    Node* temp = head_;
    head_ = head_->next_;
    delete temp;
    --size_;
    if (empty()) {
      tail_ = nullptr;
    }
  }

  void swap(queue& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void clear() {
    while (!empty()) {
      pop();
    }
  }
};

}

#endif  // QUEUE_H