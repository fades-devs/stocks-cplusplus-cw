// purchase class definition - for each stock purchase
#ifndef PURCHASE_H
#define PURCHASE_H

#include <string>
using namespace std;


class Purchase {

private:
	string stockName;
	int numShares;
	double stockPrice;

public:
	// constructors
	Purchase(string name, int shares, double price); // initialised
	Purchase() = default; // default (for array allocation)

	// getters to get values
	string getStockName() const;
	int getNumShares() const;
	double getStockPrice() const;

	// setters to set values
	void setNumShares(int shares);
	void setStockPrice(double price);

	// display formatted purchase info
	void printInfo() const;

};

#endif