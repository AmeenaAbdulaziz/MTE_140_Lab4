#ifndef LAB3_PRIORITY_QUEUE_HPP
#define LAB3_PRIORITY_QUEUE_HPP
#include <string>
using namespace std;

// PURPOSE: Models a Priority Queue of Task Items
class PriorityQueue { 
protected:
	// PURPOSE: Models a single Task Item
    // PURPOSE: Models a single Task Item as a Tree Node
    struct Node {
        Node(int value0) : value(value0), left(NULL), right(NULL) {}
        int value;
        Node* left;    // pointer to the left node
        Node* right;   // pointer to the right node
        bool operator==(const Node& rhs) {
            return value == rhs.value;
        }
        
    };//end of Node struct
	friend class PriorityQueueTest;  

	// sequential representation of the priority queue.
	Node** heap;

	// total number of elements that the priority queue can store
	unsigned int capacity;
  
	// current number of elements in the priority queue
	unsigned int size;
  
public:
	// CONSTRUCTOR AND DESTRUCTOR
	
	// PURPOSE: Parametric constructor 
	// initializes heap to an array of (n_capacity + 1) elements
	PriorityQueue(unsigned int n_capacity);
  
	// PURPOSE: Explicit destructor of the class PriorityQueue
	~PriorityQueue();
  
  	// ACCESSORS
  	
	// PURPOSE: Returns the number of elements in the priority queue
	unsigned int get_size() const;

	// PURPOSE: Returns true if the priority queue is empty; false, otherwise
	bool empty() const;
  
	// PURPOSE: Returns true if the priority queue is full; false, otherwise
	bool full() const;

	// PURPOSE: Prints the contents of the priority queue; format not specified
	void print() const;
	
	// PURPOSE: Returns the max element of the priority queue without removing it
	// if the priority queue is empty, it returns (-1, "N/A")
	Node max() const;
  
	// MUTATORS

	// PURPOSE: Inserts the given value into the priority queue
	// re-arranges the elements back into a heap
  	// returns true if successful and false otherwise
  	// priority queue does not change in capacity
	bool enqueue(Node val);
	
  	// PURPOSE: Removes the top element with the maximum priority
	// re-arranges the remaining elements back into a heap
  	// returns true if successful and false otherwise
  	// priority queue does not change in capacity
	bool dequeue();
    
};
#endif 
