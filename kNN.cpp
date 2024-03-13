#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// Debugging Flag to print out errors
bool DEBUGGING_DATASET = true;


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// DATASET INNER-CLASS DEFINITION //////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


/* Status: Finished
 */
Dataset::Dataset() {
    colName = new DLinkedList<string>();
    data = new DLinkedList<List<int>*>();
    nRows = 0;
    nCols = 0;
}


/* Status: Finished
 */
Dataset::~Dataset() {
    clear();
    delete colName;
    delete data;
}


/* Status: Finished
 */
Dataset::Dataset(const Dataset& other) {
    colName = new DLinkedList<string>(*other.colName);
    data = new DLinkedList<List<int>*>();
    other.getShape(nRows, nCols);
    for (int i = 0; i < nRows; ++i) {
        DLinkedList<int>* newRow = new DLinkedList<int>(*other.data->get(i));
        data->push_back(newRow);
    }
}


/* Status: Finished
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
    data = new DLinkedList<List<int>*>();
    for (int i = 0; i < nRows; ++i) {
        DLinkedList<int>* newRow = new DLinkedList<int>(*other.data->get(i));
        data->push_back(newRow);
    }
    return *this;
}


/* Status: Finished
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
    file.close();
    return true;
}


/* Status: Finished
*/
void Dataset::printHead(int nRows, int nCols) const {
    if (nRows <= 0 || nCols <= 0) { // Do not print anything | Note: nRows = 0 || nCols = 0 do what??
        return;
    }
    nRows = min(nRows, this->nRows);
    nCols = min(nCols, this->nCols);
    colName->printHead(nCols);
    cout << endl;
    for (int i = 0; i < nRows; ++i) {
        data->get(i)->printHead(nCols);
        cout << endl;
    }
}


/* Status: Finished
*/
void Dataset::printTail(int nRows, int nCols) const {
    if (nRows <= 0 || nCols <= 0) {
        return;
    }
    nRows = min(nRows, this->nRows);
    nCols = min(nCols, this->nCols);
    colName->printTail(nCols);
    cout << endl;
    for (int i = this->nRows - nRows; i < this->nRows; ++i) {
        data->get(i)->printTail(nCols);
        cout << endl;
    }
}


/* Status: Finished
*/
void Dataset::getShape(int& nRows, int& nCols) const {
    nRows = this->nRows;
    nCols = this->nCols;
}


/* Status: Finished
*/
void Dataset::columns() const {
    colName->print();
}


/* Status: Finished
*/
bool Dataset::drop(int axis, int index, std::string columns) {
    if (axis != 0 && axis != 1) {
        if (DEBUGGING_DATASET) {
            cout << "axis is not 0 or 1" << endl;
        }
        return false;
    }

    if (axis == 0) { // dropping a row
        if (index >= nRows || index < 0) {
            if (DEBUGGING_DATASET) {
                cout << "Index out of bound, fail to drop a col" << endl;
            }
            return false;
        }
        data->get(index)->clear();
        data->remove(index);
        nRows--;
        return true;
    } else { // dropping a column
        int colIndex = colName->getIndexOf(columns);
        if (colIndex == -1) {
            if (DEBUGGING_DATASET) {
                cout << "Column's name not found, failed to drop a col" << endl;
            }
            return false;
        }

        colName->remove(colIndex);
        for (int i = 0; i < nRows; ++i) {
            data->get(i)->remove(colIndex);
        }
        nCols--;
        return true;
    }

    if (DEBUGGING_DATASET) {
        cout << "Failed to drop a row or a col" << endl;
    }
    return false;
}


/* Status: Finished
    If endRow == -1, we will take all rows. Similarly with endCol == -1.

    Testcases will ensure that startRow, endRow, startCol, and endCol are within valid
    range (from 0 to number of rows/number of columns) and start ≤ end.
*/
Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
    Dataset extractedDataset;
    // Preprocessing
    if (endRow == -1) { // takes all rows
        startRow = 0;
        endRow = this->nRows - 1;
    }
    if (endCol == -1) { // takes all cols
        startCol = 0;
        endCol = this->nCols - 1;
    }

    // Set the nRows and nCols attribute of extractedDataset
    extractedDataset.nRows = endRow - startRow + 1;
    extractedDataset.nCols = endCol - startRow + 1;

    // Set the colName attribute of extractedDataset
    for (int i = startCol; i <= endCol; ++i) {
        extractedDataset.colName->push_back(colName->get(i));
    }

    // Set the data attribute of extractedDataset
    for (int i = startRow; i <= endRow; ++i) {
        List<int>* currentRow = this->data->get(i);
        DLinkedList<int>* extractedRow = new DLinkedList<int>();
        for (int j = startCol; j <= endCol; ++j) {
            extractedRow->push_back(currentRow->get(j));
        }
        extractedDataset.data->push_back(extractedRow);
    }
    
    return extractedDataset;
}

/* Status: Finished
*/
List<List<int>*>* Dataset::getData() const {
    return data;
}


/* Status: Finished
*/
void Dataset::clear() {
    if (nRows == 0 && nCols == 0) {
        return;
    }
    colName->clear();
    for (int i = 0; i < nRows; ++i) {
        data->get(i)->clear();
    }
    data->clear();
    nRows = 0;
    nCols = 0;
}


////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// kNN INNER-CLASS DEFINITION ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

