/**
 *  File: main.cpp
 *  Developer: Daniel Khoury
 *  Email: khouryd@student.vvc.edu
 *  Description: Receives input of a series of transactions. Then prints out a list of bank statements.
 **/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

const int MAX_DAY = 30;

class Transaction
{
public:
    Transaction();
    void read();
    void print() const;
    int get_day();
    double get_amount();
private:
    int m_day;
    double m_amount;
    std::string m_description;
};

class Statement
{
public:
    Statement();
    void read();
    void compute_balances();
    void print();
    double get_average_daily_balance();
    double get_minimum_daily_balance();
private:
    std::vector<Transaction> transactions;
    std::vector<double> daily_balances;
};

Transaction::Transaction()
{
    m_day = 0;
    m_amount = 0.0;
}

void Transaction::read()
{
    std::cin >> m_day;
    std::cin >> m_amount;
    std::cin.ignore();
    std::getline(std::cin,m_description);
}

void Transaction::print() const
{
    std::cout << std::left << std::setw(10) << m_day 
              << std::left << std::setw(10) <<  m_amount 
              << std::left << std::setw(10) << m_description;
}

int Transaction::get_day()
{
    return m_day;
}

double Transaction::get_amount()
{
    return m_amount;
}

Statement::Statement()
{
}

void Statement::read()
{
    bool more = true;
    while(more)
    {
        Transaction t;
        t.read();
        transactions.push_back(t);
        std::cout << "Enter another (Y/N): ";
        char response;
        std::cin >> response;
        if(response != 'y' && response != 'Y')
        {
            more = false;
            std::cout << std::endl;
        }
    }
   compute_balances();
}

void Statement::compute_balances()
{
    int i = 0;
    double total = 0.0;
    for (int day = 1; day <= MAX_DAY; day++)
    {
        while (i < transactions.size() && transactions[i].get_day() == day)
        {
            total += transactions[i].get_amount();
            i++;
        }
        daily_balances.push_back(total);
    }
}

void Statement::print()
{
    int i = 0;
    std::cout << "Statement:" << std::endl;
    std::cout << std::left << std::setw(10) << "Day:" << std::left << std::setw(10) << "Amount:" << std::left 
    << std::setw(10) << "Description:" << std::right << std::setw(10) <<  "Balance:" <<  std::endl;
    for(int day = 1; day <= MAX_DAY; day++)
    {
        if(i < transactions.size() && transactions[i].get_day() == day)
        {
            transactions[i].print();
            i++;
            std::cout << std::setw(12) << std::right << daily_balances[i - 1] << std::endl;
        }
        else
            day = 31;
    }
    const double interest = 0.005;
    std::cout << std::endl;
    std::cout << "Daily average interest: " << get_average_daily_balance() * interest << std::endl;
    std::cout << "Daily minimum interest: " << get_minimum_daily_balance() * interest << std::endl;
}

double Statement::get_average_daily_balance()
{
    double balance_sum = 0.0;
    for (int day = 0; day < daily_balances.size(); day++)
        balance_sum += daily_balances[day];
    
    return balance_sum/MAX_DAY;
}

double Statement::get_minimum_daily_balance()
{
    double minimum_balance = daily_balances[0];
    for (int day = 1; day < daily_balances.size(); day++)
    {
        if(daily_balances[day] < minimum_balance)
            minimum_balance = daily_balances[day];
    }
    
    return minimum_balance;
}

int main()
{
    std::cout << "Enter in following format \"Day Amount Description\"." << std::endl;
    Statement s;
    s.read();
    s.print();
    
    return 0;
}


