//============================================================================
// Name        : Flight.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   :
// Description : Class that represents one flight and its most important attributes
//				 and methods
//============================================================================
#pragma once
#include <string>
#include <iostream>
using namespace std;


enum Tip { flightNum, departure, destination, gate };


class Flight
{
private:
	string f_number;
	string destination;
	string departure;
	string gate;

public:

	Flight();
	Flight(string num, string dest, string departure, string gate);
	Flight(const Flight &f);

	string getFNumber();
	string getDestination();
	string getDeparture();
	string getGate();

	void setFNumber(string f);
	void setDestination(string dest);
	void setDeparture(string depart);
	void setGate(string g);

	bool operator ==(Flight &f2);
	bool operator !=(Flight &f2);
	int compare(Flight f2,Tip crit);
	int compareDeparture(Flight &f2);

	friend istream& operator>>(istream &in, Flight &f);
	friend ostream& operator<<(ostream &out,Flight &f);

};
