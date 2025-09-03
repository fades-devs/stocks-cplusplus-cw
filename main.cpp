// main file for program execution
#include "portfolio.h"
#include "purchase.h"
#include <iostream>
#include <iomanip>
using namespace std;

// function declarations
void stockPerformance(Portfolio& pf);
void findStock(Portfolio& pf);
void setupData(Portfolio& pf);
void showPortfolio(Portfolio& pf);

int main() {

	cout << "-------------------------------------------------------------------" << endl;
	cout << "                        Welcome to Stocks++                        " << endl;
	cout << "-------------------------------------------------------------------" << endl;

	// get valid portfolio size from user
	int size;
	while (true) {
		cout << "Please enter the estimated number of purchases you'd like to make in your portfolio (min 20 and max 40): ";
		if (cin >> size && size >= 20 && size <= 40)
		{
			break;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error. Please enter valid input." << endl;
	}
	
	// initialize portfolio (allocate memory based on user input)
	Portfolio portfolio(size);

	// display menu options
	int option;
	do {
		cout << "1. Enter stock performance" << endl;
		cout << "2. Find stock" << endl;
		cout << "3. Set up test data" << endl;
		cout << "4. Show stock portfolio" << endl;
		cout << "5. Exit" << endl;
		cout << "Select an option: ";
		cin >> option;

		// call relevant function based on selected option
		switch (option) {
		case 1:
			stockPerformance(portfolio);
			break;
		case 2:
			findStock(portfolio);
			break;
		case 3:
			setupData(portfolio);
			break;
		case 4:
			showPortfolio(portfolio);
			break;
		case 5:
			cout << "Exiting program..." << endl;
			break;
		default:
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid. Please enter a valid option." << endl;
		}
	}
	while (option != 5);

	return 0;
}

// handle stock performance based on percentage change
void stockPerformance(Portfolio& pf) {
	
	string name;
	double percentage;

	// get valid stock name and percentage change
	cout << "Enter the stock name: ";
	cin >> name;
	while (true) {
		cout << "Enter the stock percentage change (from -100 to 100)." << endl
			<< "For example: -5.5 means a decrease by 5.5 %: ";

		if (!(cin >> percentage)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error. Please enter valid input." << endl;
		}
		else {
			break;
		}

	}

	// sell shares from the earliest purchase - FIFO/queue
	if (percentage >= 5.0 && percentage <= 20.0) {

		int num;
		while (true) {
			cout << "Enter the number of shares to sell: ";

			if (!(cin >> num) || num <= 0) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error. Please enter valid input." << endl;
			}
			else {
				break;
			}
		}

		pf.sellFirst(name, num);
		
	}

	// buy shares using FIFO/queue logic
	else if (percentage >= -1.0 && percentage <= -0.5) {

		int shares;
		double price;

		while (true) {
			cout << "Enter the number of shares to buy: ";
			if (!(cin >> shares) || shares <= 0) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error. Please enter valid input." << endl;
			}
			else {
				break;
			}
		}

		while (true) {
			cout << "Enter the stock price per share in GBP: ";
			if (!(cin >> price) || price <= 0) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error. Please enter valid input." << endl;
			}
			else {
				break;
			}
		}

		pf.buy(Purchase(name, shares, price));
		cout << "Your purchase of " << shares << " shares of " << name << " @ " << price << "GBP is successful." << endl;
	}

	// sell shares from the newest purchase - LIFO/stack
	else if (percentage >= -3.0 && percentage <= -1.1) {

		int num;
		while (true) {
			cout << "Enter the number of shares to sell: ";

			if (!(cin >> num) || num <= 0) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error. Please enter valid input." << endl;
			}
			else {
				break;
			}
		}

		pf.sellLast(name, num);
	}
	else {
		cout << "No portfolio updates (no actions taken)." << endl;
	}
}

// display all purchases of specific stock
void findStock(Portfolio& pf) {

	// prompt user to enter stock name
	string name;
	cout << "Enter the stock name: ";
	cin >> name;

	pf.printStock(name);

}

// populate portfolio with 10 test purchases
void setupData(Portfolio& pf) {

	const int SIZE = 10;
	Purchase testData[SIZE] = { Purchase("MSFT", 100, 20), Purchase("GME", 200, 25), Purchase("GME", 150, 20), Purchase("AAPL", 300, 30),
	Purchase("MSFT", 250, 15), Purchase("GME", 350, 25), Purchase("MSFT", 150, 35), Purchase("AAPL", 200, 15), Purchase("GME", 100, 40),
	Purchase("AMZN", 300, 10) };

	int counter = 0;
	for (int i = 0; i < SIZE; i++) {
		if (!pf.isFull()) {
			pf.buy(testData[i]);
			counter++;
		}
		else {
			cout << "Full portfolio. " << counter << " added to purchases." << endl;
			return;
		}
	}
	cout << "Populated " << SIZE << " purchases successfully." << endl;
}

// display entire portfolio
void showPortfolio(Portfolio& pf) {

	pf.print();
}