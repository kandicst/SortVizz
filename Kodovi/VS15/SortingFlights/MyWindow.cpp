//==============================================================================
// Name        : MyWindow.cpp
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Implementation of a class that is responsible for GUI component 
//				 of the program and all its elements
//==============================================================================

#include "MyWindow.h"
#include <FL/Fl_PNG_Image.H>
#include <math.h> 
#include <windows.h>
#include <FL/Fl_Box.H>
#include <FL/Fl_draw.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Round_Button.H>

using namespace Graph_lib;

//------------------------------------------------------------------------------


MyWindow::MyWindow(Point x,int w, int h, const string& title) :
	Window(x,w, h, title),
	next(Point(w / 2 - 17, 510), 35, 20, "@>", cb_next),
	finish(Point(w / 2 - 17 + 50, 510), 35, 20, "@>|", cb_finish),
	rewind(Point(w / 2 - 17 - 50, 510), 35, 20, "@|<", cb_rewind),
	header(""),
	quickCheck(Point(50, 400), 90, 25, "Quick sort", cb_qB),
	selectionCheck(Point(50, 430), 90, 25, "Selection sort", cb_selB),

	fnumberCheck(Point(200, 370), 90, 25, "Flight Num", cb_fnumB),
	departureCheck(Point(200, 400), 90, 25, "Departure", cb_depB),
	destinationCheck(Point(200, 430), 90, 25, "Destination", cb_destB),
	gateCheck(Point(200, 460), 90, 25, "Gate", cb_gB),
	about(Point(0, 0), 65, 25, "@FLTK", cb_about),
	inFile(Point(65, 0), 65, 25, "@fileopen", cb_inFile),
	outFile(Point(130, 0), 65, 25, "@filesaveas", cb_outFile),
	slider(Point(68, 510), 200, 20, cb_slider)
{


	fill();
	attach(next);
	((Fl_Button*)next.pw)->shortcut(FL_Enter); 
	attach(rewind);
	attach(finish);
	attach(quickCheck);
	attach(selectionCheck);
	attach(fnumberCheck); fnumberCheck.value(1);
	attach(destinationCheck);
	attach(gateCheck);
	attach(departureCheck);
	attach(slider);
	attach(inFile);
	attach(outFile);
	attach(about);
	Fl_Text_Display *slow = new Fl_Text_Display(85, 550, 0, 0, "slow");
	Fl_Text_Display *fast = new Fl_Text_Display(250, 550, 0, 0, "fast");
	this->add(slow); this->add(fast); 

}


void MyWindow::draw()
{

	Window::draw();

	switch (criteria) {

	case flightNum:
		for (int i = 0; i < vectorFNUM.size(); i++) {
			vectorFNUM[i]->draw();
			vectorFNUM[i]->write(vectorFNUM[i]->flight.getFNumber().c_str());
		}
		break;

	case destination:
		for (int i = 0; i < vectorDEST.size(); i++) {
			vectorDEST[i]->draw();
			vectorDEST[i]->write(vectorDEST[i]->flight.getDestination().c_str());
		}
		break;

	case departure:
		for (int i = 0; i < vectorDEP.size(); i++) {
			vectorDEP[i]->draw();
			vectorDEP[i]->write(vectorDEP[i]->flight.getDeparture().c_str());
		}
		break;

	case gate:
		for (int i = 0; i < vectorGATE.size(); i++) {
			vectorGATE[i]->draw();
			vectorGATE[i]->write(vectorGATE[i]->flight.getGate().c_str());
		}
		break;

	}
}


//------------------------------------------------------------------------------


void MyWindow::cb_next(Address, Address pw)
{
	reference_to<MyWindow>(pw).nextIter();
}


//------------------------------------------------------------------------------

