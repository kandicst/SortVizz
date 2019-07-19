
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Output.H>
#include "GUI.h"

namespace Graph_lib {

//------------------------------------------------------------------------------


	void Button::attach(Window& win)
{
    pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
    own = &win;
}

//------------------------------------------------------------------------------

void CheckBox::attach(Window &win)
{

	pw = new Fl_Check_Button(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
	own = &win;
}

void CheckBox::value(int i)
{
	Fl_Check_Button *c = (Fl_Check_Button *)pw;
	c->value(i);
}

int CheckBox::value()
{
	Fl_Check_Button *c = (Fl_Check_Button *)pw;
	return c->value();
}


//------------------------------------------------------------------------------

void Slider::attach(Window &win)
{
	Fl_Slider *s=  new Fl_Slider(loc.x, loc.y, width, height);
	s->range(50, 150);
	s->type(FL_HOR_NICE_SLIDER);
	s->value(100);
	pw = s;
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
	own = &win;
}

void Slider::value(int i)
{
}

int Slider::value()
{
	Fl_Slider *s = (Fl_Slider *)pw;
	return s->value();
}


//------------------------------------------------------------------------------
void Tab::attach(Window &win)
{
	pw = new Fl_Tabs(loc.x, loc.y, width, height);
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
	own = &win;

}

void Tab::attach(Widget & w)
{
	Fl_Tabs *c = (Fl_Tabs *)pw;
	c->add(w.pw);
}


//------------------------------------------------------------------------------

void Group::attach(Window &win)
{
	pw = new Fl_Group(loc.x, loc.y, width, height, label.c_str());
	pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
	own = &win;

}

void Group::attach(Widget & w)
{
	Fl_Group *c = (Fl_Group *)pw;
	c->add(w.pw);
}

//------------------------------------------------------------------------------

int In_box::get_int()
{
	stringstream ss;
	int intValue;
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	// return atoi(pi.value());
	const char* p = pi.value();
	ss << *p;
	ss >> intValue;
	return intValue;
}


string In_box::get_string()
{
	Fl_Input& pi = reference_to<Fl_Input>(pw);
	// return atoi(pi.value());
	const char* p = pi.value();
	return p;
}
//------------------------------------------------------------------------------

void In_box::attach(Window& win)
{
    pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}


//------------------------------------------------------------------------------

void Out_box::put(int p)
{
	stringstream ss;
	string stringValue;
	ss << p;
	ss >> stringValue;
	reference_to<Fl_Output>(pw).value(stringValue.c_str());
}

//------------------------------------------------------------------------------

void Out_box::put(const string& s)
{
    reference_to<Fl_Output>(pw).value(s.c_str());
}

//------------------------------------------------------------------------------

void Out_box::attach(Window& win)
{
    pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

//------------------------------------------------------------------------------

int Menu::attach(Button& b)
{
    b.width = width;
    b.height = height;

    switch(k) {
    case horizontal:
        b.loc = Point(loc.x+offset,loc.y);
        offset+=b.width;
        break;
    case vertical:
        b.loc = Point(loc.x,loc.y+offset);
        offset+=b.height;
        break;
    }
    selection.push_back(b); // b is NOT OWNED: pass by reference
    return int(selection.size()-1);
}

//------------------------------------------------------------------------------

int Menu::attach(Button* p)
{
    Button& b = *p;
    b.width = width;
    b.height = height;

    switch(k) {
    case horizontal:
        b.loc = Point(loc.x+offset,loc.y);
        offset+=b.width;
        break;
    case vertical:
        b.loc = Point(loc.x,loc.y+offset);
        offset+=b.height;
        break;
    }
    selection.push_back(&b); // b is OWNED: pass by pointer
    return int(selection.size()-1);
}

//------------------------------------------------------------------------------


}; // of namespace Graph_lib
