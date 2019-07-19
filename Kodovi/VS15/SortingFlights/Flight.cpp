//============================================================================
// Name        : Flight.cpp
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Implementation of the Flight class
//============================================================================

#include "Flight.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>


string trim(std::string str);


Flight::Flight()
{
}

Flight::Flight(string num, string dest, string departure, string gate)
	: f_number(num),destination(dest),departure(departure),gate(gate)
{
}

Flight::Flight(const Flight &f)
{
	f_number = f.f_number;
	destination = f.destination;
	departure = f.departure;
	gate = f.gate;
}

string Flight::getFNumber()
{
	return f_number;
}

string Flight::getDestination()
{
	return destination;
}

string Flight::getDeparture()
{
	return departure;
}

string Flight::getGate()
{
	return gate;
}

void Flight::setFNumber(string f)
{
	f_number = f;
}

void Flight::setDestination(string dest)
{
	destination = dest;
}

void Flight::setDeparture(string depart)
{
	departure = depart;
}

void Flight::setGate(string g)
{
	gate = g;
}



bool Flight::operator==(Flight & f2)
{
	if (f_number.compare(f2.f_number) == 0)
		return true;
	
	return false;
}

bool Flight::operator!=(Flight & f2)
{
	if (f_number.compare(f2.f_number) == 0)
		return false;
	return true;
}

int Flight::compare(Flight f2, Tip crit)
{
	switch (crit) {

	case Tip::flightNum:
		return f_number.compare(f2.getFNumber());
	case Tip::destination:
		return destination.compare(f2.getDestination());
	case Tip::departure:
		return compareDeparture(f2);
	case Tip::gate:
		return gate.compare(f2.getGate());
	}
}

int Flight::compareDeparture(Flight & f2)
{
	if (departure.length() == f2.departure.length()) {
		return departure.compare(f2.departure);
	}
	else if (departure.length() > f2.departure.length()) {
		return 1;
	}
	return -1;
}


vector<string> split(const string &s, char delim = ';') {
	vector<string> result;
	stringstream ss(s);
	string item;
	
	while (getline(ss, item, delim)) {
		item = trim(item);
		result.push_back(item);
	}

	return result;
}



istream & operator >> (istream & in, Flight & f)
{
	string line;
	string s = "Destination Departure Flight No. Gate No.";		
	getline(in, line);

	if (strcmp(line.c_str(),s.c_str())==0) {
		getline(in, line);
		vector<string> data = split(line);
	}

	vector<string> data = split(line);
	if (data.size() != 4) {
		throw runtime_error("err");
	}


	f.setDestination(data[0]);
	f.setDeparture(data[1]);
	f.setFNumber(data[2]);
	f.setGate(data[3]);
	return in;
}

ostream & operator<<(ostream & out, Flight & f)
{
	out << f.getFNumber() << " " << f.getDestination() << " " << f.getDeparture() << " " << f.getGate() << endl;
	return out;
}


//functions for deleting whitespace characters in string
string trim(std::string str) {
	return std::regex_replace(str, std::regex("^\\s+"), std::string(""));
}
