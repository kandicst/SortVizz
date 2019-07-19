//============================================================================
// Name        : Sort.cpp
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Implementation of the sort classes
//============================================================================

#include "Sort.h"
#include <Windows.h>
#include <MMSystem.h>

using namespace std;



unsigned long Sort::getNumCmps()
{
	return num_cmps;
}

unsigned long Sort::getNumSwaps()
{
	return num_swaps;
}


void SelectionSort::sort(std::vector<VisualizedFlight*>&data, Tip en, list<Instruction*> &instructions)
{
	num_cmps = 0;
	num_swaps = 0;
	instructions.clear();
	for (int i = 0; i < data.size(); i++)
	{
		// Find the minimum element in unsorted array 
		int min = i;
		instructions.push_back(new ColorChange(data[min], FL_DARK_RED));
		for (int j = i + 1; j < data.size(); j++) {
			instructions.push_back(new ColorChange(data[j], FL_YELLOW));
			num_cmps += 1;
			if(data[j]->flight.compare(data[min]->flight, en)  < 0){
				instructions.push_back(new ColorSwap(data[min], FL_DARK_CYAN, data[j], FL_DARK_RED));
				min = j;
			}
			else {
				instructions.push_back(new ColorChange(data[j], FL_DARK_CYAN));
			}
		}
		if (min != i) {
			num_swaps += 1;
			swap(data[min], data[i]);
			instructions.push_back(new ColorChange(data[min], FL_DARK_RED));
			instructions.push_back(new WidgetSwap(data[min], data[i]));
			instructions.push_back(new ColorSwap(data[min], FL_DARK_CYAN, data[i], FL_GREEN));
		}
		else {
			instructions.push_back(new ColorChange(data[min], FL_GREEN));
		}
	}
}




//-----------------------------------------------------------------------------------------------------------


//Quick Sort
void QuickSort::sort(vector<VisualizedFlight*> &data, Tip en, list<Instruction*> &instructions)
{
	num_cmps = 0;
	num_swaps = 0;
	instructions.clear();
	quickSort(data, instructions,0, data.size() - 1,en);
}



void QuickSort::quickSort(vector<VisualizedFlight*> &data, list<Instruction*> &instructions, int low, int high,Tip en)
{
	if (low < high) {
		int m = partition(data, instructions, low, high,en); 
										 
		quickSort(data, instructions, low, m - 1,en); 
								  
		quickSort(data, instructions, m + 1, high,en); 
	}
	else if (low == high) {
		instructions.push_back(new ColorChange(data[low], FL_GREEN));
	}
}



int QuickSort::partition(vector<VisualizedFlight*> &a, list<Instruction*> &instructions, int i, int j, Tip en) {

	VisualizedFlight *p = a[i]; // p is the pivot
	instructions.push_back(new ColorChange(a[i], FL_DARK_RED));
	int m = i;
	for (int k = i + 1; k <= j; k++) {
		num_cmps += 1;
		instructions.push_back(new ColorChange(a[k], FL_YELLOW));

		if (a[k]->flight.compare(p->flight, en)  < 0) {
			m++;
			if (a[k]->flight != a[m]->flight) {
				swap(a[k], a[m]);
				num_swaps += 1;
				instructions.push_back(new WidgetSwap(a[k], a[m]));
			}
		}
		else {
			instructions.push_back(new ColorChange(a[k], FL_DARK_MAGENTA));  //ljubicanstvena
		}
	}
	if (i != m) {
		num_swaps += 1;
		swap(a[i], a[m]);
		instructions.push_back(new WidgetSwap(a[i], a[m]));

	}
	instructions.push_back(new ColorChange(a[m], FL_GREEN));

	vector<VisualizedFlight*> vector;
	for (int s = i; s <= j; s++) {
		if (s != m) {
			vector.push_back(a[s]);
		}

	}
	instructions.push_back(new RevertColor(vector, FL_DARK_CYAN));
	return m;
}



//-----------------------------------------------------------------------------------------------------------


















