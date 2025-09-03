#include "purchase.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

// constructor
Purchase::Purchase(string name, int shares, double price) : stockName(name), numShares(shares), stockPrice(price) {}

// member functions (getters/setters)
string Purchase::getStockName() const { return stockName; }
int Purchase::getNumShares() const { return numShares; }
double Purchase::getStockPrice() const { return stockPrice; }

void Purchase::setNumShares(int shares) { numShares = shares; }
void Purchase::setStockPrice(double price) { stockPrice = price; }

// display each purchase (print info in a formatted way)
void Purchase::printInfo() const {
	cout << left << setw(15) << stockName << setw(15) << numShares << setw(15) << stockPrice << endl;
}