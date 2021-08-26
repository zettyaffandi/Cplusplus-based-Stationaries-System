// This is a program for our project which is the Stationaries System in order to provide solutions for M&M Company that needs a small inventory system
// to manage the flow of the stationeries that they can provide to their customers.

// Subject: TMF1434 - Data Structure and Algorithms
// Project - The Stationeries System
// Group Member: SITI AZIMAH BINTI MOHAMED(63791)
//             : MYRA ANNATASHA UMANG ANAK DINEAL GUMIS (63491)
//             : ZETTY ELICA BINTI AFFANDI (63879)
//             : NUR HUDA BINTI HAMKA (63611)
// Date of Submission: 20 May 2018

#include <iostream> // Contains standard input and output functions
#include <string> // Contains string processing functions
#include <stdlib.h> // Contains conversion function from number to text and text to number, random number function, memory allocation function and other utility functions
#include <iomanip> // Contains functions to manipulate the output of cout statements
#include <conio.h> // Contains functions for console input/output.


using namespace std; // To use std (standard) namespace functions

					 // Declare strcut node
struct node {
	int itemCode;
	string itemType;
	string itemBrand;
	string itemColour1;
	string itemColour2;
	string itemColour3;
	string itemSize;
	double itemCost;
	node *next;

	node(int data, string type, string brand, string colourA, string colourB, string colourC, string size, double cost)
	{
		itemCode = data;
		itemType = type;
		itemBrand = brand;
		itemColour1 = colourA;
		itemColour2 = colourB;
		itemColour3 = colourC;
		itemSize = size;
		itemCost = cost;
		next = NULL;
	}
};

// Declare struct Order
struct Order {
	string customerName;
	string OrderName;
	string OrderColour;
	string OrderBrand;
	int quantity;
	int receiptID;
	double OrderPrice;
	double totalPrice;
}Order[4];

// Declare struct Receipt
struct Receipt
{
	int receiptNo, amount, day, month, year;
	string Name, item, colour, brandx;
	double totalCost, itemCost;
	Receipt *next;

};


// Class declaration
class Stationaries {
	node *head, *last; // Declare pointer of class node
	Receipt *top; // Declare pointer of class node

public: // Declaring public class members
	int receiptID = 1;
	Stationaries();// Default constructor
	~Stationaries()//Destructor
	{

	}
	// Functions regarding list of stationaries
	void setPresetData(int z, string a, string b, string c, string d, string e, string f, double g);// Set pre-set data
	void addStationaries(int, string, string, string, string, string, string, double); // Add stationaries to  list
	void deleteStationaries(int); // Delete stationaries from list
	void viewAllStationaries(); // Display list of all stationaries

								// Functions regarding Order
	void placeorder(); // Add order
	void deleteorder(); // Delete latest order
	int empty(); // To check if stack is empty
	void editOrder(); // Edit an order
	void sortSummaryAscendingly(); // Sort stationaries name ascendingly
	void sortSummaryDescendingly(); // Sort stationaries name descendingly
	void customerReceipt(); // Search and display receipt
	void summary(); // Display overall summary
	void weeklySummary(); //Display weekly summary

						  // Functions regarding menu
	void adminmenu(); // Display admin menu
	void customermenu(); // Display customer menu
						 /*int empty();*/
	void menu(); // Declaring a function named menu which returns nothing
};


Stationaries::Stationaries() // Default constructor
{
	last = NULL;
	head = NULL;
	top = NULL;
}

// Set pre-set data
void Stationaries::setPresetData(int z, string a, string b, string c, string d, string e, string f, double g)
{
	node *p = new node(z, a, b, c, d, e, f, g);
	if (head == NULL)
	{
		head = p;
		last = p;
	}
	else
	{
		last->next = p;
		last = p;
	}

}

// Add stationary to list
void Stationaries::addStationaries(int Pos, string Type, string Brand, string Colour1, string Colour2, string Colour3, string Size, double Cost)
{
	node *p = new node(Pos, Type, Brand, Colour1, Colour2, Colour3, Size, Cost);
	last->next = p;
	last = p;
}