/* uncomment only in case of emergency !! 
int QuickSort::partition(vector<VisualizedFlight*> &a, list<Instruction*> &instructions, int i, int j, Tip en) {

VisualizedFlight *p = a[i]; // p is the pivot
instructions.push_back(new ColorChange(a[i], FL_DARK_RED));
int m = i;
for (int k = i + 1; k <= j; k++) {
num_cmps += 1;
instructions.push_back(new ColorChange(a[k], FL_YELLOW));
switch (en) {
case flightNum:
if (a[k]->flight.getFNumber().compare(p->flight.getFNumber()) < 0) {
m++;
if (a[k]->flight != a[m]->flight) {
swap(a[k], a[m]);
num_swaps += 1;
instructions.push_back(new WidgetSwap(a[k], a[m]));
}
}
else {
instructions.push_back(new ColorChange(a[k], FL_DARK_MAGENTA));
}
break;

case destination:
if ((a[k]->flight.getDestination().compare(p->flight.getDestination()) < 0)) {
m++;
if (a[k]->flight != a[m]->flight) {
swap(a[k], a[m]);
num_swaps += 1;
instructions.push_back(new WidgetSwap(a[k], a[m]));
}
}
else {
instructions.push_back(new ColorChange(a[k], FL_DARK_MAGENTA));
}
break;

case departure:

if (a[k]->flight.compareDeparture(p->flight) < 0) {
m++;
if (a[k]->flight != a[m]->flight) {
swap(a[k], a[m]);
num_swaps += 1;
instructions.push_back(new WidgetSwap(a[k], a[m]));
}
}
else {
instructions.push_back(new ColorChange(a[k], FL_DARK_MAGENTA));
}
break;

case gate:

if (a[k]->flight.getGate().compare(p->flight.getGate()) < 0) {
m++;
if (a[k]->flight != a[m]->flight) {
swap(a[k], a[m]);
num_swaps += 1;
instructions.push_back(new WidgetSwap(a[k], a[m]));
}
}
else {
instructions.push_back(new ColorChange(a[k], FL_DARK_MAGENTA));
}
break;

}

}
if (i != m) {
num_swaps += 1;
swap(a[i], a[m]);
instructions.push_back(new WidgetSwap(a[i], a[m]));

}
instructions.push_back(new ColorChange(a[m], FL_GREEN));

vector<VisualizedFlight*> vector;
for (int s = i; s <= j; s++) {
if (s != m) {
vector.push_back(a[s]);
}

}
instructions.push_back(new RevertColor(vector,FL_DARK_CYAN));
return m;
}
*/



/*
void SelectionSort::sort(std::vector<VisualizedFlight*>&data, Tip en, list<Instruction*> &instructions)
{
num_cmps = 0;
num_swaps = 0;
instructions.clear();
for (int i = 0; i < data.size(); i++)
{
// Find the minimum element in unsorted array
int min = i;
instructions.push_back(new ColorChange(data[min], FL_DARK_RED));
for (int j = i + 1; j < data.size(); j++) {
instructions.push_back(new ColorChange(data[j], FL_YELLOW));
num_cmps += 1;
switch (en) {
case flightNum:
if (data[j]->flight.getFNumber().compare(data[min]->flight.getFNumber()) < 0) {
instructions.push_back(new ColorSwap(data[min], FL_DARK_CYAN, data[j], FL_DARK_RED));
min = j;
}
else {
instructions.push_back(new ColorChange(data[j], FL_DARK_CYAN));
}
break;
case destination:

if (data[j]->flight.getDestination().compare(data[min]->flight.getDestination()) < 0) {
instructions.push_back(new ColorSwap(data[min], FL_DARK_CYAN, data[j], FL_DARK_RED));
min = j;
}
else {
instructions.push_back(new ColorChange(data[j], FL_DARK_CYAN));
}
break;
case departure:

if (data[j]->flight.compareDeparture(data[min]->flight)  < 0) {
instructions.push_back(new ColorSwap(data[min], FL_DARK_CYAN, data[j], FL_DARK_RED));
min = j;
}
else {
instructions.push_back(new ColorChange(data[j], FL_DARK_CYAN));
}
break;

case gate:
if (data[j]->flight.getGate().compare(data[min]->flight.getGate()) < 0) {
instructions.push_back(new ColorSwap(data[min], FL_DARK_CYAN, data[j], FL_DARK_RED));
min = j;
}
else {
instructions.push_back(new ColorChange(data[j], FL_DARK_CYAN));
}
break;
}
}
if (min != i) {
num_swaps += 1;
swap(data[min], data[i]);
instructions.push_back(new ColorChange(data[min], FL_DARK_RED));
instructions.push_back(new WidgetSwap(data[min], data[i]));
instructions.push_back(new ColorSwap(data[min], FL_DARK_CYAN, data[i], FL_GREEN));
}
else {
instructions.push_back(new ColorChange(data[min], FL_GREEN));
}
}
}

*/