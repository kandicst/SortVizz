//============================================================================
// Name        : Sort.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once
#include "Instruction.h"
#include "VisualizedFlight.h"
#include <vector>
#include <list>



// Sort class
class Sort
{
protected:

	// number of comparisons performed in sort function
	unsigned long num_cmps;
	unsigned long num_swaps;
	
public:
	
	// main entry point
	virtual void sort(std::vector<VisualizedFlight*> &data, Tip, list<Instruction*> &instructions) = 0;
	// returns number of comparisons
	unsigned long getNumCmps();
	unsigned long getNumSwaps();
	// resets the number of comparisons

};


// SelectionSort class
class SelectionSort : public Sort
{
public:

	void sort(std::vector<VisualizedFlight*> &data,Tip, list<Instruction*> &instructions);

};


class QuickSort : public Sort
{

public:
	
	void sort(std::vector<VisualizedFlight*> &data, Tip, list<Instruction*> &instructions);
	void quickSort(vector<VisualizedFlight*> &data, list<Instruction*> &instructions, int low, int high, Tip en);
	int partition(std::vector<VisualizedFlight*> &a, list<Instruction*> &instructions,int i ,int j,Tip en);
	
};

