// pq_base.h
// header file to implement the base class for the priority queue
// and all it's children classes for each different sort

#include <vector>
#include <iostream>
#include "cmpt_error.h"
using namespace std;

class PQ_base {
private:
	vector<int> V;
public:

	virtual ~PQ_base() {}
	virtual int size() const = 0;
	virtual bool empty() const = 0;
	virtual void insert(int x) = 0;
	virtual void remove_min() = 0;
	virtual int pop_min() = 0;
	virtual int peek_min() const = 0;

}; //priority queue base class

class PQ_unordered : public PQ_base {
private:
	vector<int> V;
public:

	long int comparisons;

	PQ_unordered() : comparisons(0) {
		V.clear();
	}

	~PQ_unordered() {
		V.clear();
	}

	int size () const {
		return V.size();
	}

	bool empty() const {
		return V.size() == 0;
	}

	void insert(int x) {
		V.push_back(x);
		comparisons++;
	}

	void remove_min() {
		int min = V[0];
		int min_ind = 0;
		for(int i = 0; i < size(); i++) {
			if(V[i] < min) {
				min = V[i];
				min_ind = i;
			}
			comparisons++;
		}
		//loop to restore vector before deleting min value
		for(int s = min_ind; s < size(); s++) {
			V[s] = V[s+1];
		}
		//deleting min value 
		V.pop_back();
	}

	int peek_min() const {
		//find min using linear search
		int min = V[0];
		for(int i = 0; i < size(); i++) {
			if(V[i] < min) {
				min = V[i];
			}
		}
		//return the min value
		return min;
	}

	int pop_min() {
		int min = peek_min();
		remove_min();
		return min;
	}
};

class PQ_ordered : public PQ_base {
private:
	vector<int> V;
public:

	long int comparisons;

	PQ_ordered() : comparisons(0) {
		V.clear();
	}

	~PQ_ordered() {
		V.clear();
	}

	int size () const {
		return V.size();
	}

	bool empty() const {
		return V.size() == 0;
	}

	void insert(int x) {
		V.insert(upper_bound(V.begin(), V.end(), x), x);
		comparisons += size()-1;
	}

	void remove_min() {
		V.erase(V.begin());
		comparisons++;
	}

	int peek_min() const {
		return V[0];
	}

	int pop_min() {
		int min = peek_min();
		remove_min();
		return min;
	}

	void print() const {
        cout << "[ ";
        for(int i = 1; i < V.size(); i++)
            cout << V[i] << " ";
        cout << "]\n";
    }
};

class PQ_heap : public PQ_base {
private:
    vector<int> v;
    
public:

	int comparisons;
    
    PQ_heap() : comparisons(0) {
        v.clear();
        v.push_back(0);
    }        
            
    ~PQ_heap() {
        v.clear();
    }
            
    int size() const {
        return v.size() - 1;
    }
            
    bool empty() const {
        return v.size() == 1;
    }
            
    void insert(int x) {
	    //adding x as the left-most new leaf
	    v.push_back(x);
	                
	    //must check if x is in the correct node placement
	    //check if x is smaller than its parent
	    //parent of i = floor(i/2), where i is index of the child
	    int i = v.size()-1;
	    //checking if it's the first root node
	    if(i == 1) return;
	    int parent = floor(i/2);
	    comparisons++;
	    while((x < v[parent]) && (i != 1)) {
	        v[i] = v[parent];
	        v[parent] = x;
	        i = parent;
	        parent = floor(i/2);
	        comparisons++;
	    }
    }
            
    int peek_min() const {
    	if(v.empty()) {
    		cmpt::error("cannot peek an empty pq");
    	}
        return v[1];
    }
            
    void remove_min() {
    	if(v.empty()) {
    		cmpt::error("cannot remove elements from empty pq");
    	}
    	if(v.size() == 2) {
    		v.pop_back();
    		comparisons++;
    		return;
    	}
        //make the right-most child the current root of the tree
        //index 1 is the root of the tree
        //v.size()-1 is the index of the right-most child
        v[1] = v[size()-1];
        v.pop_back();
                
        //now check the children of the current node and swap
        //until we can say both children are bigger than the current
        //Left child of i = 2i ; Right child of i = 2i + 1
        //where i is the index of the parent node
        int i = 1;
        int Lt_child = 2*i;
        int Rt_child = (2*i)+1;
        comparisons++;

        while((v[i] > v[Lt_child] && v[i] > v[Rt_child]) && (Lt_child < v.size()-1 && Rt_child < v.size()-1)) {
            //choosing the smallest child to swap with
            int child = Lt_child;
            if(v[Rt_child] < v[Lt_child]) {
            	child = Rt_child;
            }
            //swapping
            int tmp = v[i];
            v[i] = v[child];
            v[child] = tmp;
            //updating indices
            i = child;
            Lt_child = 2*i;
            Rt_child = (2*i)+1;
            comparisons++;
        }
    }
            
    int pop_min() {
        int x = peek_min();
        remove_min();
        return x;
    }
            
    void print() const {
        cout << "[ ";
        for(int i = 1; i < v.size(); i++)
            cout << v[i] << " ";
        cout << "]\n";
    }
}; // PQ_heap