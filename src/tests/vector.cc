#include <gtest/gtest.h>
#ifdef LIN
#include <malloc.h>
#endif

#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

#include "../containers/s21_vector.h"

// ----------------------------------------INT------------------------------------------------

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
    EXPECT_EQ(std_vector.capacity(), (size_t)1300);
    EXPECT_EQ(std_vector.size(), (size_t)1300);
    EXPECT_EQ(std_vector.capacity(), s21_vector.capacity());
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

TEST(int_iterator, end) {
  s21::vector<int> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<int> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*(test.end() - 1) == *(vec.end() - 1));
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
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  // std::cout << "std: size = " << vec.size() << " cap = " << vec.capacity()
  //           << std::endl;
  // std::cout << "s21: size = " << test.size() << " cap = " << test.capacity()
  //           << std::endl;
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

TEST(int_methods, insert_begin) {
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

TEST(int_methods, insert) {
  std::vector<int> vec = {1, 2, 3, 4};
  s21::vector<int> test = {1, 2, 3, 4};
  vec.insert(vec.begin() + 2, 5);
  test.insert(test.begin() + 2, 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(int_methods, insert_end) {
  std::vector<int> vec = {1, 2, 3, 4};
  s21::vector<int> test = {1, 2, 3, 4};
  vec.insert(vec.end(), 5);
  test.insert(test.end(), 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(int_methods, erase_void) {
  std::vector<int> vec;
  s21::vector<int> test;
  vec.erase(vec.begin());
  test.erase(test.begin());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

TEST(int_methods, erase) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  s21::vector<int> test = {1, 2, 3, 4, 5};
  vec.erase(vec.begin() + 2);
  test.erase(test.begin() + 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(int_methods, erase_end) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  s21::vector<int> test = {1, 2, 3, 4, 5};
  vec.erase(vec.end());
  test.erase(test.end());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(int_methods, push_back_void) {
  std::vector<int> vec;
  s21::vector<int> test;
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(1);
  test.push_back(1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[0], 1);
}

TEST(int_methods, push_back_initlist) {
  std::vector<int> vec = {1, 2, 3};
  s21::vector<int> test = {1, 2, 3};
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(4);
  test.push_back(4);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[3], 4);
}

TEST(int_methods, push_back_n) {
  std::vector<int> vec(10);
  s21::vector<int> test(10);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(5);
  test.push_back(5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[10], 5);
}

TEST(int_methods, pop_back) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  s21::vector<int> test = {1, 2, 3, 4, 5};
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(int_methods, pop_back_void) {
  std::vector<int> vec;
  s21::vector<int> test;
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

TEST(int_bonus, insert_many) {
  s21::vector<int> test;
  std::cout << test.capacity() << " " << test.size() << std::endl;
  test.insert_many(test.begin(), 1, 2, 3, 4, 5, 6, 7, 8, 9);
  std::cout << test.capacity() << " " << test.size() << std::endl;
}

TEST(int_bonus, insert_many_back) {
  s21::vector<int> test;
  std::cout << test.capacity() << " " << test.size() << std::endl;
  test.insert_many_back(1, 2, 3, 4, 5, 6, 7, 8, 9);
  std::cout << test.capacity() << " " << test.size() << std::endl;
}

// ----------------------------------------FLOAT------------------------------------------------

TEST(float_constructors, default) {
  std::vector<float> vec;
  EXPECT_NO_THROW({
    s21::vector<float> test;
    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
  });
}

TEST(float_constructors, n_size) {
  size_t n = 10;
  std::vector<float> vec(n);
  EXPECT_NO_THROW({
    s21::vector<float> test(n);
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
    s21::vector<float> s21_vector(1300);
    std::vector<float> std_vector(1300);
    EXPECT_EQ(std_vector.capacity(), (size_t)1300);
    EXPECT_EQ(std_vector.size(), (size_t)1300);
    EXPECT_EQ(std_vector.capacity(), s21_vector.capacity());
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    for (size_t i = 0; i < s21_vector.size(); ++i) {
      EXPECT_TRUE(s21_vector[i] == std_vector[i]);
    }
  });

  EXPECT_ANY_THROW(s21::vector<float> test0(-1));
}

TEST(float_constructors, init_list_1) {
  std::vector<float> vec({1, 2, 3, 4});
  EXPECT_NO_THROW({
    s21::vector<float> test({1, 2, 3, 4});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(float_constructors, init_list_2) {
  std::vector<float> vec({});
  EXPECT_NO_THROW({
    s21::vector<float> test({});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(float_constructors, copy) {
  std::vector<float> vec = {1, 2, 3, 4};
  std::vector<float> vec1(vec);

  s21::vector<float> test = {1, 2, 3, 4};
  EXPECT_NO_THROW({
    s21::vector<float> test1(test);

    EXPECT_EQ(vec1.capacity(), test1.capacity());
    EXPECT_EQ(vec1.size(), test1.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec1[i], test1[i]);
    }
    EXPECT_EQ(vec1.data() != vec.data(), test1.data() != test.data());
  });
}

TEST(float_constructors, move) {
  s21::vector<float> test = {1, 2, 3, 4};
  size_t size1 = test.size(), capacity1 = test.capacity();
  float *p = test.data();
  EXPECT_NO_THROW({
    s21::vector<float> test1(std::move(test));
    EXPECT_EQ(capacity1 == test1.capacity(), size1 == test1.size());

    // проверка на то, что участок памяти не изменился в обоих случаях
    EXPECT_TRUE(test1.data() == p);
  });
}

TEST(float_operator, init_list_void) {
  std::vector<float> vec = {1, 2, 3, 4};
  s21::vector<float> test = {1, 2, 3, 4};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(float_operator, init_list_n) {
  std::vector<float> vec(10);
  s21::vector<float> test(10);
  vec = {1, 2, 3, 4};
  test = {1, 2, 3, 4};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(float_operator, copy) {
  s21::vector<float> test1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::vector<float> test2;
  test2 = test1;
  for (size_t i = 0; i < test1.size(); ++i) {
    EXPECT_TRUE(test1[i] == test2[i]);
  }
}

TEST(float_operator, move) {
  s21::vector<float> test1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::vector<float> test2;
  float *p = test1.data();
  test2 = std::move(test1);

  EXPECT_TRUE(test2.data() == p);
}

TEST(float_access, at_normal) {
  s21::vector<float> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<float> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(test.at(5) == vec.at(5));
}

#ifdef LIN
TEST(float_access, at_exceptions) {
  s21::vector<float> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_ANY_THROW(test.at(100));
  EXPECT_ANY_THROW(test.at(-5));
  test.clear();
  EXPECT_ANY_THROW(test.at(5));
}
#endif

TEST(float_access, operator_normal) {
  s21::vector<float> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<float> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(test[5] == vec[5]);
  EXPECT_NO_THROW({ test[7] = 100; });
  EXPECT_TRUE(test[7] == 100);
}

TEST(float_access, operator_ub) {
  s21::vector<float> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<float> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_NO_THROW(test[-1]);
  EXPECT_NO_THROW(test[30]);
}

TEST(float_access, front) {
  s21::vector<float> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<float> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  int my = test.front();
  int std = vec.front();
  EXPECT_TRUE(my == std);
}

TEST(float_access, back) {
  s21::vector<float> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<float> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  int my = test.back();
  int std = vec.back();
  EXPECT_TRUE(my == std);
}

TEST(float_access, data) {
  s21::vector<float> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<float> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(*test.data() == *vec.data());
  EXPECT_TRUE(*(test.data() + 3) == *(vec.data() + 3));
}

TEST(float_iterator, begin) {
  s21::vector<float> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<float> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*test.begin() == *vec.begin());
}

TEST(float_iterator, end) {
  s21::vector<float> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<float> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*(test.end() - 1) == *(vec.end() - 1));
}

TEST(float_methods, empty) {
  s21::vector<float> test;
  std::vector<float> vec;
  EXPECT_EQ(test.empty() == true, vec.empty() == true);
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_EQ(test.empty() == false, vec.empty() == false);
}

TEST(float_methods, size) {
  s21::vector<float> test;
  std::vector<float> vec;
  EXPECT_TRUE(test.size() == vec.size());
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_TRUE(test.size() == vec.size());
}

TEST(float_methods, max_size) {
  std::vector<float> vec;
  s21::vector<float> test;
  EXPECT_EQ(vec.max_size(), test.max_size());

  vec = {1, 2, 3, 4, 5};
  test = {6, 7, 8, 9, 0};
  EXPECT_EQ(vec.max_size(), test.max_size());
}

TEST(float_methods, reserve_upscale) {
  s21::vector<float> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<float> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(float_methods, reserve_downscale) {
  s21::vector<float> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<float> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(float_methods, reserve_up_down) {
  s21::vector<float> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<float> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(float_methods, capacity) {
  s21::vector<float> test;
  std::vector<float> vec;
  EXPECT_TRUE(test.capacity() == vec.capacity());
  test.reserve(20), vec.reserve(20);
  EXPECT_TRUE(test.capacity() == 20);
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_TRUE(test.capacity() == 20);
}

TEST(float_methods, shrink) {
  std::vector<float> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  s21::vector<float> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};

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

TEST(float_methods, clear) {
  std::vector<float> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  s21::vector<float> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  vec.clear();
  test.clear();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  // std::cout << "std: size = " << vec.size() << " cap = " << vec.capacity()
  //           << std::endl;
  // std::cout << "s21: size = " << test.size() << " cap = " << test.capacity()
  //           << std::endl;
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

TEST(float_methods, insert_begin) {
  std::vector<float> vec;
  s21::vector<float> test;
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

TEST(float_methods, insert) {
  std::vector<float> vec = {1, 2, 3, 4};
  s21::vector<float> test = {1, 2, 3, 4};
  vec.insert(vec.begin() + 2, 5);
  test.insert(test.begin() + 2, 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(float_methods, insert_end) {
  std::vector<float> vec = {1, 2, 3, 4};
  s21::vector<float> test = {1, 2, 3, 4};
  vec.insert(vec.end(), 5);
  test.insert(test.end(), 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(float_methods, erase_void) {
  std::vector<float> vec;
  s21::vector<float> test;
  vec.erase(vec.begin());
  test.erase(test.begin());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

TEST(float_methods, erase) {
  std::vector<float> vec = {1, 2, 3, 4, 5};
  s21::vector<float> test = {1, 2, 3, 4, 5};
  vec.erase(vec.begin() + 2);
  test.erase(test.begin() + 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(float_methods, erase_end) {
  std::vector<float> vec = {1, 2, 3, 4, 5};
  s21::vector<float> test = {1, 2, 3, 4, 5};
  vec.erase(vec.end());
  test.erase(test.end());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(float_methods, push_back_void) {
  std::vector<float> vec;
  s21::vector<float> test;
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(1);
  test.push_back(1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[0], 1);
}

TEST(float_methods, push_back_initlist) {
  std::vector<float> vec = {1, 2, 3};
  s21::vector<float> test = {1, 2, 3};
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(4);
  test.push_back(4);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[3], 4);
}

TEST(float_methods, push_back_n) {
  std::vector<float> vec(10);
  s21::vector<float> test(10);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(5);
  test.push_back(5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[10], 5);
}

TEST(float_methods, pop_back) {
  std::vector<float> vec = {1, 2, 3, 4, 5};
  s21::vector<float> test = {1, 2, 3, 4, 5};
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(float_methods, pop_back_void) {
  std::vector<float> vec;
  s21::vector<float> test;
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

// ----------------------------------------DOUBLE------------------------------------------------

TEST(double_constructors, default) {
  std::vector<double> vec;
  EXPECT_NO_THROW({
    s21::vector<double> test;
    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
  });
}

TEST(double_constructors, n_size) {
  size_t n = 10;
  std::vector<double> vec(n);
  EXPECT_NO_THROW({
    s21::vector<double> test(n);
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
    s21::vector<double> s21_vector(1300);
    std::vector<double> std_vector(1300);
    EXPECT_EQ(std_vector.capacity(), (size_t)1300);
    EXPECT_EQ(std_vector.size(), (size_t)1300);
    EXPECT_EQ(std_vector.capacity(), s21_vector.capacity());
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    for (size_t i = 0; i < s21_vector.size(); ++i) {
      EXPECT_TRUE(s21_vector[i] == std_vector[i]);
    }
  });

  EXPECT_ANY_THROW(s21::vector<double> test0(-1));
}

TEST(double_constructors, init_list_1) {
  std::vector<double> vec({1, 2, 3, 4});
  EXPECT_NO_THROW({
    s21::vector<double> test({1, 2, 3, 4});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(double_constructors, init_list_2) {
  std::vector<double> vec({});
  EXPECT_NO_THROW({
    s21::vector<double> test({});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(double_constructors, copy) {
  std::vector<double> vec = {1, 2, 3, 4};
  std::vector<double> vec1(vec);

  s21::vector<double> test = {1, 2, 3, 4};
  EXPECT_NO_THROW({
    s21::vector<double> test1(test);

    EXPECT_EQ(vec1.capacity(), test1.capacity());
    EXPECT_EQ(vec1.size(), test1.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec1[i], test1[i]);
    }
    EXPECT_EQ(vec1.data() != vec.data(), test1.data() != test.data());
  });
}

TEST(double_constructors, move) {
  s21::vector<double> test = {1, 2, 3, 4};
  size_t size1 = test.size(), capacity1 = test.capacity();
  double *p = test.data();
  EXPECT_NO_THROW({
    s21::vector<double> test1(std::move(test));
    EXPECT_EQ(capacity1 == test1.capacity(), size1 == test1.size());

    // проверка на то, что участок памяти не изменился в обоих случаях
    EXPECT_TRUE(test1.data() == p);
  });
}

TEST(double_operator, init_list_void) {
  std::vector<double> vec = {1, 2, 3, 4};
  s21::vector<double> test = {1, 2, 3, 4};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(double_operator, init_list_n) {
  std::vector<double> vec(10);
  s21::vector<double> test(10);
  vec = {1, 2, 3, 4};
  test = {1, 2, 3, 4};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(double_operator, copy) {
  s21::vector<double> test1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::vector<double> test2;
  test2 = test1;
  for (size_t i = 0; i < test1.size(); ++i) {
    EXPECT_TRUE(test1[i] == test2[i]);
  }
}

TEST(double_operator, move) {
  s21::vector<double> test1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::vector<double> test2;
  double *p = test1.data();
  test2 = std::move(test1);

  EXPECT_TRUE(test2.data() == p);
}

TEST(double_access, at_normal) {
  s21::vector<double> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<double> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(test.at(5) == vec.at(5));
}

#ifdef LIN
TEST(double_access, at_exceptions) {
  s21::vector<double> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_ANY_THROW(test.at(100));
  EXPECT_ANY_THROW(test.at(-5));
  test.clear();
  EXPECT_ANY_THROW(test.at(5));
}
#endif

TEST(double_access, operator_normal) {
  s21::vector<double> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<double> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(test[5] == vec[5]);
  EXPECT_NO_THROW({ test[7] = 100; });
  EXPECT_TRUE(test[7] == 100);
}

TEST(double_access, operator_ub) {
  s21::vector<double> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<double> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_NO_THROW(test[-1]);
  EXPECT_NO_THROW(test[30]);
}

TEST(double_access, front) {
  s21::vector<double> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<double> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  int my = test.front();
  int std = vec.front();
  EXPECT_TRUE(my == std);
}

TEST(double_access, back) {
  s21::vector<double> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<double> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  int my = test.back();
  int std = vec.back();
  EXPECT_TRUE(my == std);
}

TEST(double_access, data) {
  s21::vector<double> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<double> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(*test.data() == *vec.data());
  EXPECT_TRUE(*(test.data() + 3) == *(vec.data() + 3));
}

TEST(double_iterator, begin) {
  s21::vector<double> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<double> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*test.begin() == *vec.begin());
}

TEST(double_iterator, end) {
  s21::vector<double> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<double> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*(test.end() - 1) == *(vec.end() - 1));
}

TEST(double_methods, empty) {
  s21::vector<double> test;
  std::vector<double> vec;
  EXPECT_EQ(test.empty() == true, vec.empty() == true);
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_EQ(test.empty() == false, vec.empty() == false);
}

TEST(double_methods, size) {
  s21::vector<double> test;
  std::vector<double> vec;
  EXPECT_TRUE(test.size() == vec.size());
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_TRUE(test.size() == vec.size());
}

TEST(double_methods, max_size) {
  std::vector<double> vec;
  s21::vector<double> test;
  EXPECT_EQ(vec.max_size(), test.max_size());

  vec = {1, 2, 3, 4, 5};
  test = {6, 7, 8, 9, 0};
  EXPECT_EQ(vec.max_size(), test.max_size());
}

TEST(double_methods, reserve_upscale) {
  s21::vector<double> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<double> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(double_methods, reserve_downscale) {
  s21::vector<double> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<double> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(double_methods, reserve_up_down) {
  s21::vector<double> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<double> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(double_methods, capacity) {
  s21::vector<double> test;
  std::vector<double> vec;
  EXPECT_TRUE(test.capacity() == vec.capacity());
  test.reserve(20), vec.reserve(20);
  EXPECT_TRUE(test.capacity() == 20);
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_TRUE(test.capacity() == 20);
}

TEST(double_methods, shrink) {
  std::vector<double> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  s21::vector<double> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};

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

TEST(double_methods, clear) {
  std::vector<double> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  s21::vector<double> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  vec.clear();
  test.clear();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  // std::cout << "std: size = " << vec.size() << " cap = " << vec.capacity()
  //           << std::endl;
  // std::cout << "s21: size = " << test.size() << " cap = " << test.capacity()
  //           << std::endl;
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

TEST(double_methods, insert_begin) {
  std::vector<double> vec;
  s21::vector<double> test;
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

TEST(double_methods, insert) {
  std::vector<double> vec = {1, 2, 3, 4};
  s21::vector<double> test = {1, 2, 3, 4};
  vec.insert(vec.begin() + 2, 5);
  test.insert(test.begin() + 2, 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(double_methods, insert_end) {
  std::vector<double> vec = {1, 2, 3, 4};
  s21::vector<double> test = {1, 2, 3, 4};
  vec.insert(vec.end(), 5);
  test.insert(test.end(), 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(double_methods, erase_void) {
  std::vector<double> vec;
  s21::vector<double> test;
  vec.erase(vec.begin());
  test.erase(test.begin());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

TEST(double_methods, erase) {
  std::vector<double> vec = {1, 2, 3, 4, 5};
  s21::vector<double> test = {1, 2, 3, 4, 5};
  vec.erase(vec.begin() + 2);
  test.erase(test.begin() + 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(double_methods, erase_end) {
  std::vector<double> vec = {1, 2, 3, 4, 5};
  s21::vector<double> test = {1, 2, 3, 4, 5};
  vec.erase(vec.end());
  test.erase(test.end());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(double_methods, push_back_void) {
  std::vector<double> vec;
  s21::vector<double> test;
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(1);
  test.push_back(1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[0], 1);
}

TEST(double_methods, push_back_initlist) {
  std::vector<double> vec = {1, 2, 3};
  s21::vector<double> test = {1, 2, 3};
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(4);
  test.push_back(4);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[3], 4);
}

TEST(double_methods, push_back_n) {
  std::vector<double> vec(10);
  s21::vector<double> test(10);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(5);
  test.push_back(5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[10], 5);
}

TEST(double_methods, pop_back) {
  std::vector<double> vec = {1, 2, 3, 4, 5};
  s21::vector<double> test = {1, 2, 3, 4, 5};
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(double_methods, pop_back_void) {
  std::vector<double> vec;
  s21::vector<double> test;
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

// ----------------------------------------CHAR------------------------------------------------

TEST(char_constructors, default) {
  std::vector<char> vec;
  EXPECT_NO_THROW({
    s21::vector<char> test;
    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
  });
}

TEST(char_constructors, n_size) {
  size_t n = 10;
  std::vector<char> vec(n);
  EXPECT_NO_THROW({
    s21::vector<char> test(n);
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
    s21::vector<char> s21_vector(1300);
    std::vector<char> std_vector(1300);
    EXPECT_EQ(std_vector.capacity(), (size_t)1300);
    EXPECT_EQ(std_vector.size(), (size_t)1300);
    EXPECT_EQ(std_vector.capacity(), s21_vector.capacity());
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    for (size_t i = 0; i < s21_vector.size(); ++i) {
      EXPECT_TRUE(s21_vector[i] == std_vector[i]);
    }
  });

  EXPECT_ANY_THROW(s21::vector<char> test0(-1));
}

TEST(char_constructors, init_list_1) {
  std::vector<char> vec({1, 2, 3, 4});
  EXPECT_NO_THROW({
    s21::vector<char> test({1, 2, 3, 4});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(char_constructors, init_list_2) {
  std::vector<char> vec({});
  EXPECT_NO_THROW({
    s21::vector<char> test({});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(char_constructors, copy) {
  std::vector<char> vec = {1, 2, 3, 4};
  std::vector<char> vec1(vec);

  s21::vector<char> test = {1, 2, 3, 4};
  EXPECT_NO_THROW({
    s21::vector<char> test1(test);

    EXPECT_EQ(vec1.capacity(), test1.capacity());
    EXPECT_EQ(vec1.size(), test1.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec1[i], test1[i]);
    }
    EXPECT_EQ(vec1.data() != vec.data(), test1.data() != test.data());
  });
}

TEST(char_constructors, move) {
  s21::vector<char> test = {1, 2, 3, 4};
  size_t size1 = test.size(), capacity1 = test.capacity();
  char *p = test.data();
  EXPECT_NO_THROW({
    s21::vector<char> test1(std::move(test));
    EXPECT_EQ(capacity1 == test1.capacity(), size1 == test1.size());

    // проверка на то, что участок памяти не изменился в обоих случаях
    EXPECT_TRUE(test1.data() == p);
  });
}

TEST(char_operator, init_list_void) {
  std::vector<char> vec = {1, 2, 3, 4};
  s21::vector<char> test = {1, 2, 3, 4};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(char_operator, init_list_n) {
  std::vector<char> vec(10);
  s21::vector<char> test(10);
  vec = {1, 2, 3, 4};
  test = {1, 2, 3, 4};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(char_operator, copy) {
  s21::vector<char> test1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::vector<char> test2;
  test2 = test1;
  for (size_t i = 0; i < test1.size(); ++i) {
    EXPECT_TRUE(test1[i] == test2[i]);
  }
}

TEST(char_operator, move) {
  s21::vector<char> test1({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  s21::vector<char> test2;
  char *p = test1.data();
  test2 = std::move(test1);

  EXPECT_TRUE(test2.data() == p);
}

TEST(char_access, at_normal) {
  s21::vector<char> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<char> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(test.at(5) == vec.at(5));
}

#ifdef LIN
TEST(char_access, at_exceptions) {
  s21::vector<char> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_ANY_THROW(test.at(100));
  EXPECT_ANY_THROW(test.at(-5));
  test.clear();
  EXPECT_ANY_THROW(test.at(5));
}
#endif

TEST(char_access, operator_normal) {
  s21::vector<char> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<char> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(test[5] == vec[5]);
  EXPECT_NO_THROW({ test[7] = 100; });
  EXPECT_TRUE(test[7] == 100);
}

TEST(char_access, operator_ub) {
  s21::vector<char> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<char> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_NO_THROW(test[-1]);
  EXPECT_NO_THROW(test[30]);
}

TEST(char_access, front) {
  s21::vector<char> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<char> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  int my = test.front();
  int std = vec.front();
  EXPECT_TRUE(my == std);
}

TEST(char_access, back) {
  s21::vector<char> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<char> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  int my = test.back();
  int std = vec.back();
  EXPECT_TRUE(my == std);
}

TEST(char_access, data) {
  s21::vector<char> test({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::vector<char> vec({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_TRUE(*test.data() == *vec.data());
  EXPECT_TRUE(*(test.data() + 3) == *(vec.data() + 3));
}

TEST(char_iterator, begin) {
  s21::vector<char> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<char> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*test.begin() == *vec.begin());
}

TEST(char_iterator, end) {
  s21::vector<char> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<char> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  EXPECT_TRUE(*(test.end() - 1) == *(vec.end() - 1));
}

TEST(char_methods, empty) {
  s21::vector<char> test;
  std::vector<char> vec;
  EXPECT_EQ(test.empty() == true, vec.empty() == true);
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_EQ(test.empty() == false, vec.empty() == false);
}

TEST(char_methods, size) {
  s21::vector<char> test;
  std::vector<char> vec;
  EXPECT_TRUE(test.size() == vec.size());
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_TRUE(test.size() == vec.size());
}

TEST(char_methods, max_size) {
  std::vector<char> vec;
  s21::vector<char> test;
  EXPECT_EQ(vec.max_size(), test.max_size());

  vec = {1, 2, 3, 4, 5};
  test = {6, 7, 8, 9, 0};
  EXPECT_EQ(vec.max_size(), test.max_size());
}

TEST(char_methods, reserve_upscale) {
  s21::vector<char> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<char> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(char_methods, reserve_downscale) {
  s21::vector<char> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<char> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(char_methods, reserve_up_down) {
  s21::vector<char> test({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
  std::vector<char> vec({88, 1, 2, 3, 4, 5, 6, 7, 8, 99});
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

TEST(char_methods, capacity) {
  s21::vector<char> test;
  std::vector<char> vec;
  EXPECT_TRUE(test.capacity() == vec.capacity());
  test.reserve(20), vec.reserve(20);
  EXPECT_TRUE(test.capacity() == 20);
  test = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  vec = {88, 1, 2, 3, 4, 5, 6, 7, 8, 99};
  EXPECT_TRUE(test.capacity() == 20);
}

TEST(char_methods, shrink) {
  std::vector<char> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  s21::vector<char> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};

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

TEST(char_methods, clear) {
  std::vector<char> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  s21::vector<char> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1};
  vec.clear();
  test.clear();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  // std::cout << "std: size = " << vec.size() << " cap = " << vec.capacity()
  //           << std::endl;
  // std::cout << "s21: size = " << test.size() << " cap = " << test.capacity()
  //           << std::endl;
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

TEST(char_methods, insert_begin) {
  std::vector<char> vec;
  s21::vector<char> test;
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

TEST(char_methods, insert) {
  std::vector<char> vec = {1, 2, 3, 4};
  s21::vector<char> test = {1, 2, 3, 4};
  vec.insert(vec.begin() + 2, 5);
  test.insert(test.begin() + 2, 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(char_methods, insert_end) {
  std::vector<char> vec = {1, 2, 3, 4};
  s21::vector<char> test = {1, 2, 3, 4};
  vec.insert(vec.end(), 5);
  test.insert(test.end(), 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(char_methods, erase_void) {
  std::vector<char> vec;
  s21::vector<char> test;
  vec.erase(vec.begin());
  test.erase(test.begin());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

TEST(char_methods, erase) {
  std::vector<char> vec = {1, 2, 3, 4, 5};
  s21::vector<char> test = {1, 2, 3, 4, 5};
  vec.erase(vec.begin() + 2);
  test.erase(test.begin() + 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(char_methods, erase_end) {
  std::vector<char> vec = {1, 2, 3, 4, 5};
  s21::vector<char> test = {1, 2, 3, 4, 5};
  vec.erase(vec.end());
  test.erase(test.end());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(char_methods, push_back_void) {
  std::vector<char> vec;
  s21::vector<char> test;
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(1);
  test.push_back(1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[0], 1);
}

TEST(char_methods, push_back_initlist) {
  std::vector<char> vec = {1, 2, 3};
  s21::vector<char> test = {1, 2, 3};
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(4);
  test.push_back(4);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[3], 4);
}

TEST(char_methods, push_back_n) {
  std::vector<char> vec(10);
  s21::vector<char> test(10);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(5);
  test.push_back(5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[10], 5);
}

TEST(char_methods, pop_back) {
  std::vector<char> vec = {1, 2, 3, 4, 5};
  s21::vector<char> test = {1, 2, 3, 4, 5};
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(char_methods, pop_back_void) {
  std::vector<char> vec;
  s21::vector<char> test;
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

// ----------------------------------------BOOL------------------------------------------------

TEST(bool_constructors, default) {
  std::vector<bool> vec;
  EXPECT_NO_THROW({
    s21::vector<bool> test;
    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
  });
}

TEST(bool_constructors, n_size) {
  size_t n = 10;
  std::vector<bool> vec(n);
  EXPECT_NO_THROW({
    s21::vector<bool> test(n);
    EXPECT_EQ(vec.capacity(), (size_t)__WORDSIZE);
    EXPECT_EQ(vec.size(), (size_t)10);
    EXPECT_EQ(vec.capacity() == n, test.capacity() == n);
    EXPECT_EQ(vec.size() == n, test.size() == n);
    for (size_t i = 0; i < n; i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });

  // expected to be large
  EXPECT_NO_THROW({
    s21::vector<bool> s21_vector(1300);
    std::vector<bool> std_vector(1300);
    size_t real_cap = 1300 / __WORDSIZE * __WORDSIZE +
                      ((1300 % __WORDSIZE) > 0 ? __WORDSIZE : 0);
    EXPECT_EQ(std_vector.capacity(), real_cap);
    EXPECT_EQ(std_vector.size(), (size_t)1300);
    EXPECT_EQ(std_vector.capacity(), s21_vector.capacity());
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    EXPECT_EQ(std_vector.size(), s21_vector.size());
    for (size_t i = 0; i < s21_vector.size(); ++i) {
      EXPECT_TRUE(s21_vector[i] == std_vector[i]);
    }
  });

  EXPECT_ANY_THROW(s21::vector<bool> test0(-1));
}

TEST(bool_constructors, init_list_1) {
  std::vector<bool> vec({true, false, true, false});
  EXPECT_NO_THROW({
    s21::vector<bool> test({true, false, true, false});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(bool_constructors, init_list_2) {
  std::vector<bool> vec({});
  EXPECT_NO_THROW({
    s21::vector<bool> test({});

    EXPECT_EQ(vec.capacity(), test.capacity());
    EXPECT_EQ(vec.size(), test.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec[i], test[i]);
    }
  });
}

TEST(bool_constructors, copy) {
  std::vector<bool> vec = {false, true, true, false};
  std::vector<bool> vec1(vec);

  s21::vector<bool> test = {false, true, true, false};
  EXPECT_NO_THROW({
    s21::vector<bool> test1(test);

    EXPECT_EQ(vec1.capacity(), test1.capacity());
    EXPECT_EQ(vec1.size(), test1.size());
    for (size_t i = 0; i < vec.size(); i++) {
      EXPECT_EQ(vec1[i], test1[i]);
    }
    // EXPECT_EQ(vec1.data() != vec.data(), test1.data() != test.data());
  });
}

TEST(bool_constructors, move) {
  s21::vector<bool> test = {false, false};
  size_t size1 = test.size(), capacity1 = test.capacity();
  bool *p = test.data();
  EXPECT_NO_THROW({
    s21::vector<bool> test1(std::move(test));
    EXPECT_EQ(capacity1 == test1.capacity(), size1 == test1.size());

    // проверка на то, что участок памяти не изменился в обоих случаях
    EXPECT_TRUE(test1.data() == p);
  });
}

TEST(bool_operator, init_list_void) {
  std::vector<bool> vec = {false, false, false, true};
  s21::vector<bool> test = {false, false, false, true};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(bool_operator, init_list_n) {
  std::vector<bool> vec(10);
  s21::vector<bool> test(10);
  vec = {true, true, false, false};
  test = {true, true, false, false};
  EXPECT_EQ(vec.size() == 4, test.size() == 4);
  EXPECT_EQ(vec.capacity() == 4, test.capacity() == 4);
}

TEST(bool_operator, copy) {
  s21::vector<bool> test1(
      {false, true, false, true, false, true, false, true, true, false});
  s21::vector<bool> test2;
  test2 = test1;
  for (size_t i = 0; i < test1.size(); ++i) {
    EXPECT_TRUE(test1[i] == test2[i]);
  }
}

TEST(bool_operator, move) {
  s21::vector<bool> test1(
      {false, true, true, true, false, false, false, true, true, false});
  s21::vector<bool> test2;
  bool *p = test1.data();
  test2 = std::move(test1);

  EXPECT_TRUE(test2.data() == p);
}

TEST(bool_access, at_normal) {
  s21::vector<bool> test({false, false, true, true, false, true, false});
  std::vector<bool> vec({false, false, true, true, false, true, false});
  EXPECT_TRUE(test.at(5) == vec.at(5));
}

#ifdef LIN
TEST(bool_access, at_exceptions) {
  s21::vector<bool> test({false, false, true});
  EXPECT_ANY_THROW(test.at(100));
  EXPECT_ANY_THROW(test.at(-5));
  test.clear();
  EXPECT_ANY_THROW(test.at(5));
}
#endif

TEST(bool_access, operator_normal) {
  s21::vector<bool> test({true, false, false, true, true});
  std::vector<bool> vec({true, false, false, true, true});
  EXPECT_TRUE(test[5] == vec[5]);
  EXPECT_NO_THROW({ test[3] = false; });
  EXPECT_TRUE(test[7] == false);
}

TEST(bool_access, operator_ub) {
  s21::vector<bool> test({true, false, true, true, false});
  std::vector<bool> vec({true, false, true, true, false});
  EXPECT_NO_THROW(test[-1]);
  EXPECT_NO_THROW(test[30]);
}

TEST(bool_access, front) {
  s21::vector<bool> test({false, false, false, false, false});
  std::vector<bool> vec({false, false, false, false, false});
  int my = test.front();
  int std = vec.front();
  EXPECT_TRUE(my == std);
}

TEST(bool_access, back) {
  s21::vector<bool> test({false, true, true, false});
  std::vector<bool> vec({false, true, true, false});
  int my = test.back();
  int std = vec.back();
  EXPECT_TRUE(my == std);
}

// не работает т.к. булевый вектор
// TEST(bool_access, data) {
//   s21::vector<bool> test({false, true, false, false, true, false, true, true,
//   false}); std::vector<bool> vec({false, true, false, false, true, false,
//   true, true, false}); EXPECT_TRUE(*test.data() == *vec.data());
//   EXPECT_TRUE(*(test.data() + 3) == *(vec.data() + 3));
// }

TEST(bool_iterator, begin) {
  s21::vector<bool> test(
      {false, true, false, false, true, false, true, true, false});
  std::vector<bool> vec(
      {false, true, false, false, true, false, true, true, false});
  EXPECT_TRUE(*test.begin() == *vec.begin());
}

TEST(bool_iterator, end) {
  s21::vector<bool> test(
      {false, true, false, false, true, false, true, true, false});
  std::vector<bool> vec(
      {false, true, false, false, true, false, true, true, false});
  EXPECT_TRUE(*(test.end() - 1) == *(vec.end() - 1));
}

TEST(bool_methods, empty) {
  s21::vector<bool> test;
  std::vector<bool> vec;
  EXPECT_EQ(test.empty() == true, vec.empty() == true);
  test = {false, true, false, false, true, false, true, true, false};
  vec = {false, true, false, false, true, false, true, true, false};
  EXPECT_EQ(test.empty() == false, vec.empty() == false);
}

TEST(bool_methods, size) {
  s21::vector<bool> test;
  std::vector<bool> vec;
  EXPECT_TRUE(test.size() == vec.size());
  test = {false, true, false, false, true, false, true, true, false};
  vec = {false, true, false, false, true, false, true, true, false};
  EXPECT_TRUE(test.size() == vec.size());
}

TEST(bool_methods, max_size) {
  std::vector<bool> vec;
  s21::vector<bool> test;
  EXPECT_EQ(vec.max_size(), test.max_size());

  vec = {true, false, true};
  test = {false, false, false};
  EXPECT_EQ(vec.max_size(), test.max_size());
}

TEST(bool_methods, reserve_upscale) {
  s21::vector<bool> test(
      {false, true, false, false, true, false, true, true, false});
  std::vector<bool> vec(
      {false, true, false, false, true, false, true, true, false});
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

TEST(bool_methods, reserve_downscale) {
  s21::vector<bool> test(
      {false, true, false, false, true, false, true, true, false});
  std::vector<bool> vec(
      {false, true, false, false, true, false, true, true, false});
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

TEST(bool_methods, reserve_up_down) {
  s21::vector<bool> test(
      {false, true, false, false, true, false, true, true, false});
  std::vector<bool> vec(
      {false, true, false, false, true, false, true, true, false});
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

TEST(bool_methods, capacity) {
  s21::vector<bool> test;
  std::vector<bool> vec;
  EXPECT_TRUE(test.capacity() == vec.capacity());
  test.reserve(20), vec.reserve(20);
  EXPECT_TRUE(test.capacity() == __WORDSIZE);
  test = {false, true, false, false, true, false, true, true, false};
  vec = {false, true, false, false, true, false, true, true, false};
  EXPECT_TRUE(test.capacity() == __WORDSIZE);
}

TEST(bool_methods, shrink) {
  std::vector<bool> vec = {false, true, false, false, true,
                           false, true, true,  false};
  s21::vector<bool> test = {false, true, false, false, true,
                            false, true, true,  false};

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

TEST(bool_methods, clear) {
  std::vector<bool> vec = {false, true, false, false, true,
                           false, true, true,  false};
  s21::vector<bool> test = {false, true, false, false, true,
                            false, true, true,  false};
  vec.clear();
  test.clear();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  // std::cout << "std: size = " << vec.size() << " cap = " << vec.capacity()
  //           << std::endl;
  // std::cout << "s21: size = " << test.size() << " cap = " << test.capacity()
  //           << std::endl;
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

TEST(bool_methods, insert_begin) {
  std::vector<bool> vec;
  s21::vector<bool> test;
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

TEST(bool_methods, insert) {
  std::vector<bool> vec = {true, true, true, false};
  s21::vector<bool> test = {true, true, true, false};
  vec.insert(vec.begin() + 2, 5);
  test.insert(test.begin() + 2, 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(bool_methods, insert_end) {
  std::vector<bool> vec = {true, true, true, false};
  s21::vector<bool> test = {true, true, true, false};
  vec.insert(vec.end(), 5);
  test.insert(test.end(), 5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(bool_methods, erase_void) {
  std::vector<bool> vec;
  s21::vector<bool> test;
  vec.erase(vec.begin());
  test.erase(test.begin());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}

TEST(bool_methods, erase) {
  std::vector<bool> vec = {true, true, true, false, true};
  s21::vector<bool> test = {true, true, true, false, true};
  vec.erase(vec.begin() + 2);
  test.erase(test.begin() + 2);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(bool_methods, erase_end) {
  std::vector<bool> vec = {true, true, true, false, true};
  s21::vector<bool> test = {true, true, true, false, true};
  vec.erase(vec.end());
  test.erase(test.end());
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(bool_methods, push_back_void) {
  std::vector<bool> vec;
  s21::vector<bool> test;
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(1);
  test.push_back(1);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[0], 1);
}

TEST(bool_methods, push_back_initlist) {
  std::vector<bool> vec = {true, true, true};
  s21::vector<bool> test = {true, true, true};
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(4);
  test.push_back(4);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[3], true);
}

TEST(bool_methods, push_back_n) {
  std::vector<bool> vec(10);
  s21::vector<bool> test(10);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  vec.push_back(5);
  test.push_back(5);
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  EXPECT_EQ(test[10], true);
}

TEST(bool_methods, pop_back) {
  std::vector<bool> vec = {true, true, true, false, true};
  s21::vector<bool> test = {true, true, true, false, true};
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
  for (size_t i = 0; i < vec.capacity(); i++) {
    EXPECT_EQ(vec[i], test[i]);
  }
}

TEST(bool_methods, pop_back_void) {
  std::vector<bool> vec;
  s21::vector<bool> test;
  vec.pop_back();
  test.pop_back();
  EXPECT_EQ(vec.size(), test.size());
  EXPECT_EQ(vec.capacity(), test.capacity());
}
