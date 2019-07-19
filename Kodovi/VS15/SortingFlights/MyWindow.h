//============================================================================
// Name        : MyWindow.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Specification of a class that is responsible for GUI component 
//				 of the program and all its elements
//============================================================================

//#ifndef MY_WINDOW_GUARD
//#define MY_WINDOW_GUARD 1
#pragma once

#include "GUI.h"    
#include "Graph.h"
#include "Sort.h"
#include <vector> 
#include "IO.h"
#include <FL/Fl_Menu_Bar.H>
using namespace std;
using namespace Graph_lib;

//------------------------------------------------------------------------------

struct MyWindow : Window {
	MyWindow(Point x, int w, int h, const string& title);

	bool sorting = false;
	bool sorted = false;
	vector<VisualizedFlight> mainVector;
	IO inOut;
	bool wait_for_button();
	void setIO(IO io);
	void fill(); 

private:
	//Widgets and their respective callbacks for different ways of sorting
	CheckBox quickCheck;
	CheckBox selectionCheck;
	CheckBox fnumberCheck;
	CheckBox destinationCheck;
	CheckBox departureCheck;
	CheckBox gateCheck;
	Slider slider;
	static void cb_qB(Address, Address);	void qB();
	static void cb_selB(Address, Address);	void selB();
	static void cb_fnumB(Address, Address);	void fnumB();
	static void cb_destB(Address, Address);	void destB();
	static void cb_depB(Address, Address);	void depB();
	static void cb_gB(Address, Address);	void gB();
	static void cb_slider(Address, Address); void slide();
	
	//Widgets and their respective callbacks for visualizing
	Button next;
	Button finish;
	Button rewind;
	Button inFile;
	Button outFile;
	Button about;
	static void cb_next(Address, Address);  void nextIter();
	static void cb_finish(Address, Address); void fin();
	static void cb_rewind(Address, Address);  void rew();
	static void cb_inFile(Address, Address);  void newInF();
	static void cb_outFile(Address, Address);  void newOutF();
	static void cb_about(Address, Address);  void author();


	bool initializeSort();
	bool criteriaCheck();
	void displayStat();

	string header;
	SelectionSort ss;
	QuickSort qs;
	float plotSpeed = 105;
	list<Instruction*> instrukcije;

	//vectors with widgets for different criteria of sorting
	vector<VisualizedFlight*> vectorFNUM;
	vector<VisualizedFlight*> vectorDEST;
	vector<VisualizedFlight*> vectorDEP;
	vector<VisualizedFlight*> vectorGATE;
	vector<VisualizedFlight*> outputVector;
	Tip criteria = flightNum;



	void draw();
	
	

};

//------------------------------------------------------------------------------

//#endif // MY_WINDOW_GUARD