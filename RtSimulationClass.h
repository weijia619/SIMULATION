#ifndef _RTSIMULATIONCLASS_H_
#define _RTSIMULATIONCLASS_H_
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
using namespace std;

//Weijia Chen
//12/03/2019
//class for the simulation of the restaurant

class RtSimulationClass
{
  public:
    RtSimulationClass();
    //Default Constructor

    template <typename T>
    bool indigit(ifstream& inFName, T& inVal);
    //get the single value from file

    bool getInfo(string& parasFnameStr);
    //get the values from the file

    void printInfo();
    //printf the value gotten from the file

    void handleFirstEvent();
    //insert the first arrival event to the event list

    int getNumEvents();
    //return the amount of the events in the list

    int maxNum(int a, int b);
    //compare the two values

    void handleNextEvent();
    //handle the next event for the list

    void printStat();
    //print the important statistics

  private:
    FIFOQueueClass< EventClass > queue;
    //the line in the restaurant

    SortedListClass < EventClass > events;
    //the event list

    int longQLen;
    //the definition of the long line

    int shortQCusPct;
    //the percentage of the customer that
    //will leave because of the long line

    int intervalMin;
    //the min value of the uniform
    //distribution of the interval

    int intervalMax;
    //the max value of the uniform
    //distribution of the interval

    double oneCusMean;
    //the mean value if the normal distribution
    //of the time for serving one customer

    double oneCusDev;
    //the standard deviation if the normal distribution
    //of the time for serving one customer

    int closeTime;
    //the close time for the restaurant

    int seed;
    //the seed for the random function

    int isOccupied;
    //whether the waiter is occupied

    int totalCusNum;
    //the amount of customers who showed up

    int leftCus;
    //the number of customers that left
    //because of the long line

    int srvdCusNum;
    //the number of customers that had been served

    int currQ;
    //the length of current line

    int  longestQ;
    //the longest line

    int totalQCus;
    //total number of customer who queued

    int totalSrvTime;
    //waiter's total serving time

    int lastSrvTime;
    //the actual close time
};
#endif