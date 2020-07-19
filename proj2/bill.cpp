//
//  bill.cpp
//  Project 2
//
//  Created by Amy Yu on 4/12/19.
//  Copyright © 2019 Amy Yu. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main(){
    cout << "Initial meter reading: ";
    int initialReading;
    cin >> initialReading;
    
    if (initialReading < 0)         // error if initial reading is negative
    {
        cout << "---" << endl;
        cout << "The initial meter reading must be nonnegative." << endl;
        return 1;   // ends program
    }
    
    cout << "Final meter reading: ";
    int finalReading;
    cin >> finalReading;
    cin.ignore(10000, '\n');    // throws out new line since string is being read after int
    
    if (finalReading < initialReading)      // error if final reading is less than initial reading
    {
        cout << "---" << endl;
        cout << "The final meter reading must be at least as large as the initial reading." << endl;
        return 1;
    }
    
    cout << "Customer name: ";
    string name;
    getline(cin, name);
    
    if (name == "")         // error if empty string is entered
    {
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 1;
    }
    
    cout << "Month number (1=Jan, 2=Feb, etc.): ";
    int month;
    cin >> month;
    
    if (1 > month || month > 12)        // error if month is not between 1 and 12
    {
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;
        return 1;
    }
    
    cout << "---" << endl;
    
    int HCF = finalReading - initialReading;
    
    cout.setf(ios::fixed);
    cout.precision(2);          // sets decimal place to 2 significant figures
    
    if (month >= 4 && month <= 10)     // checks if month is between April and October
    {
        if (HCF <= 43)  // checks if HCF used is less than or equal to 43
            cout << "The bill for " << name << " is $" << (2.71 * HCF) << endl;
        else  // if HCF used is greater than 43
            cout << "The bill for " << name << " is $" << ((2.71 * 43) + (3.39 * (HCF - 43))) << endl;
    }
    else    // if month is not between April and October
    {
        if (HCF <= 29)  // checks if HCF used is less than or equal to 29
            cout << "The bill for " << name << " is $" << (2.71 * HCF) << endl;
        else  // if HCF used is greater than 29
            cout << "The bill for " << name << " is $" << ((2.71 * 29) + (2.87 * (HCF - 29))) << endl;
    }
}
