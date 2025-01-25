#include <gtest/gtest.h>
#include "list.cpp"
#include <list> 

TEST(Constructor, PushBackUltimate) {
    list<int> myList;
    EXPECT_EQ(myList.size(), 0);
    EXPECT_EQ(myList.begin(), myList.end());

    myList.push_back(1);
    EXPECT_EQ(myList.size(), 1);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*(--myList.end()), 1);
    EXPECT_EQ(myList.begin(), --myList.end());

    myList.push_back(2);
    EXPECT_EQ(myList.size(), 2);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*(--myList.end()), 2);

    myList.push_back(3);
    EXPECT_EQ(myList.size(), 3);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*(--myList.end()), 3);

    for (int i = 4; i <= 10; ++i) {
        myList.push_back(i);
    }
    EXPECT_EQ(myList.size(), 10);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*(--myList.end()), 10);

    myList.clear();
    EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, PushFrontUltimate) {
    list<int> myList;
    std::list<int> stdList;
    EXPECT_EQ(myList.size(), 0);
    EXPECT_EQ(stdList.size(), 0);
    EXPECT_EQ(myList.begin(), myList.end());
    EXPECT_EQ(stdList.begin(), stdList.end());

    myList.push_front(1);
    stdList.push_front(1);
    EXPECT_EQ(myList.size(), 1);
    EXPECT_EQ(stdList.size(), 1);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*stdList.begin(), 1);
    EXPECT_EQ(myList.begin() == --myList.end(), true);
    EXPECT_EQ(stdList.begin(), --stdList.end());

    myList.push_front(2);
    stdList.push_front(2);
    EXPECT_EQ(myList.size(), 2);
    EXPECT_EQ(stdList.size(), 2);
    EXPECT_EQ(*myList.begin(), 2);
    EXPECT_EQ(*stdList.begin(), 2);
    EXPECT_EQ(*(--myList.end()), 1);
    EXPECT_EQ(*(--stdList.end()), 1);
    EXPECT_EQ(myList.begin() == --(--myList.end()), true);


    myList.push_front(3);
    stdList.push_front(3);
    EXPECT_EQ(myList.size(), 3);
    EXPECT_EQ(stdList.size(), 3);
    EXPECT_EQ(*myList.begin(), 3);
    EXPECT_EQ(*stdList.begin(), 3);
    EXPECT_EQ(*(--myList.end()), 1);
    EXPECT_EQ(*(--stdList.end()), 1);

    for (int i = 4; i <= 10; ++i) {
        myList.push_front(i);
        stdList.push_front(i);
    }
    EXPECT_EQ(myList.size(), 10);
    EXPECT_EQ(stdList.size(), 10);
    EXPECT_EQ(*myList.begin(), 10);
    EXPECT_EQ(*stdList.begin(), 10);
    EXPECT_EQ(*(--myList.end()), 1);
    EXPECT_EQ(*(--stdList.end()), 1);

    myList.clear();
    stdList.clear();
    EXPECT_EQ(myList.size(), 0);
    EXPECT_EQ(stdList.size(), 0);
}

TEST(ConstructorTest, DefaultConstructor) {
    list<int> myList;
    std::list<int> stdList;

    EXPECT_EQ(myList.size(), 0);
    EXPECT_EQ(stdList.size(), 0);
    EXPECT_EQ(myList.begin(), myList.end());
    EXPECT_EQ(stdList.begin(), stdList.end());
}

TEST(ConstructorTest, InitializerListConstructor) {
    list<int> myList = {1, 2, 3, 4, 5};
    std::list<int> stdList = {1, 2, 3, 4, 5};

    EXPECT_EQ(myList.size(), 5);
    EXPECT_EQ(stdList.size(), 5);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*stdList.begin(), 1);
    EXPECT_EQ(*(--myList.end()), 5);
    EXPECT_EQ(*(--stdList.end()), 5);
}

TEST(ConstructorTest, MoveConstructor) {
    list<int> myList = {1, 2, 3, 4, 5};
    list<int> movedList = std::move(myList);
    
    EXPECT_EQ(movedList.size(), 5);
    EXPECT_EQ(myList.size(), 0);
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

    EXPECT_EQ(myList.size(), 5);
    EXPECT_EQ(stdList.size(), 5);

    myList.pop_back();
    stdList.pop_back();
    EXPECT_EQ(myList.size(), 4);
    EXPECT_EQ(stdList.size(), 4);
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

    EXPECT_EQ(myList.size(), 5);
    EXPECT_EQ(stdList.size(), 5);

    myList.pop_front();
    stdList.pop_front();
    EXPECT_EQ(myList.size(), 4);
    EXPECT_EQ(stdList.size(), 4);
    EXPECT_EQ(*myList.begin(), 2);
    EXPECT_EQ(*stdList.begin(), 2);
}

TEST(InsertTest, InsertIntoEmptyList) {
    list<int> myList;
    std::list<int> stdList;

    myList.insert(myList.begin(), 1);
    stdList.insert(stdList.begin(), 1);

    EXPECT_EQ(myList.size(), 1);
    EXPECT_EQ(stdList.size(), 1);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*stdList.begin(), 1);
}

TEST(InsertTest, InsertAtBeginning) {
    list<int> myList = {2, 3, 4};
    std::list<int> stdList = {2, 3, 4};

    myList.insert(myList.begin(), 1);
    stdList.insert(stdList.begin(), 1);

    EXPECT_EQ(myList.size(), 4);
    EXPECT_EQ(stdList.size(), 4);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*stdList.begin(), 1);
}

TEST(InsertTest, InsertAtEnd) {
    list<int> myList = {1, 2, 3};
    std::list<int> stdList = {1, 2, 3};

    myList.insert(myList.end(), 4);
    stdList.insert(stdList.end(), 4);

    EXPECT_EQ(myList.size(), 4);
    EXPECT_EQ(stdList.size(), 4);
    EXPECT_EQ(*(--myList.end()), 4);
    EXPECT_EQ(*(--stdList.end()), 4);
}

// TEST(InsertTest, InsertInMiddle) {
//     list<int> myList = {1, 3, 4};
//     std::list<int> stdList = {1, 3, 4};

//     //myList.insert(++myList.begin(), 2);

//     stdList.insert(++stdList.begin(), 2);

//     EXPECT_EQ(myList.size(), 4);
//     EXPECT_EQ(stdList.size(), 4);
//     EXPECT_EQ(*(++myList.begin()), 2);
//     EXPECT_EQ(*(++stdList.begin()), 2);
// }

TEST(InsertTest, InsertMultipleElements) {
    list<int> myList;
    std::list<int> stdList;

    for (int i = 1; i <= 5; ++i) {
        myList.insert(myList.end(), i);
        stdList.insert(stdList.end(), i);
    }

    EXPECT_EQ(myList.size(), 5);
    EXPECT_EQ(stdList.size(), 5);
    EXPECT_EQ(*myList.begin(), 1);
    EXPECT_EQ(*stdList.begin(), 1);
    EXPECT_EQ(*(--myList.end()), 5);
    EXPECT_EQ(*(--stdList.end()), 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}