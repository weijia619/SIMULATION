#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"
#include "constants.h"
#include "random.h"
#include "RtSimulationClass.h"
using namespace std;

//Weijia Chen
//12/03/2019
//class for the simulation of the restaurant

RtSimulationClass::RtSimulationClass()
{
  isOccupied = false;
  totalCusNum = INIT_TOTALCUSNUM;
  leftCus = INIT_LEFTCUS;
  srvdCusNum = INIT_SRVDCUSNUM;
  currQ = INIT_CURRQ;
  longestQ = INIT_LONGESTQ;
  totalQCus = INIT_TOTALQCUS;
  totalSrvTime = INIT_TOTALSRVTIME;
  lastSrvTime = INIT_LASTSRVTIME;
}

template <typename Tinv>
bool RtSimulationClass::indigit(ifstream& inFName, Tinv& inVal)
{
  if (inFName.eof())
  {
    cout << "eof()" << endl;
    return false;
  }
  inFName >> inVal;
  if (inFName.fail())
  {
    cout << "fail()" << endl;
    inFName.clear();
    inFName.ignore(CIN_IGNORE, '\n');
    return false;
  }
  return true;
}

bool RtSimulationClass::getInfo(string& parasFnameStr)
{
  ifstream parasFname;
  parasFname.open(parasFnameStr.c_str());
  bool valid = true;
  if (!indigit(parasFname, shortQCusPct))
  {
    cout << "The percent of customers who don't want to";
    cout << " join a long line is invalid" << endl;
    valid = false;
  }
  if (!indigit(parasFname, longQLen))
  {
    cout << "Number of people in the queue";
    cout << " that is defined as a long line is invalid" << endl;
    valid = false;
  }
  if (!indigit(parasFname, intervalMin))
  {
    cout << "The min value of the amount of time";
    cout << " between customers is invalid " << endl;
    valid = false;
  }
  if (!indigit(parasFname, intervalMax))
  {
    cout << "The max value of the amount of time";
    cout << " between customers is invalid " << endl;
    valid = false;
  }
  if (!indigit(parasFname, oneCusMean))
  {
    cout << "The mean value of the amount of time it takes";
    cout << " for the server to wait on a customer is invalid " << endl;
    valid = false;
  }
  if (!indigit(parasFname, oneCusDev))
  {
    cout << "The deviation value of the amount of time it takes";
    cout << " for the server to wait on a customer is invalid " << endl;
    valid = false;
  }
  if (!indigit(parasFname, closeTime))
  {
    cout << "The time when restaurant will be closed is invalid" << endl;
    valid = false;
  }
  if (!indigit(parasFname, seed))
  {
    cout << "The seed for the random program is invalid" << endl;
    valid = false;
  }
  setSeed(seed);
  return valid;
}

void RtSimulationClass::printInfo()
{
  cout << "The percent of customers who don't want to join a long line: ";
  cout << shortQCusPct << endl;
  cout << "Number of people in the queue that is defined as a long line: ";
  cout << longQLen << endl;
  cout << "The min value of the amount of time between customers: ";
  cout << intervalMin << endl;
  cout << "The max value of the amount of time between customers: ";
  cout << intervalMax << endl;
  cout << "The mean value of the amount of time";
  cout << "it takes for the server to wait on a customer: ";
  cout << oneCusMean << endl;
  cout << "The deviation value of the amount of time ";
  cout << "it takes for the server to wait on a customer: ";
  cout << oneCusDev << endl;
  cout << "The time when restaurant will be closed: ";
  cout << closeTime << endl;
  cout << "The seed for the random program: ";
  cout << seed << endl;
}

void RtSimulationClass::handleFirstEvent()
{
  EventClass firstCusA(ARR, INIT_TIMESTEP, FIRST);
  //the first customer arrived at time 0
  events.insertValue(firstCusA);
  totalCusNum++;
}

int RtSimulationClass::getNumEvents()
{
  return events.getNumElems();
}

int RtSimulationClass::maxNum(int a, int b)
{
  if (a > b)
  {
    return a;
  }
  return b;
}

