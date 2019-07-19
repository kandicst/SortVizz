//=======================================================================================
// Name        : Instruction.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Specification of a class that represents an atomic task that needs to be
//				 done in order to visualize a process of sorting
//=======================================================================================
#pragma once
#include "VisualizedFlight.h"

class Instruction {
public:
	
	Instruction()
	{}

	Instruction(VisualizedFlight *f):
		vf(f)
	{}
	Instruction(const Instruction&f) :
		vf(f.vf)
	{}
	bool operator ==(Instruction &i) {
		return false;
	}

	VisualizedFlight *vf;
	virtual void do_it() = 0;
	
};

//------------------------------------------------------------------------------

class ColorChange :public Instruction {
public:
	
	ColorChange(VisualizedFlight *vf, Fl_Color c):
		Instruction(vf),color(c)
	{}
	
	ColorChange(const ColorChange&f1):
		Instruction(f1.vf),color(f1.color)
	{}
	bool operator ==(ColorChange &i) {
		return false;
	}
	Fl_Color color;
	void do_it();

};

//------------------------------------------------------------------------------

class ColorSwap :public Instruction {
public:
	
	ColorSwap(VisualizedFlight *f1, Fl_Color c1, VisualizedFlight *f2, Fl_Color c2):
		Instruction(f1),color1(c1),
		vf2(f2),color2(c2)
	{}

	ColorSwap(const ColorSwap &mc):
		Instruction(mc.vf), color1(mc.color1),
		vf2(mc.vf2), color2(mc.color2)
	{}
	bool operator ==(ColorSwap &i) {
		return false;
	}
	void do_it();
	VisualizedFlight *vf2;
	Fl_Color color1;
	Fl_Color color2;

};

//------------------------------------------------------------------------------

class WidgetSwap : public Instruction {
public:


	WidgetSwap(VisualizedFlight *f1, VisualizedFlight *f2):
		Instruction(f1),vf2(f2)
	{}

	WidgetSwap(const WidgetSwap&ws):
		Instruction(ws.vf), vf2(ws.vf2)
	{}
	bool operator ==(WidgetSwap &i) {
		return false;
	}
	void do_it();
	VisualizedFlight *vf2;

};

//------------------------------------------------------------------------------

class RevertColor: public Instruction {
public:
	
	RevertColor(vector<VisualizedFlight*> &v,Fl_Color fc) :
		vector(v),color(fc)
	{}

	vector<VisualizedFlight*> vector;
	Fl_Color color;
	void do_it();
};