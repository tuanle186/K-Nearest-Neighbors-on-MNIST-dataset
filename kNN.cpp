#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

Dataset::Dataset() {
    data = new DLinkedList<DLinkedList<int>*>();
    nRows = 0;
    nCols = 0;
}

Dataset::~Dataset() {
    nRows = 0;
    nCols = 0;
    data->clear();
    delete data;
}

Dataset::Dataset(const Dataset& other) {

    /* 
     * The data variable has not been dynamically allocated
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

}

bool Dataset::loadFromCSV(const char* fileName) {

}