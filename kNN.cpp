#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

Dataset::Dataset() {
    colName = new DLinkedList<string>();
    data = new DLinkedList<DLinkedList<int>*>();
    nRows = 0;
    nCols = 0;
}

Dataset::~Dataset() {
    nRows = 0;
    nCols = 0;
    colName->clear();
    data->clear();
    delete colName;
    delete data;
}

Dataset::Dataset(const Dataset& other) {
    /* 
     * The data variable has not been dynamically allocated
     * => Allocate new dynamic data
    */
    if (!data) data = new DLinkedList<DLinkedList<int>*>();
    
    /* 
     * The data has ALREADY BEEN dynamically allocated but it is not empty
     * => Clear the data
    */
    else if (nRows != 0 || nCols != 0) {
        data->clear();
    }
    
    // If the PC is here, it means that the data var has been allocated and empty
    // => Deep copy the other dataset
    // Implement later
    
}

Dataset& Dataset::operator=(const Dataset& other) {
    // Implement later
}


/*
 * This method is used to load data from the file fileName, 
 * specifically in this assignment is the 'mnist.csv' file. 
 * The information in the file will be stored in the variable
 * data and other proposed variables by students.
 * 
 * It returns true if the data loading is successful, otherwise false.
 *
*/
bool Dataset::loadFromCSV(const char* fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return false;
    }
    bool is1stRow = true;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        if (is1stRow) { // 1st row detected, add columns' names into colName
            while (getline(iss, token, ',')) {
                colName->push_back(token);
                nCols++;
            }
            is1stRow = false;
        } else { // Not first Row
            DLinkedList<int>* newRow = new DLinkedList<int>();
            while (getline(iss, token, ',')) {
                newRow->push_back(stoi(token));
            }
            data->push_back(newRow);
            nRows++;
        }
    }
    nRows++;

    // For debugging only
    cout << "nCols = " << nCols << endl;
    cout << "nRows = " << nRows << endl;
    return true;
}


/*
 * Print the first nRows rows, and only print the first nCols columns of the data table.

 * • Print format:
 * – The first row prints the names of the columns of the data table.
 * – From the second row onwards, print the value of each cell in the table, each
 * element separated by a space, with no trailing space at the end of the line.
 * 
 * • Exceptions: 
 * If nRows is greater than the number of rows in the data table, print all
 * rows in the data table. If nCols is greater than the number of columns in the data
 * table, print all columns in the data table. If nRows or nCols is less than 0, do not
 * print anything.
*/
void Dataset::printHead(int nRows, int nCols) const {
    if (nRows < 0 || nCols < 0) { // Do not print anything
        return;
    }

    // int nRows = min(this->nRows, nRows);
    // int nCols = min(this->nCols, nCols);

    // for (int i = 0; i < nCols; ++i) {

    // }





    // For the debugging only: Test printing all    
    /*
    // Print column names
    colName->print();
    cout << endl;
    // Print data
    for (int i = 0; i < this->nRows - 1; i++) {
        cout << "New line:" << endl;
        data->get(i)->print();
    }   
    */
}


// void Dataset::printTail(int nRows = 5, int nCols = 5) const {

// }


void Dataset::getShape(int& nRows, int& nCols) const {
    nRows = this->nRows;
    nCols = this->nCols;
}

void Dataset::columns() const {
    colName->print();
}

