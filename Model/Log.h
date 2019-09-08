#ifndef log_h
#define log_h

#include <string>

using namespace std;

/*This class is used to bind the data of t he log when customer borrows or returns the book*/
class Log
{
  public:
    string getUsername() { return username; }
    void setUsername(string usrname) { username = usrname; }

    string getIsbn() { return isbn; }
    void setIsbn(string isb) { isbn = isb; }

    string getBookname() { return bookname; }
    void setBookname(string book) { bookname = book; }

    string getIssueDate() { return issuedate; }
    void setIssueDate(string issue) { issuedate = issue; }

    string getReturnDate() { return returndate; }
    void setReturnDate(string ret) { returndate = ret; }

    string getstatus() { return status; }
    void setstatus(string sts) { status = sts; }

  private:
    string username;
    string isbn;
    string bookname;
    string issuedate;
    string returndate;
    string status;
};
#endif
