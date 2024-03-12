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

void tc6() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(5, 5);
    // drop all rows
    for (int i = 0; i < 198; ++i) {
        dataset.drop(0, dataset.getData()->length() - 1);
        // cout << dataset.drop(0, i) << endl;
    }
    cout << dataset.getData()->length() << endl;
    dataset.printHead(5, 5);
}

void tc7() {
    Dataset dataset;
    cout << "Origin: " << endl;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(10, 10);

    Dataset extractedDataset;
    extractedDataset = dataset.extract(0, 99, 0, 99);
    cout << "\nExtracted: \n";
    int nRows = 0, nCols = 0;
    extractedDataset.getShape(nRows, nCols);
    extractedDataset.printHead(1000, 1000);
    cout << endl;
    cout << "Shape: " << endl;
    cout << "nRows = " << nRows << endl;
    cout << "nCols = " << nCols << endl;
}

int main() {
    tc7();
    return 0;
}