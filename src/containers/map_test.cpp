#include "s21_map.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cassert>
#include <map>
template <typename K, typename T>
void printMapAsTree(const std::map<K, T>& myMap, int indent = 0) {
    for (auto it = myMap.rbegin(); it != myMap.rend(); ++it) {
        std::cout << std::setw(indent) << " " << it->first << ": " << it->second << std::endl;
    }
}


TEST(map_test, insert_simple) {
    std::pair<int, double> pair1{9, 1.4};
  std::pair<int, double> pair2{9, 1.4};
  std::pair<int, double> pair3{9, 1.4};
  std::pair<int, double> pair4{23, 2.77};
  std::pair<int, double> pair5{98, 3.9};

  map<int, double> s21_map;

  std::pair<map<int, double>::iterator, bool> insert1 =
      s21_map.insert(pair1);
  EXPECT_EQ(insert1.first->first, 9);
  EXPECT_EQ(insert1.second, 1);

  std::pair<map<int, double>::iterator, bool> insert2 =
      s21_map.insert(pair2);
  std::pair<map<int, double>::iterator, bool> insert3 =
      s21_map.insert(pair3);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, 0);

  std::pair<map<int, double>::iterator, bool> insert4 =
      s21_map.insert(pair4);
  EXPECT_EQ(insert4.first->first, 23);
  EXPECT_EQ(insert4.second, 1);

  std::pair<map<int, double>::iterator, bool> insert5 =
      s21_map.insert(pair5);
  EXPECT_EQ(insert5.first->first, 98);
  EXPECT_EQ(insert5.second, 1);
  rbtree<int, double>::iterator it = s21_map.begin();

  EXPECT_EQ(s21_map.size(), 3);


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

TEST(Map, EraseOperations) {
    std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{15, 15};
  std::pair<int, int> pair4{4, 4};
  std::pair<int, int> pair5{18, 18};
  std::pair<int, int> pair6{13, 13};
  std::pair<int, int> pair7{16, 16};

  map<int, int> s21_map = {pair1, pair2, pair3, pair4,
                                pair5, pair6, pair7};
  auto it = s21_map.begin();
  printf("begin:%d\n", (*it).first);
  it++;
  it++;
  it++;
  it++;
  s21_map.print_tree();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 4);
  EXPECT_EQ(s21_map.size(), 6U);
  s21_map.print_tree();
    printf("here\n");
  it = s21_map.begin();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.size(), 5U);
  s21_map.print_tree();

  it = s21_map.begin();
  ++it;

  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.size(), 4U);
  s21_map.print_tree();

  it = s21_map.begin();
  it++;
  s21_map.erase(it);
  s21_map.print_tree();

  it = s21_map.begin();
  it++;
  s21_map.erase(it);
  s21_map.print_tree();

  it = s21_map.begin();
  s21_map.erase(it);

  s21_map.print_tree();
    it = s21_map.begin();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.size(), 0);

}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}