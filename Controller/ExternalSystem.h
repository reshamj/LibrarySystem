#ifndef externalsystem_h
#define externalsystem_h
#include <string>

/*It is interface class which contains pure virtual class .
This class in used to implement the connection with the external interface*/
class ExternalSystem
{
public:
  virtual std::string ExternalBookRequest(std::string username, std::string isbn, std::string externalLibrary) = 0;
};

#endif