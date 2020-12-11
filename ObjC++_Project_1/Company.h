#pragma once


#include <iostream>
#include <variant>
#include <compare>
#include <vector>

#include "Rules.h"
#include "Worker.h"
#include "Credit.h"
#include "HRorWorkerPrinter.h"

using worker_t = std::variant<Engineer, Marketeer, Magazineer, Shift_Worker>;

class Company
{
private:
	//HRorWorkerPrinter IHireWorkers;
	Rules theseAreOurRules{};

	double bankBalance = theseAreOurRules.startingCash;
	int numberOfCredits;
	//std::unique_ptr<Credit[]> Credits;
	std::vector<std::unique_ptr<Credit>> Credits;
	int numberOfWorkers;
	//std::unique_ptr<worker_t[]> Workers;
	std::vector<std::unique_ptr<worker_t>> Workers;
	std::vector<double> incomeHistory;
	int stockInStorage;

public:
	const void printWorkers()
	{
		for (auto const& worker : Workers )
		{
			std::visit(CallPrintName{}, (*worker));
		}
	}

	//tutaj trzeba zrobic max loan size * company value
	void takeCredit(double size, int time)
	{
		if ((size + amountInLoans()) <= theseAreOurRules.maxLoanSize && time <= theseAreOurRules.maxTimeToRepayLoan)
		{
			std::unique_ptr<Credit> tempPtr(new Credit(size,time));
			Credits.push_back(std::move(tempPtr));
		}
		else if ((size + amountInLoans()) > theseAreOurRules.maxLoanSize && time > theseAreOurRules.maxTimeToRepayLoan)
		{
			std::cout << "loan too big, you can still take: " << theseAreOurRules.maxLoanSize - size - amountInLoans() << "\n";
			std::cout << "Time to repay too long. Max time is:" << theseAreOurRules.maxTimeToRepayLoan << "\n";
		}
		else if ((size + amountInLoans()) > theseAreOurRules.maxLoanSize)
		{
			std::cout << "loan too big, you can still take: " << theseAreOurRules.maxLoanSize - amountInLoans() << "\n";
		}
		else if (time > theseAreOurRules.maxTimeToRepayLoan)
		{
			std::cout << "Time to repay too long. Max time is:" << theseAreOurRules.maxTimeToRepayLoan << "\n";
		}
	}
	
	void hire(const worker_t& a)
	{
		std::unique_ptr<worker_t> tempPtr(new worker_t(a));
		Workers.push_back(std::move(tempPtr));
	}

	double getBankBalance()
	{
		return bankBalance;
	}

	double companyValue()
	{
		double sum=0;
	
		for (unsigned int i = (incomeHistory.size() - (theseAreOurRules.valueCalculatedByXMonths)); i <= incomeHistory.size(); i++)
		{
			sum += incomeHistory[i];
		}
		return sum + bankBalance;
	}
	
	double amountInLoans()
	{
		double sum = 0;
		for (const auto& credit : Credits)
		{
			sum += (credit->creditSize);
		}
		return sum;

	}

	double paySalary()
	{
		double totalSalary=0;

		for (auto const& worker : Workers)
		{
			if (std::visit(TypeName{}, (*worker)) == typeid(Engineer).name())
			{
				totalSalary += theseAreOurRules.salaryOfEngineer;
			}
			if (std::visit(TypeName{}, (*worker)) == typeid(Marketeer).name())
			{
				totalSalary += theseAreOurRules.salaryOfMarketeer;
			}
			if (std::visit(TypeName{}, (*worker)) == typeid(Magazineer).name())
			{
				totalSalary += theseAreOurRules.salaryOfMagazineer;
			}
			if (std::visit(TypeName{}, (*worker)) == typeid(Shift_Worker).name())
			{
				totalSalary += theseAreOurRules.salaryOfShiftWorker;
			}
		}

		return totalSalary;
	}

	double payBackLoans()
	{
		double sum = 0;
		for (auto& credit : Credits)
		{
			sum += credit->RepayCreditInstallment();
		}
		return sum;
	}

	void calculateEOM()
	{
		int amountOfEngineers = 0;
		int amoutSold = amountOfProductSold();
		std::cout << amoutSold << "\n";

		for (auto const& worker : Workers)
		{
			if (std::visit(TypeName{}, (*worker)) == typeid(Engineer).name())
			{
				amountOfEngineers += 1;
			}
		}

		std::cout << amountOfEngineers << "\n";

		bankBalance += (amoutSold * theseAreOurRules.efficiencyOfEngineer * amountOfEngineers - payBackLoans() - paySalary() );
	}

	int amountOfProductSold()
	{
		int amountOfMarketeers = 0;
		int amountOfMagazineers = 0;
		int amountOfShiftWorkers = 0;
		
		for (auto const& worker : Workers)
		{
			if (std::visit(TypeName{}, (*worker)) == typeid(Marketeer).name())
			{
				amountOfMarketeers += 1;
			}
			if (std::visit(TypeName{}, (*worker)) == typeid(Magazineer).name())
			{
				amountOfMagazineers += 1;
			}
			if (std::visit(TypeName{}, (*worker)) == typeid(Shift_Worker).name())
			{
				amountOfShiftWorkers += 1;
			}
		}


		if (theseAreOurRules.efficiencyOfMarketeer * amountOfMarketeers <= stockInStorage + theseAreOurRules.efficiencyOfShiftWorker * amountOfShiftWorkers)
		{
			if (stockInStorage + theseAreOurRules.efficiencyOfShiftWorker * amountOfShiftWorkers - theseAreOurRules.efficiencyOfMarketeer * amountOfMarketeers	<=	theseAreOurRules.efficiencyOfMagazineer * amountOfMagazineers)
			{
				stockInStorage = stockInStorage + theseAreOurRules.efficiencyOfShiftWorker * amountOfShiftWorkers - theseAreOurRules.efficiencyOfMarketeer * amountOfMarketeers;
			}
			else
			{
				stockInStorage = 0;
			}
			return theseAreOurRules.efficiencyOfMarketeer * amountOfMarketeers;
		}
		else
		{
			int temp = stockInStorage;
			stockInStorage = 0;
			return (temp + theseAreOurRules.efficiencyOfShiftWorker * amountOfShiftWorkers);
		}
	}
};

