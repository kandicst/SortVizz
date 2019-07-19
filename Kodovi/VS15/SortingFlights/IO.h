//=======================================================================================
// Name        : IO.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Specification of a class that is responsible supplying the GUI component 
//				 of the program with information required for a program to run properly,  
//				 and also to write new information to the specified file
//=======================================================================================
#pragma once
#include <string.h>
#include <iostream>
#include <FL/Fl_Native_File_Chooser.H>
#include <vector>
#include <set>
#include "VisualizedFlight.h"
using namespace std;

class IO {

public:

	string zaglavlje;
	string inPath = "";
	string outPath = "";
	string crit = "";
	string type = "";
	vector<Flight> letovi;
	vector<VisualizedFlight> viz;

	IO() {}
	IO(IO &io);
	IO(string s1, string s2);
	IO(string s1);

	void check_arguments(int argc, char* argv[]);
	void setInPath(string s);
	void loadFlights();
	void writeFlights(vector<VisualizedFlight*> &v,string header);

};