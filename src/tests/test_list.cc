#include <gtest/gtest.h>

#include <list>

#include "../containers/s21_list.h"
using namespace s21;
TEST(Constructor, PushBackUltimate) {
  list<int> myList;
  EXPECT_EQ(myList.size(), 0UL);
  EXPECT_EQ(myList.begin(), myList.end());

  myList.push_back(1);
  EXPECT_EQ(myList.size(), 1UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*(--myList.end()), 1);
  EXPECT_EQ(myList.begin(), --myList.end());

  myList.push_back(2);
  EXPECT_EQ(myList.size(), 2UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*(--myList.end()), 2);

  myList.push_back(3);
  EXPECT_EQ(myList.size(), 3UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*(--myList.end()), 3);

  for (int i = 4; i <= 10; ++i) {
    myList.push_back(i);
  }
  EXPECT_EQ(myList.size(), 10UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*(--myList.end()), 10);

  myList.clear();
  EXPECT_EQ(myList.size(), 0UL);
}

TEST(ListTest, PushFrontUltimate) {
  list<int> myList;
  std::list<int> stdList;
  EXPECT_EQ(myList.size(), 0UL);
  EXPECT_EQ(stdList.size(), 0UL);
  EXPECT_EQ(myList.begin(), myList.end());
  EXPECT_EQ(stdList.begin(), stdList.end());

  myList.push_front(1);
  stdList.push_front(1);
  EXPECT_EQ(myList.size(), 1UL);
  EXPECT_EQ(stdList.size(), 1UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*stdList.begin(), 1);
  EXPECT_EQ(myList.begin() == --myList.end(), true);
  EXPECT_EQ(stdList.begin(), --stdList.end());

  myList.push_front(2);
  stdList.push_front(2);
  EXPECT_EQ(myList.size(), 2UL);
  EXPECT_EQ(stdList.size(), 2UL);
  EXPECT_EQ(*myList.begin(), 2);
  EXPECT_EQ(*stdList.begin(), 2);
  EXPECT_EQ(*(--myList.end()), 1);
  EXPECT_EQ(*(--stdList.end()), 1);
  EXPECT_EQ(myList.begin() == --(--myList.end()), true);

  myList.push_front(3);
  stdList.push_front(3);
  EXPECT_EQ(myList.size(), 3UL);
  EXPECT_EQ(stdList.size(), 3UL);
  EXPECT_EQ(*myList.begin(), 3);
  EXPECT_EQ(*stdList.begin(), 3);
  EXPECT_EQ(*(--myList.end()), 1);
  EXPECT_EQ(*(--stdList.end()), 1);

  for (int i = 4; i <= 10; ++i) {
    myList.push_front(i);
    stdList.push_front(i);
  }
  EXPECT_EQ(myList.size(), 10UL);
  EXPECT_EQ(stdList.size(), 10UL);
  EXPECT_EQ(*myList.begin(), 10);
  EXPECT_EQ(*stdList.begin(), 10);
  EXPECT_EQ(*(--myList.end()), 1);
  EXPECT_EQ(*(--stdList.end()), 1);

  myList.clear();
  stdList.clear();
  EXPECT_EQ(myList.size(), 0UL);
  EXPECT_EQ(stdList.size(), 0UL);
}

TEST(ConstructorTest, DefaultConstructor) {
  list<int> myList;
  std::list<int> stdList;

  EXPECT_EQ(myList.size(), 0UL);
  EXPECT_EQ(stdList.size(), 0UL);
  EXPECT_EQ(myList.begin(), myList.end());
  EXPECT_EQ(stdList.begin(), stdList.end());
}

TEST(ConstructorTest, InitializerListConstructor) {
  list<int> myList = {1, 2, 3, 4, 5};
  std::list<int> stdList = {1, 2, 3, 4, 5};

  EXPECT_EQ(myList.size(), 5UL);
  EXPECT_EQ(stdList.size(), 5UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*stdList.begin(), 1);
  EXPECT_EQ(*(--myList.end()), 5);
  EXPECT_EQ(*(--stdList.end()), 5);
}

