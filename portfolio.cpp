#include "portfolio.h"
#include "purchase.h"

#include <iostream>
#include <iomanip>
using namespace std;

// constructor (allocate memory and initialise values)
Portfolio::Portfolio(int size) : maxSize(size), purchases(new Purchase[size]), stackTop(-1), queueFront(0), queueBack(0) {}
// destructor (free memory)
Portfolio::~Portfolio() { delete[] purchases; }

// add purchase to portfolio (buy stock shares)
bool Portfolio::buy(const Purchase& pNew) {

    if (isFull()) {
        cout << "Portfolio is full." << endl;
        return false;
    }

    purchases[queueBack] = pNew; // insert at back
    queueBack = (queueBack + 1) % maxSize; // update back index (circular)
    stackTop++; // update stack index
    count++;
    return true;
}

// remove (pop) purchase from portfolio (sell stocks - LIFO/stack)
bool Portfolio::sellLast(string& name, int num) {

    if (isEmpty()) {
        cout << "Portfolio is empty." << endl;
        return false;
    }

    int remaining = num;
    int sold = 0;

    while (remaining > 0) {
        int found = 0;

        // Search from newest to oldest (LIFO)
        for (int i = stackTop; i >= 0; i--) {
            if (purchases[i].getStockName() == name) {
                Purchase& p = purchases[i];

                // full purchase sale
                if (p.getNumShares() == remaining) {
                    for (int j = i; j < stackTop; j++) {
                        purchases[j] = purchases[j + 1];
                    }
                    stackTop--;
                    queueBack--;
                    count--;
                    cout << remaining << " shares of " << name << " stock from most recent purchase are sold successfully." << endl;
                    return true;
                }
                // partial sale
                else if (p.getNumShares() > remaining) {

                    p.setNumShares(p.getNumShares() - remaining);
                    cout << remaining << " shares of " << name << " stock from most recent purchase are sold successfully." << endl;
                    return true;
                }
                else {
                    // sell entire purchase and continue
                    remaining -= p.getNumShares();
                    // Shift elements down
                    for (int j = i; j < stackTop; j++) {
                        purchases[j] = purchases[j + 1];
                    }
                    stackTop--;
                    queueBack--;
                    count--;
                    cout << remaining << " shares remaining to sell." << endl;

                    found = 1;
                    sold = 1;
                    break; // restart search from new top
                }

            }
        }
        
        if (found == 0) {
            if (sold == 0) {
                cout << remaining << " shares of " << name << " not sold." << endl;
                return true;
            }
            cout << "No shares of " << name << " have been found." << endl;
            return false;
        }

    }
    return true;
}

// remove (dequeue) purchase from portfolio (sell stocks - FIFO/queue)
bool Portfolio::sellFirst(string& name, int num) {

    if (isEmpty()) {
        cout << "Portfolio is empty." << endl;
        return false;
    }

    int remaining = num;
    int sold = 0;

    while (remaining > 0) {
        int found = 0;

        // search from front to back
        for (int i = 0; i < count; i++) {
            Purchase& p = purchases[(queueFront + i) % maxSize];
            if (p.getStockName() == name) {
                
                if (p.getNumShares() == remaining) {
                    // full removal - shift elements left
                    for (int j = (queueFront + i) % maxSize; j < (queueFront + count - 1) % maxSize; j++) {
                        purchases[j] = purchases[(j + 1) % maxSize];
                    }
           
                    queueBack = (queueBack - 1 + maxSize) % maxSize;
                    count--;

                    if (stackTop >= ((queueFront + i) % maxSize)) {
                        stackTop = (stackTop - 1 + maxSize) % maxSize;
                    }

                    cout << remaining << " shares of " << name << " stock from oldest purchase are sold successfully." << endl;
                    return true;

                }
                else if (p.getNumShares() > remaining) {
                    // partial sale
                    p.setNumShares(p.getNumShares() - remaining);

                    cout << remaining << " shares of " << name << " stock from oldest purchase are sold successfully." << endl;
                    return true;
                }
                else {
                    // sell entire purchase and continue
                    remaining -= p.getNumShares();
                    // shift elements left
                    for (int j = (queueFront + i) % maxSize; j < (queueFront + count - 1) % maxSize; j++) {
                        purchases[j] = purchases[(j + 1) % maxSize];
                    }
                    queueBack = (queueBack - 1 + maxSize) % maxSize;
                    count--;
                    if (stackTop >= ((queueFront + i) % maxSize)) {
                        stackTop = (stackTop - 1 + maxSize) % maxSize;
                    }

                    cout << remaining << " shares remaining to sell." << endl;

                    found = 1;
                    sold = 1;
                    break; // restart search from new front

                }

            }
        }

        if (found == 0) {
            if (sold == 0) {
                cout << remaining << " shares of " << name << " not sold." << endl;
                return true;
            }
            cout << "No shares of " << name << " have been found." << endl;
            return false;
        }
    }

    return true;

}

// check if portfolio is full
bool Portfolio::isFull() const {
    if (count == maxSize) {
        return true;
    }
    else {
        return false;
    }
}

// check if portfolio is empty
bool Portfolio::isEmpty() const {
    if (count == 0) {
        return true;
    }
    else {
        return false;
    }
}

// print portfolio (purchases) using queue/FIFO order
void Portfolio::print() const {
    
    // check if portfolio is empty
    if (isEmpty()) {
        cout << "Portfolio is empty." << endl;
        return;
    }

    cout << "-------------------------------------------------------------------" << endl;
    cout << "               " << left << setw(15) << "Stock Name" << setw(15) << "Num of Shares" << setw(15) << "Price in GBP" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << ("Purchase n-" + to_string(i + 1));
        Purchase p = purchases[(queueFront + i) % maxSize];
        p.printInfo(); // print purchase object
    }
    cout << "-------------------------------------------------------------------" << endl;

}

// print purchases of specific stock using queue/FIFO order
void Portfolio::printStock(string& name) const {

    if (isEmpty()) {
        cout << "Portfolio is empty." << endl;
        return;
    }

    cout << "-------------------------------------------------------------------" << endl;
    cout << "               " << left << setw(15) << "Stock Name" << setw(15) << "Num of Shares" << setw(15) << "Price in GBP" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    // search for purchases with stock name
    int found = 0;
    for (int i = 0; i < count; i++) {
        Purchase& p = purchases[(queueFront + i) % maxSize];
        if (p.getStockName() == name) {
            cout << left << setw(15) << ("Purchase n-" + to_string(i + 1));
            p.printInfo();

            found = 1;
        }
    }

    if (found == 0) {
        cout << "No purchases with " << name << " stock are found." << endl;
    }

}