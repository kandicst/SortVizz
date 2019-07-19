#include "Instruction.h"
#include <Windows.h>
#include <MMSystem.h>
#include "GUI.h"    
#include "Graph.h"


void ColorChange::do_it()
	//changes the color of a widget representing a flight
{
	//s2 default - laser2 moze kao
	PlaySound(TEXT("Resources\\laser2.wav"), NULL, SND_ASYNC || SND_SYSTEM);
	vf->boja = this->color;
}


void WidgetSwap::do_it()
	//swaps the places of two widgets 
{
	PlaySound(TEXT("Resources\\s2.wav"), NULL, SND_ASYNC || SND_SYSTEM);
	int x1, x2;
	x1 = vf2->x() - vf->x();
	x2 = vf->x() - vf2->x();
	
	vf->move(x1, 0);
	vf2->move(x2, 0);

	//redraw of window should be called after this function
}


void ColorSwap::do_it()
	//changes the color of two widgets at the same time
{
	PlaySound(TEXT("laser2.wav"), NULL, SND_ASYNC || SND_SYSTEM);
	vf->boja = this->color1;
	vf2->boja = this->color2;
}

void RevertColor::do_it()
	//changes the color of multiple widgets to the specified Fl_Color
{
	for (int i = 0; i < vector.size(); i++) {
		vector[i]->boja = color;
	}
}