TEST(ConstructorTest, MoveConstructor) {
  list<int> myList = {1, 2, 3, 4, 5};
  list<int> movedList = std::move(myList);

  EXPECT_EQ(movedList.size(), 5UL);
  EXPECT_EQ(myList.size(), 0UL);
  EXPECT_EQ(*movedList.begin(), 1);
  EXPECT_EQ(*(--movedList.end()), 5);
}

TEST(ListTest, PopBack) {
  list<int> myList;
  std::list<int> stdList;

  for (int i = 1; i <= 5; ++i) {
    myList.push_back(i);
    stdList.push_back(i);
  }

  EXPECT_EQ(myList.size(), 5UL);
  EXPECT_EQ(stdList.size(), 5UL);

  myList.pop_back();
  stdList.pop_back();
  EXPECT_EQ(myList.size(), 4UL);
  EXPECT_EQ(stdList.size(), 4UL);
  EXPECT_EQ(*(--myList.end()), 4);
  EXPECT_EQ(*(--stdList.end()), 4);
}

TEST(ListTest, PopFront) {
  list<int> myList;
  std::list<int> stdList;

  for (int i = 1; i <= 5; ++i) {
    myList.push_back(i);
    stdList.push_back(i);
  }

  EXPECT_EQ(myList.size(), 5UL);
  EXPECT_EQ(stdList.size(), 5UL);

  myList.pop_front();
  stdList.pop_front();
  EXPECT_EQ(myList.size(), 4UL);
  EXPECT_EQ(stdList.size(), 4UL);
  EXPECT_EQ(*myList.begin(), 2);
  EXPECT_EQ(*stdList.begin(), 2);
}

TEST(InsertTest, InsertIntoEmptyList) {
  list<int> myList;
  std::list<int> stdList;

  myList.insert(myList.begin(), 1);
  stdList.insert(stdList.begin(), 1);

  EXPECT_EQ(myList.size(), 1UL);
  EXPECT_EQ(stdList.size(), 1UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*stdList.begin(), 1);
}

TEST(InsertTest, InsertAtBeginning) {
  list<int> myList = {2, 3, 4};
  std::list<int> stdList = {2, 3, 4};

  myList.insert(myList.begin(), 1);
  stdList.insert(stdList.begin(), 1);

  EXPECT_EQ(myList.size(), 4UL);
  EXPECT_EQ(stdList.size(), 4UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*stdList.begin(), 1);
}

TEST(InsertTest, InsertAtEnd) {
  list<int> myList = {1, 2, 3};
  std::list<int> stdList = {1, 2, 3};

  myList.insert(myList.end(), 4);
  stdList.insert(stdList.end(), 4);

  EXPECT_EQ(myList.size(), 4UL);
  EXPECT_EQ(stdList.size(), 4UL);
  EXPECT_EQ(*(--myList.end()), 4);
  EXPECT_EQ(*(--stdList.end()), 4);
}

TEST(InsertTest, InsertInMiddle) {
  list<int> myList = {1, 3, 4};
  std::list<int> stdList = {1, 3, 4};
  myList.insert(++myList.begin(), 2);
  stdList.insert(++stdList.begin(), 2);
  EXPECT_EQ(myList.size(), 4UL);
  EXPECT_EQ(stdList.size(), 4UL);
  EXPECT_EQ(*(++myList.begin()), 2);
  EXPECT_EQ(*(++stdList.begin()), 2);
}

TEST(InsertTest, InsertMultipleElements) {
  list<int> myList;
  std::list<int> stdList;

  for (int i = 1; i <= 5; ++i) {
    myList.insert(myList.end(), i);
    stdList.insert(stdList.end(), i);
  }

  EXPECT_EQ(myList.size(), 5UL);
  EXPECT_EQ(stdList.size(), 5UL);
  EXPECT_EQ(*myList.begin(), 1);
  EXPECT_EQ(*stdList.begin(), 1);
  EXPECT_EQ(*(--myList.end()), 5);
  EXPECT_EQ(*(--stdList.end()), 5);
}

