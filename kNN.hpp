#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// LIST INTERFACE AND DLINKEDLIST IMPLEMENTATION //////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};


template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void printHead(int n) const = 0;
    virtual void printTail(int n) const = 0;
    virtual void reverse() = 0;
    virtual Node<T>* getHead() const = 0;
    virtual Node<T>* getTail() const = 0;
    virtual int getIndexOf(T item) const = 0;
};


template<typename T>
class DLinkedList : public List<T> {        
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    DLinkedList(const List<T>& other) {
        head = nullptr;
        tail = nullptr;
        size = 0;
        Node<T>* current = other.getHead();
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    ~DLinkedList() {
        clear();
    }

    void push_back(T value) override {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void push_front(T value) override {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insert(int index, T value) override {
        if (index < 0 || index > size) {
            return;
        }
        if (index == 0) {
            push_front(value);
        } else if (index == size) {
            push_back(value);
        } else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            size++;
        }
    }

    void remove(int index) override {
        if (index < 0 || index >= size) {
            return;
        }
        Node<T>* temp;
        if (index == 0) {
            temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (index == size - 1) {
            temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            temp = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        delete temp;
        size--;
    }

    T& get(int index) const override {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    int length() const override {
        return size;
    }

    void clear() override {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    void print() const override {
        Node<T>* current = head;
        while (current != nullptr) {
            // if (current->next != nullptr) {
            //     cout << current->data << " ";
            // } else {
            //     cout << current->data; // Last element => no trailing space at the end
            // }
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void printHead(int n=5) const override {
        if (n <= 0) {
            throw std::out_of_range("Out of range");
            return;
        }
        n = min(n, size);
        Node<T>* current = head;
        for (int i = 0; i < n; ++i) {
            if (i < n - 1) {
                cout << current->data << " ";
            } else {
                cout << current->data; // Last element => no trailing space at the end
            }
            current = current->next;
        }
    }

    void printTail(int n=5) const override {
        if (n <= 0) {
            throw std::out_of_range("Out of range");
            return;
        }
        n = min(n, size);
        Node<T>* current = tail;
        for (int i = 0; i < n - 1; ++i) {
            current = current->prev;
        }
        
        while (current != nullptr) {
            if (current->next != nullptr) {
                cout << current->data << " ";
            } else {
                cout << current->data; // Last element => no trailing space at the end
            }
            current = current->next;
        }
    }

    void reverse() override {
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    Node<T>* getHead() const override {
        return head;
    }

    Node<T>* getTail() const override {
        return tail;
    }

    int getIndexOf(T item) const override {
        int index = 0;
        Node<T>* current = head;
        while (current != nullptr && current->data != item) {
            current = current->next;
            index++;
        }

        if (current != nullptr) {
            return index;
        } else {
            return -1; // Item not found
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// DATASET CLASS FORWARD DECLARATION ////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

class Dataset {
private:
    int nRows;
    int nCols;
    List<string>* colName;
    List<List<int>*>* data;
    //You may need to define more
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    List<List<int>*>* getData() const;
    List<string>* getColName() const;
    void clear();
    void setShape(int nRows, int nCols);
};

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// kNN CLASS FORWARD DECLARATION //////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset y_train;
    struct kNN_Node; // class forward declaration
    class kNN_List; // class forward declaration
    //You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);

private:
    struct kNN_Node {
        int label;
        double distance;
        kNN_Node* next;

        kNN_Node(int label, double distance) {
            this->label = label;
            this->distance = distance;
            this->next = nullptr;
        }
    };

    class kNN_List {
    private:
        kNN_Node* head;
        kNN_Node* tail;

        void swap(kNN_Node* a, kNN_Node* b) {
            int label_tmp = a->label;
            a->label = b->label;
            b->label = label_tmp;
            double distance_tmp = a->distance;
            a->distance = b->distance;
            b->distance = distance_tmp;
        }

    public:
        kNN_List() {
            head = nullptr;
        }

        ~kNN_List() {
            clear();
        }

        void push_back(int label, double distance) {
            if (head == nullptr) {
                head = new kNN_Node(label, distance);
                tail = head;
            } else {
                tail->next = new kNN_Node(label, distance);
                tail = tail->next;
            }
        }

        void print() {
            kNN_Node* current = head;
            while (current != nullptr) {
                cout << "Label: " << current->label << " - Distance: " << current->distance << endl;
                current = current->next;
            }
            cout << endl;
        }

        void sort() {
            if (head == nullptr || head->next == nullptr) {
                return;
            }

            kNN_Node* current;
            kNN_Node* last = nullptr;
            bool swapped = false;
            do {
                swapped = false;
                current = head;
                kNN_Node* prev = nullptr;

                while (current->next != last) {
                    if (current->distance > current->next->distance) {
                        swap(current, current->next);
                        swapped = true;
                    }
                    prev = current;
                    current = current->next;
                }
                last = current;
            } while (swapped);
        }

        void clear() {
            kNN_Node* current = head;
            while (current != nullptr) {
                kNN_Node* next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
            tail = nullptr;
        }

        int get_common_label(int k) {
            if (head == nullptr) {
                return -1;
            }
            int record[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Since there are just 10 digits (types of labels)
            kNN_Node* current = head;
            for (int i = 0; i < k; ++i) {
                record[current->label]++;
                current = current->next;
            }
            int max_idx = 0;
            for (int i = 0; i < 10; ++i) {
                if (record[i] > record[max_idx]) {
                    max_idx = i;
                }
            }
            return max_idx;
        }
    };
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed
