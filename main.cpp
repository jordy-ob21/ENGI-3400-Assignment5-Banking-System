
#include <iostream>

using namespace std;
// Base function
class accountInfo{
public:
    double numDeposits = 0;
    double numWithdraw = 0;
    double yearInt;
    double sCharges = 0;
    double balance;
    double monthlyIntr;
    
    accountInfo(double b, double y){
        balance = b;
        yearInt = y;
        
    }

    virtual double deposit(double depositAmount){
       return balance += depositAmount;
    }
    
    virtual double withdraw(double withdrawAmount){
        return balance -= withdrawAmount;
    }
    
    virtual double calcInt(double yearlyIntr){
        double monthlyIntrR = yearInt/12;
        double monthlyIntr = monthlyIntrR*balance;
        cout << "Interest Earned: " << monthlyIntr << endl;
        balance += monthlyIntr;
        return balance;
        }
        
    virtual double monthlyProc(){
        cout <<"Balance:" << balance << endl;
        cout << "Number of deposits: "<< numDeposits << endl;
        cout << "Number of withdrawals: " << numWithdraw << endl;
        balance -= sCharges;
        cout << "Service Charges: " << sCharges << endl;
        if(balance > 0){
            calcInt(yearInt);
        }
        else{
            cout << "Interest Earned: 0" << endl;
        }
        numDeposits =0;
        numWithdraw = 0;
        sCharges =0;
        
        return balance;
        
    }
    ~accountInfo() {}
};




class savings: public accountInfo{
public:
    savings(double b, double y): accountInfo (b,y){}
    bool accountActive = true;
    
    double withdraw(double a){
        if(balance < 25){
            accountActive = false;
            cout << "Balance below $25, account inactive" << endl;
        }
        if((balance - a) < 0){
            cout << "Insufficient Funds" << endl;
        }
        else if(accountActive==true){
            numWithdraw += 1;
            balance = accountInfo:: withdraw(a);}
      
        return balance;
    }
    double deposit(double a){
        numDeposits +=1;
        balance = accountInfo:: deposit(a);
        if (accountActive==false && balance > 25){
            accountActive = true;
        }
        return balance;
    }
    double monthlyProc(){
       
        if(numWithdraw > 4 ){
            sCharges += (numWithdraw - 4);
            
            balance = accountInfo:: monthlyProc();
            if(balance < 25){
                accountActive = false;
            }
        }
        else{
            sCharges = 0;
            balance = accountInfo:: monthlyProc();
        }
        cout << "Remaining balance: " << balance << endl;
        
        return balance;
    }
};

class checking: public accountInfo{
public:
    checking(double b, double y):accountInfo (b,y){}
    
    double withdraw(double a){
        if((balance - a) < 0){
            cout << "Insufficient Funds" << endl;
            sCharges += 15;
        }
        else{
            balance = accountInfo::withdraw(a);
            numWithdraw += 1;
        }
        return balance;
    }
    double deposit(double a){
        balance = accountInfo:: deposit(a);
        numDeposits +=1;
        return balance;
    }
    double monthlyProc(){
        sCharges += (5 + (numWithdraw * 0.1));
        accountInfo:: monthlyProc();
        cout << "Remaining balance: " << balance << endl;
        
        return balance;
    }
    
};

int main(){
    
    double bS;
    cout << "Enter savings balance: ";
    cin >> bS;
    double cS;
    cout << "Enter checking balance: ";
    cin >> cS;
    double iY;
    cout << "Enter yearly intrest rate: ";
    cin >> iY;
    savings s(bS, iY);
    checking c(cS, iY);
    
    
    while(true){
        
        int input;
        cout << "[1] Savings account deposit" << endl;
        cout << "[2] Savings account withdrawal" << endl;
        cout << "[3] Checking account deposit" << endl;
        cout << "[4] Checking account withdrawl" << endl;
        cout << "[5] Monthly statistics calculation" << endl;
        cout << "[6] Show statistics"<< endl;
        cout << "[7] Quit" << endl;
        cin >> input;
        double amount;
        switch(input){
            case 1:
                
                cout << "Savings Deposit" << endl << "Deposit amount: ";
                cin >> amount;
                s.deposit(amount);
                break;
            case 2:
                
                cout << "Savings Withdraw" << endl << "Withdraw amount: ";
                cin >> amount;
                s.withdraw(amount);
                break;
            case 3:
                cout << "Checking Deposit" << endl << "Deposit amount: ";
                cin >> amount;
                c.deposit(amount);
                break;
            case 4:
                cout << "Checking Withdraw" << endl << "Withdraw amount: ";
                cin >> amount;
                c.withdraw(amount);
                break;
            case 5:
                cout << "Savings:" << endl;
                s.monthlyProc();
                cout << "Checking:" << endl;
                c.monthlyProc();
               
                break;
            case 6:
                cout << "Savings: "<< endl;
                cout << "Balance: " << s.balance << endl;
                cout << "Number of withdrawals: " << s.numWithdraw << endl;
                cout << "Number of deposits: " << s.numDeposits << endl;

                cout << endl;
                cout << "Checking: "<< endl;
                cout << "Balance: " << c.balance << endl;
                cout << "Number of withdrawals: " << c.numWithdraw << endl;
                cout << "Number of deposits: " << c.numDeposits << endl;
                break;
            case 7:
                return 0;
            }
    }
}