// Delete stationary from list
void Stationaries::deleteStationaries(int del)
{
	node *current; //pointer to traverse the list
	node *trailCurrent; //pointer just before current
	bool found;
	if (head == NULL)
	{
		cout << "Cannot delete from an empty list." << endl;
	} // End if
	else
	{
		current = head;
		found = false;
		while (current != NULL && !found) //search the list
		{
			if (current->itemCode >= del) {
				found = true;
			}
			else
			{
				trailCurrent = current;
				current = current->next;
			}
		}
		if (current == NULL) {//Case 4
			cout << "The item to be deleted is not in the list."
				<< endl;
		}
		else if (current->itemCode == del) //the item to be
										   //deleted is in the list
		{
			if (head == current)
			{
				head = head->next;
				if (head == NULL)
					last = NULL;
				delete current;
			}
			else
			{
				current = current->next;
				trailCurrent = current;
				trailCurrent = trailCurrent->next;
				if (current == last)
					last = trailCurrent;
				delete current;
			}

		}
		else
		{
			cout << "The item to be deleted is not in the "
				<< "list." << endl;
		}



	} // End else
}

// Display list of stationaries details
void Stationaries::viewAllStationaries() {
	node *p = head;
	cout << "_______________________________________________________________________________________________________________________________" << endl;
	cout << left << setw(10) << "Code" <<
		left << setw(20) << "Stationaries" <<
		left << setw(40) << "Brand" <<
		left << setw(30) << "Colours" <<
		left << setw(10) << "Size" <<
		left << setw(10) << "Price(RM)" << endl;
	cout << "________________________________________________________________________________________________________________________________" << endl;
	while (p != NULL) {
		cout << left << setw(10) << p->itemCode <<
			left << setw(20) << p->itemType <<
			left << setw(30) << p->itemBrand <<
			left << setw(10) << p->itemColour1 <<
			left << setw(10) << p->itemColour2 <<
			left << setw(15) << p->itemColour3 <<
			left << setw(20) << p->itemSize <<
			left << setw(10) << p->itemCost << endl;
		p = p->next;
	}
}