void MyWindow::fill()
	//provides all info to specified vectors that contain widgets for different criterium of sorting
{
	vectorFNUM.clear(); vectorDEST.clear(); vectorDEP.clear(); vectorGATE.clear();

	for (int i = 0; i < mainVector.size(); i++) {

		//FNUM
		int m = 0;
		for (int j = 0; j < mainVector.size(); j++) {
			if ((mainVector[i].flight.getFNumber().compare(mainVector[j].flight.getFNumber())) > 0) {
				m++;
			}
			//if (mainVector[i].flight.getFNumber() > mainVector[j].flight.getFNumber())
		}
		vectorFNUM.push_back(new VisualizedFlight(mainVector[i].flight, m, i, mainVector.size()));

		//DEST
		m = 0;
		for (int j = 0; j < mainVector.size(); j++) {
			if (mainVector[i].flight.getDestination() > mainVector[j].flight.getDestination())
				m++;
		}
		vectorDEST.push_back(new VisualizedFlight(mainVector[i].flight, m, i, mainVector.size()));

		//DEP
		m = 0;
		for (int j = 0; j < mainVector.size(); j++) {
			if (mainVector[i].flight.compareDeparture(mainVector[j].flight) > 0) {
				m++;
			}
		}

		vectorDEP.push_back(new VisualizedFlight(mainVector[i].flight, m, i, mainVector.size()));

		//GATE
		m = 0;
		for (int j = 0; j < mainVector.size(); j++) {
			if (mainVector[i].flight.getGate() > mainVector[j].flight.getGate())
				m++;
		}

		vectorGATE.push_back(new VisualizedFlight(mainVector[i].flight, m, i, mainVector.size()));

	}

}

//------------------------------------------------------------------------------

bool MyWindow::criteriaCheck()
	// is at least one checkbox for criteria selected by the user?
{
	if (fnumberCheck.value() || destinationCheck.value() || departureCheck.value() || gateCheck.value())
		return true;

	PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
	fl_alert("You need to select sorting criteria first");
	return false;
}


//------------------------------------------------------------------------------

