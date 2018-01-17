// a4.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Josie Buter
// St.# : 301275572
// Email: jbuter@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////


#include <algorithm>
#include "pq_base.h"
#include <iostream>

using namespace std;

//global variable for comparisons in sort()
int comps_1 = 0;
//global var for comparisons in PQ_unordered
long int comps_2 = 0;
//global var for comparisons in PQ_ordered
long int comps_3 = 0;
//global var for comparisons in PQ_heap
int comps_4 = 0;

bool cmp(int a, int b) {
	comps_1 += 1;
	return a < b;
}

//priority queue sort function
template<class PQ>
void pq_sort(vector<int>& v) {
	PQ pq;
	for(int x : v) {
		pq.insert(x);
	}
	
	v.clear();
	while(!pq.empty()) {
		v.push_back(pq.pop_min());	
	}

	//updating all comparison counts, only the correct one will output
	comps_2 = pq.comparisons;
	comps_3 = pq.comparisons;
	comps_4 = pq.comparisons;
}

int main () {

	//vector we will be manipulating
	vector<int> v;

	//random number seed
	srand(time(NULL));

	//calculating comparisons for sort()
	cout << "\n";
	v.clear();
	for(int i = 5000; i <= 100000; i+= 5000) {
		comps_1 = 0;
		v.clear();
		for(int j = 0; j < i; j++) {
			//generate random array here
			int ra = rand() % i;
			v.push_back(ra);
		}
		sort(v.begin(), v.end(), cmp);
		cout << comps_1 << "\n";
	}

	//calculating comparisons for PQ_unordered
	cout << "\n";
	v.clear();
	for(int i = 5000; i <= 100000; i+= 5000) {
		comps_2 = 0;
		v.clear();
		for(int j = 0; j < i; j++) {
			//generate random array here
			int ra = rand() % i;
			v.push_back(ra);
		}
		pq_sort<PQ_unordered>(v);
		cout << comps_2 << "\n";
	}

	//calculating comparisons for PQ_ordered
	cout << "\n";
	v.clear();
	for(int i = 5000; i <= 100000; i+= 5000) {
		comps_3 = 0;
		v.clear();
		for(int j = 0; j < i; j++) {
			//generate random array here
			int ra = rand() % i;
			v.push_back(ra);
		}
		pq_sort<PQ_ordered>(v);
		cout << comps_3 << "\n";
	}

	//calculating comparisons for PQ_heap
	cout << "\n";
	v.clear();
	for(int i = 50; i <= 1000; i+= 50) {
		comps_4 = 0;
		v.clear();
		for(int j = 0; j < i; j++) {
			//generate random array here
			int ra = rand() % 10000;
			v.push_back(ra);
		}
		pq_sort<PQ_heap>(v);
		cout << comps_4 << "\n";
	}

	cout << "\n";

	return 0;
}
