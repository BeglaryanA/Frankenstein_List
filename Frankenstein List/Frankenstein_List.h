#ifndef FRANKENSTEIN_LIST_H
#define FRANKENSTEIN_LIST_H
#include <initializer_list>
template <typename T>
class frankenstein_list {
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node* greater;
        Node* lesser;
        Node();
        Node(const T& rhs);
    };
public:

    frankenstein_list();
    frankenstein_list(const frankenstein_list&);
    frankenstein_list(frankenstein_list&&);
    frankenstein_list(std::initializer_list<T>);
    ~frankenstein_list();
public:
    frankenstein_list& operator=(const frankenstein_list&);
    frankenstein_list& operator=(frankenstein_list&&);

public:
    void push_back(const T&);
    void push_back(T&&);
    void push_front(const T&);
    void push_front(T&&);
    void pop_back();
    void pop_front();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void swap(frankenstein_list&);
    int size() const;
    void clear();
    void erase(const std::size_t&);
    void insert(const std::size_t&, const T&);

public:
    void PutInSortedOreder(Node*&);

public:

    void printForward() {
        Node* tmp = this->head;
        while (tmp) {
            std::cout << tmp->data << " ";
            tmp = tmp->next;
        }
    }
    void printReverse() {
        Node* tmp = this->tail;
        while (tmp) {
            std::cout << tmp->data << " ";
            tmp = tmp->prev;
        }
    }
    
    void printGrowth() {
        Node* tmp = asc_head;
        while (tmp) {
            std::cout << tmp->data << " ";
            tmp = tmp->greater;
        }
    }
    
    void printDecrease() {
        Node* tmp = desc_head;
        while (tmp) {
            std::cout << tmp->data << " ";
            tmp = tmp->lesser;
        }

    }
private:
    Node* head;
    Node* tail;
    Node* asc_head; // lessest
    Node* desc_head; // greates
    std::size_t m_size;
};

#endif // FRANKENSTEIN_LIST_H