bool MyWindow::initializeSort() 
	//gathering all the instructions needed to visualize sorting
{

	if (sorted) {
		PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
		if (fl_ask("Flights are already sorted, do you want to randomize them first?")) {
			rew();
		}
		else {
			return false;
		}
	}

	if (!sorting) {

		int ln = round(log(mainVector.size()))*mainVector.size();
		fl_message_hotspot(0);
		instrukcije.clear();
		switch (criteria) {

		case flightNum:
			if (quickCheck.value()) {
				qs.sort(vectorFNUM, flightNum, instrukcije);
				outputVector = vectorFNUM;
				header = "Algorithm used:\tQuick sort\nCriteria used:\tFlight number\nExpected number of comparisons: nlog(n) => " +
					to_string(ln) + "\nActual number of comparisons:" + to_string(qs.getNumCmps()) + "\nNumber of swaps: " + to_string(qs.getNumSwaps());
				
			}
			else if (selectionCheck.value()) {
				ss.sort(vectorFNUM, flightNum, instrukcije);
				outputVector = vectorFNUM;
				header = "Algorithm used:\t\Selection sort\nCriteria :\t Flight Number\nExpected num of comparisons: (n^2-n)/2 => " +
					to_string((mainVector.size()*mainVector.size() - mainVector.size()) / 2) + "\nActual number of comparisons: " + to_string(ss.getNumCmps()) +
					"\nNumber of swaps:    " + to_string(ss.getNumSwaps());

			}
			else {
				PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
				fl_alert("You need to select a sorting algorithm");
				return false;
			}
			break;

		case destination:
			if (quickCheck.value()) {
				qs.sort(vectorDEST, destination, instrukcije);
				outputVector = vectorDEST;
				header = "Algorithm used:\tQuick sort\nCriteria used:\tDestination\nExpected number of comparisons: nlog(n) => " +
					to_string(ln) + "\nActual number of comparisons:" + to_string(qs.getNumCmps()) + "\nNumber of swaps: " + to_string(qs.getNumSwaps());
				
			}
			else if (selectionCheck.value()) {
				ss.sort(vectorDEST, destination, instrukcije);
				outputVector = vectorDEST;
				header = "Algorithm used:\t\Selection sort\nCriteria :\t Destination\nExpected num of comparisons: (n^2-n)/2 => " +
					to_string((mainVector.size()*mainVector.size() - mainVector.size()) / 2) + "\nActual number of comparisons: " + to_string(ss.getNumCmps()) +
					"\nNumber of swaps:    " + to_string(ss.getNumSwaps());

			}
			else {
				PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
				fl_alert("You need to select a sorting algorithm");
				return false;
			}
			break;

		case departure:
			if (quickCheck.value()) {
				qs.sort(vectorDEP, departure, instrukcije);
				outputVector = vectorDEP;
				header = "Algorithm used:\tQuick sort\nCriteria used:\tDeparture\nExpected number of comparisons: nlog(n) => " +
					to_string(ln) + "\nActual number of comparisons:" + to_string(qs.getNumCmps()) + "\nNumber of swaps: " + to_string(qs.getNumSwaps());
				
			}
			else if (selectionCheck.value()) {
				ss.sort(vectorDEP, departure, instrukcije);
				outputVector = vectorDEP;
				header = "Algorithm used:\t\Selection sort\nCriteria :\t Departure\nExpected num of comparisons: (n^2-n)/2 => " +
					to_string((mainVector.size()*mainVector.size() - mainVector.size()) / 2) + "\nActual number of comparisons: " + to_string(ss.getNumCmps()) +
					"\nNumber of swaps:    " + to_string(ss.getNumSwaps());

			}
			else {
				PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
				fl_alert("You need to select a sorting algorithm");
				return false;
			}
			break;

		case gate:
			if (quickCheck.value()) {
				qs.sort(vectorGATE, gate, instrukcije);
				outputVector = vectorGATE;
				header = "Algorithm used:\tQuick sort\nCriteria used:\tGate number\nExpected number of comparisons: nlog(n) => " +
					to_string(ln) + "\nActual number of comparisons:" + to_string(qs.getNumCmps()) + "\nNumber of swaps: " + to_string(qs.getNumSwaps());
			}
			else if (selectionCheck.value()) {
				ss.sort(vectorGATE, gate, instrukcije);
				outputVector = vectorGATE;
				header = "Algorithm used:\t\Selection sort\nCriteria :\t Gate number\nExpected num of comparisons: (n^2-n)/2 => " +
					to_string((mainVector.size()*mainVector.size() - mainVector.size()) / 2) + "\nActual number of comparisons: " + to_string(ss.getNumCmps()) +
					"\nNumber of swaps:    " + to_string(ss.getNumSwaps());

			}
			else {
				PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
				fl_alert("You need to select a sorting algorithm");
				return false;
			}
			break;
		}
	}

	return true;
}

//------------------------------------------------------------------------------

void MyWindow::nextIter()
{

	if (!criteriaCheck())
		return;
	if (!initializeSort())
		return;
	if (mainVector.empty()) {
		PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
		fl_alert("There's nothing to sort!");
		return;
	}


	sorting = true;

	list<Instruction*>::iterator it = instrukcije.begin();
	if (it != instrukcije.end()) {
		(*it)->do_it();
		this->redraw();
		instrukcije.erase(instrukcije.begin());
	}
	else {
		displayStat();
	}




}
//------------------------------------------------------------------------------

void MyWindow::cb_finish(Address, Address pw)
{
	reference_to<MyWindow>(pw).fin();
	

}

void MyWindow::fin()
{

	if (!criteriaCheck())
		return;
	if (!initializeSort())
		return;
	if (mainVector.empty()) {
		PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
		fl_alert("There's nothing to sort!");
		return;
	}

	sorting = true;

	list<Instruction*>::iterator it = instrukcije.begin();

	for(;it!=instrukcije.end();it++){
		(*it)->do_it();
		this->redraw();

		if (Fl::ready()) {
			Fl::flush();
			if (Fl::check) {}
		}
		Sleep(plotSpeed);
	}
	instrukcije.clear();

	displayStat();
}


//------------------------------------------------------------------------------


