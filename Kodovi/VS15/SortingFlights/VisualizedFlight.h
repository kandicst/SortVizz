//=======================================================================================
// Name        : VisualizedFlight.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Class that represents a main widget in the application
//=======================================================================================
#pragma once
#include "Graph.h"
#include "Flight.h"
using namespace Graph_lib;


class VisualizedFlight : public Fl_Widget{


public:

	Flight flight;
	int unsortedIndex;
	int sortedIndex;
	Fl_Color boja = FL_DARK_CYAN;
	int numOfFlightsTotal;

	VisualizedFlight(Flight f, int sor, int unsor,int num);
	VisualizedFlight(Flight f, int sor, int unsor);
	VisualizedFlight(const VisualizedFlight &vf);
	
	void draw();
	void write(const char* s);
	void move(int jean, int dva);

	bool operator =(VisualizedFlight &vf);
	

};



