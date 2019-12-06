#include <iostream>
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
//simulate the restaurant

//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main(int argc, char* argv[])
{
  bool valid;
  string parasFname;
  RtSimulationClass rtSimulator;
  if (argc != 2)
  {
    //if the user did not provide the file name
    cout << "Usage: " << argv[0] << " <parameterFile.txt>" << endl;
    valid = false;
  }
  else
  {
    //if the parameters are not all valid
    parasFname = argv[1];
    valid = rtSimulator.getInfo(parasFname);
    if (!valid)
    {
      cout << "Error: The parameters file is not valid!" << endl;
    }
  }

  if (valid)
  {
    rtSimulator.printInfo();
    cout << "The first customer comes at time 0" << endl;
    rtSimulator.handleFirstEvent();
    cout << "*****************START!********************" << endl;

    while (rtSimulator.getNumEvents() > 0)
    {
      rtSimulator.handleNextEvent();
    }
    cout << "Restaurant simulation finished!" << endl;
    rtSimulator.printStat();
    cout << "**************THANKS!*****************" << endl;
  }
  return 0;
}
#endif