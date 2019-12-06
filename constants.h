#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//Weijia Chen
//12/03/2019
//constants

//initial values for the EventClass
const int INI_TYPE = 0;
const int INI_TIME = 0;
const int INI_CUSNUM = 0;

//event type
const int ARR = 1;
const int START_SRV = 2;
const int FINISH_SRV = 3;

//initial value for the RtSimulationClass
const int FIRST = 1;
const int INIT_TOTALCUSNUM = 0;
const int INIT_TIMESTEP = 0;
const int INIT_LEFTCUS = 0;
const int INC_TO_NEXT = 1;
const int INIT_SRVDCUSNUM = 0;
const int INIT_CURRQ = 0;
const int INIT_LONGESTQ = 0;
const int INIT_TOTALQCUS = 0;
const int INIT_TOTALSRVTIME = 0;
const int INIT_LASTSRVTIME = 0;

const int ONEPCT = 1;
const int FULLPCT = 100;
const int CIN_IGNORE = 200;
const double BASIC_DOUBLE = 1.0;
#endif
