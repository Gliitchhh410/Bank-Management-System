#include <iostream>
#include <vector>
#include <string>
#include "bank.h"
using namespace std;


void Bank::openAccount(int customerId, string type){
    Customer* targetCustomer = nullptr;

    for (auto &cust : Customers){
        if (cust.getCustomerId() == customerId){
            targetCustomer = &cust;
            break;
        }
    }

    if (!targetCustomer){
        cout << "Error: Customer ID not found" << endl;
        return;
    }

    Account* newAccount = nullptr;
    int newAccId = rand() * 1000;


    
}