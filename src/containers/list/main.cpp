#include <assert.h>
#include "list.cpp"
#include <iostream>
#include <list>
void test_push_back() {
    list<int> myList;

    // Проверка, что список пуст
    assert(myList.size() == 0);
    assert(myList.begin() == myList.end());
    // Добавление первого элемента
    myList.push_back(1);
    assert(myList.size() == 1);
    assert(*myList.begin() == 1);
    assert(*(--myList.end()) == 1);
    assert(myList.begin() == --myList.end());
    //Добавление второго элемента
    myList.push_back(2);
    assert(myList.size() == 2);
    assert(*myList.begin() == 1);
    assert(*(--myList.end()) == 2);

    // Добавление третьего элемента
    myList.push_back(3);
    assert(myList.size() == 3);
    assert(*myList.begin() == 1);
    assert(*(--myList.end()) == 3);

   
    // Проверка на добавление нескольких элементов
    for (int i = 4; i <= 10; ++i) {
        myList.push_back(i);
    }
    assert(myList.size() == 10);
    assert(*myList.begin() == 1);
    assert(*(--myList.end()) == 10);

    // Очистка списка
    myList.clear();
    assert(myList.size() == 0);
    std::cout << "Список очищен. Текущий размер: " << myList.size() << std::endl; // Ожидается: 0
}

int main() {
    test_push_back();
    std::cout << "Все тесты пройдены успешно!" << std::endl;
    return 0;
}