// Add order
void Stationaries::placeorder() {

	int id, amount, choice1, day, month, year, confirm;
	double subtotal = 0.00, totalPurchase, tax = 0.06;
	string name;
	string design;
	string customer;
	string brandName;
	unsigned int counter = 0, loop;

	cout << endl << "Enter 0 to return to main menu.\n\n Place your order.\n";
	cout << "How many types of stationaries do you want to order? ";
	while (!(cin >> loop))
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid input. Please try again\n";
		cout << ":-";
	}
	if (loop == 0)
	{
		system("cls");
	}
	else
	{
		while (counter < loop)
		{

		Code:
			node * p;
			p = head;
			viewAllStationaries();

			cout << endl << "Enter item code : "; // Prompt user to enter the type of item
			while (!(cin >> id))
			{

				cin.clear();
				cin.ignore();
				cout << "Invalid input. Please try again\n";
				cout << ":-";
			}
			while (id != p->itemCode) {

				p = p->next;

				if (p == NULL) {

					cout << "Item code entered is not in the list.\nPlease enter the correct item code.\n ";
					system("pause");
					goto Code;

				}


			}

			if (id == p->itemCode) {

			Colour:
				cout << endl << "Select the colour of the item (without space) : "; // Prompt user to enter the colour of item
				cout << endl << "1." << p->itemColour1 << endl << "2." << p->itemColour2 << endl << "3." << p->itemColour3;
				cout << endl;
				cin >> choice1;

				if (choice1 == 1)
				{
					Order[counter].OrderColour = p->itemColour1;
				}
				else if (choice1 == 2)
				{
					Order[counter].OrderColour = p->itemColour2;
				}
				else if (choice1 == 3)
				{
					Order[counter].OrderColour = p->itemColour3;
				}
				else
				{
					cout << "Invalid input. Please try again";
					goto Colour;
				}

			Quantity:
				cout << endl << "Enter quantity :  "; // Prompt user to enter quantity of item
				while (!(cin >> amount))
				{
					cin.clear();
					cin.ignore();
					cout << "Invalid input. Please try again\n";
					cout << "Enter quantity :  ";
				}

				if (amount == 0) {

					cout << "Quantity Can not be Zero. Try again.\n ";

					system("pause");
					system("cls");
					goto Quantity;

				}
				Order[counter].quantity = amount;
				Order[counter].OrderName = p->itemType;
				Order[counter].OrderBrand = p->itemBrand;
				Order[counter].OrderPrice = p->itemCost;
				Order[counter].totalPrice = p->itemCost*amount;

			}
			counter++;

		}
		cout << endl << "Enter your name : "; // Prompt user to enter their name
		cin.ignore();
		getline(cin, customer);

		cout << endl << "Enter today's date."; // Prompt user to enter the date
		cout << endl << "Year (yy) :";
		while (!(cin >> year))
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input. Please try again\n";
			cout << ":-";
		}
		if (year > 0)
		{
		Month:
			cout << endl << "Month (mm) : ";
			while (!(cin >> month))
			{
				cin.clear();
				cin.ignore();
				cout << "Invalid input. Please try again\n";
				cout << ":-";
			}
			if (month < 1 || month > 12)
			{
				cout << "Invalid month";
				goto Month;

			}

		Day:
			cout << endl << "Day (dd) : ";
			while (!(cin >> day))
			{
				cin.clear();
				cin.ignore();
				cout << "Invalid input. Please try again\n";
				cout << ":-";
			}
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				if (day <= 0 || day > 31)
				{
					cout << "Invalid input. Please try again\n";
					goto Day;
				}

			}
			else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day <= 0 && day>30)
				{
					cout << "Invalid input. Please try again\n";
					goto Day;
				}

			}
			else if (month == 2)
			{
				if (year % 4 == 0)
				{
					if (day <= 0 && day>29)
					{
						cout << "Invalid input. Please try again\n";
						goto Day;
					}

				}
				else if (year % 4 != 0)
				{
					if (day <= 0 && day>28)
					{
						cout << "Invalid input. Please try again\n";
						goto Day;
					}

				}
				else
				{
					cout << "Invalid date\n";
					goto Day;
				}
			}
		}



		for (unsigned int i = 0; i < loop; i++)
		{
			subtotal = subtotal + Order[i].totalPrice;
		}

		totalPurchase = subtotal + subtotal * tax;
		for (unsigned int i = 0; i< loop; i++)
		{
			cout << endl << " Item " << i+1;
			cout << endl << "Stationeries : " << Order[i].OrderName;
			cout << endl << "Brand : " << Order[i].OrderBrand;
			cout << endl << "Colour : " << Order[i].OrderColour;
			cout << endl << "Price(RM) : " << Order[i].OrderPrice;
			cout << endl << "Quantity : " << Order[i].quantity;
			cout << endl << "Total (RM) : " << Order[i].totalPrice << endl;
		}

		cout << "Subtotal: RM " << subtotal << endl;
		cout << "Tax (6%):" << subtotal * tax << endl;
		cout << "Total: RM " << totalPurchase << endl;

	confirmation:
		cout << endl << " 1. Confirm order || 2. Cancel order" << endl; // Ask user for confirmation
		cout << ": ";
		while (!(cin >> confirm))
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input. Please try again\n";
			cout << ":-";
		}
		if (confirm == 1)
		{
			for (counter = 0; counter < loop; counter++)
			{
				Receipt *z = new Receipt;
				z->receiptNo = receiptID;
				z->Name = customer;
				z->day = day;
				z->month = month;
				z->year = year;
				z->item = Order[counter].OrderName;
				z->brandx = Order[counter].OrderBrand;
				z->colour = Order[counter].OrderColour;
				z->totalCost = Order[counter].totalPrice;
				z->amount = Order[counter].quantity;
				z->itemCost = Order[counter].OrderPrice;
				z->next = top;
				top = z;
			}

			receiptID++;
		}
		else if (confirm == 2)
		{
			cout << "The order was cancelled...\n" << endl;
		}

		else
		{
			cout << "Invalid input. Please try again\n";
			goto confirmation;
		}


	}

}

// Delete latest order
void Stationaries::deleteorder()
{
	if (empty() == 1) {
		cout << "\nNo order has been made.\n";
	}
	else
	{
		Receipt *z = top;
		top = top->next;
		delete z;
		cout << " Latest order has been deleted\n";
	}


}

