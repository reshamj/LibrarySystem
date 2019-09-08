#ifndef BookDataPersistance_h
#define BookDataPersistance_h

#include <string>
using namespace std;

#include "Book.h"
#include <vector>

// * This class contains abstract methods which is inherited by DataAccess class
// * This class contains method which is specific to a particular database.
class BookDataPersistance{
    public:
        virtual vector<Book> LoadBookData() = 0;
        virtual void UpdateBookData() = 0;
};

#endif
