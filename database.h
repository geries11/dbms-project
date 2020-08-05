/*
 * ===================================================================
 *
 *       Filename:  database.h
 *
 *    Description:  Declaring MySQL class for using database.
 *        
 *       Compiler:  gcc
 *
 * ===================================================================
 */

/**-------------------------------------------------------------------
 *  Include database-detail.h and other files
 *------------------------------------------------------------------*/

#include "header.h"
#include "database-detail.h"

/**
 * ===================================================================
 *        Class:  MySQL
 *  Description:  MySQL class for database accessability
 * ===================================================================
 */

class MySQL
{
    protected:
        /** MySQL connectivity Variables */
        MYSQL *connect;
        MYSQL_RES *res_set;
        MYSQL_ROW row;
        MYSQL_FIELD field;
		string getCurrDate();
		string getDateXYearsAgo(int x);
		bool isBookBool(string bookName);
		bool isCustomer(int id);
		bool checkMonth(int month);

        unsigned int i;

    public:
        /** MySQL Constructor */
        MySQL();

		void searchByAuthor();;
		void search_by_title();
		//1
		void isBook();
		//2
		void seniorCustomer();
		//3
		void oldestBook();
		//4
		void reservationsList();
		//5
		void getSold();
		//6
		void bestAuthorByDate();
		//7
		void bestCustomers();
		//8
		void maxTranslator();
		//9
		void PurchasingHistory();
		//10
		void reservationHistory();
		//11
		void deliveryTotalPrice();
		//12
		void deliverySplitByCustomer();
		//13
		void getStatusPurchaseById();
		//14
		void xpressTotalPrice();
		//15
		void sumBit();
		//16
		void xactionsLargerThanAnnualAvg();
		//17
		void deliveriesByCompany();
		//18
		void twoEditionsIndelivery();
		void noneRecentlyCustomer();
		//20
		void orderedAndNotBought();
		//21
		void booksInStorage();
		//22A
		void purchase_store_books();
		//22B
		void monthRevenue();
		//23
		void annualTransactionsAvg();
		//24
		void employee_salary_per_month();
        //25
		void employee_Of_The_Month();

		/** MySQL Destructor */
        ~MySQL();
};