// Check if stack is empty
int Stationaries::empty() {
	if (top == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

// Edit an order
void Stationaries::editOrder() {

	bool found = false;
	int searchReceipt, select;
	int id, amount, choice1, day, month, year;
	double subtotal = 0.00, totalPurchase, tax = 0.06;
	string name;
	Receipt *z;
	z = top;

	cout << endl << "Enter 0 to return to main menu.\n\n ";
	cout << "Enter receipt id to edit the order : "; // Prompt user to end receipt id
	while (!(cin >> searchReceipt))
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid input. Please try again\n";
		cout << ":-";
	}
	if (searchReceipt == 0)
	{
		system("cls");
	}
	else
	{
		found = false;

		while (z != NULL)
		{
			if (z->receiptNo == searchReceipt)
			{
				cout << " Edit\n" << "1. Name || 2. Date || 3. Purchase details\n" << " Enter your choice : ";
				while (!(cin >> select))
				{

					cin.clear();
					cin.ignore();
					cout << "Invalid input. Please try again\n";
					cout << ":-";
				}
				if (select == 1)
				{

					cout << endl << "Enter name : "; // Prompt user to enter new name
					cin.ignore();
					getline(cin, name);
					z->Name = name;
					found = true;
					break;

				}
				else if (select == 2)
				{

					cout << endl << "Enter today's date."; // Prompt user to enter new date
					cout << endl << "Year (yy) :";
					while (!(cin >> year))
					{
						cin.clear();
						cin.ignore();
						cout << "Invalid input. Please try again\n";
						cout << ":-";
					}
					if (year > 0)
					{
					Month:
						cout << endl << "Month (mm) : ";
						while (!(cin >> month))
						{
							cin.clear();
							cin.ignore();
							cout << "Invalid input. Please try again\n";
							cout << ":-";
						}
						if (month < 1 || month > 12)
						{
							cout << "Invalid month";
							goto Month;

						}

					Day:
						cout << endl << "Day (dd) : ";
						while (!(cin >> day))
						{
							cin.clear();
							cin.ignore();
							cout << "Invalid input. Please try again\n";
							cout << ":-";
						}
						if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
						{
							if (day <= 0 || day > 31)
							{
								cout << "Invalid input. Please try again\n";
								goto Day;
							}

						}
						else if (month == 4 || month == 6 || month == 9 || month == 11)
						{
							if (day <= 0 && day>30)
							{
								cout << "Invalid input. Please try again\n";
								goto Day;
							}

						}
						else if (month == 2)
						{
							if (year % 4 == 0)
							{
								if (day <= 0 && day>29)
								{
									cout << "Invalid input. Please try again\n";
									goto Day;
								}

							}
							else if (year % 4 != 0)
							{
								if (day <= 0 && day>28)
								{
									cout << "Invalid input. Please try again\n";
									goto Day;
								}

							}
							else
							{
								cout << "Invalid date\n";
								goto Day;
							}
						}
					}

					z->day = day;
					z->month = month;
					z->year = year;
					found = true;
					break;
				}

				else if (select == 3)
				{

				Code:
					node * p;
					p = head;
					viewAllStationaries();

					cout << endl << "Enter item code : "; // Prompt user to enter item code
					while (!(cin >> id))
					{

						cin.clear();
						cin.ignore();
						cout << "Invalid input. Please try again\n";
						cout << ":-";
					}
					while (id != p->itemCode) {

						p = p->next;

						if (p == NULL) {

							cout << "Item code entered is not in the list.\nPlease enter the correct item code.\n ";
							system("pause");
							goto Code;

						}


					}

					if (id == p->itemCode) {

					Colour:
						cout << endl << "Select the colour of the item (without space) : "; // Prompt user to enter the colour of item
						cout << endl << "1." << p->itemColour1 << endl << "2." << p->itemColour2 << endl << "3." << p->itemColour3;
						cout << endl;
						cin >> choice1;

						if (choice1 == 1)
						{
							z->colour = p->itemColour1;
						}
						else if (choice1 == 2)
						{
							z->colour = p->itemColour2;
						}
						else if (choice1 == 3)
						{
							z->colour = p->itemColour3;
						}
						else
						{
							cout << "Invalid input. Please try again";
							goto Colour;
						}

					Quantity:
						cout << endl << "Enter quantity :  "; // Prompt user to enter quantity of item
						while (!(cin >> amount))
						{
							cin.clear();
							cin.ignore();
							cout << "Invalid input. Please try again\n";
							cout << "Enter quantity :  ";
						}

						if (amount == 0) {

							cout << "Quantity Can not be Zero. Try again.\n ";

							system("pause");
							system("cls");
							goto Quantity;

						}

						z->amount = amount;
						z->item = p->itemType;
						z->brandx = p->itemBrand;
						z->itemCost = p->itemCost;
						z->totalCost = p->itemCost*amount;
						subtotal = subtotal + z->totalCost;

						found = true;
					}

					tax = subtotal * 0.06;
					totalPurchase = subtotal + tax;

					cout << endl << "Subtotal: RM " << subtotal << endl;
					cout << "Tax (6%):" << subtotal * tax << endl;
					cout << "Total: RM " << totalPurchase << endl;
				}


			}
			z = z->next;
		}

		if (found == false)
		{
			system("cls");
			cout << "Receipt not found" << endl;
		}


	}

}

// Search & display receipt
void Stationaries::customerReceipt()
{

	bool found = false;
	int searchreceipt;
	double tax, subtotal = 0.0, totalPurchase;

	Receipt *z;
	z = top;

	cout << "Enter receipt id you want view (Enter 0 to return to admin menu) : " << endl; // Prompt user to enter receipt id

	while (!(cin >> searchreceipt))
	{

		cin.clear();
		cin.ignore();
		cout << "Invalid input. Please try again\n";
		cout << ":-";
	}

	system("cls");
	if (searchreceipt == 0)
	{
		cout << endl;
	}

	else
	{
		found = false;

		cout << endl;
		cout << "                             The M&M Stationeries Company                            " << endl;
		cout << "                                   Customer's Receipt                                " << endl;
		cout << endl << "Receipt No :" << searchreceipt << endl << endl;
		while (z != NULL)
		{
			if (z->receiptNo == searchreceipt)
			{
				cout << "Customer Name : " << z->Name << endl;
				cout << "Date : " << z->day << "/" << z->month << "/" << z->year << endl;
				break;

			}
			z = z->next;
		}

		cout << "___________________________________________________________________________________________" << endl;
		cout << left << setw(30) << "Stationeries" <<
			left << setw(10) << "Brand" <<
			left << setw(10) << "Colour" <<
			left << setw(10) << "Price(RM)" <<
			left << setw(10) << "Quantity" <<
			left << setw(10) << "Total (RM)" << endl;
		cout << "___________________________________________________________________________________________" << endl;

		while (z != NULL)
		{

			if (z->receiptNo == searchreceipt)
			{

				cout << left << setw(30) << z->item <<
					left << setw(10) << z->brandx <<
					left << setw(10) << z->colour <<
					left << setw(10) << z->itemCost <<
					left << setw(10) << z->amount <<
					left << setw(10) << z->totalCost << endl;
				subtotal = subtotal + z->totalCost;
				tax = subtotal * 0.06;
				totalPurchase = subtotal + tax;

				found = true;

			}

			z = z->next;


		}
		if (z == NULL)
		{
			cout << endl;
		}
		else
		{
			cout << "\n_________________________________________________________________________________________" << endl;
			cout << "Subtotal: RM " << subtotal << endl;
			cout << "Tax (6%):" << tax << endl;
			cout << "Total: RM " << totalPurchase << endl;
		}




		if (found == false)
		{
			system("cls");
			cout << "Receipt not found" << endl;
		}

	}


	system("pause");
	system("cls");
}

// Sort stationaries name ascendingly
void Stationaries::sortSummaryAscendingly()
{
	node * temphead = head;
	string tempname;
	int counter = 0;
	while (temphead)
	{
		temphead = temphead->next;
		counter++;
	}
	temphead = head;

	for (int j = 0; j<counter; j++)
	{
		while (temphead->next)
		{
			if (temphead->itemType > temphead->next->itemType)
			{
				tempname = temphead->itemType;
				temphead->itemType = temphead->next->itemType;
				temphead->next->itemType = tempname;
			}
			temphead = temphead->next;
		}
		temphead = head;
	}

}

// Sort stationaries name descendingly
void Stationaries::sortSummaryDescendingly()
{
	node * temphead = head;
	string tempname;
	int counter = 0;
	while (temphead)
	{
		temphead = temphead->next;
		counter++;
	}
	temphead = head;

	for (int j = 0; j<counter; j++)
	{
		while (temphead->next)
		{
			if (temphead->itemType < temphead->next->itemType)
			{
				tempname = temphead->itemType;
				temphead->itemType = temphead->next->itemType;
				temphead->next->itemType = tempname;
			}
			temphead = temphead->next;
		}
		temphead = head;
	}
}

// Display weekly summary of transactions
void Stationaries::weeklySummary() {

	node *p;
	p = head;
	int day, month, year;
	int sort;

	cout << "Enter starting date. "; // Prompt user to enter starting date
	cout << endl << "Year (yy) :";
	while (!(cin >> year))
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid input. Please try again\n";
		cout << ":-";
	}
	if (year > 0)
	{
	Month:
		cout << endl << "Month (mm) : ";
		while (!(cin >> month))
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input. Please try again\n";
			cout << ":-";
		}
		if (month < 1 || month > 12)
		{
			cout << "Invalid month";
			goto Month;

		}

	Day:
		cout << endl << "Day (dd) : ";
		while (!(cin >> day))
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input. Please try again\n";
			cout << ":-";
		}
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day <= 0 || day > 31)
			{
				cout << "Invalid input. Please try again\n";
				goto Day;
			}

		}
		else if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day <= 0 && day>30)
			{
				cout << "Invalid input. Please try again\n";
				goto Day;
			}

		}
		else if (month == 2)
		{
			if (year % 4 == 0)
			{
				if (day <= 0 && day>29)
				{
					cout << "Invalid input. Please try again\n";
					goto Day;
				}

			}
			else if (year % 4 != 0)
			{
				if (day <= 0 && day>28)
				{
					cout << "Invalid input. Please try again\n";
					goto Day;
				}

			}
			else
			{
				cout << "Invalid date\n";
				goto Day;
			}
		}
	}

