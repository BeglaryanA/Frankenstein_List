#include "Frankenstein_List.h"

template <typename T>
frankenstein_list<T>::Node::Node() 
: data{}
, next{nullptr}
, prev{nullptr}
, greater{nullptr}
, lesser{nullptr}
{}

template <typename T>
frankenstein_list<T>::Node::Node(const T& rhs) 
: data{rhs}
, next{nullptr}
, prev{nullptr}
, greater{nullptr}
, lesser{nullptr}
{}

template <typename T>
frankenstein_list<T>::frankenstein_list() 
: head{nullptr}
, tail{nullptr}
, asc_head{nullptr}
, desc_head{nullptr}
, m_size{0}
{}

template <typename T>
frankenstein_list<T>::frankenstein_list(const frankenstein_list<T>& rhs) {

}

template <typename T>
frankenstein_list<T>::frankenstein_list(frankenstein_list<T>&& rhs) {
    this->head = rhs.head;
    this->tail = rhs.tail;
    this->asc_head = rhs.asc_head;
    this->desc_head = rhs.desc_head;
    this->m_size = rhs.m_size;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.asc_head = nullptr;
    rhs.desc_head = nullptr;
    rhs.m_size = 0;

}

template <typename T>
frankenstein_list<T>::frankenstein_list(std::initializer_list<T> init) {
    for (auto it : init) {
        push_back(it);
    }
}

template <typename T>
frankenstein_list<T>::~frankenstein_list() {    
    this->clear();
}

template <typename T>
void frankenstein_list<T>::clear() {
    if (!head) {
        return;
    }
    Node* del = this->head;
    while (this->head != nullptr) {
        this->head = this->head->next;
        delete del;
        del = nullptr;
        del = this->head;
    }
}

template <typename T>
void frankenstein_list<T>::push_back(const T& rhs) {
    if (!head) {
        Node* pushed = new Node(rhs);
        this->head = pushed;
        this->tail = pushed;
        this->asc_head = pushed;
        this->desc_head = pushed;
        ++this->m_size;
        return;
    }
    Node* pushed = new Node(rhs);
    this->tail->next = pushed;
    pushed->prev = this->tail;
    this->tail = pushed;
    ++this->m_size;
    PutInSortedOreder(this->tail);

}

template <typename T>
void frankenstein_list<T>::push_back(T&& rhs) {
    if (!head) {
        Node* pushed = new Node(rhs);
        this->head = pushed;
        this->tail = pushed;
        this->asc_head = pushed;
        this->desc_head = pushed;
        ++this->m_size;
        return;
    }
    Node* pushed = new Node(rhs);
    this->tail->next = pushed;
    pushed->prev = this->tail;
    this->tail = pushed;
    ++this->m_size;
    PutInSortedOreder(this->tail);
}

template <typename T>
void frankenstein_list<T>::push_front(T&& rhs) {
    if (!head) {
        Node* pushed = new Node(rhs);
        this->head = pushed;
        this->tail = pushed;
        this->asc_head = pushed;
        this->desc_head = pushed;
        ++this->m_size;
        return;
    }
    Node* pushed = new Node(rhs);
    this->head->prev = pushed;
    pushed->next = this->head;
    this->head = pushed;
    ++this->m_size;
    PutInSortedOreder(this->head);
}

template <typename T>
void frankenstein_list<T>::push_front(const T& rhs) {
    if (!head) {
        Node* pushed = new Node(rhs);
        this->head = pushed;
        this->tail = pushed;
        this->asc_head = pushed;
        this->desc_head = pushed;
        ++this->m_size;
        return;
    }
    Node* pushed = new Node(rhs);
    this->head->prev = pushed;
    pushed->next = this->head;
    this->head = pushed;
    ++this->m_size;
    PutInSortedOreder(this->head);

}





