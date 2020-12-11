#pragma once
class Credit
{
public:

	Credit(double size, int time)
	{
		creditSize = size;
		remainingCreditInstallments = time;
	}

	double creditSize;
	int remainingCreditInstallments;


	double RepayCreditInstallment()
	{
		double thisRate = (creditSize / remainingCreditInstallments);
		creditSize -= thisRate;
		remainingCreditInstallments--;
		return thisRate;
	}
};