Sort:
	cout << "1. Sort stationaries name ascendingly" << endl;
	cout << "2. Sort stationaries name descending" << endl;

	while (!(cin >> sort))
	{
		cin.clear();
		cin.ignore();
	}
	if (sort == 1)
	{
		sortSummaryAscendingly();
	}
	else if (sort == 2)
	{
		sortSummaryDescendingly();
	}
	else
	{
		cout << "Invalid input. Please try again\n";
		goto Sort;
	}

	if (p == NULL)
		cout << "Empty. Please create a receipt.\n";
	else
	{
		cout << day << "/" << month << "/" << year << '-' << day + 6 << "/" << month << "/" << year << endl;
		cout << "_____________________________________________________________________________________" << endl <<
			left << setw(30) << "Stationaries" <<
			left << setw(10) << "Quantity" <<
			left << setw(10) << "Total (RM)" <<
			left << setw(10) << "Date" << endl;

		cout << "-------------------------------------------------------------------------------------";

		while (p != NULL)
		{
			Receipt *z;
			z = top;
			int quantityX = 0;
			double totalX = 0.0;
			cout << endl << left << setw(30) << p->itemType;
			while (z != NULL)
			{
				if (z->day == day || z->day <= day + 6 && z->month == month && z->year == year)
				{
					if (z->item == p->itemType)
					{
						quantityX = quantityX + z->amount;
						totalX = totalX + z->totalCost;
					}
					else
					{
						quantityX = quantityX + 0;
						totalX = totalX + 0;
					}
				}

				z = z->next;
			}

			cout << left << setw(10) << quantityX <<
				left << setw(10) << totalX;

			p = p->next;

		}


	}


}

