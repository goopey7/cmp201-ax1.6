#pragma once
#include <string>
#include <iostream>
#include <vector>

class Bear
{
public:
	std::string name;
	int hunger;
	Bear() {
		name = "";
		hunger = 0;
	}
	Bear(std::string n, int pri)
	{
		name = n;
		hunger = pri;
	}
	static Bear* randomBear();
	void Check();
};

class Heap
{
public:
	int last_index;
	int size;
	Bear** arr;

	Heap(Bear* root)
	{
		size = 16;
		last_index = 0;
		arr = new Bear*[size]();
		arr[0] = root;
	}

	void heapify(int i);
	Bear* peek();
	Bear* pop();
	void push(Bear* b);
	void resize();
	std::vector<Bear*> toSortedVector();
};

