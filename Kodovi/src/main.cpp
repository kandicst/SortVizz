//============================================================================
// Name        : main.cpp
// Author      :Stefan Kandic
// Date        : 8.1.2018.
// Copyright   :
// Description : module only responsible for the start of the program
//============================================================================


#include "MyWindow.h"
#include <FL/abi-version.h>
#include <string>
#include <FL/fl_utf8.h>

using namespace std;




int main(int argc, char* argv[]) {

	IO inout;
	inout.loadFlights();

	MyWindow w(Point(450,250),800, 600, "SortVizz");
	w.color(FL_DARK2);
	w.setIO(inout);
	w.wait_for_button();
	

	return 0;
}





