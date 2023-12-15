//testSimulation.cpp
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include "waitingCustomerQueueType.h"
#include "serverListType.h"
using namespace std;
void setSimulationParameters(int& sTime, int& numOfServers, int& transTime, int& tBetweenCArrival);
bool isCustomerArrived(double arvTimeDiff);

int main()
{
   int simulationTime;              //how long it runs
   int numberOfServers;             //number of servers 
   int transactionTime;             //transactin time
   int timeBetweenCustomerArrival;  //average wait between customers
   waitingCustomerQueueType customerQueue;  //customers in line
   customerType customer;
   int custNumber = 0;	
   int totalWaitTime = 0;
   int numberOfCustomersServed = 0;
   int clock = 0;
   int serverID;
   setSimulationParameters(simulationTime, numberOfServers, transactionTime, timeBetweenCustomerArrival);
   serverListType serverList(numberOfServers); 

   for(clock = 1; clock <= simulationTime; clock++)
   {
      //update remaining transactiontime for the servers
      serverList.updateServers();

      //update the waiting time for each customer
      if(!customerQueue.isEmptyQueue())
         customerQueue.updateWaitingQueue();

      //check to see if a customer arrives
      if(isCustomerArrived(timeBetweenCustomerArrival))
      {
         custNumber++;
         customer.setCustomerInfo(custNumber,clock,0, transactionTime);
         customerQueue.addQueue(customer);
         //cout<<"Customer #"<<custNumber
	 //    <<" arrived at time unit "<< clock <<endl;
      }
		
      //check for a free server
      serverID = serverList.getFreeServerID();
      if(serverID != -1 && !customerQueue.isEmptyQueue())
      {
         customer = customerQueue.front();
         customerQueue.deleteQueue();
         totalWaitTime = totalWaitTime + customer.getWaitingTime();
         numberOfCustomersServed++;
         serverList.setServerBusy(serverID, customer);
      }
   }
   //print simulation results
   cout<<"\nSimulation ran for "<<simulationTime <<" time units"<<endl;
   cout<< numberOfCustomersServed << " were served.\n";
   cout<<"The total waiting time was " <<totalWaitTime<<endl;
   cout<<"The average wait per customer was "<<float(totalWaitTime)/float(numberOfCustomersServed)<< endl;
   return 0;
}
void setSimulationParameters(int& sTime, int& numOfServers,int& transTime, int& tBetweenCArrival)
{
   cout<<"\nEnter simulation time: "<<flush;
   cin>>sTime;
   cout<<"\nEnter number of servers: "<<flush;
   cin>>numOfServers;
   cout<<"\nEnter transaction time: "<<flush;
   cin>>transTime;
   cout<<"\nEnter time between customer arrivals: "<<flush;
   cin>>tBetweenCArrival;
}
bool isCustomerArrived(double arvTimeDiff)
{
   double value;
   value = static_cast<double> (rand()) / static_cast<double>(RAND_MAX);
   return (value > exp(- 1.0/arvTimeDiff));
}
