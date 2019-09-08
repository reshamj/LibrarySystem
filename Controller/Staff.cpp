#include "Customer.h"
#include "../Model/DataAccess.h"
#include "Functions.h"
#include "../Model/Log.h"
#include "Staff.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

extern vector<Book> Bookvector;
extern vector<User> Uservector;
extern vector<Log> IssuedBookvector;
extern string loggedinUser;
DataAccess dataAccessS;

// * This method displays interface for the staff to return the borrowed book
void UILayer::returnBookInterface()
{
    string username, isbn;

    int i, retbook;
    cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM - Staff Interface ***********\n";
    cout << "\n\t\t>>Return Book Interface \n";
    cout << "\n\t\tEnter ISBN number of Book : ";
    cin >> isbn;
    cout << "\n\t\tEnter Username of Book Borrower : ";
    cin >> username;

    Staff st;
    retbook = st.returnIssuedBook(isbn, username);

    if (retbook == 1)
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\t\tBook Returned Successfully: :)\n\n";
        cout << "\n\t*****************************************************************************************\n";
        staffInterface();
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\t\tThe book you are trying to return is not found in log :(\n\n";
        cout << "\n\t*****************************************************************************************\n";
        returnBookInterface();
    }
}

// * This method checks if the book is issued to the customer.
// * If the isbn and username matches, then book with the given
//   isbn number is issued to the customer with given username
int Staff::returnIssuedBook(string isbn, string username)
{
    int ret = 0;

    for (int i = 0; i < IssuedBookvector.size(); i++)
    {
        //checks the IssuedBookvector to see if the the book with given isbn is issued to the customer with the given username
        if (IssuedBookvector[i].getIsbn() == isbn && IssuedBookvector[i].getUsername() == username && IssuedBookvector[i].getstatus() == "checked-out")
        {
            IssuedBookvector[i].setstatus("returned");
            dataAccessS.UpdateIssueBookData();
            ret = 1;

            //increases the count of the book from Bookvector after it is returned and update the database
            for (int j = 0; j < Bookvector.size(); j++)
            {
                if (Bookvector[j].getIsbn() == isbn)
                {

                    Bookvector[j].setCount(Bookvector[j].getCount() + 1);
                    dataAccessS.UpdateBookData();
                }
            }
            return ret;
        }
    }
    return ret;
}

// * This method duisplays the home interface for the staff user
void UILayer::staffInterface()
{
    int i;
    cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM - Staff Interface ***********\n";
    cout << "\n\t\t>>Please Choose Any Option \n";
    cout << "\n\t\t1.Books Availability\n\n\t\t2.Return Issued Book\n\n\t\t3.View Checkout Log\n\n\t\t4.Log out\n\n\t\t5.Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "................";
        cin >> i;
    }

    if (i == 1)
    {
        Staff s;
        s.listbooks();
    }
    else if (i == 2)
    {
        returnBookInterface();
    }
    else if (i == 3)
    {
        Staff s;
        s.showdetails();
    }
    else if (i == 4)
    {
        Functions functions;
        functions.startup();
    }
    else if (i == 5)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tPlease enter correct option :(\n";
        cout << "\n\t*****************************************************************************************\n";
        staffInterface();
    }
}

// * This method displayes the book to the staff
void Staff::listbooks()
{
    int i;
    cout << "Books Availability in the System:" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|       ISBN       |             Name            |      Author      |           Information           |   Availability    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    for (auto i : Bookvector)
    {

        cout << "|" << setw(18) << i.getIsbn() << "|" << setw(29) << i.getName() << "|"
             << setw(18) << i.getAuthor() << "|" << setw(33) << i.getInformation() << "|" << setw(19) << i.getCount() << "|" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------\n\n"
         << endl;

    cout << "1.Staff Home Interface\t\t\t 2. Log out\t\t\t3. Close Application\n\n";
    cout << "Choose the option: ";
    cin >> i;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << ".........";
        cin >> i;
    }

    if (i == 1)
    {
        staffInterface();
    }

    else if (i == 2)
    {
        Functions functions;
        functions.startup();
    }
    else if (i == 3)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tPlease enter correct option :(\n";
        cout << "\n\t*****************************************************************************************\n";
        showdetails();
    }
}

// * This method displays the details from the log file.
void Staff::showdetails()
{
    int i;
    cout << "This is the details:" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|     Username     |       ISBN       |             BookName            |      IssueDate      |        ReturnDate       |      Status      |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (auto i : IssuedBookvector)
    {

        cout << "|" << setw(18) << i.getUsername() << "|" << setw(18) << i.getIsbn() << "|" << setw(33) << i.getBookname() << "|"
             << setw(21) << i.getIssueDate() << "|" << setw(25) << i.getReturnDate() << "|" << setw(18) << i.getstatus() << "|" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------\n\n"
         << endl;

    cout << "1..Staff Interface\t\t\t 2. Log out\t\t\t3. Close Application\n\n";
    cout << "Choose the option: ";
    cin >> i;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << ".........";
        cin >> i;
    }
    if (i == 1)
    {
        staffInterface();
    }

    else if (i == 2)
    {
        Functions functions;
        functions.startup();
    }
    else if (i == 3)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tPlease enter correct option :(\n";
        cout << "\n\t*****************************************************************************************\n";
        listbooks();
    }
}