// Display overall summary of transactions
void Stationaries::summary() {

	int sort;
	node *p;
	p = head;

Sort:
	cout << "1. Sort stationaries name ascendingly" << endl;
	cout << "2. Sort stationaries name descending" << endl;	
	while (!(cin >> sort))
	{
		cin.clear();
		cin.ignore();
	}
	if (sort == 1)
	{
		sortSummaryAscendingly();
	}
	else if (sort == 2)
	{
		sortSummaryDescendingly();
	}
	else if (sort == 3)
	{
		cout << endl;
	}
	else
	{
		cout << "Invalid input. Please try again\n";
		goto Sort;
	}



	if (p == NULL)
		cout << "Empty. Please create a receipt.\n";
	else
	{

		cout << "_____________________________________________________________________________________" << endl <<
			left << setw(30) << "Stationaries" <<
			left << setw(10) << "Quantity" <<
			left << setw(10) << "Total (RM)" << endl;
		cout << "-------------------------------------------------------------------------------------";

		while (p != NULL)
		{
			Receipt *z;
			z = top;
			int quantityX = 0;
			double totalX = 0.0;
			cout << endl << left << setw(30) << p->itemType;
			while (z != NULL)
			{
				if (z->item == p->itemType)
				{
					quantityX = quantityX + z->amount;
					totalX = totalX + z->totalCost;
				}
				else
				{
					quantityX = quantityX + 0;
					totalX = totalX + 0;
					//cout << left << setw(10) << "-" <<
					//left << setw(10) << "-" << endl;
				}

				z = z->next;

			}

			cout << left << setw(10) << quantityX <<
				left << setw(10) << totalX << endl;

			p = p->next;

		}


	}


}