void RtSimulationClass::handleNextEvent()
{
  EventClass curr;
  events.removeFront(curr);
  //if the event type is ARRIVAL
  if (curr.getType() == ARR)
  {
    cout << "The " << curr.getCusNum() << " th customer ";
    cout << "arrives at time " << curr.getTime() << endl;
    int interval = getUniform(intervalMin, intervalMax);
    int nextArrTime = curr.getTime() + interval;

    if (nextArrTime > closeTime)
    {
      //if the restaurant has cloesd, there will be no new customers
      cout << "The restaurant has closed. So the ";
      cout << curr.getCusNum() + 1 << " th customer left." << endl;
    }
    else
    {
      //if the restaurant has not cloesd when the next customer arrives
      totalCusNum++;
      EventClass nextCusA(ARR, nextArrTime, totalCusNum);
      events.insertValue(nextCusA);
    }

    if (queue.getNumElems() >= longQLen
       && getUniform(ONEPCT, FULLPCT) <= shortQCusPct)
    {
      //The queue is too long and the current cutomer decide to leave
      leftCus++;
      cout << "The " << curr.getCusNum() << " th customer left";
      cout << " because of the long line." << endl;
    }
    else
    {
      //The current customer does not leave
      if (isOccupied)
      {
        //The waiter is occupied
        currQ++;
        longestQ = maxNum(longestQ, currQ);
        totalQCus++;
        queue.enqueue(curr);
        cout << "The " << curr.getCusNum() << " th customer wait ";
        cout << "in the " << currQ << " th position in the queue" << endl;
      }
      else
      {
        //The waiter is not occupied
        EventClass srvCurrCus(START_SRV, curr.getTime(), curr.getCusNum());
        events.insertValue(srvCurrCus);
      }
    }
  }
  else if (curr.getType() == START_SRV)
  {
    cout << "The waiter starts to serve the ";
    cout << curr.getCusNum() << " th customer ";
    cout << "at time " << curr.getTime() << "." << endl;
    isOccupied = true;
    srvdCusNum++;
    int duration = getNormal(oneCusMean, oneCusDev);
    totalSrvTime += duration;
    lastSrvTime = curr.getTime() + duration;
    EventClass currFinSrv(FINISH_SRV, lastSrvTime, curr.getCusNum());
    events.insertValue(currFinSrv);
  }
  else
  {
    //the current customer is finished
    cout << "The " << curr.getCusNum() << " th customer finished";
    cout << " at time " << curr.getTime() << "." << endl;
    if (!queue.getNumElems())
    {
      //if there is no people waiting in the line
      isOccupied = false;
    }
    else
    {
      //if there is a queue, put the next customer in queue
      //to the event list as START_SRV type
      EventClass nextCusInQ;
      queue.dequeue(nextCusInQ);
      currQ--;
      EventClass nextCusToSrv(START_SRV, curr.getTime(),
                             nextCusInQ.getCusNum());
      events.insertValue(nextCusToSrv);
    }
    cout << "*********************************************" << endl;
  }
}

void RtSimulationClass::printStat()
{
  cout << "********IMPORTANT STATISTICS***********" << endl;
  cout << "Total number of customers that showed up" << endl;
  cout << "(except the customer who arrived after the close time): ";
  cout << totalCusNum << endl;
  cout << "Percentage of time the server was busy: ";
  double actualCloseT = maxNum(lastSrvTime, closeTime);
  double pctBusy = BASIC_DOUBLE * totalSrvTime / actualCloseT;
  cout << pctBusy * FULLPCT << "%" << endl;
  cout << "Percentage of customers had to wait in line " << endl;
  cout << "(customers who queued / ";
  cout << "total number of customers that showed up): ";
  cout << totalQCus << "/" << totalCusNum << ", ";
  double pctLine = BASIC_DOUBLE * totalQCus / totalCusNum;
  cout << pctLine * FULLPCT << "%" << endl;
  cout << "The number of customers that arrived, ";
  cout << "but left due to excessive line length: ";
  cout << leftCus << endl;
  cout << "The longest the line was throughout the simulation: ";
  cout << longestQ << endl;
  cout << "The amount of customers that the waiter served: ";
  cout << srvdCusNum << endl;
  cout << "The actual close time: ";
  cout << actualCloseT << endl;
}
