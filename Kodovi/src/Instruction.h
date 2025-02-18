//=======================================================================================
// Name        : Instruction.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Atomic task that needs to be done in order to visualize a process of sorting
//=======================================================================================
#pragma once
#include "VisualizedNumber.h"

class Instruction {
public:
	
	Instruction()
	{}

	Instruction(VisualizedNumber *f):
		vf(f)
	{}
	Instruction(const Instruction&f) :
		vf(f.vf)
	{}
	bool operator ==(Instruction &i) {
		return false;
	}

	VisualizedNumber *vf;
	virtual void do_it() = 0;
	
};

//------------------------------------------------------------------------------

class ColorChange :public Instruction {
public:
	
	ColorChange(VisualizedNumber *vf, Fl_Color c):
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
	
	ColorSwap(VisualizedNumber *f1, Fl_Color c1, VisualizedNumber *f2, Fl_Color c2):
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
	VisualizedNumber *vf2;
	Fl_Color color1;
	Fl_Color color2;

};

//------------------------------------------------------------------------------

class WidgetSwap : public Instruction {
public:


	WidgetSwap(VisualizedNumber *f1, VisualizedNumber *f2):
		Instruction(f1),vf2(f2)
	{}

	WidgetSwap(const WidgetSwap&ws):
		Instruction(ws.vf), vf2(ws.vf2)
	{}
	bool operator ==(WidgetSwap &i) {
		return false;
	}
	void do_it();
	VisualizedNumber *vf2;

};

//------------------------------------------------------------------------------

class RevertColor: public Instruction {
public:
	
	RevertColor(vector<VisualizedNumber*> &v,Fl_Color fc) :
		vector(v),color(fc)
	{}

	vector<VisualizedNumber*> vector;
	Fl_Color color;
	void do_it();
};