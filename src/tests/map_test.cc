#include <gtest/gtest.h>

#include <cassert>
#include <iostream>
#include <map>

#include "../containers/s21_map.h"

TEST(map_test, insert_simple) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{9, 1.4};
  std::pair<int, double> pair3{9, 1.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{98, 3.9};

  map<int, double> s21_map;

  std::pair<map<int, double>::iterator, bool> insert1 = s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->first, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<map<int, double>::iterator, bool> insert2 = s21_map.insert(pair2);
  std::pair<map<int, double>::iterator, bool> insert3 = s21_map.insert(pair3);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  std::pair<map<int, double>::iterator, bool> insert4 = s21_map.insert(pair4);
  EXPECT_EQ(insert4.first->first, 23);
  EXPECT_EQ(insert4.second, 1);

  std::pair<map<int, double>::iterator, bool> insert5 = s21_map.insert(pair5);
  EXPECT_EQ(insert5.first->first, 98);
  EXPECT_EQ(insert5.second, 1);

  EXPECT_EQ(s21_map.size(), 3UL);
}

TEST(map_insert, case2) {
  std::pair<double, std::string> pair1{1.4, "hello"};
  std::pair<double, std::string> pair2{2.77, "hi"};
  std::pair<double, std::string> pair3{3.9, "hla"};
  std::pair<double, std::string> pair4{2.77, "hi"};
  std::pair<double, std::string> pair5{2.77, "hola"};

  map<double, std::string> s21_map;

  std::pair<map<double, std::string>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->first, 1.4);
  EXPECT_EQ(insert1.second, 1);

  std::pair<map<double, std::string>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  EXPECT_EQ(insert2.first->first, 2.77);
  EXPECT_EQ(insert2.second, 1);

  std::pair<map<double, std::string>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert3.first->first, 3.9);
  EXPECT_EQ(insert3.second, 1);
  std::pair<map<double, std::string>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  std::pair<map<double, std::string>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert4.second, 0);
  EXPECT_EQ(insert5.second, 0);

  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(map_insert, case5) {
  map<double, std::string> s21_map;

  std::pair<map<double, std::string>::iterator, bool> insert1 =
      s21_map.insert(1, "one");
  EXPECT_EQ(insert1.first->first, 1);
  EXPECT_EQ(insert1.second, 1);

  std::pair<map<double, std::string>::iterator, bool> insert2 =
      s21_map.insert(2, "two");
  EXPECT_EQ(insert2.first->first, 2);
  EXPECT_EQ(insert2.second, 1);

  std::pair<map<double, std::string>::iterator, bool> insert3 =
      s21_map.insert(3, "thee");
  EXPECT_EQ(insert3.first->first, 3);
  EXPECT_EQ(insert3.second, 1);
  s21_map.insert(4, "four");
  s21_map.insert(5, "five");

  EXPECT_EQ(s21_map.size(), 5UL);
}

TEST(map_erase, EraseOperations) {
  std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{15, 15};
  std::pair<int, int> pair4{4, 4};
  std::pair<int, int> pair5{18, 18};
  std::pair<int, int> pair6{13, 13};
  std::pair<int, int> pair7{16, 16};

  map<int, int> s21_map = {pair1, pair2, pair3, pair4, pair5, pair6, pair7};
  auto it = s21_map.begin();
  printf("begin:%d\n", (*it).first);
  it++;
  it++;
  it++;
  it++;
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 4);
  EXPECT_EQ(s21_map.size(), 6U);
  it = s21_map.begin();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.size(), 5U);

  it = s21_map.begin();
  ++it;

  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  s21_map.erase(it);

  it = s21_map.begin();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.size(), 0UL);
}

TEST(map_erase, case2) {
  std::pair<int, int> pair1{30, 30};
  std::pair<int, int> pair2{1543, 1543};

  map<int, int> s21_map = {pair1, pair2};

  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(map_insert_or_assign, case1) {
  map<int, std::string> s21_map;
  std::map<int, std::string> std_map;
  s21_map.insert_or_assign(10, "ten");
  std_map.insert_or_assign(10, "ten");
  EXPECT_EQ("ten", s21_map.at(10));
  EXPECT_EQ(s21_map.size(), 1UL);
  EXPECT_EQ(s21_map.at(10), std_map.at(10));

  s21_map.insert_or_assign(11, "eleven");
  std_map.insert_or_assign(11, "eleven");
  EXPECT_EQ("eleven", s21_map.at(11));
  EXPECT_EQ(s21_map.size(), 2UL);
  EXPECT_EQ(s21_map.at(11), std_map.at(11));

  s21_map.insert_or_assign(11, "11");
  std_map.insert_or_assign(11, "11");
  EXPECT_EQ(s21_map.size(), 2UL);
  EXPECT_EQ(s21_map.at(11), std_map.at(11));
}

TEST(map_merge, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 4.59};
  std::pair<int, double> pair22{88, 12.902};
  std::pair<int, double> pair33{108, 56.41};

  map<int, double> s21_map_int_ref{pair1, pair2, pair3};

  map<int, double> s21_map_int_res{pair11, pair22, pair33};
  s21_map_int_res.merge(s21_map_int_ref);
  EXPECT_EQ(s21_map_int_res.size(), 6U);
}

TEST(map_swap, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  std::pair<int, double> pair11{78, 4.59};
  std::pair<int, double> pair22{88, 12.902};
  std::pair<int, double> pair33{108, 56.41};

  map<int, double> s21_map_int_ref{pair1, pair2, pair3};

  map<int, double> s21_map_int_res{pair11, pair22, pair33};
  s21_map_int_res.swap(s21_map_int_ref);
  EXPECT_EQ(s21_map_int_res.size(), 3U);
}

TEST(map_contains, case1) {
  std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{23, 2.77};
  std::pair<int, double> pair3{98, 3.9};
  map<int, double> s21_map_int_ref{pair1, pair2, pair3};
  EXPECT_TRUE(s21_map_int_ref.contains(9));
  EXPECT_TRUE(s21_map_int_ref.contains(23));
  EXPECT_FALSE(s21_map_int_ref.contains(24));
}

TEST(InsertManyTest, InsertNewElements) {
    map<int, std::string> myMap;
    auto results = myMap.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"), std::make_pair(3, "three"));

    EXPECT_EQ(results.size(), 3);
    EXPECT_TRUE(results[0].second);
    EXPECT_TRUE(results[1].second);
    EXPECT_TRUE(results[2].second);

    EXPECT_EQ(myMap.size(), 3);
}