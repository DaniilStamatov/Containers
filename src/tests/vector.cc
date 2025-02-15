#include <gtest/gtest.h>
#ifdef LIN
#include <malloc.h>
#endif

#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

#include "../containers/s21_vector.h"

TEST(int_constructors, default) {
  std::vector<int> vec;
  EXPECT_NO_THROW({
    s21::vector<int> test;
    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
  });
}

TEST(int_constructors, n_size) {
  size_t n = 10;
  std::vector<int> vec(n);
  EXPECT_NO_THROW({
    s21::vector<int> test(n);
    EXPECT_EQ(vec.capacity(), (size_t)10);
    EXPECT_EQ(vec.size(), (size_t)10);
    EXPECT_EQ(vec.capacity() == n, test.capacity() == n);
    EXPECT_EQ(vec.size() == n, test.size() == n);
    for (size_t i = 0; i < n; i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });

  // expected to be large
  EXPECT_NO_THROW({
    s21::vector<int> s21_vector(1300);
    std::vector<int> std_vector(1300);
    EXPECT_EQ(std_vector.capacity() == n, s21_vector.capacity() == n);
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    for (size_t i = 0; i < s21_vector.size(); ++i) {
      EXPECT_TRUE(s21_vector[i] == std_vector[i]);
    }
  });

  EXPECT_ANY_THROW(s21::vector<int> test0(-1));
}

TEST(int_constructors, init_list_1) {
  std::vector<int> vec({1, 2, 3, 4});
  EXPECT_NO_THROW({
    s21::vector<int> test({1, 2, 3, 4});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(int_constructors, init_list_2) {
  std::vector<int> vec({});
  EXPECT_NO_THROW({
    s21::vector<int> test({});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(int_constructors, copy) {
  std::vector<int> vec = {1, 2, 3, 4};
  std::vector<int> vec1(vec);

  s21::vector<int> test = {1, 2, 3, 4};
  EXPECT_NO_THROW({
    s21::vector<int> test1(test);

    EXPECT_EQ(vec1.capacity(), test1.capacity());
    EXPECT_EQ(vec1.size(), test1.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec1[i], test1[i]);
    }
    EXPECT_EQ(vec1.data() != vec.data(), test1.data() != test.data());
  });
}

TEST(int_constructors, move) {
  s21::vector<int> test = {1, 2, 3, 4};
  size_t size1 = test.size(), capacity1 = test.capacity();
  int *p = test.data();
  EXPECT_NO_THROW({
    s21::vector<int> test1(std::move(test));
    EXPECT_EQ(capacity1 == test1.capacity(), size1 == test1.size());

    // проверка на то, что участок памяти не изменился в обоих случаях
    EXPECT_TRUE(test1.data() == p);
  });
}

TEST(int_operator, init_list_void) {
  std::vector<int> vec = {1, 2, 3, 4};
  s21::vector<int> test = {1, 2, 3, 4};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(int_operator, init_list_n) {
  std::vector<int> vec(10);
  s21::vector<int> test(10);
  vec = {1, 2, 3, 4};
  test = {1, 2, 3, 4};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(int_operator, copy) {
  s21::vector<int> test1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::vector<int> test2;
  test2 = test1;
  for (size_t i = 0; i < test1.size(); ++i) {
    EXPECT_TRUE(test1[i] == test2[i]);
  }
}

TEST(int_operator, move) {
  s21::vector<int> test1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::vector<int> test2;
  int *p = test1.data();
  test2 = std::move(test1);

  EXPECT_TRUE(test2.data() == p);
}

TEST(int_access, at_normal) {
  s21::vector<int> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<int> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(test.at(5) == vec.at(5));
}

#ifdef LIN
TEST(int_access, at_exceptions) {
  s21::vector<int> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_ANY_THROW(test.at(100));
  EXPECT_ANY_THROW(test.at(-5));
  test.clear();
  EXPECT_ANY_THROW(test.at(5));
}
#endif

TEST(int_access, operator_normal) {
  s21::vector<int> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<int> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(test[5] == vec[5]);
  EXPECT_NO_THROW({ test[7] = 100; });
  EXPECT_TRUE(test[7] == 100);
}

TEST(int_access, operator_ub) {
  s21::vector<int> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<int> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_NO_THROW(test[-1]);
  EXPECT_NO_THROW(test[30]);
}

TEST(int_access, front) {
  s21::vector<int> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<int> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  int my = test.front();
  int std = vec.front();
  EXPECT_TRUE(my == std);
}

TEST(int_access, back) {
  s21::vector<int> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<int> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  int my = test.back();
  int std = vec.back();
  EXPECT_TRUE(my == std);
}

TEST(int_access, data) {
  s21::vector<int> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<int> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(*test.data() == *vec.data());
  EXPECT_TRUE(*(test.data() + 3) == *(vec.data() + 3));
}

TEST(int_iterator, begin) {
  s21::vector<int> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<int> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*test.begin() == *vec.begin());
}

TEST(int_iterator, begin_empty) {
  s21::vector<int> test;
  std::vector<int> vec;
  // std::cout << *vec.begin();
}

TEST(int_iterator, end) {
  s21::vector<int> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<int> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*(test.end() - 1) == *(vec.end() - 1));
}

TEST(int_iterator, end_empty) {
  s21::vector<int> test;
  std::vector<int> vec;
  // std::cout << *vec.end();
}

TEST(int_methods, empty) {
  s21::vector<int> test;
  std::vector<int> vec;
  EXPECT_EQ(test.empty() == true, vec.empty() == true);
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_EQ(test.empty() == false, vec.empty() == false);
}

TEST(int_methods, size) {
  s21::vector<int> test;
  std::vector<int> vec;
  EXPECT_TRUE(test.size() == vec.size());
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_TRUE(test.size() == vec.size());
}

TEST(int_methods, max_size) {
  std::vector<int> vec;
  s21::vector<int> test;
  EXPECT_EQ(vec.max_size(), test.max_size());

  vec = {1, 2, 3, 4, 5};
  test = {6, 7, 8, 9, 0};
  EXPECT_EQ(vec.max_size(), test.max_size());
}

TEST(int_methods, reserve_upscale) {
  s21::vector<int> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<int> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());

  test.reserve(test.size() * 2);
  vec.reserve(vec.size() * 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
#ifdef LIN
  EXPECT_EQ(malloc_usable_size(vec.data()), malloc_usable_size(test.data()));
  std::cout << "std real size = " << malloc_usable_size(vec.data())
            << std::endl;
  std::cout << "s21 real size = " << malloc_usable_size(test.data())
            << std::endl;
#endif
}

TEST(int_methods, reserve_downscale) {
  s21::vector<int> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<int> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());

  test.reserve(test.size() / 2);
  vec.reserve(vec.size() / 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
#ifdef LIN
  EXPECT_EQ(malloc_usable_size(vec.data()), malloc_usable_size(test.data()));
  std::cout << "std real size = " << malloc_usable_size(vec.data())
            << std::endl;
  std::cout << "s21 real size = " << malloc_usable_size(test.data())
            << std::endl;

  EXPECT_ANY_THROW(test.reserve(-1));
#endif
}

TEST(int_methods, reserve_up_down) {
  s21::vector<int> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<int> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());

  test.reserve(test.size() * 2);
  vec.reserve(vec.size() * 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
#ifdef LIN
  EXPECT_EQ(malloc_usable_size(vec.data()), malloc_usable_size(test.data()));
  std::cout << "std real size = " << malloc_usable_size(vec.data())
            << std::endl;
  std::cout << "s21 real size = " << malloc_usable_size(test.data())
            << std::endl;
#endif
  test.reserve(test.capacity() / 2);
  vec.reserve(vec.capacity() / 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
#ifdef LIN
  EXPECT_EQ(malloc_usable_size(vec.data()), malloc_usable_size(test.data()));
  std::cout << "std real size = " << malloc_usable_size(vec.data())
            << std::endl;
  std::cout << "s21 real size = " << malloc_usable_size(test.data())
            << std::endl;
#endif
  test.reserve(test.capacity());
  vec.reserve(vec.capacity());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

TEST(int_methods, capacity) {
  s21::vector<int> test;
  std::vector<int> vec;
  EXPECT_TRUE(test.capacity() == vec.capacity());
  test.reserve(20), vec.reserve(20);
  EXPECT_TRUE(test.capacity() == 20);
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_TRUE(test.capacity() == 20);
}

TEST(int_methods, shrink) {
  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  s21::vector<int> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};

  vec.reserve(20);
  test.reserve(20);
  EXPECT_EQ(vec.capacity(), test.capacity());
#ifdef LIN
  EXPECT_EQ(malloc_usable_size(vec.data()), malloc_usable_size(test.data()));
  std::cout << "std real size = " << malloc_usable_size(vec.data())
            << std::endl;
  std::cout << "s21 real size = " << malloc_usable_size(test.data())
            << std::endl;
#endif

  vec.shrink_to_fit();
  test.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), test.capacity());
#ifdef LIN
  EXPECT_EQ(malloc_usable_size(vec.data()), malloc_usable_size(test.data()));
  std::cout << "std real size = " << malloc_usable_size(vec.data())
            << std::endl;
  std::cout << "s21 real size = " << malloc_usable_size(test.data())
            << std::endl;
#endif
}

TEST(int_methods, clear) {
  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  s21::vector<int> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  vec.clear();
  test.clear();
  std::cout << "std: size = " << vec.size() << " cap = " << vec.capacity()
            << std::endl;
  std::cout << "s21: size = " << test.size() << " cap = " << test.capacity()
            << std::endl;
#ifdef LIN
  EXPECT_EQ(malloc_usable_size(vec.data()), malloc_usable_size(test.data()));
  std::cout << "std real size = " << malloc_usable_size(vec.data())
            << std::endl;
  std::cout << "s21 real size = " << malloc_usable_size(test.data())
            << std::endl;
#endif
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(int_methods, insert) {
  std::vector<int> vec;
  s21::vector<int> test;
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.insert(vec.begin(), 1);
  test.insert(test.begin(), 1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.insert(vec.begin(), 1);
  test.insert(test.begin(), 1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.insert(vec.begin(), 1);
  test.insert(test.begin(), 1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.insert(vec.begin(), 1);
  test.insert(test.begin(), 1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.insert(vec.begin(), 1);
  test.insert(test.begin(), 1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.insert(vec.begin(), 1);
  test.insert(test.begin(), 1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

TEST(int_methods, erase) {
  
}

// ----------------------------------------BOOL------------------------------------------------

TEST(bool_constructors, n_size) {
  size_t n = 67;
  std::vector<bool> vec(n);
  s21::vector<bool> test(n);

  std::cout << "std: size = " << vec.size() << " cap = " << vec.capacity()
            << std::endl;
  std::cout << "s21: size = " << test.size() << " cap = " << test.capacity()
            << std::endl;
  EXPECT_EQ(vec.capacity() == n, test.capacity() == n);
  EXPECT_EQ(vec.size(), test.size());
  for (size_t i = 0; i < n; i++) {
    EXPECT_EQ(vec[i], test[i]);
  }

  // EXPECT_ANY_THROW(s21::vector<bool> test0(-1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}