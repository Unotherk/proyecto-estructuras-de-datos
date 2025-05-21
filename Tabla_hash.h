#ifndef HASH_TABLE_H
#ifndef HASH_TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Hastable {
private:

	struct KeyValuePair {
		int key;
		string value;
		KeyValuePair(int k, string v) : key(k), value(v) {}

	};

	vector<list<KeyValuePair>> table;
	int tableSize;
	int itemCount;

	int hashFuntion(int key);

	bool isPrime(int n);

	int nextPrime(int n);

	void resize();

	public
		Hashtable(int size = 17);
	
	void insert(int Key, string value);

	string search(int key);

	bool remove(int key);

	void display();

	int size();

	bool isEmpty();

	void clear();

};

void showHashTableMenu();

#endif