// variable-sized array implementation of portfolio with FIFO/LIFO
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "purchase.h"
#include <string>
using namespace std;


class Portfolio {

private:
    Purchase* purchases; // pointer to array of purchases
    int maxSize; // max size of portfolio
    int count; // keep track of number of purchases
    int stackTop; // index to track most recent - lifo
    int queueFront; // index to track oldest - fifo
    int queueBack; // index to track insertion

public:

    Portfolio(int size = 20); // constructor - initialize with default size of 20 (if no user input)
    ~Portfolio(); // destructor (free allocated memory)

    // main methods/functions
    bool buy(const Purchase& pNew); // add purchase
    bool sellFirst(string& name, int num); // FIFO - queue
    bool sellLast(string& name, int num); // LIFO - stack

    // check if portfolio is full/empty
    bool isEmpty() const;
    bool isFull() const;

    // display portfolio (in fifo order)
    void print() const;
    // display filtering by stock name (in fifo order)
    void printStock(string& name) const;

};
#endif