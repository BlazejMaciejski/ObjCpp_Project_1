#pragma once

#include <variant>
#include <typeinfo>

#include "Worker.h"

using worker_t = std::variant<Engineer, Marketeer, Magazineer, Shift_Worker>;

struct HRorWorkerPrinter
{
	template <class T> 
	void operator() (const T&)
	{
		if (typeid(T) == typeid(Engineer))
		{
			return new Engineer{};
		}
		if (typeid(T) == typeid(Marketeer))
		{
			return new Marketeer{};
		}
		if (typeid(T) == typeid(Magazineer))
		{
			return new Magazineer{};
		}
		if (typeid(T) == typeid(Shift_Worker))
		{
			return new Shift_Worker{};
		}
		else
		{
			std::cout << "Wystapil blad, zly typ pracownika";
			return new Engineer{};
		}
	}

};