TEST(MergeTest, EmptyLists) {
  list<int> list1;
  list<int> list2;

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 0UL);
  EXPECT_EQ(list2.size(), 0UL);
}

TEST(MergeTest, EmptyList) {
  list<int> list1 = {1, 3, 5};
  list<int> list2;

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3UL);
  EXPECT_EQ(*list1.begin(), 1);
  EXPECT_EQ(*(--list1.end()), 5);
}

TEST(MergeTest, EqualTest) {
  list<int> list1 = {1, 2, 3};
  list<int> list2 = {1, 2, 3};

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6UL);
  EXPECT_EQ(*list1.begin(), 1);
  EXPECT_EQ(*(++list1.begin()), 1);
  EXPECT_EQ(*(++(++list1.begin())), 2);
  EXPECT_EQ(*(++(++(++list1.begin()))), 2);
  EXPECT_EQ(*(++(++(++(++list1.begin())))), 3);
  EXPECT_EQ(*(--list1.end()), 3);
}

TEST(MergeTest, MergeNormal) {
  list<int> list1 = {1, 3, 5};
  list<int> list2 = {2, 4, 6};

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6UL);
  EXPECT_EQ(*list1.begin(), 1);
  EXPECT_EQ(*(++list1.begin()), 2);
  EXPECT_EQ(*(++(++list1.begin())), 3);
  EXPECT_EQ(*(++(++(++list1.begin()))), 4);
  EXPECT_EQ(*(++(++(++(++list1.begin())))), 5);
  EXPECT_EQ(*(--list1.end()), 6);
}

TEST(SpliceTest, EmptyList) {
  list<int> list1;
  list<int> list2;

  list1.splice(list1.begin(), list2);

  EXPECT_EQ(list1.size(), 0UL);
  EXPECT_EQ(list2.size(), 0UL);
}

TEST(SpliceTest, NormalTest) {
  list<int> list1 = {1, 2, 3};
  list<int> list2 = {4, 5, 6};

  list1.splice(list1.end(), list2);

  EXPECT_EQ(list1.size(), 6UL);
  EXPECT_EQ(list2.size(), 0UL);
  EXPECT_EQ(*(--list1.end()), 6);
}

TEST(SortTest, EmptyList) {
  list<int> myList;
  myList.sort();
  EXPECT_EQ(myList.size(), 0UL);
}

TEST(SortTest, SingleList) {
  list<int> myList = {51};
  myList.sort();
  EXPECT_EQ(myList.size(), 1UL);
  EXPECT_EQ(*myList.begin(), 51);
}

