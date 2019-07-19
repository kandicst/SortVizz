//=======================================================================================
// Name        : IO.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Implementation of a class that is responsible supplying the GUI component 
//				 of the program with information required for a program to run properly,  
//				 and also to write new information to the specified file
//=======================================================================================
#include "IO.h"
#include <FL/fl_ask.H>
using namespace std;

IO::IO(IO & io):
	inPath(io.inPath),
	outPath(io.outPath),
	crit(io.crit),
	type(io.type),
	nums(io.nums),
	viz(io.viz)
{
}

IO::IO(string s1, string s2):
	inPath(s1),outPath(s2)
{
	loadFlights();
}

IO::IO(string s1):
	inPath(s1)
{
	loadFlights();
}


void IO::loadFlights()
	//loading flights info from specified source
{

	for (int i = 0; i < 10; i++) {
		VisualizedNumber vn(i, 0, i, 10);
		viz.push_back(vn);
	}

	return;
	/*
	try {
		nums.clear();
		viz.clear();

		if (strcmp(inPath.c_str(), "") == 0) {		//path not chosen
			return;
		}

		ifstream ifs(inPath);
		int i = 0;
		while (!ifs.eof()) {
			double num;
			ifs >> num;
			nums.push_back(num);
			i += 1;
		}
		
		for (int i = 0; i < nums.size(); i++) {
			viz.push_back(VisualizedNumber(nums[i], 0, i, nums.size()));
		}
	}
	catch (exception& e) {
		PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
		if (fl_ask("The input file you've chosen is invalid.\nDo you want to see how it should be structured?")) {
			system("start Resources\\zzz.pdf");
		}
	}
	*/
}

void IO::writeFlights(vector<VisualizedNumber*> &v,string header)
{
	fl_message_hotspot(0);
	if (v.empty() || strcmp(header.c_str(),"") == 0) {
		PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
		fl_alert("You haven't any sorted flights yet");
		return;
	}

	cout << outPath << endl;
	ofstream myfile(outPath);
	if (myfile.is_open())
	{
		myfile << header << endl;
		for (int i = 0; i < v.size(); i++) {
			//myfile << (v[i]->flight);
		}
		string s = "Flights were successfully writen to: " + outPath;
		fl_message(s.c_str());
		myfile.close();
	}
	else {
		PlaySound(TEXT("Resources\\notification.wav"), NULL, SND_ASYNC);
		fl_alert("There seems to be an issue with the ouput file.\n Please select a new one");
	}
}



void IO::setInPath(string s)
	//changing the input file requires reload of flights and widgets displayed
{
	inPath = s;
	loadFlights();
}

