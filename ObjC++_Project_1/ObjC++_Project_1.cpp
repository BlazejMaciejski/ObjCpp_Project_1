// ObjC++_Project_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Company.h"
#include "Worker.h"
#include "Credit.h"
#include "Rules.h"
int main()
{
    std::unique_ptr<Company> ourCompany (new Company);
    std::unique_ptr<Rules> ourRules (new Rules);
    bool state;
    std::cout << "Hello World!\n";

    ourCompany->hire(Engineer{});
    ourCompany->hire(Magazineer{});
    ourCompany->hire(Marketeer{});
    ourCompany->hire(Shift_Worker{});

    std::cout << "Warunek Wygranej - Wartosc = " << ourRules->goal << "  na przestrzeni : "<<ourRules->valueCalculatedByXMonths <<"miesiecy  \n";
    std::cout << "Aktualna wartosc spolki:  " << ourCompany->companyValue() << "\n";
    std::cout << "Aktualny stan konta:  " << ourCompany->getBankBalance() << "\n";


    std::string currentCommand;

    while (ourCompany->companyValue() < ourRules->goal && ourCompany->getBankBalance() >= 0)
    {
        std::cin >> currentCommand;

        if (currentCommand == "howmuch")
        {
            std::cout << ourCompany->getBankBalance() <<"\n";
        }
        if (currentCommand == "lp")
        {
            ourCompany->printWorkers();
        }
        
        if (currentCommand == "zinz")
        {
            ourCompany->hire(Engineer{});
        }
        if (currentCommand == "zmag")
        {
            ourCompany->hire(Magazineer{});
        }
        if (currentCommand == "zmkt")
        {
            ourCompany->hire(Marketeer{});
        }
        if (currentCommand == "zrob")
        {
            ourCompany->hire(Shift_Worker{});
        }
        
        if (currentCommand == "kt")
        {
            ourCompany->calculateEOM();

            std::cout << "Warunek Wygranej - Wartosc = " << ourRules->goal << "  na przestrzeni : " << ourRules->valueCalculatedByXMonths << "miesiecy  \n";
            std::cout << "Aktualna wartosc spolki:  " << ourCompany->companyValue() << "\n";
            std::cout << "Aktualny stan konta:  " << ourCompany->getBankBalance() << "\n";

        }

        if (currentCommand == "kred")
        {
            int kwota;
            int czas;
            std::cout << "wpisz kwote:   ";
            std::cin >> kwota;
            std::cout << "\n wpisz czas na splate:    ";
            std::cin >> czas;
            std::cout << "\n";
            ourCompany->takeCredit(kwota, czas);
        }

        if (currentCommand == "ls")
        {
            std::cout << "Lista komend: \n lp - wylistuj pracownikow \n zinz - zatrodnij inzyniera \n zmag - zatrudnij magazyniera \n zmkt - zatrudnij marketoludzia \n zrob - zatrudnij pracownika";
            std::cout << "\n kred - wez kredyt \n kt - skoncz ture \n";
        }
    }


    if (ourCompany->companyValue() >= ourRules->goal)
    {
        std::cout << "You Won";
    }
    if (ourCompany->getBankBalance() < 0)
    {
        std::cout << "You Lost";
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