TEST(SortTest, SortedList) {
  list<int> myList = {1, 2, 3, 4, 5};
  myList.sort();
  list<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(SortTest, ReversedList) {
  std::list<int> myList = {5, 4, 3, 2, 1};
  myList.sort();
  list<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(SortTest, SortWithDuplicates) {
  list<int> myList = {3, 1, 2, 3, 2, 1};
  myList.sort();
  list<int> expected = {1, 1, 2, 2, 3, 3};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ReverseTest, ReverseEmptyList) {
  list<int> myList;
  myList.reverse();
  EXPECT_EQ(myList.size(), 0UL);
}

TEST(ReverseTest, ReverseSingleElement) {
  list<int> myList = {42};
  myList.reverse();
  EXPECT_EQ(myList.size(), 1UL);
  EXPECT_EQ(*myList.begin(), 42);
}

TEST(ReverseTest, ReverseAlreadyReversed) {
  list<int> myList = {5, 4, 3, 2, 1};
  myList.reverse();
  list<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ReverseTest, ReverseMultipleElements) {
  list<int> myList = {1, 2, 3, 4, 5};
  myList.reverse();
  list<int> expected = {5, 4, 3, 2, 1};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ReverseTest, Reverse2) {
  list<int> myList = {1, 2, 3, 4, 5, 6};
  myList.reverse();
  list<int> expected = {6, 5, 4, 3, 2, 1};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(EraseTest, EraseSimple) {
  list<int> myList = {1, 2, 3};
  myList.erase(myList.begin());
  list<int> expected = {2, 3};
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(EraseTest, EraseMultiple) {
  list<int> myList = {1, 2, 3, 4, 5, 6};
  myList.erase(myList.begin());
  myList.erase(myList.begin());
  myList.erase(myList.begin());
  list<int> expected = {4, 5, 6};
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(EraseTest, EraseOne) {
  list<int> myList = {1};
  myList.erase(myList.begin());
  list<int> expected;
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(EraseTest, EraseEnd) {
  list<int> myList = {1, 2, 3, 4, 5, 6};
  myList.erase(--myList.end());
  myList.erase(--myList.end());
  myList.erase(--myList.end());
  list<int> expected = {1, 2, 3};
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(UniqueTest, UniqueEmptyList) {
  list<int> myList;
  myList.unique();
  EXPECT_EQ(myList.size(), 0UL);
}

TEST(UniqueTest, UniqueSingleElement) {
  list<int> myList = {42};
  myList.unique();
  EXPECT_EQ(myList.size(), 1UL);
  EXPECT_EQ(*myList.begin(), 42);
}

TEST(UniqueTest, UniqueWithDuplicates) {
  list<int> myList = {1, 2, 2, 3, 3, 3, 4, 5, 5};
  myList.unique();
  list<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(UniqueTest, UniqueAlreadyUnique) {
  list<int> myList = {1, 2, 3, 4, 5};
  myList.unique();
  list<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(UniqueTest, UniqueWithAllDuplicates) {
  list<int> myList = {1, 1, 1, 1, 1};
  myList.unique();
  list<int> expected = {1};
  EXPECT_EQ(myList.size(), expected.size());
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, FrontBack) {
  s21::list<int> myList = {42};
  EXPECT_EQ(myList.back(), 42);
  EXPECT_EQ(myList.front(), 42);
}

TEST(ListTest, FrontMulty) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.front(), 1);
}

TEST(ListTest, BackMulty) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.back(), 5);
}

TEST(MaxSizeTest, Ints) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  std::list<int> List = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.max_size(), List.max_size());
}

TEST(InsertManyTest, Ints) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  std::list<int> expected = {1, 6, 7, 8, 2, 3, 4, 5};
  s21::list<int>::iterator it = myList.begin();
  ++it;
  myList.insert_many(it, 6, 7, 8);
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(InsertManyTest, Empty) {
  s21::list<int> myList;
  std::list<int> expected = {6, 7, 8};
  s21::list<int>::iterator it = myList.begin();
  myList.insert_many(it, 6, 7, 8);
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(InsertManyTest, InsertAtEnd) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  std::list<int> expected = {1, 2, 3, 4, 5, 6, 7, 8};
  myList.insert_many(myList.end(), 6, 7, 8);
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(InsertManyTest, InsertAtBeginning) {
  s21::list<int> myList = {2, 3, 4, 5};
  std::list<int> expected = {1, 6, 7, 8, 2, 3, 4, 5};
  s21::list<int>::iterator it = myList.begin();
  myList.insert_many(it, 6, 7, 8);
  it = myList.begin();
  myList.insert(it, 1);
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(InsertManyBack, Ints) {
  s21::list<int> myList = {2, 3, 4, 5};
  myList.insert_many_back(6, 7, 8);
  std::list<int> expected = {2, 3, 4, 5, 6, 7, 8};
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(InsertManyBack, Empty) {
  s21::list<int> myList;
  myList.insert_many_back(6, 7, 8);
  std::list<int> expected = {6, 7, 8};
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(InsertManyFront, Empty) {
  s21::list<int> myList;
  myList.insert_many_front(6, 7, 8);
  std::list<int> expected = {8, 7, 6};
  auto it1 = myList.begin();
  auto it2 = expected.begin();
  while (it1 != myList.end() && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}