


# Visualizing Sorting Algorithms
Sorting algorithms are one of the most fundamental algorithms in computer science and they are considered one of the must-know things for every aspiring as well as experienced software engineer.

However, they can be pretty complicated, so the aim of this project was that through visualization understand them better, and for me to learn some C++ while doing so!

## Sorting
So let's start with explaining what even is sorting.
The most simple explanation, without any complicated mathematical notations, would be that sorting is just the process of rearranging a array of elements in a order in a specified order.

But if that's the case, then why do we have all these numerous complicated algorithms for a such an simple task?
Well, 99% of the time the algorithm used won't massively affect the performance of our sorting, but if we are working with a huge collection of data using the  "slower" algorithms sorting will  become almost impossible past the certain threshold.

## How is one algorithm slower than another?
The most obvious, and  worst solution to our problem would be to do something like this:

```python
for element in collection:
	for second_element in colletion:
		if element > second_element:		# sorting in ascending order
			swap(element, second_element)

```

We can analyze this code here, so basically if the collection has _n_ elements, the first for loop will be executed exactly _n_ times, and the inner for loop since it is defined on the same collection will be executed exactly _n_ times for every execution of the outer loop.
So that is _n_*_n_ times = n<sup>2</sup> times.
That means if we have 10 elements, we will have 10<sup>2</sup> = 100 loop executions which is basically nothing for computers today.
But if were to have a collection of 100 000 elements, we would now have 10 billion executions and we would have to wait a considerable amount of time for even the better CPUs to do all this work.

And finally, we arrive at the realization that this is just not going to cut it.
So what if we can find a way to do the same thing, but instead of having n<sup>2</sup>  we can do it way less loop executions?

Algorithms that can do this have been around a long time now, and there are plenty of source that explain them better than I could so I will just link them here.

Algorithms that are n<sup>2</sup> in the worst case, but can be pretty fast depending on the collection which we are sorting :
 - [Selection sort](https://www.geeksforgeeks.org/selection-sort/) - worst case  n<sup>2</sup>, best case also  n<sup>2</sup>
 - [Bubble sort](https://www.geeksforgeeks.org/bubble-sort/) - worst case n<sup>2</sup>, best case is only n (on an already sorted collection)
- [Insertion sort](https://www.geeksforgeeks.org/insertion-sort/)

Algorithms that work better than n*log(n) in average case
- [Quick sort](https://www.geeksforgeeks.org/quick-sort/)
- [Merge sort](https://www.geeksforgeeks.org/merge-sort/)
- [Heap sort](https://www.geeksforgeeks.org/heap-sort/)
