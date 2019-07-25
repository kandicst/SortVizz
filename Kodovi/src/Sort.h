//============================================================================
// Name        : Sort.h
// Author      : Stefan Kandic
// Date        : 8.1.2018.
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once
#include "Instruction.h"
#include "VisualizedNumber.h"
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
	virtual void sort(std::vector<VisualizedNumber*> &data, list<Instruction*> &instructions) = 0;
	// returns number of comparisons
	unsigned long getNumCmps();
	unsigned long getNumSwaps();

};


//---------------------------------------------------------------------------------------------------------------


// SelectionSort class
class BubbleSort : public Sort
{
public:

	void sort(std::vector<VisualizedNumber*> &data, list<Instruction*> &instructions);

};


//---------------------------------------------------------------------------------------------------------------


// SelectionSort class
class InsertionSort : public Sort
{
public:

	void sort(std::vector<VisualizedNumber*> &data, list<Instruction*> &instructions);

};

//---------------------------------------------------------------------------------------------------------------

// SelectionSort class
class SelectionSort : public Sort
{
public:

	void sort(std::vector<VisualizedNumber*> &data, list<Instruction*> &instructions);

};


//---------------------------------------------------------------------------------------------------------------


class QuickSort : public Sort
{

public:
	
	void sort(std::vector<VisualizedNumber*> &data, list<Instruction*> &instructions);
	void quickSort(vector<VisualizedNumber*> &data, list<Instruction*> &instructions, int low, int high);
	int partition(std::vector<VisualizedNumber*> &a, list<Instruction*> &instructions,int i ,int j);
	
};

