//=======================================================================================
// Name        : VisualizedNumber.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Class that represents a main widget in the application
//=======================================================================================
#pragma once
#include "Graph.h"
#include <iostream>
using namespace Graph_lib;


class VisualizedNumber : public Fl_Widget{


public:

	int value;
	int unsortedIndex;
	int sortedIndex;
	Fl_Color boja = FL_DARK_CYAN;
	int numOfFlightsTotal;

	VisualizedNumber(double value_, int sor, int unsor,int num);
	VisualizedNumber(double value_, int sor, int unsor);
	VisualizedNumber(const VisualizedNumber &vf);
	
	void draw();
	void write();
	void move(int jean, int dva);

	VisualizedNumber& operator =(VisualizedNumber &vf);
	

};



