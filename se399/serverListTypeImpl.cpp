
#include <iostream>
#include <string>
#include "serverListType.h"

using namespace std;

serverListType::serverListType(int num)
{
    numOfServers = num;
    servers = new serverType[num];
}

serverListType::~serverListType()
{
    delete[] servers;
}

int serverListType::getFreeServerID() const
{
    int serverID = -1;

    int i;

    for (i = 0; i < numOfServers; i++)
        if (servers[i].isFree())
        {
            serverID = i;
            break;
        }
    return serverID;
}

int serverListType::getNumberOfBusyServers() const
{
    int busyServers = 0;

    int i;

    for (i = 0; i < numOfServers; i++)
        if (!servers[i].isFree())
            busyServers++;
    return busyServers;
}

void serverListType::setServerBusy(int serverID,
                                   customerType cCustomer,
                                   int tTime)
{
    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(tTime);
    servers[serverID].setCurrentCustomer(cCustomer);
}

void serverListType::setServerBusy(int serverID,
                                   customerType cCustomer)
{
    int time;

    time = cCustomer.getTransactionTime();

    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(time);
    servers[serverID].setCurrentCustomer(cCustomer);
}

void serverListType::updateServers()
{
    int i;

    for (i = 0; i < numOfServers; i++)
        if (!servers[i].isFree())
        {
            servers[i].decreaseTransactionTime();
            if (servers[i].getRemainingTransactionTime() == 0)
            {
                cout << "Server No: " << (i + 1) << " Customer number "
                     << servers[i].getCurrentCustomerNumber()
                     << " departed at " << endl
                     << " clock unit "
                     << servers[i].getCurrentCustomerArrivalTime() + servers[i].getCurrentCustomerWaitingTime() + servers[i].getCurrentCustomerTransactionTime()
                     << endl;
                servers[i].setFree();
            }
        }
}

void serverListType::updateServers(ostream& outFile)
{
    int i;

    for (i = 0; i < numOfServers; i++)
        if (!servers[i].isFree())
        {
            servers[i].decreaseTransactionTime();
            if (servers[i].getRemainingTransactionTime() == 0)
            {
                outFile << "Server No: " << (i + 1) << " Customer number "
                        << servers[i].getCurrentCustomerNumber()
                        << " departed at " << endl
                        << " clock unit "
                        << servers[i].getCurrentCustomerArrivalTime() + servers[i].getCurrentCustomerWaitingTime() + servers[i].getCurrentCustomerTransactionTime()
                        << endl;
                servers[i].setFree();
            }
        }
}