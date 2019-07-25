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
	vector<VisualizedNumber> mainVector;
	IO inOut;
	bool wait_for_button();
	void setIO(IO io);
	void fill(); 

private:
	//Widgets and their respective callbacks for different ways of sorting
	CheckBox bubbleCheck;
	CheckBox insertionCheck;
	CheckBox quickCheck;
	CheckBox selectionCheck;
	Slider slider;
	static void cb_bubbleB(Address, Address);	void bubbleB();
	static void cb_insertionB(Address, Address);	void insertionB();
	static void cb_qB(Address, Address);	void qB();
	static void cb_selB(Address, Address);	void selB();
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
	void displayStat();
	void deleteDynObjects(list<Instruction*> vektor);

	string header;
	SelectionSort ss;
	QuickSort qs;
	BubbleSort bubsort;
	InsertionSort inssort;
	float plotSpeed = 105;
	list<Instruction*> instrukcije;

	//vectors with widgets for different criteria of sorting
	vector<VisualizedNumber*> vectorNUM;
	vector<VisualizedNumber*> outputVector;

	void draw();
};

//------------------------------------------------------------------------------

//#endif // MY_WINDOW_GUARD