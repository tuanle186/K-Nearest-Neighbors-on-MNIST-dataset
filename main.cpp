#include "kNN.hpp"

/*
void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);

    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);
    double accuracy = knn.score(y_test, y_pred);
    cout << "Accuracy: " << accuracy << endl;
} */

void tc2() {
    DLinkedList<int>* list = new DLinkedList<int>();
    for (int i = 0; i < 10; ++i) {
        list->push_back(i);
    }
    cout << "Print all: ";
    list->print();
    cout << endl;

    cout << "Print head n = 3: ";
    list->printHead(3);
    cout << endl;

    cout << "Print tail n = 4: ";
    list->printTail(4);
    list->clear();
}

void tc3() { // Test Printing
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
}

int main() {
    tc3();
    return 0;
}