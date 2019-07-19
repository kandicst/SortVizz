
#include "Window.h"


using namespace Graph_lib;



struct MOJ : Fl_Window {

	MOJ(int w, int h, const char *s);

	bool sorting = false;// da li je korisnik zapoceo sortiranje
	bool sorted = false;

	Fl_Tabs *tabs;
	Fl_Group *vis;
	Fl_Group *autor;

	//checkboxovi za izbor sortiranja
	Fl_Check_Button *quickB;
	Fl_Check_Button *selcectionB;
	Fl_Check_Button *fnumberB;
	Fl_Check_Button *destinationB;
	Fl_Check_Button *departureB;
	Fl_Check_Button *gateB;

	Fl_Return_Button *randomize;

	Fl_Slider *slider;
	float sortSpeed;

	Fl_Button *nextIter;
	Fl_Button *finish;
	Fl_Button *rewind;

	void kreiraj();






};