// Display admin menu
void Stationaries::adminmenu()
{
	int password, choice;
	string Type;
	string Brand;
	string Colour1;
	string Colour2;
	string Colour3;
	string Size;
	double Cost;
	int Pos = 6;
	int del;

Password:
	cout << "Enter Password (Enter 0 to return to main menu) : ";// Admin menu is protected. Password is 1234
	while (!(cin >> password))
	{

		cin.clear();
		cin.ignore();
		cout << "Incorrect Password. Please try again.\n";
		cout << ":-";
	}
	if (password == 0)
	{
		cout << endl;
	}
	else if (password == 1234)
	{

		do
		{
			system("cls");
			cout << endl << endl << endl << "\t\tM & M   S T A T I O N A R Y   S T O R E";
			cout << endl << endl << "\t\t\t\tAdmin Menu    " << endl;
			cout << "\t\t\t************************" << endl;
			cout << "\t\t\t 1. View overall summary" << endl;
			cout << "\t\t\t 2. View weekly summary" << endl;
			cout << "\t\t\t 3. Delete latest order" << endl;
			cout << "\t\t\t 4. Add stationaries" << endl;
			cout << "\t\t\t 5. Delete stationaries" << endl;
			cout << "\t\t\t 6. Search receipt" << endl;
			cout << "\t\t\t 7. Return to main menu" << endl;
			cout << "\t\t\t************************" << endl;
			cout << endl << endl << "\t\t\t Choose your option: ";// Prompt user to enter the option they want
			while (!(cin >> choice))
			{
				cin.clear();
				cin.ignore();
				break;
			}

			switch (choice)
			{
			case 1:

				system("cls");
				summary();
				system("pause");
				break;

			case 2:

				system("cls");
				weeklySummary();
				system("pause");
				break;

			case 3:

				deleteorder();
				system("pause");
				break;


			case 4:

				cout << endl << "Enter item details.\n";
				cout << endl << "Enter item type (Enter 0 to return to admin menu) : "; // Prompt user to enter the type of item
				cin.ignore();
				getline(cin, Type);
				if (Type == "0")
				{
					system("pause");
					system("cls");
				}
				else
				{
					cout << endl << "Enter the brand of the item (without space) : "; // Prompt user to enter the brand of item
					cin >> Brand;
					cout << endl << "Enter the colour of the item (without space) : "; // Prompt user to enter the colour of item
					cout << endl << "Colour 1: ";
					cin >> Colour1;
					cout << endl << "Colour 2: ";
					cin >> Colour2;
					cout << endl << "Colour 3: ";
					cin >> Colour3;
					cout << endl << "Enter the size of the item (without space) : "; // Prompt user to enter the size of item
					cin >> Size;
					cout << endl << "Enter Cost : RM "; // Prompt user to enter cost of item
					cin >> Cost;
					cout << endl << "Item has been added successfully" << endl; // Notify user that item has been added in the list of items
					Pos++;
					addStationaries(Pos, Type, Brand, Colour1, Colour2, Colour3, Size, Cost); // Calls the function addData() to add data
				}

				break;

			case 5:

				system("cls");
				viewAllStationaries();
				cout << "Item code to be deleted :\n";
				cin >> del;
				deleteStationaries(del);
				cout << " Item has been deleted\n";
				system("pause");
				break;

			case 6:

				system("cls");
				customerReceipt();
				system("pause");
				break;

			case 7:

				system("cls");
				cout << endl << "You are returning to main menu" << endl;
				cout << endl;
				break;

			default:
				cout << endl << "\t\t\tInavlid input. Please try again.\n";
				break;

			}
		} while (choice != 7);

	}
	else
	{

		cout << endl << "Incorrect Password. Please try again.\n";
		goto Password;
	}
}

