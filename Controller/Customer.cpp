#include "Customer.h"
#include "../Model/DataAccess.h"
#include "Functions.h"
#include "../Model/Log.h"
#include "ExternalSystem.h"
#include "ExternalSystem.cpp"
#include <iomanip>
#include <iostream>

using namespace std;

extern string loggedinUser;

Functions functions;
DataAccess dataAccessC;

extern vector<Book> Bookvector;
extern vector<Log> IssuedBookvector;
extern string loggedinUser;
extern vector<User> Uservector;

// * This method is used to request a book loan when customer enters a isbn
// * It first checks
//      (1) if the book matching with 'isbn' number is available and
//      (2) customer has not alreay borrowed that book
//  It the above conditions are true then, the book is issued to the customer
int Customer::RequestBookLoan(std::string isbn)
{
    Log newlog;
    int bookloan = 0;
    bool isavailable = isAvailable(isbn);
    bool alreadyissued = isAlreadyissued(isbn);
    if (isavailable && !alreadyissued)
    {
        for (int i = 0; i < Bookvector.size(); i++)
        {
            // this code block updates the book log with the name of the customer,
            // book details, issue date and return date
            if (Bookvector[i].getIsbn() == isbn)
            {
                time_t rawtime;
                struct tm *timeinfo;
                char buffer[80];

                time(&rawtime);

                timeinfo = localtime(&rawtime);

                strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
                std::string idate(buffer);

                rawtime += 60 * 60 * 24 * 40;

                timeinfo = localtime(&rawtime);

                strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
                std::string rdate(buffer);

                newlog.setUsername(loggedinUser);
                newlog.setBookname(Bookvector[i].getName());
                newlog.setIsbn(isbn);
                newlog.setstatus("checked-out");
                newlog.setIssueDate(idate);
                newlog.setReturnDate(rdate);
                IssuedBookvector.push_back(newlog);

                dataAccessC.UpdateIssueBookData();

                // If the book is issued to the customer, then the count of that book is decreased by 1
                Bookvector[i].setCount(Bookvector[i].getCount() - 1);
                bookloan = 1;
                return bookloan;
            }
        }
    }

    // If the book is not available, (count = 0), then the system will call external interface
    else if (!isavailable)
    {

        //        Customer c;

        string library_name = "Hope International University";
        PollakLibrary p;
        string msg = p.ExternalBookRequest(loggedinUser,isbn,library_name);
        //ExternalBookRequest(loggedinUser,isbn, library_name);
        //cout << "\n\t\t" + msg;
        
        if (msg == "YES")
        {
            //string persist = dataAccessC.ExternalBookRequest(loggedinUser, isbn, library_name);
            cout << "\n\t\tRequested Book is Available at: " + library_name + ". We will inform you once available for loan at our Library....";
            bookloan = 2;
        }
        else{

            cout << "\n\t\t Requested Book is not Available at: " + library_name;
        }
    }

    return bookloan;
}

// * This method is used to show the details of the book borrowed by the customer.
void Customer::showdetails()
{
    int i;
    cout << "This is the details:" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|       ISBN       |             BookName            |      IssueDate      |        ReturnDate       |      Status        |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
    for (auto i : IssuedBookvector)
    {
        if (i.getUsername() == loggedinUser)
        {

            cout << "|" << setw(18) << i.getIsbn() << "|" << setw(33) << i.getBookname() << "|"
                 << setw(21) << i.getIssueDate() << "|" << setw(25) << i.getReturnDate() << "|" << setw(18) << i.getstatus() << "|" << endl;
        }
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------\n\n"
         << endl;

    cout << "1..Home Interface\t\t\t 2. Log out\t\t\t3. Close Application\n\n";
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
        customerInterface();
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
        showdetails();
        cout << "\n\t*****************************************************************************************\n";
    }
}

// * This method checks if the book matching the entered isbn is present in the Bookvector
bool Customer::isAvailable(std::string isbn)
{
    bool availability = false;

    for (auto i : Bookvector)
    {
        if (i.getIsbn() == isbn)
        {
            // if book is present, then it checks if the count is greater than 0.
            // If count is 0 then the book is not available
            if (i.getCount() > 0)
            {
                bool availability = true;
                return availability;
            }
        }
    }
    return availability;
}

// * This methods lists all the book (along with details) which is available in the dataabase
void Customer::listbooks()
{
    int i;
    cout << "This is the list of all the book:" << endl;
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

    cout << "1. Request Book Loan\t\t\t2.Home Interface\t\t\t 3. Log out\t\t\t4. Close Application\n\n";
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
        string isbn, username;
        cout << "\n Please Enter the ISBN number of the Book :";
        cin >> isbn;
        Customer c;
        int status = c.RequestBookLoan(isbn);

        if (status == 1)
        {
            cout << "\n\t*****************************************************************************************\n";
            cout << "\t\tBook is issued to you successfully...Happy Reading :)\n\n";
            cout << "\n\t*****************************************************************************************\n";
            dataAccessC.UpdateBookData();
            customerInterface();
        }
        else if(status == 2){

            cout << "\n\t\tAbove message is from External Interface, please get the Contact information from front desk. :)\n\n";
            listbooks();
        }
        else
        {
            cout << "\n\t*****************************************************************************************\n";
            cout << "\t\tThe book you are requesting is not available or already checked out to you: :(\n\n";
            cout << "\n\t*****************************************************************************************\n";
            listbooks();
        }
    }
    else if (i == 2)
    {
        customerInterface();
    }

    else if (i == 3)
    {
        Functions functions;
        functions.startup();
    }
    else if (i == 4)
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

// * This method check if the book with matching isbn is already issued to the customer.
bool Customer::isAlreadyissued(std::string isbn)
{
    bool issuestatus = false;

    for (auto i : IssuedBookvector)
    {
        //It checks if the isbn is matching with the userID and status is 'checked-out'.
        if (i.getIsbn() == isbn && i.getUsername() == loggedinUser && i.getstatus() == "checked-out")
        {
            bool issuestatus = true;
            return issuestatus;
        }
    }
    return issuestatus;
}

// * This method displayes the home interface for the customer
void CustomerUI::customerInterface()
{
    int i;
    cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM - Customer Interface ***********\n";
    cout << "\n\t\t Hello :" << loggedinUser << "\t Welocme to the System\n";
    cout << "\n\t\t>>Please Choose Any Option \n";
    cout << "\n\t\t1.List Books\n\n\t\t2.Show Details\n\n\t\t3.Log out\n\n\t\t4.Close Application\n";
    cout << "\n\t\tEnter your choice : ";
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
        Customer c;
        c.listbooks();
    }
    else if (i == 2)
    {
        Customer c;
        c.showdetails();
    }

    else if (i == 3)
    {
        Functions functions;
        functions.startup();
    }
    else if (i == 4)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t*****************************************************************************************\n";
        cout << "\n\t\tPlease enter correct option :(\n";
        cout << "\n\t*****************************************************************************************\n";
        customerInterface();
    }
}