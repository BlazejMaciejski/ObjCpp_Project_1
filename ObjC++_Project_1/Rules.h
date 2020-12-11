#pragma once
struct Rules
{
public:
	double efficiencyOfEngineer = 5;
	double efficiencyOfMagazineer = 500;
	double efficiencyOfMarketeer = 20;
	double efficiencyOfShiftWorker = 50;

	double salaryOfEngineer = 10;
	double salaryOfMagazineer = 8;
	double salaryOfMarketeer = 12;
	double salaryOfShiftWorker = 7;

	int maxTimeToRepayLoan = 5;
	double maxLoanSize = 0.5; //(part of Company value)
	double installmentRate = 0.05; //(number of months to repaty * this)

	int valueCalculatedByXMonths = 12;

	double goal = 1000;
	double startingCash = 50;
};