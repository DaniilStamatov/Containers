#ifndef STACK_H
#define STACK_H

#include <initializer_list>
#include <stdexcept>

namespace s21 {

    template <typename T>
    class stack {
    public:
        // Member types
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
        size_type size_ = 0;

    public:
        // Member functions
        stack() noexcept = default;  // Default constructor

        stack(std::initializer_list<value_type> const& items) : stack() {
          for (const auto& item : items) {
            push(item);
          }
        }

        stack(const stack& other) : stack() {
          Node* temp = other.head_;
          stack temp_stack;
          while (temp) {
            temp_stack.push(temp->value_);
            temp = temp->next_;
          }
          while (!temp_stack.empty()) {
            push(temp_stack.top());
            temp_stack.pop();
          }
        }

        stack(stack&& other) noexcept : head_(other.head_), size_(other.size_) {
          other.head_ = nullptr;
          other.size_ = 0;
        }

        ~stack() {
          clear();
        }

        stack& operator=(stack&& other) noexcept {
          if (this != &other) {
            clear();
            swap(other);
          }
          return *this;
        }

        // Element access
        const_reference top() const {
          if (empty()) {
            throw std::out_of_range("Stack is empty!");
          }
          return head_->value_;
        }

        // Capacity
        bool empty() const noexcept { return size_ == 0; }

        size_type size() const noexcept { return size_; }

        // Modifiers
        void push(const_reference value) {
          Node* new_node = new Node(value, head_);
          head_ = new_node;
          ++size_;
        }

        void pop() {
          if (empty()) {
            throw std::out_of_range("Stack is empty!");
          }
          Node* temp = head_;
          head_ = head_->next_;
          delete temp;
          --size_;
        }

        void swap(stack& other) noexcept {
          std::swap(head_, other.head_);
          std::swap(size_, other.size_);
        }

        void clear() {
          while (!empty()) {
            pop();
          }
        }
    };

}

#endif  // STACK_H