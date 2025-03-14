#include <gtest/gtest.h>

#include <set>

#include "../containersplus/s21_multiset.h"
TEST(multiset_test, insert_simple) {
  s21::multiset<int> s21_multiset;

  std::pair<s21::multiset<int>::iterator, bool> insert1 =
      s21_multiset.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::multiset<int>::iterator, bool> insert2 =
      s21_multiset.insert(9);
  std::pair<s21::multiset<int>::iterator, bool> insert3 =
      s21_multiset.insert(9);
  EXPECT_EQ(*insert2.first, 9);
  EXPECT_EQ(*insert3.first, 9);

  EXPECT_EQ(insert2.second, true);
  EXPECT_EQ(insert3.second, true);

  std::pair<s21::multiset<int>::iterator, bool> insert4 =
      s21_multiset.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::multiset<int>::iterator, bool> insert5 =
      s21_multiset.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);

  EXPECT_EQ(s21_multiset.size(), 5UL);
}

TEST(multiset_erase, EraseOperations) {
  int num1 = 10;
  int num2 = 5;
  int num3 = 15;
  int num4 = 4;
  int num5 = 18;
  int num6 = 13;
  int num7 = 16;

  s21::multiset<int> s21_set = {num1, num2, num3, num4, num5, num6, num7};
  std::multiset<int> std_set = {num1, num2, num3, num4, num5, num6, num7};
  auto it = s21_set.begin();
  auto std_it = std_set.begin();
  it++;
  it++;
  it++;
  it++;
  std_it++;
  std_it++;
  std_it++;
  std_it++;
  s21_set.erase(it);
  std_set.erase(std_it);

  EXPECT_EQ(*s21_set.begin(), 4);
  EXPECT_EQ(*std_set.begin(), 4);
  EXPECT_EQ(s21_set.size(), 6U);
  EXPECT_EQ(s21_set.size(), 6U);
  it = s21_set.begin();
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(s21_set.size(), 5U);

  it = s21_set.begin();
  ++it;

  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(s21_set.size(), 4U);

  it = s21_set.begin();
  it++;
  s21_set.erase(it);

  it = s21_set.begin();
  it++;
  s21_set.erase(it);

  it = s21_set.begin();
  s21_set.erase(it);

  it = s21_set.begin();
  s21_set.erase(it);
  EXPECT_EQ(s21_set.size(), 0UL);
}

TEST(multiset_erase, case2) {
  s21::multiset<int> s21_set = {30, 1543};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  s21_set.erase(it);

  EXPECT_EQ(s21_set.size(), 0UL);
}

TEST(multiset_merge, case1) {
  double val1 = 1.4;
  double val2 = 2.77;
  double val3 = 3.9;
  double val11 = 4.59;
  double val22 = 12.902;
  double val33 = 56.41;

  s21::multiset<double> s21_set_int_ref{val1, val2, val3};

  s21::multiset<double> s21_set_int_res{val11, val22, val33};
  s21_set_int_res.merge(s21_set_int_ref);
  EXPECT_EQ(s21_set_int_res.size(), 6U);
}

TEST(multiset, case1) {
  double val1 = 1.4;
  double val2 = 2.77;
  double val3 = 3.9;
  double val11 = 4.59;
  double val22 = 12.902;
  double val33 = 56.41;

  s21::multiset<double> s21_set_int_ref{val1, val2, val3};

  s21::multiset<double> s21_set_int_res{val11, val22, val33};
  s21_set_int_res.swap(s21_set_int_ref);
  EXPECT_EQ(s21_set_int_res.size(), 3U);
  EXPECT_TRUE(s21_set_int_ref.find(4.59) == s21_set_int_ref.begin());
}

TEST(multisetInsertManyTest, strings) {
  s21::multiset<std::string> mySet;
  auto results = mySet.insert_many("one", "two", "three");

  EXPECT_EQ(results.size(), (size_t)3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(mySet.size(), (size_t)3);
}

TEST(multisetInsertManyTest, doubles) {
  s21::multiset<double> mySet;
  auto results = mySet.insert_many(4.59, 12.902, 56.41);

  EXPECT_EQ(results.size(), (size_t)3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  EXPECT_EQ(mySet.size(), (size_t)3);
}

TEST(multiset, find) {
  s21::multiset<int> mySet = {1, 3, 5};
  std::multiset<int> stdSet = {1, 3, 5};
  auto it = mySet.find(3);
  auto stdIt = stdSet.find(3);
  bool eq = (it == (++mySet.begin()));
  bool eq2 = (stdIt == (++stdSet.begin()));
  mySet.insert(3);
  mySet.insert(5);
  stdSet.insert(5);
  stdSet.insert(3);
  auto it1 = mySet.begin();
  auto it2 = stdSet.begin();
  for (; it1 != mySet.end(); ++it1) {
    std::cout << *it1 << " ";
  }
  std::cout << std::endl;
  for (; it2 != stdSet.end(); ++it2) {
    std::cout << *it2 << " ";
  }
  it1 = mySet.begin();
  it2 = stdSet.begin();
  for (; it1 != mySet.end(); ++it1) {
    EXPECT_EQ(*it1, *it2);
    ++it2;
  }
  std::cout << std::endl;
  std::cout << *mySet.begin() << " " << *stdSet.begin() << std::endl;
  EXPECT_EQ(eq, true);
  EXPECT_EQ(eq2, true);
}