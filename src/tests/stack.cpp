#include "s21_stack.h"
#include "tests.h"

// Test default constructor
TEST(StackTest, DefaultConstructor) {
  s21::stack<int> stack;
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0UL);
}

// Test initializer list constructor
TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> stack = {1, 2, 3};
  EXPECT_EQ(stack.size(), 3UL);
  EXPECT_EQ(stack.top(), 3);
}

// Test copy constructor
TEST(StackTest, CopyConstructor) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2(stack1);

  EXPECT_EQ(stack1.size(), stack2.size());
  EXPECT_EQ(stack1.top(), stack2.top());
}

// Test move constructor
TEST(StackTest, MoveConstructor) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2(std::move(stack1));

  EXPECT_EQ(stack2.size(), 3UL);
  EXPECT_EQ(stack2.top(), 3);
  EXPECT_TRUE(stack1.empty());
}

// Test move assignment operator
TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2;
  stack2 = std::move(stack1);

  EXPECT_EQ(stack2.size(), 3UL);
  EXPECT_EQ(stack2.top(), 3);
  EXPECT_TRUE(stack1.empty());
}

// Test top() method
TEST(StackTest, Top) {
  s21::stack<int> stack = {1, 2, 3};
  EXPECT_EQ(stack.top(), 3);

  stack.pop();
  EXPECT_EQ(stack.top(), 2);
}

// Test top() method on an empty stack
TEST(StackTest, TopEmptyStack) {
  s21::stack<int> stack;
  EXPECT_THROW(stack.top(), std::out_of_range);
}

// Test empty() method
TEST(StackTest, Empty) {
  s21::stack<int> stack;
  EXPECT_TRUE(stack.empty());

  stack.push(1);
  EXPECT_FALSE(stack.empty());
}

// Test size() method
TEST(StackTest, Size) {
  s21::stack<int> stack;
  EXPECT_EQ(stack.size(), 0UL);

  stack.push(1);
  stack.push(2);
  EXPECT_EQ(stack.size(), 2UL);
}

// Test push() method
TEST(StackTest, Push) {
  s21::stack<int> stack;
  stack.push(1);
  stack.push(2);

  EXPECT_EQ(stack.size(), 2UL);
  EXPECT_EQ(stack.top(), 2);
}

// Test pop() method
TEST(StackTest, Pop) {
  s21::stack<int> stack = {1, 2, 3};
  stack.pop();

  EXPECT_EQ(stack.size(), 2UL);
  EXPECT_EQ(stack.top(), 2);
}

// Test pop() method on an empty stack
TEST(StackTest, PopEmptyStack) {
  s21::stack<int> stack;
  EXPECT_THROW(stack.pop(), std::out_of_range);
}

// Test swap() method
TEST(StackTest, Swap) {
  s21::stack<int> stack1 = {1, 2, 3};
  s21::stack<int> stack2 = {4, 5};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 2UL);
  EXPECT_EQ(stack1.top(), 5);

  EXPECT_EQ(stack2.size(), 3UL);
  EXPECT_EQ(stack2.top(), 3);
}

// Test clear() method
TEST(StackTest, Clear) {
  s21::stack<int> stack = {1, 2, 3};
  stack.clear();

  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0UL);
}

// Test edge case: large stack
TEST(StackTest, LargeStack) {
  s21::stack<int> stack;
  for (int i = 0; i < 1000; ++i) {
    stack.push(i);
  }

  EXPECT_EQ(stack.size(), 1000UL);
  EXPECT_EQ(stack.top(), 999);
}

// Test edge case: stack with one element
TEST(StackTest, SingleElementStack) {
  s21::stack<int> stack = {42};

  EXPECT_EQ(stack.size(), 1UL);
  EXPECT_EQ(stack.top(), 42);

  stack.pop();
  EXPECT_TRUE(stack.empty());
}

// Test edge case: stack with strings
TEST(StackTest, StringStack) {
  s21::stack<std::string> stack = {"hello", "world"};

  EXPECT_EQ(stack.size(), 2UL);
  EXPECT_EQ(stack.top(), "world");

  stack.pop();
  EXPECT_EQ(stack.top(), "hello");
}