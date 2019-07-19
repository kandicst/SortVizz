//=======================================================================================
// Name        : VisualizedNumber.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Class that represents a main widget in the application
//=======================================================================================
#pragma once
#include "Graph.h"
#include "Flight.h"
using namespace Graph_lib;


class VisualizedNumber : public Fl_Widget{


public:

	double value;
	Flight flight;
	int unsortedIndex;
	int sortedIndex;
	Fl_Color boja = FL_DARK_CYAN;
	int numOfFlightsTotal;

	VisualizedNumber(double value, int sor, int unsor,int num);
	VisualizedNumber(double value, int sor, int unsor);
	VisualizedNumber(const VisualizedNumber &vf);
	
	void draw();
	void write(const char* s);
	void move(int jean, int dva);

	bool operator =(VisualizedNumber &vf);
	

};



