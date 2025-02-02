#include <gtest/gtest.h>

#include <set>

#include "../containers/s21_set.h"
TEST(set_test, insert_simple) {
  set<int> s21_set;

  std::pair<set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  std::pair<set<int>::iterator, bool> insert4 = s21_set.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, 1);

  std::pair<set<int>::iterator, bool> insert5 = s21_set.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, 1);

  EXPECT_EQ(s21_set.size(), 3);
}

TEST(set_insert, case2) {
  set<std::string> s21_set;

  std::pair<set<std::string>::iterator, bool> insert1 = s21_set.insert("hello");
  EXPECT_EQ(*insert1.first, "hello");
  EXPECT_EQ(insert1.second, 1);

  std::pair<set<std::string>::iterator, bool> insert2 = s21_set.insert("hi");
  EXPECT_EQ(*insert2.first, "hi");
  EXPECT_EQ(insert2.second, 1);

  std::pair<set<std::string>::iterator, bool> insert3 = s21_set.insert("hla");
  EXPECT_EQ(*insert3.first, "hla");
  EXPECT_EQ(insert3.second, 1);
  s21_set.insert("hi");
  s21_set.insert("hola");

  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, EraseOperations) {
  int num1 = 10;
  int num2 = 5;
  int num3 = 15;
  int num4 = 4;
  int num5 = 18;
  int num6 = 13;
  int num7 = 16;

  set<int> s21_set = {num1, num2, num3, num4, num5, num6, num7};
  std::set<int> std_set = {num1, num2, num3, num4, num5, num6, num7};
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
  EXPECT_EQ(s21_set.size(), 0);
}

TEST(set_erase, case2) {
  set<int> s21_set = {30, 1543};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  s21_set.erase(it);

  EXPECT_EQ(s21_set.size(), 0);
}

TEST(set_merge, case1) {
  double val1 = 1.4;
  double val2 = 2.77;
  double val3 = 3.9;
  double val11 = 4.59;
  double val22 = 12.902;
  double val33 = 56.41;

  set<double> s21_set_int_ref{val1, val2, val3};

  set<double> s21_set_int_res{val11, val22, val33};
  s21_set_int_res.merge(s21_set_int_ref);
  EXPECT_EQ(s21_set_int_res.size(), 6U);
}

TEST(set, case1) {
  double val1 = 1.4;
  double val2 = 2.77;
  double val3 = 3.9;
  double val11 = 4.59;
  double val22 = 12.902;
  double val33 = 56.41;

  set<double> s21_set_int_ref{val1, val2, val3};

  set<double> s21_set_int_res{val11, val22, val33};
  s21_set_int_res.swap(s21_set_int_ref);
  EXPECT_EQ(s21_set_int_res.size(), 3U);
  EXPECT_TRUE(s21_set_int_ref.find(4.59) == s21_set_int_ref.begin());
}