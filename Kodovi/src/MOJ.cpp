#include "MOJ.h"
//#include <FL/fl_draw.H>


void whenPushed(Fl_Widget* w, void* p);
void selection_cb(Fl_Widget* w, void *p);
void quick_cb(Fl_Widget* w, void* p);
void gate_cb(Fl_Widget* w, void* p);
void destination_cb(Fl_Widget* w, void* p);
void departure_cb(Fl_Widget* w, void* p);
void fnumber_cb(Fl_Widget* w, void* p);
void slider_cb(Fl_Widget* w, void* p);


void MOJ::kreiraj() {
	quickB = new Fl_Check_Button(50, 400, 90, 25, "Quick sort"); quickB->callback(quick_cb, this);
	selcectionB = new Fl_Check_Button(50, 430, 90, 25, "Selection sort"); selcectionB->callback(selection_cb, this);
	Fl_Button *b1 = new Fl_Button(50, 60, 90, 25, "Button B1"); b1->color(88 + 1);
	Fl_Button *b2 = new Fl_Button(150, 60, 90, 25, "Button B2"); b2->color(88 + 3);
	vis = new Fl_Group(10, 35, 800, 600, "Visualizer");
	vis->add(quickB);
	vis->add(selcectionB);
	autor = new Fl_Group(10, 35, 500 - 10, 200 - 35, "O Autoru");
	autor->add(b1);
	autor->add(b2);



	tabs = new Fl_Tabs(10, 10, 800, 600);
	tabs->add(autor);
	tabs->add(vis);
	this->add(tabs);
}


MOJ::MOJ( int w, int h, const char *s):
	 Fl_Window (w, h, s)
{
	tabs = new Fl_Tabs(10, 10, 800, 600);
	{
		// Aaa tab

		vis = new Fl_Group(10, 35, 800, 600, "Visualizer");
		{
			
			quickB = new Fl_Check_Button(50, 400, 90, 25, "Quick sort"); quickB->callback(quick_cb,this);
			selcectionB = new Fl_Check_Button(50, 430, 90, 25, "Selection sort"); selcectionB->callback(selection_cb,this);
			fnumberB = new Fl_Check_Button(200, 370, 90, 25, "Flight Num"); fnumberB->callback(fnumber_cb, this);
			departureB = new Fl_Check_Button(200, 400, 90, 25, "Departure"); departureB->callback(departure_cb, this);
			destinationB = new Fl_Check_Button(200, 430, 90, 25, "Destination"); destinationB->callback(destination_cb, this);
			gateB = new Fl_Check_Button(200, 460, 90, 25, "Gate"); gateB->callback(gate_cb, this);
			slider = new Fl_Slider(68, 510, 200, 20); slider->callback(slider_cb, this);
			slider->type(FL_HOR_NICE_SLIDER); slider->range(0.1, 1); slider->value(0.55);
			Fl_Text_Display *slow = new Fl_Text_Display(85, 550, 0, 0, "slow");
			Fl_Text_Display *fast = new Fl_Text_Display(250, 550, 0, 0, "fast");
			
			nextIter = new Fl_Button(this->w()/2 - 17,510, 35, 20, "@>"); nextIter->shortcut(FL_Enter);
			finish = new Fl_Button(this->w() / 2 - 17 + 50, 510, 35, 20, "@>|");
			rewind = new Fl_Button(this->w() / 2 - 17 - 50, 510, 35, 20, "@|<");
			//fl_draw("gsags", 550, 333);
			//nextIter = new Fl_Button(300, 510, 50, 10, "@->");
			
		
		}
		vis->end();

		// Bbb tab
		autor = new Fl_Group(10, 35, 500 - 10, 200 - 35, "O Autoru");
		{
			Fl_Button *b1 = new Fl_Button(50, 60, 90, 25, "Button B1"); b1->color(88 + 1);
			Fl_Button *b2 = new Fl_Button(150, 60, 90, 25, "Button B2"); b2->color(88 + 3);
			Fl_Button *b3 = new Fl_Button(250, 60, 90, 25, "Button B3"); b3->color(88 + 5);
			Fl_Button *b4 = new Fl_Button(50, 90, 90, 25, "Button B4"); b4->color(88 + 2);
			Fl_Button *b5 = new Fl_Button(150, 90, 90, 25, "Button B5"); b5->color(88 + 4);
			Fl_Button *b6 = new Fl_Button(250, 90, 90, 25, "Button B6"); b6->color(88 + 6);
		}
		autor->end();

	}
	tabs->end();
	this->end();
}



void whenPushed(Fl_Widget* w, void* p)
{
	Fl_Check_Button *a = (Fl_Check_Button*)p;
	a->parent()->redraw();
	printf("Ouch!\n");
}

void selection_cb(Fl_Widget* w, void *p) {
	MOJ *aaa = (MOJ*) p;
	if (aaa->sorting) {
		aaa->selcectionB->value(abs(aaa->selcectionB->value() - 1));
		printf("HEJ");
	}
	else if (aaa->selcectionB->value() && aaa->quickB->value()) {
		aaa->quickB->value(0);
	}
}

void quick_cb(Fl_Widget* w, void* p) {
	MOJ *aaa = (MOJ*)p;
	if (aaa->sorting) {
		aaa->quickB->value(abs(aaa->quickB->value()-1)); // 0->1 , 1->0
		printf("HEJ");
	}
	else if (aaa->selcectionB->value() && aaa->quickB->value()) {
		aaa->selcectionB->value(0);
	}
}


void fnumber_cb(Fl_Widget* w, void* p) {
	MOJ *win = (MOJ*)p;
	if (win->sorting) {
		win->fnumberB->value(abs(win->fnumberB->value() - 1));
	}
	else if(win->departureB->value() || win->destinationB->value() || win->gateB->value() && win->fnumberB->value()){
		win->departureB->value(0);
		win->destinationB->value(0); 
		win->gateB->value(0);
	}

}

void departure_cb(Fl_Widget* w, void* p) {
	MOJ *win = (MOJ*)p;
	if (win->sorting) {
		win->departureB->value(abs(win->departureB->value() - 1));
	}
	else if (win->departureB->value() && win->destinationB->value() || win->gateB->value() || win->fnumberB->value()) {
		win->fnumberB->value(0); win->destinationB->value(0); win->gateB->value(0);
	}
}

void destination_cb(Fl_Widget* w, void* p) {
	MOJ *win = (MOJ*)p;
	if (win->sorting) {
		win->destinationB->value(abs(win->destinationB->value() - 1));
	}
	else if (win->departureB->value() || win->fnumberB->value() || win->gateB->value() && win->destinationB->value()) {
		win->fnumberB->value(0); win->departureB->value(0); win->gateB->value(0);
	}

}

void gate_cb(Fl_Widget* w, void* p) {
	MOJ *win = (MOJ*)p;
	if (win->sorting) {
		win->gateB->value(abs(win->gateB->value() - 1));
	}
	else if (win->departureB->value() || win->fnumberB->value() || win->destinationB->value() && win->gateB->value()) {
		win->fnumberB->value(0); win->departureB->value(0); win->destinationB->value(0);
	}

}

void slider_cb(Fl_Widget* w, void* p) {
	MOJ *win = (MOJ*)p;
	win->sortSpeed = win->slider->value();
}