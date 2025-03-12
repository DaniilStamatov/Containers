<<<<<<< HEAD
#include "../containers/s21_queue.h"
=======
#include "s21_queue.h"
>>>>>>> 69ac7c723b96bc8d91fa0df2650b8692ea2e95b0
#include <gtest/gtest.h>

namespace s21 {

TEST(QueueTest, DefaultConstructor) {
  queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0UL);
}

TEST(QueueTest, InitializerListConstructor) {
  queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.size(), 3UL);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, CopyConstructor) {
  queue<int> q1 = {1, 2, 3};
  queue<int> q2(q1);

  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.front(), q2.front());
  EXPECT_EQ(q1.back(), q2.back());
}

TEST(QueueTest, MoveConstructor) {
  queue<int> q1 = {1, 2, 3};
  queue<int> q2(std::move(q1));

  EXPECT_EQ(q2.size(), 3UL);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, MoveAssignmentOperator) {
  queue<int> q1 = {1, 2, 3};
  queue<int> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 3UL);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, Front) {
  queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);
}

TEST(QueueTest, Back) {
  queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.back(), 3);
  q.push(4);
  EXPECT_EQ(q.back(), 4);
}

TEST(QueueTest, FrontEmptyQueue) {
  queue<int> q;
  EXPECT_THROW(q.front(), std::out_of_range);
}

TEST(QueueTest, BackEmptyQueue) {
  queue<int> q;
  EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(QueueTest, Empty) {
  queue<int> q;
  EXPECT_TRUE(q.empty());
  q.push(1);
  EXPECT_FALSE(q.empty());
}

TEST(QueueTest, Size) {
  queue<int> q;
  EXPECT_EQ(q.size(), 0UL);
  q.push(1);
  q.push(2);
  EXPECT_EQ(q.size(), 2UL);
}

TEST(QueueTest, Push) {
  queue<int> q;
  q.push(1);
  q.push(2);
  EXPECT_EQ(q.size(), 2UL);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 2);
}

TEST(QueueTest, Pop) {
  queue<int> q = {1, 2, 3};
  q.pop();
  EXPECT_EQ(q.size(), 2UL);
  EXPECT_EQ(q.front(), 2);
}

TEST(QueueTest, PopEmptyQueue) {
  queue<int> q;
  EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueTest, Swap) {
  queue<int> q1 = {1, 2, 3};
  queue<int> q2 = {4, 5};
  q1.swap(q2);
  EXPECT_EQ(q1.size(), 2UL);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q2.size(), 3UL);
  EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, Clear) {
  queue<int> q = {1, 2, 3};
  q.clear();
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0UL);
}

TEST(QueueTest, LargeQueue) {
  queue<int> q;
  for (int i = 0; i < 1000; ++i) {
    q.push(i);
  }
  EXPECT_EQ(q.size(), 1000UL);
  EXPECT_EQ(q.front(), 0);
  EXPECT_EQ(q.back(), 999);
}

TEST(QueueTest, SingleElementQueue) {
  queue<int> q = {42};
  EXPECT_EQ(q.size(), 1UL);
  EXPECT_EQ(q.front(), 42);
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, StringQueue) {
  queue<std::string> q = {"hello", "world"};
  EXPECT_EQ(q.size(), 2UL);
  EXPECT_EQ(q.front(), "hello");
  q.pop();
  EXPECT_EQ(q.front(), "world");
}

}