template <typename T>
void frankenstein_list<T>::pop_back() {
    if (this->tail == nullptr) {
        return;
    }
    Node* del = this->tail;
    if (desc_head == del) {
        desc_head = desc_head->lesser;
        del->lesser->greater = nullptr;
        del->lesser = nullptr;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        delete del;
        del = nullptr;
        --this->m_size;
        return;
    } else if (asc_head == del) {
        asc_head = asc_head->greater;
        del->greater->lesser = nullptr;
        del->greater = nullptr;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        delete del;
        del = nullptr;
        --this->m_size;
        return;
    }
    del->greater->lesser = del->lesser;
    del->lesser->greater = del->greater;
    this->tail = this->tail->prev;
    delete del;
    del = nullptr;
    this->tail->next = nullptr;
    --this->m_size;

}

template <typename T>
void frankenstein_list<T>::pop_front() {
    if (this->head == nullptr) {
        return;
    }
    Node* del = this->head;
    if (asc_head == del) {
        asc_head = asc_head->greater;
        del->lesser->greater = nullptr;
        del->lesser = nullptr;
        this->head = this->head->next;
        this->head->prev = nullptr;
        delete del;
        del = nullptr;
        --this->m_size;

        return;
    } else if (desc_head == del) {
        desc_head = desc_head->lesser;
        del->lesser->greater = nullptr;
        del->lesser = nullptr;
        this->head = this->head->next;
        this->head->prev = nullptr;
        delete del;
        del = nullptr;
        --this->m_size;
        return;
    }
    del->greater->lesser = del->lesser;
    del->lesser->greater = del->greater;
    this->head = this->head->next;
    this->head->prev = nullptr;
    delete del;
    del = nullptr;
    --this->m_size;

}

template <typename T>
void frankenstein_list<T>::PutInSortedOreder(Node*& node) {
    if (!node) { return ;}
    if (!asc_head) {
        asc_head = node;
        desc_head = node;
        return;
    }
    Node* curr = asc_head;
    while (curr->data < node->data && curr->greater) {
        curr = curr->greater;
    }
    if (curr->data < node->data) {
        node->greater = curr->greater;
        curr->greater = node;
        node->lesser = curr;
        if (!node->greater) {
            desc_head = node;
        }
    } else {
        node->lesser = curr->lesser;
        if (curr->lesser) {
            curr->lesser->greater = node;
        } else {
            asc_head = node;
        }
        node->greater = curr;
        curr->lesser = node;
    }
}


template <typename T>
void frankenstein_list<T>::insert(const std::size_t& pos, const T& rhs) {
    if (pos == 0) {
        return push_front(rhs);
    }
    if (pos >= m_size) {
        return push_back(rhs);
    }
    Node* node = new Node(rhs);
    Node* curr = this->head;
    std::size_t count = 0;
    
    while (count != pos) {
        ++count;
        curr = curr->next;
    }
    curr->prev->next = node;
    node->prev = curr->prev;
    node->next = curr;
    curr->prev = node;
    ++m_size;
    PutInSortedOreder(node);
}

template <typename T>
void frankenstein_list<T>::erase(const std::size_t& pos) {
    if (pos == 0) {
        return pop_front();
    }
    if (pos >= m_size) {
        return pop_back();
    }
    Node* curr = this->head;
    std::size_t count = 0;
    while (count != pos) {
        ++count;
        curr = curr->next;
    }
    if (asc_head == curr) {
        asc_head = asc_head->greater;
        asc_head->lesser = nullptr;
        curr->greater = nullptr;
        delete curr;
        curr = nullptr;
        return;
    } else if (desc_head == curr) {
        desc_head = desc_head->lesser;
        curr->lesser = nullptr;
        desc_head->greater = nullptr;
        delete curr;
        curr = nullptr;
        return;
    }
    curr->greater->lesser = curr->lesser;
    curr->lesser->greater = curr->greater;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    curr = nullptr;
}

template <typename T>
int frankenstein_list<T>::size() const {
    return this->m_size;
}

template <typename T>
void frankenstein_list<T>::swap(frankenstein_list<T>& rhs) {
    std::swap(this->head, rhs.head);
    std::swap(this->tail, rhs.tail);
    std::swap(this->asc_head, rhs.asc_head);
    std::swap(this->desc_head, rhs.desc_head);
}


template <typename T>
bool frankenstein_list<T>::empty() const {
    return this->head == nullptr;
}