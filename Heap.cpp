// Abertay University, CMP201 AX1.6, Priority Queues over Heaps as Arrays, but they're bears.
// Author: William Kavanagh
// Partial Framework

#include "Heap.h"
#include "time.h"
#include <vector>

// Recursive operation to arrange array to satisfy heap property focusing on the element at index i
void Heap::heapify(int i)
{
	// assessed 2 marks
	int largest = i;
	int left = 2*i+1;
	int right = 2*i+2;
	if(left <= last_index && arr[left]->hunger > arr[i]->hunger)
	{
		largest = left;
	}
	if(right <= last_index && arr[right]->hunger > arr[largest]->hunger)
	{
		largest = right;
	}
	if(largest != i)
	{
		std::swap(arr[i],arr[largest]);
		heapify(largest);
	}
}

// Add a pointer to a bear object to the heap, heapify all internal nodes.
void Heap::push(Bear* c)
{
	// assessed 1 mark
	if(last_index == size - 1)
	{
		resize();
	}
	last_index++;
	arr[last_index] = c;
	for(int i = last_index / 2; i>=0; i--)
	{
		heapify(i);
	}
}

// Doubles the array referenced by the heap, copies values in element by element, updates reference.
void Heap::resize()
{
	// unassessed (look back to ArrayStacks and ArrayQueues, W4)
	size = size * 2;
	Bear** newArr = new Bear*[size]();
	for (int i = 0; i < last_index; i++) newArr[i] = arr[i];
	delete arr;
	arr = newArr;
}

// Removes the element at the head of the heap, replaces with the final element, heapify all internal nodes
Bear* Heap::pop()
{
	// assessed 1 mark
	Bear* bearToReturn = arr[0];
	arr[0] = arr[last_index];
	arr[last_index] = nullptr;
	last_index--;
	for(int i = last_index/2; i>=0; i--)
	{
		heapify(i);
	}
	return bearToReturn;
}

// Converts the heap to a vector sorted in descending order of hunger (hungriest first). Recreates the heap.
std::vector<Bear*> Heap::toSortedVector() 
{
	// assessed 1 mark

	std::vector<Bear*> vec;
	for(int i = last_index; i >= 0; i--)
	{
		Bear* bigBear = pop();
		vec.push_back(bigBear);
		heapify(i);
	}
	// recreate the heap
	for(int i=0; i<vec.size(); i++)
	{
		push(vec[i]);
	}
	return vec;
}

// Return a pointer to the hungriest bear
Bear* Heap::peek()
{
	// unassessed
	return arr[0];
}

// Prints the name and hunger of a given bear.
void Bear::Check()
{
	// provided
	if (name != "")	std::cout << name << " is next, with a hunger of " << hunger << "\n";
}

// Return a pointer to a randomly generated bear with some prefix+suffix combination and a random hunger value from 1-200
Bear* Bear::randomBear()
{
	// provided
	std::string first_names[] = { "Grizzly", "Big", "Chubby", "Snoozy", "Dopey", "Hungry", "Ostentatious", "Territorial", "Fluffy", "Powerful", "Grumpy", "Whinny the", "Bewildered", "Rambunctious", "Uncouth", "Mischievous", "Baby", "Elderly", "Dapper"};
	std::string second_names[] = {"Alan", "Bella", "Charlie", "Danielle", "Evan", "Felicity", "Gerry", "Helena", "Iain", "Juliette", "Pooh"};
	std::string name = first_names[rand() % 19] + " " + second_names[rand() % 11];
	return new Bear(name, 1 + (rand() % 200));
}

// main() included for testing. Remove or delete before submission or [-1]. This is being accurate is not guaranteed to be sufficient for full marks.
int main()
{
	// provided, templated.
	srand(time(NULL));	// set random seed

	int num_bears = 10;												// TODO: Muck about with this to test resize(). 


	Bear* b = new Bear("Important Barry", 200);						// Point to hungry Barry.
	Heap* h = new Heap(b);											// Create a heap with only Barry
	for (int i = 0; i < num_bears; i++) h->push(Bear::randomBear());		// generate 10 random friends for Barry, put them in the heap.
	std::cout << "\n~~~~~~\n";

	Heap* secondHeap = new Heap(b);									// second heap with just Barry.
	secondHeap->push(new Bear("Almost as hungry Barry", 195));
	secondHeap->push(new Bear("Just eaten Nigel", 5));
	secondHeap->push(new Bear("Ridiculously Hungry Kev", 300));
	std::cout << "Kev should be at the root, currently at the root is: " << secondHeap->peek()->name << "\n";

	if (b == h->pop())												// pop, this should murder and return Barry
	{
		std::cout << "Pop correctly found Barry, good stuff\n";
	}
	else
	{
		std::cout << "Pop didn't find Barry?!\n";
	}
	std::cout << "=====\n";

	// This block will print out all of our bears, it should do so in order.	
	std::cout << "Hopefully we see Kev, Barry, Barry again and then Nigel:\n";
	int original_last_index = secondHeap->last_index;
	for (int i = 0; i <= original_last_index; i++) {
		Bear* c =secondHeap->pop();
		if (c->name != "")
		{
			c->Check();
		}
	}

	std::cout << "\n===\nPrint out all " << std::to_string(num_bears) << " bears in the first heap : \n";
	std::vector<Bear*> v = h->toSortedVector();
	for (Bear* b : v)
	{
		b->Check();
	}
	return 0;
}
