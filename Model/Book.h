#ifndef book_h
#define book_h

#include <string>

using namespace std;

// * It is a model class which is used to set and get all the details about each Book
class Book
{
  public:
    string getName() { return name; }
    string getIsbn() { return isbn; }
    string getAuthor() { return author; }
    string getInformation() { return information; }
    int getCount() { return count; }

    void setName(string new_name) { name = new_name; }
    void setIsbn(string new_isbn) { isbn = new_isbn; }
    void setAuthor(string new_author) { author = new_author; }
    void setInformation(string new_imfor) { information = new_imfor; }
    void setCount(int c) { count = c; }

  private:
    string name;
    string isbn;
    string author;
    string information;
    int count;
};

#endif
