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
    DoublyLinkedList<int>* list = new DoublyLinkedList<int>();
    list->push_back(1);
    list->push_back(3);
    list->push_front(2);
    list->print();
    list->clear();
    list->print();
}

int main() {
    tc2();
    return 0;
}