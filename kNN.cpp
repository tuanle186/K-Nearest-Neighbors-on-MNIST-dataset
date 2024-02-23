#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

template<typename T>
class SinglyLinkedList : public List<T> {
private:
    class ListNode {
    public:
        T data;
        ListNode* next;

        ListNode(T value) : data(value), next(nullptr) {}
    };

    ListNode* head;
    ListNode* tail;
    int size;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void push_back(T value) override;
    void push_front(T value) override;
    void insert(int index, T value) override;
    void remove(int index) override;
    T& get(int index) const override;
    int length() const override;
    void clear() override;
    void print() const override;
    void reverse() override;
};

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

template<typename T>
void SinglyLinkedList<T>::push_back(T value) {
    ListNode* newNode = new ListNode(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        tail->next = newNode;
    }
    tail = newNode;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::push_front(T value) {
    ListNode* newNode = new ListNode(value);
    newNode->next = head;
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
    size++;
}

template<typename T>
void SinglyLinkedList<T>::insert(int index, T value) {
    if (index < 0 || index > size) {
        std::cerr << "Index out of range" << std::endl;
        return;
    }
    if (index == 0) {
        push_front(value);
    } else if (index == size) {
        push_back(value);
    } else {
        ListNode* newNode = new ListNode(value);
        ListNode* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

template<typename T>
void SinglyLinkedList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        std::cerr << "Index out of range" << std::endl;
        return;
    }
    ListNode* temp;
    if (index == 0) {
        temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        ListNode* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = current->next->next;
        if (current->next == nullptr) {
            tail = current;
        }
    }
    delete temp;
    size--;
}

template<typename T>
T& SinglyLinkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        std::cerr << "Index out of range" << std::endl;
        return head->data;
    }
    ListNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<typename T>
int SinglyLinkedList<T>::length() const {
    return size;
}

template<typename T>
void SinglyLinkedList<T>::clear() {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template<typename T>
void SinglyLinkedList<T>::print() const {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
void SinglyLinkedList<T>::reverse() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    ListNode* prev = nullptr;
    ListNode* current = head;
    ListNode* nextNode;
    while (current != nullptr) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    head = prev;
    tail = head;
}
