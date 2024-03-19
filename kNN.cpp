#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// Debugging Flag to print out errors
bool DEBUGGING_DATASET = false;

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
    if (nRows < 0 || nCols <= 0) { // Do not print anything | Note: nRows = 0 || nCols = 0 do what??
        return;
    }
    nRows = min(nRows, this->nRows);
    nCols = min(nCols, this->nCols);
    colName->printHead(nCols);
    cout << endl;
    for (int i = 0; i < nRows; ++i) {
        data->get(i)->printHead(nCols);
        if (i < nRows - 1) {
            cout << endl;
        }
    }
}


/* Status: Finished
*/
void Dataset::printTail(int nRows, int nCols) const {
    if (nRows < 0 || nCols <= 0) {
        return;
    }
    nRows = min(nRows, this->nRows);
    nCols = min(nCols, this->nCols);
    colName->printTail(nCols);
    cout << endl;
    for (int i = this->nRows - nRows; i < this->nRows; ++i) {
        data->get(i)->printTail(nCols);
        if (i < this->nRows - 1) {
            cout << endl;
        }
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
        endRow = this->nRows - 1;
    }
    if (endCol == -1) { // takes all cols
        endCol = this->nCols - 1;
    }

    // Set the nRows and nCols attribute of extractedDataset
    extractedDataset.nRows = endRow - startRow + 1;
    extractedDataset.nCols = endCol - startCol + 1;

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


List<string>* Dataset::getColName() const {
    return colName;
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


void Dataset::setShape(int nRows, int nCols) {
    this->nRows = nRows;
    this->nCols = nCols;
}


////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// kNN INNER-CLASS DEFINITION ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

kNN::kNN(int k) {
    this->k = k;
}


void kNN::fit(const Dataset& X_train, const Dataset& y_train) {
    this->X_train = X_train;
    this->y_train = y_train;
}


Dataset kNN::predict(const Dataset& X_test) {
    // Preprocessing
    // Prepare necessary vars of X_test traversing
    List<List<int>*>* X_test_data = X_test.getData();
    Node<List<int>*>* current_row_X_test = X_test_data->getHead();
    Node<int>* current_col_X_test;
    int nRows_X_test, nCols_X_test;
    X_test.getShape(nRows_X_test, nCols_X_test);

    // Prepare necessary vars of X_train traversing
    List<List<int>*>* X_train_data = X_train.getData();
    Node<List<int>*>* current_row_X_train = X_train_data->getHead();
    Node<int>* current_col_X_train;

    // Prepare necessary vars of y_train traversing
    List<List<int>*>* y_train_data = y_train.getData();
    Node<List<int>*>* current_row_y_train = y_train_data->getHead();
    Node<int>* current_col_y_train;
    
    // Prepare y_pred to store predicted label
    Dataset y_pred;
    List<List<int>*>* y_pred_data = y_pred.getData();
    Node<List<int>*>* current_row_y_pred = y_pred_data->getHead();
    y_pred.setShape(nRows_X_test, 1);
    List<string>* y_pred_colName = y_pred.getColName();
    y_pred_colName->push_back("label");

    // Prepare other necessary vars
    kNN_List* list = new kNN_List();
    int sum, feature_X_test, feature_X_train, prediced_label;
    double distance;

    while (current_row_X_test != nullptr) {
        current_row_X_train = X_train_data->getHead();
        current_row_y_train = y_train_data->getHead();
        while (current_row_X_train != nullptr) {
            sum = 0;
            current_col_X_test = current_row_X_test->data->getHead();
            current_col_X_train = current_row_X_train->data->getHead();
            current_col_y_train = current_row_y_train->data->getHead();
            while (current_col_X_test != nullptr && current_row_X_train != nullptr) {
                feature_X_test = current_col_X_test->data;
                feature_X_train = current_col_X_train->data;
                sum += pow(feature_X_test - feature_X_train, 2);
                current_col_X_test = current_col_X_test->next;
                current_col_X_train = current_col_X_train->next;
            }
            distance = sqrt(sum);
            list->push_back(current_col_y_train->data, distance);
            current_row_X_train = current_row_X_train->next;
            current_row_y_train = current_row_y_train->next;
        }
        list->sort();
        prediced_label = list->get_common_label(this->k);
        List<int>* newRow_y_pred = new DLinkedList<int>();
        newRow_y_pred->push_back(prediced_label);
        y_pred_data->push_back(newRow_y_pred);
        list->clear();
        current_row_X_test = current_row_X_test->next;
    }
    delete list;
    return y_pred;
}


double kNN::score(const Dataset& y_test, const Dataset& y_pred) {
    List<List<int>*>* y_test_data = y_test.getData();
    List<List<int>*>* y_pred_data = y_pred.getData();

    Node<List<int>*>* current_row_y_test = y_test_data->getHead();
    Node<List<int>*>* current_row_y_pred = y_pred_data->getHead();
    int n_correct_prediction = 0; // counting correct prediction
    int a, b;
    while (current_row_y_test != nullptr && current_row_y_test != nullptr) {
        a = current_row_y_test->data->getHead()->data;
        b = current_row_y_pred->data->getHead()->data;
        if (a == b) {
            n_correct_prediction++;
        }
        current_row_y_test = current_row_y_test->next;
        current_row_y_pred = current_row_y_pred->next;
    }

    int n_prediction, dummy;
    y_test.getShape(n_prediction, dummy);
    double accuracy = n_correct_prediction/double(n_prediction);
    return accuracy;
}


void train_test_split(  Dataset& X,           // Input: features
                        Dataset& y,           // Input: labels
                        double test_size,     // Input: test_size (0, 1)
                        Dataset& X_train,     // Output
                        Dataset& X_test,      // Output
                        Dataset& y_train,     // Output
                        Dataset& y_test)      // Output
{
    // Preprocessing
    int nRows_original, nCols_original;
    X.getShape(nRows_original, nCols_original);
    int nRows_test = ceil(test_size*nRows_original);
    int nRows_train = nRows_original - nRows_test;

    // Extracting
    X_train = X.extract(0, nRows_train - 1, 0, -1);
    X_test = X.extract(nRows_train, -1, 0, -1);
    y_train = y.extract(0, nRows_train - 1, 0, -1);
    y_test = y.extract(nRows_train, -1, 0, -1);
}