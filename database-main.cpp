/*
 * ===================================================================
 *
 *       Filename:  database-main.cpp
 *
 *    Description:  Main Method
 * 
 *       Compiler:  gcc
 *       
 * ===================================================================
 */

/**-------------------------------------------------------------------
 *  Include required header files
 *------------------------------------------------------------------*/
 
#include "database.h"
typedef enum operation { searchByAuthor = 1, search_by_title, isBook=3, seniorCustomer, oldestBook, reservationsList, getSold, bestAuthorByDate, bestCustomers, maxTranslator, PurchasingHistory, reservationHistory, deliveryTotalPrice, deliverySplitByCustomer, getStatusPurchaseById, xpressTotalPrice, sumBit, xactionsLargerThanAnnualAvg, deliveriesByCompany, twoEditionsIndelivery=20, noneRecentlyCustomer, orderedAndNotBought, booksInStorage, purchase_store_books, monthRevenue, annualTransactionsAvg, employee_salary_per_month, employee_Of_The_Month, main_menu
} Operation;

void menuEmployee(MySQL& Mysql);
void menuManager(MySQL&  Mysql);
void mainMenu(MySQL &Mysql)
{
	int user;
	cout << "Please press 1 for manager or 2 to employee (press 0 to exit)" << endl;
	cin >> user;
	if (user == 1)
	{
		menuManager(Mysql);
	}
	else if (user == 2)
	{
		menuEmployee(Mysql);
	}
	else if (user == 0)
	{
		exit;
	}
	else
	{
		cout << "Wrong number" << endl;
		mainMenu(Mysql);
	}
}

/**
	void printCommonMenu(): Prints menu of joint operations for manager and employee 
*/
void printCommonMenu()
{
	int op;
		cout << "\n Please press:\n\n 1 for searchByAuthor\n"
			" 2 for search_by_title\n"
			" 3 for isBook\n"
			" 4 for seniorCustomer\n"
			" 5 for oldestBook\n"
			" 6 for reservationsList\n"
			" 7 for getSold\n"
			" 8 for bestAuthorByDate\n"
			" 9 for bestCustomers\n"
			" 10 for maxTranslator\n"
			" 11 for PurchasingHistory\n"
			" 12 for reservationHistory\n"
			" 13 for deliveryTotalPrice\n"
			" 14 for deliverySplitByCustomer\n"
			" 15 for getStatusPurchaseById\n"
			" Enter 0 to main menu\n" << endl;
}

/**
	void printManagerMenu(): Prints menu of operations for manager only
*/
void printManagerMenu()
{
	int i = 0;
	cout << " \n Please press:\n 16 to xpressTotalPrice\n"
			" 17 to sumBit\n"
			" 18 to xactionsLargerThanAnnualAvg\n"
			" 19 to deliveriesByCompany\n"
			" 20 to twoEditionsIndelivery\n"
			" 21 to noneRecentlyCustomer\n"
			" 22 to orderedAndNotBought\n"
			" 23 to booksInStorage\n"
			" 24 to purchase_store_books\n"
			" 25 to monthRevenue\n"
			" 26 to annualTransactionsAvg\n"
			" 27 to employee_salary_per_month\n"
			" 28 to employee_Of_The_Month\n"
			" Enter 0 to main menu\n" << endl;

}

void menuEmployee(MySQL& Mysql)
{
	int option;
	do
	{
		printCommonMenu();
		cin >> option;
		switch (option)
		{
		case searchByAuthor: Mysql.searchByAuthor(); break;
		case search_by_title: Mysql.search_by_title(); break;
		case isBook: Mysql.isBook(); break;
		case seniorCustomer: Mysql.seniorCustomer(); break;
		case oldestBook: Mysql.oldestBook();  break;
		case reservationsList: Mysql.reservationsList(); break;
		case getSold: Mysql.getSold(); break;
		case bestAuthorByDate: Mysql.bestAuthorByDate(); break;
		case bestCustomers: Mysql.bestCustomers(); break;
		case maxTranslator: Mysql.maxTranslator(); break;
		case PurchasingHistory: Mysql.PurchasingHistory(); break;
		case reservationHistory: Mysql.reservationHistory(); break;
		case deliveryTotalPrice: Mysql.deliveryTotalPrice(); break;
		case deliverySplitByCustomer: Mysql.deliverySplitByCustomer(); break;
		case getStatusPurchaseById: Mysql.getStatusPurchaseById(); break;
		}
	} while (option > 0 && option < 16);
	mainMenu(Mysql);
}

void menuManager(MySQL& Mysql)
{
	int option;
	do
	{
		printManagerMenu();
		cin >> option;
		switch (option)
		{
		case xpressTotalPrice: Mysql.xpressTotalPrice(); break;
		case sumBit: Mysql.sumBit(); break;
		case xactionsLargerThanAnnualAvg: Mysql.xactionsLargerThanAnnualAvg(); break;
		case deliveriesByCompany: Mysql.deliveriesByCompany(); break;
		case twoEditionsIndelivery: Mysql.twoEditionsIndelivery(); break;
		case noneRecentlyCustomer: Mysql.noneRecentlyCustomer(); break;
		case orderedAndNotBought: Mysql.orderedAndNotBought(); break;
		case booksInStorage: Mysql.booksInStorage(); break;
		case purchase_store_books: Mysql.purchase_store_books(); break;
		case monthRevenue: Mysql.monthRevenue(); break;
		case annualTransactionsAvg: Mysql.annualTransactionsAvg(); break;
		case employee_salary_per_month: Mysql.employee_salary_per_month(); break;
		case employee_Of_The_Month: Mysql.employee_Of_The_Month(); break;

		}
	} while (option > 15 && option < 29);
	mainMenu(Mysql);
}

int main(void)
{
	MySQL Mysql;

	cout << "Hello!" << endl;
	mainMenu(Mysql);
	
    return 0;
}
