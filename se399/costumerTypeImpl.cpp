
#include <iostream>
#include <string>
#include "costumerType.h"

using namespace std;

customerType::customerType(int customerN, int arrvTime, int wTime,
int tTime)
{
setCustomerInfo(customerN, arrvTime, wTime, tTime);
}

int customerType::getWaitingTime() const
{
return waitingTime;
}

void customerType::incrementWaitingTime()
{
waitingTime++;
}

void customerType::setWaitingTime(int time)
{
waitingTime = time;
}

void customerType::setCustomerInfo(int customerN, int arrvTime,
int wTime, int tTime)
{
customerNumber = customerN;
arrivalTime = arrvTime;
waitingTime = wTime;
transactionTime = tTime;
}

int customerType::getArrivalTime() const
{
return arrivalTime;
}

int customerType::getTransactionTime() const
{
return transactionTime;
}

int customerType::getCustomerNumber() const
{
return customerNumber;
}