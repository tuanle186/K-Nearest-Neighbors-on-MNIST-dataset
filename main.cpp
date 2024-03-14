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
}
*/

void tc2() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl << endl;

    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    
    cout << "X_train: " << endl;
    int nRows_X_train, nCols_X_train;
    X_train.getShape(nRows_X_train, nCols_X_train);
    cout << "Shape: " << nRows_X_train << "x" << nCols_X_train << endl;
    // X_train.printHead(1000, 5);
    cout << endl;

    cout << "X_test: " << endl;
    int nRows_X_test, nCols_X_test;
    X_test.getShape(nRows_X_test, nCols_X_test);
    cout << "Shape: " << nRows_X_test << "x" << nCols_X_test << endl;
    // X_test.print(1000, 5);
    cout << endl;

    cout << "y_train: " << endl;
    int nRows_y_train, nCols_y_train;
    y_train.getShape(nRows_y_train, nCols_y_train);
    cout << "Shape: " << nRows_y_train << "x" << nCols_y_train << endl;
    y_train.printHead(1000, 5);
    cout << endl;

    cout << "y_test: " << endl;
    int nRows_y_test, nCols_y_test;
    y_test.getShape(nRows_y_test, nCols_y_test);
    cout << "Shape: " << nRows_y_test << "x" << nCols_y_test << endl;
    y_test.printHead(1000, 5);
    cout << endl;
}


void tc3() {
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
    knn.predict(X_test);
}

void tc4() {
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(10, 10);
    cout << endl;
    dataset.printTail(10, 10);
    cout << endl;
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;
}

int main() {
    tc3();
    return 0;
}