// Display customer menu
void Stationaries::customermenu()
{
	int option;
	do {
		system("cls");
		cout << endl << endl << endl << "\t\tM & M   S T A T I O N A R Y   S T O R E";
		cout << endl << endl << "\t\t\t\tCustomer Menu    " << endl;
		cout << "\t\t\t************************" << endl;
		cout << "\t\t\t 1. View Stationaries" << endl;
		cout << "\t\t\t 2. Place order" << endl;
		cout << "\t\t\t 3. View receipt" << endl;
		cout << "\t\t\t 4. Exit to main menu" << endl;
		cout << "\t\t\t************************" << endl;
		cout << endl << endl << "\t\t\t Choose your option: ";
		while (!(cin >> option))
		{
			cin.clear();
			cin.ignore();
			break;
		}

		switch (option)
		{
		case 1:
			system("cls");
			viewAllStationaries();
			system("pause");
			break;

		case 2:
			system("cls");
			placeorder();
			system("pause");
			break;

		case 3:
			system("cls");
			customerReceipt();
			system("pause");
			break;

		case 4:
			system("cls");
			break;

		default:
			cout << endl << "\t\t\tInavlid input. Please try again.\n";
			system("pause");
			system("cls");
			break;
		} // End switch
	} while (option != 4);

}

// Function to display main menu for this program
void Stationaries::menu()
{

	int  menuOpt; // Declaring an integer named menuOpt

	setPresetData(1, "A4 Paper", "Paperone", "White", "Yellow", "Blue", "100 sheets", 15.00); // Set pre-set data 1 with all item details
	setPresetData(2, "Marker Pen", "Stabilo", "Blue", "Black", "Red", "15cm", 3.50); // Set pre-set data 2 with all item details
	setPresetData(3, "Pen", "Pilot", "Black", "Blue", "Red", "0.7mm", 2.00); // Set pre-set data 3 with all item details
	setPresetData(4, "Pencil", "Faber-Castell", "Black", "Purple", "Green", "0.5mm", 1.50); // Set pre-set data 4 with all item details
	setPresetData(5, "Highlighter", "Pro", "Green", "Yellow", "Orange", "Small", 4.00); // Set pre-set data 5 with all item details
	setPresetData(6, "Glue", "Stadler", "Purple", "Blue", "Yellow", "Small", 5.00);// Set pre-set data 6 with all item details
	do {
		system("cls");
		// Display the main menu & options provided by this program
		cout << endl << endl << "\t\t\t\t Main Menu:    " << endl;
		cout << "\t\t\t************************" << endl;
		cout << "\t\t\t 1. Customer menu" << endl;
		cout << "\t\t\t 2. Admin menu" << endl;
		cout << "\t\t\t 3. Exit Program" << endl;
		cout << "\t\t\t************************" << endl;
		cout << endl << endl << "\t\t\t Choose your option: ";// Prompt user to enter the option they want
		while (!(cin >> menuOpt))
		{

			cin.clear();
			cin.ignore();
			break;
		}


		switch (menuOpt)
		{
		case 1:
			system("cls");
			customermenu();
			system("pause");
			break;

		case 2:
			system("cls");
			adminmenu();
			system("pause");
			break;

		case 3:
			system("cls");
			int confirm; // Declare an integer named confirm
			cout << "If you wish to continue to exit please enter 1..." << endl
				<< "otherwise, please enter any number other than 1 to go back to main menu." << endl;
			cout << "Enter your choice : ";
			// Prompt user to enter 1 if they want to exit or enter any number other than 1 if they want to go back to the main menu
			cin >> confirm;
			if (confirm != 1)
			{
				menu(); // Calls the function main to go back to the main menu if user entered any number other than 1
			} // End if

			else
			{
				cout << endl << "\t\t\tYou are exiting this program...." << endl;
				cout << "\t\t-----------------------------------------------" << endl;
				cout << "\t\t\tThank You For Using This Program" << endl;
				cout << "\t\t-----------------------------------------------" << endl;
				// Notify user that they are exiting this program
				system("pause");
			} // End else
			  // Exit the program
			break; // Skip the remainder of switch statement

		default:
			cout << endl << "\t\t\tInavlid input. Please try again.\n";
			system("pause");
			system("cls");


		} // End switch
	} while (menuOpt != 3); // End do...while

}

int main()
{
	Stationaries program; // Declares record to be an object of class Stationaries
	cout << "\t\t________________________________________________________________________________" << endl << endl;
	cout << "						WELCOME TO THE M&M STATIONERIES                         " << endl << endl;
	cout << "\t\t________________________________________________________________________________" << endl << endl;
	cout << "Press any key..." << endl;
	_getch();
	system("cls");
	program.menu(); // Acessing the class member function named menu

}
