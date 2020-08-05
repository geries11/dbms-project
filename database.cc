/**-------------------------------------------------------------------  *  Include mysql.h file local header file(declaration of class)  *------------------------------------------------------------------*/

#include "database.h"
#include <string>#include<ctime>
#include<ctime>

/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: MySQL()
 * Description:  Constructor to initialize database conectivity
 *--------------------------------------------------------------------
 */

MySQL :: MySQL()
{
    connect = mysql_init(NULL);
    if ( !connect )
    {
        cout << "MySQL Initialization Failed";
    }   

    connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0,NULL,0);
    
    /*if ( connect )
    {
        cout << "Connection Succeeded\n";
    }*/
    
	if (!(connect))
    {
        cout << "Connection Failed\n";
    }
}

/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: ShowTables()
 * Description:  Show tables in database
 *--------------------------------------------------------------------
 */

/*-------------------------------------------------*/

//search by book name
void MySQL::search_by_title()
{
	string bookName;
	int op;
	cout << "Please enter book name: ";
	std::getline(std::cin >> std::ws, bookName);
	string sql = "select* from book b, inventory i where b.book_id = i.book_id AND b.name = '" + bookName + "';";
	mysql_query(connect, sql.c_str()); //run query 
	res_set = mysql_store_result(connect); //get results from DB

	unsigned int numrows = mysql_num_rows(res_set);
	unsigned int numcols = mysql_num_fields(res_set);
	if (numrows == 0) {
		cout << "Couldn't find book" << endl;
		cout << "Please enter 1 to search a book or 0 to menu" << endl;
		cin >> op;
		if (op == 1) {
			search_by_title();
		}
	}
		while (((row = mysql_fetch_row(res_set)) != NULL)) {
		for (int i = 0; i < numcols; i++) {
			if (row[i] == NULL)
			{
				continue;
			}
			cout << row[i] << " ";
		}
		cout << endl;
		cout << "Please enter 1 to search a book or 0 to menu" << endl;
		cin >> op;
		if (op == 1) {
			search_by_title();
		}

	}
}


//search by author name
void MySQL::searchByAuthor()
{
	string author;
	int op;
	cout << "Please enter author first name: ";
	std::getline(std::cin >> std::ws, author);
	string sql = "SELECT   b.name, GROUP_CONCAT(CONCAT(a.first_name, ' ', a.last_name)) AS author_names, GROUP_CONCAT(a.author_id) as author_id FROM book b LEFT JOIN author_book ab ON b.book_id = ab.book_id LEFT JOIN author a ON ab.author_id = a.author_id WHERE a.first_name = '"+author+"' GROUP BY b.book_id";

	mysql_query(connect, sql.c_str()); //run query 
	res_set = mysql_store_result(connect); //get results from DB

	unsigned int numrows = mysql_num_rows(res_set);
	unsigned int numcols = mysql_num_fields(res_set);
	if (numrows == 0) {
		cout << "Couldn't find author" << endl;
		return;
	}
	while (((row = mysql_fetch_row(res_set)) != NULL)) {
		for (int i = 0; i < numcols; i++) {
			if (row[i] == NULL)
			{
				continue;
			}
			cout << row[i] << " ";
		}
		cout << endl;
	}
}

/**void MySQL::isBook(): search if book exists. gets name as a string, prints true or false. 
*/
//1
void MySQL::isBook()
{
	string s;
	int op;
	string sql;
	cout << "Please enter book name: ";
	std::getline(std::cin >> std::ws, s);
	sql = "select count from book inner join inventory on book.book_id = inventory.book_id where name='" + s + "' And inventory.count>0";
	mysql_query(connect, sql.c_str());
	int i = 0;

	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	if (numrows == 0) 
	{
		cout << "Book not found" << endl;
		cout << "Please enter 1 to search a book or 0 to menu" << endl;
		cin >> op;
		if (op == 1){
			isBook();
		}
	}
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
			cout << "Book is found" << endl;
			cout << "Please enter 1 to search a book or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				isBook();
			}
	}
}

