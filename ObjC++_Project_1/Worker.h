#pragma once

#include <iostream>
#include <typeinfo>>

class Worker
{
	public:
	std::string name;
};

class Engineer : Worker
{
	std::string finishedFaculty;

public:
	Engineer()
	{
		name = "Steve";
		finishedFaculty = "Hogward";
	}

	void printPerson()
	{
		std::cout << "Engineer " << name << " Faculty: " << finishedFaculty <<"\n";
	}
};

class Marketeer : Worker
{
	int numberOfFollowersOnMedia;

public:
	Marketeer()
	{
		name = "Bob";
		numberOfFollowersOnMedia = 0;
	}
	
	void printPerson()
	{
		std::cout << "Marketeer " << name << " number of followers on media: " << numberOfFollowersOnMedia<<"\n";
	}
};

class Magazineer : Worker
{
	bool ForkliftLicence;

public:
	Magazineer()
	{
		name = "Tom";
		ForkliftLicence = true;
	}
	
	void printPerson()
	{
		std::cout << "Magazeneer " << name;
		if (ForkliftLicence == true)
		{
			std::cout << " Has forlift licence \n";
		}
		else
		{
			std::cout << " Doesn't have forlift licence \n";
		}

	}
};

class Shift_Worker : Worker
{	
	double bootsize;

public:
	Shift_Worker()
	{
		name = "Joe";
		bootsize = 99;
	}
	
	void printPerson()
	{
		std::cout << "Shift Worker " << name << " boot size: " << bootsize << "\n";
	}
};

struct CallPrintName 
{
	void operator()(Engineer& d) { d.printPerson(); }
	void operator()(Marketeer& d) { d.printPerson(); }
	void operator()(Magazineer& d) { d.printPerson(); }
	void operator()(Shift_Worker& d) { d.printPerson(); }
	//byc moze const przed kalsa ?
};

struct TypeName
{
	auto operator()(Engineer& d) { return typeid(Engineer).name(); }
	auto operator()(Marketeer& d) { return typeid(Marketeer).name(); }
	auto operator()(Magazineer& d) { return typeid(Magazineer).name(); }
	auto operator()(Shift_Worker& d) { return typeid(Shift_Worker).name(); }
	//byc moze const przed kalsa ?
};