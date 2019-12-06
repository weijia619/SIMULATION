#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "constants.h"
#include "EventClass.h"
using namespace std;

//Weijia Chen
//12/03/2019
//event class

EventClass::EventClass()
{
  type = INI_TYPE;
  time = INI_TIME;
  cusNum = INI_CUSNUM;
}

EventClass::EventClass(int inType, int inTime, int inCusNum)
{
  type = inType;
  time = inTime;
  cusNum = inCusNum;
}

int EventClass::getType() const
{
  return type;
}

int EventClass::getTime() const
{
  return time;
}

int EventClass::getCusNum() const
{
  return cusNum;
}

bool EventClass::operator>=(const EventClass &in) const
{
  return time >= in.getTime();
}

bool EventClass::operator<=(const EventClass& in) const
{
  return time <= in.getTime();
}

bool EventClass::operator<(const EventClass& in) const
{
  return time < in.getTime();
}

bool EventClass::operator==(const EventClass& in) const
{
  return time == in.getTime();
}

EventClass& EventClass::operator=(const EventClass& rhs)
{
  type = rhs.getType();
  time = rhs.getTime();
  cusNum = rhs.getCusNum();
  return *this;
}

ostream& operator<<(ostream& os, const EventClass& iObj)
{
  if (iObj.getType() == ARR)
  {
    os << "Event Type: ARRIVAL" << endl;
  }
  else if (iObj.getType() == START_SRV)
  {
    os << "Event Type: START_SERVE" << endl;
  }
  else if (iObj.getType() == FINISH_SRV)
  {
    os << "Event Type: FINISH_SERVE" << endl;
  }
  os << "  Time Step: " << iObj.getTime() << endl;
  os << "  Customer NO.:" << iObj.getCusNum() << endl;
  return (os);
}