/**void MySQL::seniorCustomer(): prints senior customer
*/
//2
void MySQL::seniorCustomer()
{
	string sql = "select concat(first_name, ' ', last_name) as name from customer order by date_created limit 1";
	mysql_query(connect, sql.c_str()); //run query 
	
	int i = 0;

	res_set = mysql_store_result(connect); //get results from DB

	unsigned int numrows = mysql_num_rows(res_set); //rows number of results
	
	if (numrows == 0) { 
		cout << "no customers" << endl; 
		return;
	}
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		cout <<"senior customer is: "<< row[0]<<endl;
	}
}
/**prints the book that is in stock the longest
*/
//3
void MySQL::oldestBook() {
	string sql = "select book.name from book inner join inventory on book.book_id = inventory.book_id where inventory.count > 0 order by time_stamp limit 1";
	mysql_query(connect, sql.c_str()); //run query 
	res_set = mysql_store_result(connect); //get results from DB
	unsigned int numrows = mysql_num_rows(res_set); //rows number of results
	unsigned int numcols = mysql_num_fields(res_set);
	if (numrows == 0) {
		cout << "no books in inventory" << endl;
		return;
	}
	while (((row = mysql_fetch_row(res_set)) != NULL)) {
		for (int i = 0; i < numcols; i++) {
			if (row[i] == NULL) { continue; }
			cout <<"Oldest book: "<< row[i]<<" "<< endl;
		}
	}
}
/**void MySQL::reservationsList(): prints all reservations and details  
*/
//4
void MySQL::reservationsList() {
	string sql = "select * from reservation inner join reservation_book on reservation.reservation_id = reservation_book.reservation_id inner join book on book.book_id = reservation_book.book_id inner join customer c on c.customer_id = reservation.customer_id order by time_stamp; ";
	mysql_query(connect, sql.c_str()); //run query 
	res_set = mysql_store_result(connect); //get results from DB
	unsigned int numrows = mysql_num_rows(res_set); //rows number of results
	unsigned int numcols = mysql_num_fields(res_set);
	if (numrows == 0) {
		cout << "There are no reservations" << endl;
		return;
	}
	int j = 1;
	cout << "Reservations list\n" << endl;
	while (((row = mysql_fetch_row(res_set)) != NULL)) {
		cout << j << ".Reservation id: " << row[1] << endl;
		cout << "  Reservation date: " << row[2] << endl;
		cout << "  Book name: " << row[7] << endl;
		cout << "  Books amount: " << row[6] << endl;
		if (row[13]!=NULL && row[14]!=NULL && row[15]!=NULL)
		{
			cout << "  Customer name: " << row[13] << " " << row[14] << endl;
			cout << "  Mobile: " << row[15] << endl;
		}
		j++;
		cout <<"\n\n";
	}
}
/**bool MySQL::isBookBool(string bookName): inner function: check if book is in stock. returns true or false
*/
bool MySQL::isBookBool(string bookName)
{
	string sql;
	sql = "select count from book inner join inventory on book.book_id = inventory.book_id where name='" + bookName + "' And inventory.count>0";
	mysql_query(connect, sql.c_str());

	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	if (numrows == 0)
	{
		return false;
	}
	return true;

}
/**void MySQL::getSold(): gets book name as a string, prints amount of books the sotre sold 
*/
//5
	void MySQL::getSold() {
		string bookName;
		int op;
		cout << "please enter book name: ";
		std::getline(std::cin >> std::ws, bookName);
		if (!(isBookBool(bookName)))
		{
			cout << "No such book exists.\n" << endl;
			cout << "Press 1 to try again id or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				getSold();
			}
			return;
			
		}
		string sql = "select sum(inventory.sold_counter) as sold_books_amount from book left join inventory on book.book_id = inventory.book_id where book.name='" + bookName + "'";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 1) {
			while (((row = mysql_fetch_row(res_set)) != NULL))
			{
				if (row[0] != NULL && row[1] != NULL) {
					cout << "number of books wich have been sold: ";
					cout << row[0] << endl;
					cout << "Please enter 1 to search a book or 0 to menu" << endl;
					cin >> op;
					if (op == 1) {
						getSold();
					}
					return;
				}
			}
			cout << "the book never sold" << endl;
			cout << "Please enter 1 to search a book or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				getSold();
			}
			return;
		}
		
	}
	
	//6
	/**void MySQL::bestAuthorByDate(): gets two dates, prints the most popular author (according to purchases) 
	*/
	void MySQL::bestAuthorByDate()
	{
		string date1, date2;
		int op;
		cout << "please enter start date (for example: 2020-01-27): ";
		cin >> date1;
		cout << "\nplease enter end date (for example: 2020-01-27): ";
		cin >> date2;
		string sql = "select a.first_name, a.last_name from author a, purchase_customer pc, purchase_customer_book pcb, author_book ab where pc.purchase_id = pcb.purchase_id AND pcb.book_id = ab.book_id AND a.author_id = ab.author_id AND pc.purchase_date between '" + date1 + "' AND '" + date2 + "' group by a.author_id order by count(*) desc limit 1";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "Coudn't find author" << endl;
			cout << "Press 1 to change dates or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				bestAuthorByDate();
			}
			return;
		}
		cout << "Best author during '"+date1+"'-'"+date2+"': ";
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL && row[1] != NULL) {
				cout << row[0] << row[1] <<endl;
			}
		}
		cout << "Press 1 to change dates or 0 to menu" << endl;
		cin >> op;
		if (op == 1) {
			bestAuthorByDate();
		}
		return;
	}
	//7
	/**void MySQL::bestCustomers():  prints 3 best customers
	*/
	void MySQL::bestCustomers() {
		string sql = "	select customer.first_name, customer.last_name from customer inner join purchase_customer on customer.customer_id = purchase_customer.customer_id group by customer.customer_id order by count(*) desc limit 3";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "Coudn't find customers" << endl;
			return;
		}
		cout << "Best 3 customers: " << endl;
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL && row[1] != NULL) {
				cout << row[0] <<" "<<row[1] << endl;
			}
		}
	}

	/**
	void MySQL::maxTranslator(): prints the book with max number of translations in stock
	*/
	//8
	void MySQL::maxTranslator() {
		string sql = "select count(b.name) as translations_amount,b.name from book b inner join inventory i on b.book_id = i.book_id inner join book_edition be on b.book_id = be.book_id where be.translator IS NOT NULL group by b.name order by count(b.name) desc limit 1;";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "No translated books found" << endl;
			return;
		}
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL && row[1] != NULL) {
				cout << "the book with the max number of translations:" << endl;
				cout << row[1] <<" was translated " << row[0] << " different times"<< endl;
			}
		}
	}
	/**void MySQL::PurchasingHistory(): gets customer id, prints customer's purchasing history
	*/
	//9
	void MySQL::PurchasingHistory() {
		int customer_id;
		int op;
		cout << "please enter customer id: ";
		cin >> customer_id;
		if (!(isCustomer(customer_id)))
		{
			cout << "No such customer exists.\n" << endl;
			cout << "Press 1 to try again or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				PurchasingHistory();
			}
			return;
		}
		string sql = "select book.name, pc.purchase_date, pcb.price, pc.purchase_id from book, purchase_customer pc, purchase_customer_book pcb, customer c where c.customer_id = pc.customer_id AND pc.purchase_id = pcb.purchase_id AND book.book_id = pcb.book_id AND c.customer_id='"+to_string(customer_id)+"' order by pc.purchase_date;";

		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "couldn't find purchases" << endl;
			cout << "Press 1 to change name or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				PurchasingHistory();
			}
			return;
		}
		cout << "Purchasing History:" << endl;
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL && row[1] != NULL) {
				cout <<"Purchase id: "<<row[3]<<" purchase date: " << " " << row[1] << " " << "price: " << row[2] << " " << "book name: " << row[0] << endl;
			}
		}
	}

	/**
	void MySQL::reservationHistory(): A query that takes customer id and returns his reservations history, and books in inventory of which he ordered in the past - if he did. 
	*/
	//10
	void MySQL::reservationHistory() {
		int customer_id;
		int op;
		cout << "please enter customer id: ";
		cin >> customer_id;
		if (!(isCustomer(customer_id)))
		{
			cout << "No such customer exists.\n" << endl;
			cout << "Press 1 to try again or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				reservationHistory();
			}
			return;
		}
		string sql = "select book.name, rb.count, reservation.time_stamp, inventory.book_id, pcb.*, pc.purchase_date from customer inner join reservation on customer.customer_id = reservation.customer_id "
			"			inner join reservation_book rb on rb.reservation_id = reservation.reservation_id "
			"			inner join book on book.book_id = rb.book_id "
			"			left join inventory on inventory.book_id = book.book_id "
			"			left join purchase_customer_book pcb on pcb.book_id = book.book_id "
			"			left join purchase_customer pc on pc.purchase_id = pcb.purchase_id AND pc.customer_id = customer.customer_id"
			"			where customer.customer_id='" + to_string(customer_id) + "' order by reservation.time_stamp ";
		
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "There are no reservations" << endl;
			cout << "Press 1 to change name or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				reservationHistory();
			}
			return;
		}
		cout << "\n" <<"Customer's reservations: \n";
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL && row[1] != NULL && row[2]!= NULL) {
				cout << "Book name: "<<row[0]<< "\n" <<row[1]<<" copies were ordered.\nreservation date: " << row[2]<<endl;
				if (row[4] != NULL) 
				{ 
					cout << "Book is found in inventory" << endl;
					if (row[5] != NULL)
					{
						cout << "Book was bought by customer" << endl;
					}
					else
					{
						cout << "Customer didn't purchase book" << endl;

					}
				} 
				else
				{ 
					cout << "Book not found in inventory" << endl;
				}
			}
		}
	}
	/**void MySQL::deliveryTotalPrice(): Calculation of the amount of delivery price by weight in addition to the price of the books
	*/
	//11
	void MySQL::deliveryTotalPrice() {
		int purchase_id;
		int op;
		cout << "Please enter purchase id: ";
		cin >> purchase_id;
		string sql = "	select sum((d.price* book.weight) + pcb.price) from purchase_customer pc inner join deliveries d on pc.purchase_id = d.purchase_id inner join purchase_customer_book pcb on pcb.purchase_id = pc.purchase_id inner join book on book.book_id = pcb.book_id where pc.purchase_id = '"+to_string(purchase_id)+"';";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);
		
		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 1) {
			while (((row = mysql_fetch_row(res_set)) != NULL))
			{
				if (row[0] != NULL) {
					cout << "Total price: " << row[0] << endl;
					cout << "Press 1 to change purchase id or 0 to menu" << endl;
					cin >> op;
					if (op == 1) {
						deliveryTotalPrice();
					}
					return;
				}
			}
			cout << "Couldn't find delivery" << endl;
			cout << "Press 1 to change purchase id or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				deliveryTotalPrice();
			}
			return;
		}

	}
	/**
	bool MySQL::isCustomer(int id): gets customer id, returns true - customer exist ot false - customer doesn't exist
	*/
	bool MySQL::isCustomer(int id)
	{
		string sql = "select * from customer c where c.customer_id = '"+to_string(id)+"'";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);

		if (numrows == 0)
		{
			return false;
		}
		return true;
	}
	/**void MySQL::deliverySplitByCustomer(): gets id number and prints allpurchases wich splited to 2 or more deliveries 
	*/
	//12
	void MySQL::deliverySplitByCustomer()
	{
		int customer_id;
		int op = 1;
		cout << "Please enter customer id: ";
		cin >> customer_id;
		if (!(isCustomer(customer_id)))
		{
			cout << "No such customer exists.\n" << endl;
			cout << "Press 1 to try again or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				deliverySplitByCustomer();
			}
			return;
		}
		string sql = "select * from deliveries d left join purchase_customer pc on pc.purchase_id = d.purchase_id where pc.customer_id = '"+to_string(customer_id)+"' and d.purchase_id in (select d.purchase_id from deliveries d  group by d.purchase_id having count(d.purchase_id) > 1) order by d.purchase_id;";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "Customer did not split delivery" << endl;
			return;
		}
		cout << "\nThe customer splited the following purchases to number of deliveries: \n" << endl;
		while (((row = mysql_fetch_row(res_set)) != NULL)) {
			cout <<"Purchase id: " << row[1] << "\nDelivery Id: " << row[0] << "\nStatus: " << row[3] << "\nType: " << row[4] << "\nPrice: " << row[5] << "\nDate: " << row[6] << endl;
			cout << endl;
		}
	}

	//13
	/**void MySQL::getStatusPurchaseById(): returns status delivery by getting purchase id 
	*/
	void MySQL::getStatusPurchaseById() {
		int purchaseIdd;
		cout << "Please enter purchase id: ";
		cin >> purchaseIdd;
		string sql = "select d.status from deliveries d, purchase_customer pc where d.purchase_id = pc.purchase_id And d.purchase_id = '" + to_string(purchaseIdd) + "'";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "Couldn't find delivery" << endl;
			return;
		}
		cout << "Delivery status: " << endl;
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL) {
				cout << row[0] << endl;
			}
		}
	}
	/*-------------------------------------------------------------------*/
	/**bool MySQL::checkMonth(int month): an inner finction to check if month is valid
	*/
	bool MySQL::checkMonth(int month)
	{
		if (month < 1 || month > 12)
			return false;
		else {
			return true;
		}
	}
	//14
	/** void MySQL::xpressTotalPrice(): sum deliveries of Xpress company at specific month
	*/
	void MySQL::xpressTotalPrice() {
		int month;
		int year;
		int op;
		cout << "Enter wanted month (1-12) and year to check total price for xPress Company: ";
		cin >> month >> year;
		if (!(checkMonth(month)))
		{
			cout << "Not a valid month.\nPress 1 to try again or 0 to menu\n";
			cin >> op;
			if (op == 1) 
			{
				xpressTotalPrice();
			}
			return; 
		}
		string sql = "	select sum((d.price* book.weight)) from purchase_customer pc inner join deliveries d on pc.purchase_id = d.purchase_id inner join purchase_customer_book pcb on pcb.purchase_id = pc.purchase_id inner join book on book.book_id = pcb.book_id inner join delivery_company dc on dc.company_id = d.delivery_company where dc.company_name = 'Xpress' AND month(d.delivery_date) = ' " + to_string(month) + " ' AND year(d.delivery_date) ='"+to_string(year)+"' ";

		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);

		if (numrows == 1) {
			while (((row = mysql_fetch_row(res_set)) != NULL))
			{
				if (row[0] != NULL) {
					cout << "Total price: " << row[0] << endl;
					cout << "Please enter 1 to check different month or 0 to menu" << endl;
					cin >> op;
					if (op == 1) {
						xpressTotalPrice();
					}
					return;
				}
				else
				{
					cout << "NO data" << endl;
					cout << "Please enter 1 to check different month or 0 to menu" << endl;
					cin >> op;
					if (op == 1) {
						xpressTotalPrice();
					}
					 return;

				}
			}
		}
		
	}

	//15
	/** void MySQL::sumBit(): A query that returns the total sum  
	that was transferred to the store via bit 
	by month and year enetered by the manager. 
	*/
	void MySQL::sumBit()
	{
		int month, year;
		int op;
		cout << "Enter wanted month (1-12) and year to check sum of purchases made via Bit: ";
		cin >> month >> year;
		if (!(checkMonth(month)))
		{
			cout << "Not a valid month.\nPress 1 to try again or 0 to menu\n";
			cin >> op;
			if (op == 1)
			{
				sumBit();
			}
			return; 
		}

		string sql = "select sum(pcb.price) from purchase_customer pc inner join purchase_customer_book pcb on pc.purchase_id = pcb.purchase_id where pc.payment_method='bit' AND month(pc.purchase_date) = '" + to_string(month) + "' AND year(pc.purchase_date) = '"+to_string(year)+"'";

		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 1) {
			while (((row = mysql_fetch_row(res_set)) != NULL))
			{
				if (row[0] != NULL) {
					cout << "Bit sum: " << row[0] << endl;
					cout << "Please enter 1 to check different month or 0 to menu" << endl;
					cin >> op;
					if (op == 1) {
						sumBit();
					}
					return;
				}
				else 
				{
					cout << "There are no payments from bit" << endl;
					cout << "Please enter 1 to check different month or 0 to menu" << endl;
					cin >> op;
					if (op == 1) {
						sumBit();
					}
					return;
				}
			}

		}
	}

	/** string MySQL::getCurrDate(): An inner method that returns current date used for some queries.
	*/
	string MySQL::getCurrDate()
	{
		string str_month;
		string str_day;
		time_t now = time(0);//get the current time
		tm* ltm = localtime(&now);
		int curr_year = 1900 + ltm->tm_year;
		int curr_month = 1 + ltm->tm_mon;
		if (curr_month < 10)
		{
			str_month = "0" + to_string(curr_month);
		}
		else
		{
			str_month = to_string(curr_month);
		}
		int curr_day = ltm->tm_mday;
		if (curr_day < 10)
		{
			str_day = "0" + to_string(curr_day);
		}
		else
		{
			str_day = to_string(curr_day);
		}
		string current_date = to_string(curr_year) + "-" + str_month + "-" + str_day;
		return current_date;
	}

	/** string MySQL::getDateXYearsAgo(): An inner method 
	gets number of years as x variable
	returns date x years ago from now as a string
	*/
	string MySQL::getDateXYearsAgo(int x)
	{
		string str_month;
		string str_day;
		time_t now = time(0);//get the current time
		tm* ltm = localtime(&now);
		int curr_year = 1900 -x + ltm->tm_year;
		int curr_month = 1 + ltm->tm_mon;
		if (curr_month < 10)
		{
			str_month = "0" + to_string(curr_month);
		}
		else
		{
			str_month = to_string(curr_month);
		}
		int curr_day = ltm->tm_mday;
		if (curr_day < 10)
		{
			str_day = "0" + to_string(curr_day);
		}
		else
		{
			str_day = to_string(curr_day);
		}
		string current_date = to_string(curr_year) + "-" + str_month + "-" + str_day;
		return current_date;
	}

	//16 x=trans
	/**
	void MySQL::xactionsLargerThanAnnualAvg(): A query that returns all transactions that 
	are bigger than the annual transactions average.
	*/
	void MySQL::xactionsLargerThanAnnualAvg()
	{
		string one_year_ago_date = getDateXYearsAgo(1); //get the current date minus a year
		string sql = "select pcb.purchase_id, sum(pcb.price) as sum_purchase, pc.purchase_date from purchase_customer pc, purchase_customer_book pcb where pc.purchase_id = pcb.purchase_id AND pc.purchase_date > '" + one_year_ago_date + "' group by pc.purchase_date having sum_purchase > (select avg(pcb.price) as annual_avg from purchase_customer pc inner join purchase_customer_book pcb where pc.purchase_id = pcb.purchase_id AND pc.purchase_date > '" + one_year_ago_date + "'); ";
		int i = 0;

		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		unsigned int numcols = mysql_num_fields(res_set);

		
		if (numrows == 0) {
			cout << "Each of the transactions is less that the annual average cost of the whole transactions\n OR there were no transactions at all" << endl;
			return;
		}
		cout << "Transactions from the last 12 months that are larger than the annual average cost of the whole transactions\n"<< endl;
		cout << "purchase id\tpurchase price\tpurchase date" << endl;
		while (((row = mysql_fetch_row(res_set)) != NULL)) {
			for (int i = 0; i < numcols; i++) {
				if (row[i] == NULL)
				{
					continue;
				}
				cout << row[i] << "\t\t";
			}
			cout << endl;
		}
	}


	//17
	/** void MySQL::deliveriesByCompany():A query that returns the number of transactions made by each comany during the past 12 months. 
	*/
	void MySQL::deliveriesByCompany()
	{
		string current_date = getCurrDate(); //get the current date
		string sql = "select count(*), dc.company_name from deliveries d, delivery_company dc where dc.company_id = d.delivery_company AND d.delivery_date > '" + current_date + "' group by dc.company_name";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "there are no deliveries" << endl;
			return;
		}
		cout << "All deliveries during the last 12 months:\n";
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL && row[1] != NULL) {
				cout << row[0] << " deliveries from company: " << row[1] << endl;
			}
		}
		return;
	}

	//18 
	/**void MySQL::twoEditionsIndelivery(): prints list of deliveries wich contain two editions of book
	*/
	void MySQL::twoEditionsIndelivery()
	{
		string sql = "select d.*, d.deliveries_id, b.name from deliveries d inner join deliveries_books db on d.deliveries_id = db.deliveries_id inner join book b on db.book_id = b.book_id group by d.deliveries_id, b.name having count(*)>=2; "; 
		mysql_query(connect, sql.c_str());
		res_set = mysql_store_result(connect);
		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "Couldn't find delivery with two editions of book" << endl;
			return;
		}

		cout << "Lists of deliveries wich contains two editons of book:\n" << endl;
		while (((row = mysql_fetch_row(res_set)) != NULL)) {
			cout <<" Delivery id: "<<row[0]<<"\n Purchase id: "<< row[1] << " \n Status:" << row[3] << "\n Delivery type " << row[4] << "\n Delivery date: " << row[6] <<"\n Book: "<<row[8]<<endl;
			cout << endl;
		}
	}

	//19
	/**void MySQL::noneRecentlyCustomer() : A query that retuns a list of customers who have not been active for the past two years.
	*/
	void MySQL::noneRecentlyCustomer() 
	{
		string twoYearsAgo = getDateXYearsAgo(2);
		string sql = "select c.first_name, c.last_name, c.mobile_phone, pc.purchase_date from purchase_customer pc, customer c where pc.customer_id = c.customer_id AND pc.purchase_date < '"+ twoYearsAgo +"' and c.customer_id NOT IN (select c.customer_id from purchase_customer pc, customer c where pc.customer_id = c.customer_id AND pc.purchase_date > '" + twoYearsAgo + "') group by c.customer_id";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);
		unsigned int numrows = mysql_num_rows(res_set);
		unsigned int numcols = mysql_num_fields(res_set);
		if (numrows == 0) {
			cout << "All customers have made at least one purchase during the last two years" << endl;
			return;
		}
		cout << "All customers who didn't buy for two years (customer name, mobile, last pruchase' date):" << endl;
		while (((row = mysql_fetch_row(res_set)) != NULL)) {
			for (int i = 0; i < numcols; i++) {
				if (row[i] == NULL) 
				{
					continue; 
				}
				cout << row[i] << " ";
			}
			cout << endl;
		}
	}

	//20
	/** void MySQL::orderedAndNotBought(): A query that returns the list of customers who have made a purchase during the last 14 days.
	*/
	void MySQL::orderedAndNotBought() {
		cout << "List of Customers who ordered a book, the store contact them at least 14 days ago and they didn't buy the books: \n\n";
		string sql = "select c.*,r.contact_customer from customer c, reservation r, reservation_book rb where r.customer_id = c.customer_id AND rb.reservation_id = r.reservation_id AND r.contact_customer IS NOT NULL and r.contact_customer <= curdate() - 14 AND NOT EXISTS( select * from purchase_customer pc, purchase_customer_book pcb where pc.purchase_id = pcb.purchase_id AND pc.customer_id = c.customer_id AND pcb.book_id = rb.book_id);";
		int i = 1;

		mysql_query(connect, sql.c_str());
		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		unsigned int numcols = mysql_num_fields(res_set);
		if (numrows == 0) {
			cout << "no data" << endl;
			return;
		}

		while (((row = mysql_fetch_row(res_set)) != NULL)) {
			cout <<i<<". Customer id: " << row[0] << "\n   Name: " << row[1] << " " << row[2] << "\n   Mobile: "<<row[3]<<"\n   Contact date: " << row[6] << endl;
			cout << endl;
			i++;
		}
	}

	//21
	/** void MySQL::booksInStorage(): Number of books in storage per month.
	*/
	void MySQL::booksInStorage() {
		string sql =  "select sum(i2.count) as AccumelatedNoOfBooks, month(i1.time_stamp), year(i1.time_stamp) from inventory i1 join inventory i2 on month(i2.time_stamp) <= month(i1.time_stamp) and year(i2.time_stamp) <= year(i1.time_stamp) and i2.location = i1.location where i1.location = 'storage' and i1.count > 0 and i2.location = 'storage' and i2.count > 0 and i2.time_stamp <= i1.time_stamp and month(i2.time_stamp) <= month(i1.time_stamp) and year(i2.time_stamp) <= year(i1.time_stamp) group by month(i1.time_stamp), year(i1.time_stamp) order by year(i1.time_stamp),month(i1.time_stamp);";

		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "couldn't find deliveries" << endl;
			return;
		}
		cout << "Number of books in storage (per month):" << endl;
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL) {
				cout << "number of books in storage in month: "<< row[1] << " of the year: " << row[2] <<"  is: "<< row[0] <<endl;
			}
		}
	}
	//22A
	/**The following func(query) checks purchases of books made between dates enetered by the user.
	It returns thier amount and the price paid for them by the store.
	*/
	void MySQL::purchase_store_books()
	{
		string date1;
		string date2;
		cout << "Enter wanted dates to check purchases between them (for example: 2020-01-27):\n";
		cin >> date1 >> date2;
		string sql = "	select count(*) as books_bought_by_store, sum(ps.count*ps.book_price) as books_payment from purchase_store ps  where ps.purchase_date between '" + date1 + "' and '" + date2 + "'";
		mysql_query(connect, sql.c_str());
		res_set = mysql_store_result(connect);
		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0) {
			cout << "There are no deliveries" << endl;
			return;
		}

		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			
			if (row[0] != NULL && row[1] != NULL) {
				cout << "Number of books purchased by store between the given dates is: " << row[0] << "\nTotal price: "<<row[1]<< endl;
			}
		}
	}
	//22B
	/**
	monthRevenue() checks the revenue in a month of a year entered by the user (the manager)
	*/
	void MySQL::monthRevenue()
	{
		int month;
		int year;
		int op;
		cout << "Enter wanted month and year to check the revenue at \n";
		cin >> month >> year;
		if (!(checkMonth(month)))
		{
			cout << "Not a valid month.\nPress 1 to try again or 0 to menu\n";
			cin >> op;
			if (op == 1)
			{
				monthRevenue();
			}
			return;
		}
		
		string strMonth = to_string(month);
		string strYear = to_string(year);
		string sql = "select (sum(pcb.price)-sum(ps.count*ps.book_price)) as revenue, month(pc.purchase_date) as month, year(pc.purchase_date) as year from purchase_customer pc, purchase_customer_book pcb, purchase_store ps where pcb.purchase_id = pc.purchase_id and month(pc.purchase_date) = '" + strMonth + "' AND year(pc.purchase_date) = '" + strYear + "'AND pcb.purchase_id = pc.purchase_id";
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 1) {
			while (((row = mysql_fetch_row(res_set)) != NULL))
			{
				if (row[0] != NULL) {
					cout << "revenue is: " << row[0] << endl;
					cout << "Please enter 1 to monthRevenue or 0 to menu" << endl;
					cin >> op;
					if (op == 1) {
						monthRevenue();
					}
					return;
				}
			}
			cout << "No sales or payments (purchase-store) were made in this month of the year" << endl;
			cout << "Please enter 1 to monthRevenue or 0 to menu" << endl;
			cin >> op;
			if (op == 1) {
				monthRevenue();
			}
			return;
		}


	}
	//23
	/**
	annualTransactionsAvg() runs a query in sql after connecting to the database 
	and shows the average of the annual transactions made
	*/
	void MySQL::annualTransactionsAvg()
	{
		string sql = "select avg(pcb.price), year(pc.purchase_date) from purchase_customer pc inner join purchase_customer_book pcb where pc.purchase_id=pcb.purchase_id group by year(pc.purchase_date) order by year(pc.purchase_date)";
		
		mysql_query(connect, sql.c_str());

		res_set = mysql_store_result(connect);

		unsigned int numrows = mysql_num_rows(res_set);
		if (numrows == 0){
			cout << "There is no data" << endl;
			return;
		}
		while (((row = mysql_fetch_row(res_set)) != NULL))
		{
			if (row[0] != NULL) {
				cout << "Average of transaction of the year: "<<row[1]<<" is: "<< row[0] << endl;
			}
		}
	}
	/*-----------------------------------------------*/
	//24
	/**
	employee_salary_per_month() lets the manager check 
	the salary of any employee by his/her id per month of year which he/she enters
	*/
	void MySQL::employee_salary_per_month()
	{
		int month;
		int year;
		int employee_id;
		int op;
		cout << "Enter wanted employee id you want to check his/her salary: ";
		cin >> employee_id;
		cout << "Enter wanted month and year to check the employee salary at: ";
		cin >> month >> year;
		if (!(checkMonth(month)))
		{
			cout << "Not a valid month.\nPress 1 to try again or 0 to menu\n";
			cin >> op;
			if (op == 1)
			{
				employee_salary_per_month();
			}
			return;
		}
			string sql = "select wmh.hour_payment*wmh.hours from working_month_hours wmh inner join employees e on e.employee_id = wmh.employee_id where e.employee_id='" + to_string(employee_id) + "' AND wmh.year = '" + to_string(year) + "' AND wmh.month = '" + to_string(month) + "'";
			mysql_query(connect, sql.c_str());

			res_set = mysql_store_result(connect);

			unsigned int numrows = mysql_num_rows(res_set);
			if (numrows == 0) {
				cout << "no data" << endl;
				return;
			}

			while (((row = mysql_fetch_row(res_set)) != NULL))
			{
				cout << "salary: ";
				if (row[0] != NULL) {
					cout << row[0] << endl;
				}
			}
		}

	//25
	/**
	employee_Of_The_Month() is a query that shows the manager the best employee of specific month he/she enters
	*/
	void MySQL::employee_Of_The_Month()
	{
		int month, year, op;
		cout << "Please enter month and year you want to see the best employee of it\n";
		cin >> month >> year;
		if (!(checkMonth(month)))
		{
			cout << "Not a valid month.\nPress 1 to try again or 0 to menu\n";
			cin >> op;
			if (op == 1)
			{
				employee_Of_The_Month();
			}
			return;
		}
			string sql = "select e.first_name, e.last_name from employees e inner join purchase_customer pc on e.employee_id = pc.employee_id where month(pc.purchase_date) = '" + to_string(month) + "'  AND year(pc.purchase_date) = '" + to_string(year) + "' group by e.employee_id order by count(*) desc limit 1";
			mysql_query(connect, sql.c_str());

			res_set = mysql_store_result(connect);

			unsigned int numrows = mysql_num_rows(res_set);
			while (((row = mysql_fetch_row(res_set)) != NULL))
			{
				cout << "\nEmployee Of The Month: ";
				if (row[0] != NULL && row[1] != NULL) {
					cout << row[0] << " " << row[1] << endl;
				}
				return;
			}			
			cout << "no data" << endl;
			cout << "Not a valid month.\nPress 1 to try again or 0 to menu\n";
			cin >> op;
			if (op == 1)
			{
				employee_Of_The_Month();
			}
			return;
	}

	/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: ~MySQL()
 * Description:  Destructor of MySQL class for closing mysql
 *               connection
 *--------------------------------------------------------------------
 */

MySQL :: ~MySQL()
{
    mysql_close (connect);
}
/*--------------------------------------------------------------------*/