void MyWindow::displayStat()
	//displays statistics of the finished sorting
{
	string size = to_string(mainVector.size());
	fl_message_hotspot(0);
	PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
	if (quickCheck.value()) {

		int ln = round(log(mainVector.size()))*mainVector.size();
		string s = "Sorting has successfully finished!\n\nAlgorithm used:Quick sort\nExpected number of comparisons: nlog(n) => " +
			to_string(ln) + "\nActual number of comparisons:" + to_string(qs.getNumCmps()) + "\nNumber of swaps: " + to_string(qs.getNumSwaps());
		fl_message(s.c_str());
	}
	else {
		string s = "Sorting has successfully finished!\n\nAlgorithm used:\t\Selection sort\nExpected num of comparisons: (n^2-n)/2 => " +
			to_string((mainVector.size()*mainVector.size() - mainVector.size()) / 2) + "\nActual number of comparisons: " + to_string(ss.getNumCmps()) +
			"\nNumber of swaps:    " + to_string(ss.getNumSwaps());

		fl_message(s.c_str());
	}
	sorting = false;
	sorted = true;
}



//------------------------------------------------------------------------------

void MyWindow::cb_rewind(Address, Address pw)
{
	reference_to<MyWindow>(pw).rew();
}

void MyWindow::rew()
{
	fill();
	sorted = false;
	sorting = false;
	this->redraw();
}



//------------------------------------------------------------------------------


void MyWindow::cb_qB(Address, Address pw)
{
	reference_to<MyWindow>(pw).qB();
}


void MyWindow::qB()
{
	if (sorting) {
		quickCheck.value(abs(quickCheck.value() - 1)); // 0->1 , 1->0
	
	}
	else if (selectionCheck.value() && quickCheck.value()) {
		selectionCheck.value(0);
	}
}



//------------------------------------------------------------------------------



void MyWindow::cb_selB(Address, Address pw)
{
	reference_to<MyWindow>(pw).selB();
}


void MyWindow::selB()
{
	if (sorting) {
		selectionCheck.value(abs(selectionCheck.value() - 1)); // 0->1 , 1->0
	
	}
	else if (quickCheck.value() && selectionCheck.value()) {
		quickCheck.value(0);
	}
}


//------------------------------------------------------------------------------


void MyWindow::cb_fnumB(Address, Address pw)
{
	reference_to<MyWindow>(pw).fnumB();
}

void MyWindow::fnumB()
{
	//if sorting currently in progress
	if (sorting) {
		fnumberCheck.value(abs(fnumberCheck.value() - 1));
		return;
	}

	//one is checked
	else if (departureCheck.value() || destinationCheck.value() || gateCheck.value() && fnumberCheck.value()) {
		departureCheck.value(0);
		destinationCheck.value(0);
		gateCheck.value(0);
	}

	criteria = flightNum;
	sorted = false;
	this->redraw();
}

//------------------------------------------------------------------------------

void MyWindow::cb_destB(Address, Address pw)
{
	reference_to<MyWindow>(pw).destB();
}

void MyWindow::destB()
{
	if (sorting) {
		destinationCheck.value(abs(destinationCheck.value() - 1));
		return;
	}
	else if (departureCheck.value() || fnumberCheck.value() || gateCheck.value() && destinationCheck.value()) {
		departureCheck.value(0);
		fnumberCheck.value(0);
		gateCheck.value(0);

	}
	criteria = destination;
	sorted = false;
	this->redraw();
}

//------------------------------------------------------------------------------

void MyWindow::cb_depB(Address, Address pw)
{
	reference_to<MyWindow>(pw).depB();
}

void MyWindow::depB()
{
	if (sorting) {
		departureCheck.value(abs(departureCheck.value() - 1));
		return;
	}
	else if (gateCheck.value() || fnumberCheck.value() || destinationCheck.value() && departureCheck.value()) {
		gateCheck.value(0);
		fnumberCheck.value(0);
		destinationCheck.value(0);
	}

	criteria = departure;
	sorted = false;
	this->redraw();

}

//------------------------------------------------------------------------------

void MyWindow::cb_gB(Address, Address pw)
{
	reference_to<MyWindow>(pw).gB();
}

void MyWindow::gB()
{
	if (sorting) {
		gateCheck.value(abs(gateCheck.value() - 1));
		return;
	}

	else if (departureCheck.value() || fnumberCheck.value() || destinationCheck.value() && gateCheck.value()) {
		departureCheck.value(0);
		fnumberCheck.value(0);
		destinationCheck.value(0);
	}

	criteria = gate;
	sorted = false;
	this->redraw();
}

