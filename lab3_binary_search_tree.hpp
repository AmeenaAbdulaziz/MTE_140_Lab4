#ifndef LAB3_BINARY_SEARCH_TREE_HPP
#define LAB3_BINARY_SEARCH_TREE_HPP

#include <string>
#include <stdio.h>
#include <cmath>
#include <cstdlib>

using namespace std;

// PURPOSE: Models a Binary Search Tree of Task Items

class BinarySearchTree {
    // PURPOSE: Models a single Task Item as a Tree Node
    public:
    struct Node {
        Node(int value0) : value(value0), left(NULL), right(NULL) {}
        int value;
        Node* left;    // pointer to the left node
        Node* right;   // pointer to the right node
        bool operator==(const Node& rhs) {
            return value == rhs.value;
        }
        
    };//end of Node struct
    
    friend class BinarySearchTreeTest;
    
    // pointer to the root node of the tree
    Node* root;
    
    // number of nodes in the tree
    unsigned int size;

    // CONSTRUCTOR AND DESTRUCTOR
    
    // PURPOSE: Default/empty constructor
    BinarySearchTree();
    
    //destructor helper function
    void destroy(Node* node);
    
    // PURPOSE: Explicit destructor of the class BinarySearchTree
    ~BinarySearchTree();
    
    // ACCESSORS
    // PURPOSE: Returns the number of nodes in the tree
    unsigned int get_size() const;
    
    // PURPOSE: Returns the maximum value of a node in the tree
    // if the tree is empty, it returns (-1, "N/A")
    Node max() const;
    
    // PURPOSE: Returns the minimum value of a node in the tree
    // if the tree is empty, it returns (-1, "N/A")
    Node min() const;
    
    // PURPOSE: Returns the tree height
    unsigned int height() ;
    unsigned int height(Node** cur, int max, int curMax) ;
    
    // PURPOSE: Prints the contents of the tree; format not specified
    void print() const;
    void print(Node * val) const;
    
    // PURPOSE: Returns true if a node with the value val exists in the tree
    // otherwise, returns false
    bool exists(Node val) const;
    
    // PURPOSE: Optional helper function that returns a pointer to the root node
    Node* get_root_node();
    
    // PURPOSE: Optional helper function that returns the root node pointer address
    Node** get_root_node_address();
    
    // PURPOSE: Optional helper function that gets the maximum depth for a given node
    int get_node_depth(Node* n) const;
    
    // MUTATORS
    
    // PURPOSE: Inserts the value val into the tree if it is unique
    // returns true if successful; returns false if val already exists
    bool insert(Node val);
    
    // PURPOSE: Removes the node with the value val from the tree
    // returns true if successful; returns false otherwise
    bool remove(Node val);
    
    void find_and_print_sum_of_nodes (BinarySearchTree::Node* T, int desired_sum, int cur_sum, string buffer);
    
    int find_max_sum (BinarySearchTree::Node* T, int &cur_max_sum);
};
#endif
