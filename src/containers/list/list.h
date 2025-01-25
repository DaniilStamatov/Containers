#include <initializer_list>
#include <stdexcept>
#ifndef LIST_H
#define LIST_H
template<typename T>
class list {
private:
    struct Node {
        Node() = default;
        Node(const T& value, Node* next = nullptr, Node* prev = nullptr) : value_(value), next_(next), prev_(prev){}

        T value_;
		Node* next_ = nullptr;
        Node* prev_ = nullptr;
    };

public:
   
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    class ListConstIterator {
    public: 
        ListConstIterator() noexcept;
        ListConstIterator(Node* node) noexcept;

        const_reference operator*() const;
        ListConstIterator& operator++();
        ListConstIterator operator++(int);
        ListConstIterator& operator--();
        ListConstIterator operator--(int);
        bool operator==(const ListConstIterator& other) const;
        bool operator!=(const ListConstIterator& other) const;
    protected:
        friend class list;
        Node* current_;
    };

    class ListIterator : public ListConstIterator {
    public:
        ListIterator() noexcept;
        ListIterator(Node* node) noexcept;
        reference operator*() const;
    };
    
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;

    iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator cend() const noexcept;

    list() noexcept;	                                                        //default constructor, creates empty list 
    explicit list(size_type n);	                                                //parameterized constructor, creates the list of size n
    list(std::initializer_list<value_type> const &items);	                    //initializer list constructor, creates list initizialized using std::initializer_list
    list(const list &l) noexcept;	                                            //copy constructor
    list(list &&l) noexcept;	                                                //move constructor
    ~list();	                                                                //destructor
    void update_end();

    bool empty();
    void copy(const list &l);
    void swap(list& l);
    list& operator=(const list &l) noexcept;
    list& operator=(list &&l) noexcept;
    size_type size();
    void clear();
    iterator insert(iterator pos, const_reference value);
    void push_back(const_reference data) noexcept;
    void pop_back();
    void push_front(const_reference value) noexcept;
    void pop_front();
    
private:
    Node* m_head;
    Node* m_tail;
    Node* m_end;
    size_type m_size;
};

#endif