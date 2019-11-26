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


void SelectionSort::sort(std::vector<VisualizedNumber*>&data, list<Instruction*> &instructions)
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
			if (data[j]->value < data[min]->value) {
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
void QuickSort::sort(vector<VisualizedNumber*> &data, list<Instruction*> &instructions)
{
	num_cmps = 0;
	num_swaps = 0;
	instructions.clear();
	quickSort(data, instructions,0, data.size() - 1);
}



void QuickSort::quickSort(vector<VisualizedNumber*> &data, list<Instruction*> &instructions, int low, int high)
{
	if (low < high) {
		int m = partition(data, instructions, low, high); 
										 
		quickSort(data, instructions, low, m - 1); 
								  
		quickSort(data, instructions, m + 1, high); 
	}
	else if (low == high) {
		instructions.push_back(new ColorChange(data[low], FL_GREEN));
	}
}



int QuickSort::partition(vector<VisualizedNumber*> &a, list<Instruction*> &instructions, int i, int j) {

	VisualizedNumber *p = a[i]; // p is the pivot
	instructions.push_back(new ColorChange(a[i], FL_DARK_RED));
	int m = i;
	for (int k = i + 1; k <= j; k++) {
		num_cmps += 1;
		instructions.push_back(new ColorChange(a[k], FL_YELLOW));

		if (a[k]->value < p->value) {
			m++;
			if (a[k]->value != a[m]->value) {
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

	vector<VisualizedNumber*> vector;
	for (int s = i; s <= j; s++) {
		if (s != m) {
			vector.push_back(a[s]);
		}

	}
	instructions.push_back(new RevertColor(vector, FL_DARK_CYAN));
	return m;
}



//-----------------------------------------------------------------------------------------------------------

void BubbleSort::sort(std::vector<VisualizedNumber*>& data, list<Instruction*>& instructions)
{

	num_cmps = 0;
	num_swaps = 0;
	instructions.clear();

	int i, j;
	for (i = 0; i < data.size() - 1; i++) {
		// Last i elements are already in place  
		for (j = 0; j <  data.size() - i - 1; j++) {
			num_cmps+=1;
			instructions.push_back(new ColorChange(data[j], FL_DARK_RED));
			instructions.push_back(new ColorChange(data[j+1], FL_DARK_RED));
			if (data[j]->value > data[j + 1]->value) {
				swap(data[j], data[j + 1]);
				instructions.push_back(new WidgetSwap(data[j], data[j+1]));
				instructions.push_back(new ColorChange(data[j], FL_DARK_CYAN));
				num_swaps+=1;
			}
			else {
				instructions.push_back(new ColorChange(data[j], FL_DARK_CYAN));
			}
		}
		instructions.push_back(new ColorChange(data[data.size() - i - 1], FL_GREEN));
	}
	
	instructions.push_back(new ColorChange(data[0], FL_GREEN));
}


//-----------------------------------------------------------------------------------------------------------


void InsertionSort::sort(std::vector<VisualizedNumber*>& data, list<Instruction*>& instructions)
{
	/*
	int i, j;
	VisualizedNumber* key;
	for (i = 1; i < data.size(); i++)
	{
		instructions.push_back(new ColorChange(data[i], FL_DARK_RED));
		key = data[i];
		j = i - 1;

		while (j >= 0 && data[j] > key)
		{
			//data[j + 1] = data[j];
			j = j - 1;
		}
		data[j + 1] = key;
	}



	*/
}
