#ifndef logging_h
#define logging_h

#include "Log.h"
#include <string>
#include "User.h"
#include <vector>

using namespace std;

// * This class is used for managing the logs of books
// * It contains abstract methods which is implemented in DataAccess
//  concrete class
class Logging
{
    public:
        virtual vector<Log> LoadIssueBookData() = 0;
        virtual void UpdateIssueBookData() = 0;
};

#endif