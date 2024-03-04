#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */


/* Status: Finished
 *  
 */
Dataset::Dataset() {
    colName = new DLinkedList<string>();
    data = new DLinkedList<DLinkedList<int>*>();
    nRows = 0;
    nCols = 0;
}


/* Status: Finished
 *  
 */
Dataset::~Dataset() {
    clear();
    delete colName;
    delete data;
}


/* Status: Finished,
 * not yet implemented deep copy of other dataset
 */
Dataset::Dataset(const Dataset& other) {
    colName = new DLinkedList<string>(*other.colName);
    data = new DLinkedList<DLinkedList<int>*>();
    other.getShape(nRows, nCols);
    for (int i = 0; i < nRows - 1; ++i) {
        DLinkedList<int>* newRow = new DLinkedList<int>(*other.data->get(i));
        data->push_back(newRow);
    }
}


/* Status: Finished
 *  
 */
Dataset& Dataset::operator=(const Dataset& other) {
    // Check for self-assignment
    if (this == &other) {
        return *this;
    }
    if (nRows > 0 || nCols > 0) { // not empty
        clear();
    }
    other.getShape(nRows, nCols);
    delete colName;
    colName = new DLinkedList<string>(*other.colName);
    delete data;
    data = new DLinkedList<DLinkedList<int>*>();
    for (int i = 0; i < nRows - 1; ++i) {
        DLinkedList<int>* newRow = new DLinkedList<int>(*other.data->get(i));
        data->push_back(newRow);
    }
    return *this;
}


/* Status: Finished
 *
 * This method is used to load data from the file fileName, 
 * specifically in this assignment is the 'mnist.csv' file. 
 * The information in the file will be stored in the variable
 * data and other proposed variables by students.
 * 
 * It returns true if the data loading is successful, otherwise false.
 */
bool DEBUG_dataset_loadFromCSV = false;
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
            nRows++;
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

    if (DEBUG_dataset_loadFromCSV) {
        cout << "DEBUGGING Dataset::loadFromCSV\n";
        cout << "dataset's number of columns = " << nCols << endl;
        cout << "dataset's number of rows = " << nRows << endl;
    }
    return true;
}


/* Status: Finished
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
bool DEBUG_dataset_printHead = false;
void Dataset::printHead(int nRows, int nCols) const {
    if (nRows <= 0 || nCols <= 0) { // Do not print anything | Note: nRows = 0 || nCols = 0 do what??
        return;
    }
    nRows = min(nRows, this->nRows - 1); // -1 as 1st row's stored in colName
    nCols = min(nCols, this->nCols);
    colName->printHead(nCols);
    cout << endl;
    for (int i = 0; i < nRows; ++i) {
        data->get(i)->printHead(nCols);
        cout << endl;
    }

    // For the debugging only: Test printing all    
    if (DEBUG_dataset_printHead) {
        // Print first row (column names)
        colName->print();
        cout << endl;

        // Print remaining rows (labels and vale)
        for (int i = 0; i < this->nRows - 1; i++) {
            cout << "New line: " << endl;
            data->get(i)->print();
        }
    }
}


void Dataset::printTail(int nRows, int nCols) const {
    if (nRows <= 0 || nCols <= 0) {
        return;
    }
    nRows = min(nRows, this->nRows - 1); // -1 as 1st row's stored in colName
    nCols = min(nCols, this->nCols);
    colName->printTail(nCols);
    cout << endl;
    for (int i = this->nRows - nRows - 1; i < this->nRows - 1; ++i) {
        data->get(i)->printTail(nCols);
        cout << endl;
    }
}


void Dataset::getShape(int& nRows, int& nCols) const {
    nRows = this->nRows;
    nCols = this->nCols;
}


void Dataset::columns() const {
    colName->print();
}


void Dataset::clear() {
    if (nRows == 0 && nCols == 0) {
        return;
    }
    colName->clear();
    for (int i = 0; i < nRows - 1; ++i) {
        data->get(i)->clear();
    }
    data->clear();
    nRows = 0;
    nCols = 0;
}