#ifndef _EVENTCLASS_H_
#define _EVENTCLASS_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "constants.h"
using namespace std;

//Weijia Chen
//12/03/2019
//event class

class EventClass
{
  public:
    EventClass();
    //default constructor

    EventClass(int inType, int inTime, int inCusNum);
    //set the value as the input value

    int getType() const;
    //return the value of type

    int getTime() const;
    //return the value of time

    int getCusNum() const;
    //return the value of customer number

    bool operator>=(const EventClass& in) const;
    bool operator<=(const EventClass& in) const;
    bool operator<(const EventClass& in) const;
    bool operator==(const EventClass& in) const;
    EventClass& operator=(const EventClass& rhs);
    //overload the operator

  private:
    int type;
    int time;
    int cusNum;
};
ostream& operator<<(ostream& os, const EventClass& iObj);
#endif