//------------------------------------------------------------------------------


void MyWindow::cb_slider(Address, Address pw)
{
	reference_to<MyWindow>(pw).slide();
}

void MyWindow::slide()
{
	Fl_Slider *s = (Fl_Slider*)slider.pw;
	plotSpeed = abs(200 - s->value()) + 10;

}

//------------------------------------------------------------------------------


bool MyWindow::wait_for_button()
{

	size_range(800, 600, 800, 600);
	show();
	return(Fl::run());
}

//------------------------------------------------------------------------------

void MyWindow::setIO(IO io)
{
	inOut = io;
	mainVector = vector<VisualizedFlight>(io.viz);
	sorted = false;
	fill();
	

	if (strcmp(io.crit.c_str(), "fnum") == 0) {
		fnumberCheck.value(1); fnumB();
	}
	else if (strcmp(io.crit.c_str(), "dest") == 0) {
		destinationCheck.value(1); destB();
	}
	else if (strcmp(io.crit.c_str(), "dep") == 0) {
		departureCheck.value(1); depB();
	}
	else if (strcmp(io.crit.c_str(), "gate") == 0) {
		gateCheck.value(1); gB();
	}


	if (strcmp(io.type.c_str(), "qs") == 0) {
		quickCheck.value(1);
	}
	else if (strcmp(io.type.c_str(), "ss") == 0) {
		selectionCheck.value(1);
	}

	redraw();
}	



//------------------------------------------------------------------------------



void MyWindow::cb_inFile(Address, Address pw) {
	reference_to<MyWindow>(pw).newInF();
}

void MyWindow::newInF() 
	//choosing a file to load the flights from
{
	Fl_Native_File_Chooser fc;
	fc.title("Please select the input file ");
	fc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fc.filter("Text\t*.txt\n");
	switch (fc.show()) {

	case -1:
		printf("ERROR: %s\n", fc.errmsg());
		break;  // ERROR
	case  1:
		break;  // CANCEL
	default:
		inOut.setInPath(fc.filename());
		mainVector = vector<VisualizedFlight>(inOut.viz);
		fill();
		sorted = false;
		header = "";
		this->redraw();
		printf("PICKED: %s\n", fc.filename());
		break;  // FILE CHOSEN
	}
}

//------------------------------------------------------------------------------


 void MyWindow::cb_outFile(Address, Address pw) {
	 reference_to<MyWindow>(pw).newOutF();
}

void MyWindow::newOutF()
	// choosing output file, or writing to one if it has been selected
{
	if (inOut.outPath.compare("") !=0 ) {
		inOut.writeFlights(outputVector,header);
		return;
	}

	Fl_Native_File_Chooser fc;
	fc.title("Please select the output file: ");
	fc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fc.filter("Text\t*.txt\n");
	switch (fc.show()) {

	case -1:
		printf("ERROR: %s\n", fc.errmsg());
		break;  // ERROR
	case  1:
		inOut.outPath = "";
		printf("CANCEL\n");
		return;
		break;  // CANCEL
	default:
		inOut.outPath = fc.filename();
		printf("PICKED: %s\n", fc.filename());
		break;  // FILE CHOSEN
	}

	if (strcmp("", header.c_str()) != 0) {
		//already sorted
		inOut.writeFlights(outputVector, header);
	}
}

//------------------------------------------------------------------------------


void MyWindow::cb_about(Address, Address pw) {

	reference_to<MyWindow>(pw).author();
}

void MyWindow::author() {
	fl_message_hotspot(0);
	string s1 = "Project info:\n\tTheme:\tVisualizing sort algorithms\n\tClass: Object oriented programming 2\n\tProgramming language: C++ 11\n\tLibrary used: FLTK 1.3.3\n\n";
	string s2 = "Author info:\n\tName:\tStefan Kandic\n\tStudent ID: SW 73/2017";
	fl_message((s1 + s2).c_str());
}

//------------------------------------------------------------------------------



//zi end