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

    cout << "Print head: ";
    list->printHead(0);
    cout << endl;

    cout << "Print tail: ";
    list->printTail(0);
    list->clear();
}

void tc3() { // Test Printing
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "nRows: " << nRows << endl;
    cout << "nCols: " << nCols << endl;
}

void tc4() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    // Dataset dataset2(dataset);
    // dataset2.printHead();
    dataset.printTail(5, 5);
}

void tc5() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(50,50);
}

int main() {
    tc4();
    return 0;
}