#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
    root = NULL;
    size = 0;
}

void BinarySearchTree::destroy(Node* node){
    if (node)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
    destroy(root);
    root = NULL;
    size = 0;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
    return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::Node BinarySearchTree::max() const {
    if(!root || size == 0)
        return BinarySearchTree::Node(NULL);
    else if (size == 1)
        return *root;
    //    else if(!root -> right && size == 2){
    //        return *root;
    //    }
    else{
        Node* cur = root;
        while(cur -> right){
            cur = cur -> right;
        }
        return *cur;
    }
    //return BinarySearchTree::TaskItem(-1, "N/A");
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::Node BinarySearchTree::min() const {
    if (!root)
        return BinarySearchTree::Node(NULL);
    Node* cur = root;
    if (size == 1)
        return *cur;
    while ((cur->left))
        cur = cur->left;
    return *cur;
}

bool BinarySearchTree::exists( BinarySearchTree::Node val) const {
    if(!root || size == 0)
        return false;
    
    Node* cur = root;
    
    while(cur){
        if(cur -> value == val.value)
            return true;
        else if (cur -> value > val.value)
            cur = (cur->right? cur -> right: NULL);
        else if (cur -> value < val.value)
            cur = (cur->left? cur -> left: NULL);
    }
    return false;
}


// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height()  {
    
    if (!root) {
        return 0;
    }
    
    Node **cur = &root;
    
    int max = 0, curMax = 0;
    
    max = height(cur, max, curMax);
    return max;
    
}

unsigned int BinarySearchTree::height(Node** cur, int max, int curMax)  {
    if (!((*cur)->left || (*cur)->right)) {
        return 0;
    }
    else if ((*cur)->left) {
        curMax = height(&((*cur)->left), max, curMax) + 1;
        if (curMax > max) {
            max = curMax;
        }
    } else if ((*cur)->right) {
        curMax = height(&((*cur)->right), max, curMax) + 1;
        if (curMax > max) {
            max = curMax;
        }
    }
    
    return max;
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
    Node* cur = root;
    print(cur);
}


void BinarySearchTree::print(BinarySearchTree::Node * val) const {
    if (val == NULL) {
        return;
    }
    else {
        cout << val->value << "\n";
        print(val->left);
        print(val->right);
    }
    
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::Node* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::Node** BinarySearchTree::get_root_node_address() {
    if (root)
        return &root;
    else
        return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::Node* n ) const {
    if(!root || size == 0 || !exists(*n)){
        cout << "base case triggered";
        return 0;
    }
    Node* cur = root;
    if (size == 1)
        return 1;
    else {
        int count = 2;
        
        for (int i = 0; i < size; i++){
            if(cur -> value == n -> value){
                cout << "base case triggered" << endl;
                return count;
                
            }
            else if (cur -> value > n -> value){
                if (cur -> right) {
                    cur = cur -> right;
                    count++;
                }
            }
            else if (cur -> value < n -> value)
                if (cur -> left) {
                    cur = cur -> left;
                    count++;
                }
        }
    }
    return -1;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::Node val ) {
    Node** cur = &root;
    if (!root) {
        *cur = new Node(val);
        ++size;
        return true;
    }
    
    while (*cur) {
        if ((*cur)->value == val.value) {
            return false;
        }
        else if ((*cur)->value > val.value) {
            cur = &((*cur)->left);
        }
        else if ((*cur)->value < val.value) {
            cur = &((*cur)->right);
        }
    }
    
    (*cur) = new Node(val);
    ++size;
    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(BinarySearchTree::Node val) {
    if (!root)
        return false;
    if (root->value == val.value && size == 1) {//if one element
        delete root;
        root = NULL;
        size--;
        return true;
    }
    Node* cur = root;
    Node* prev = root;
    bool found = false;
    //finding node to remove
    while (!found) {
        if (*(cur) == val)
            found = true;
        else if (cur->value > val.value && cur->left != NULL) {
            if (*(cur->left) == val){//stops if next one is node
                prev = cur;
                found = true;
            }
            cur = cur->left;
        }
        else if (cur->value < val.value && cur->right != NULL) {
            if (*(cur->right) == val) {//ditto
                prev = cur;
                found = true;
            }
            cur = cur->right;
        }
        else
            return false;
    }
    
    //removing node
    while (cur->right != NULL || cur->left != NULL){//if not leaf node
        Node* temp = cur;
        prev = cur;
        
        if (cur->left != NULL) {//moving successor up
            temp = temp->left;
            while (temp->right != NULL) {
                if (temp->right->right == NULL)
                    prev = temp;
                temp = temp->right;
            }
        }
        else {//moving predecessor up
            temp = temp->right;
            while (temp->left != NULL) {//>1 child
                if (temp->left->left == NULL)
                    prev = temp;
                temp = temp->left;
            }
        }
        Node* temp_right = temp->right;
        Node* temp_left = temp->left;
        
        temp->right = cur->right;
        temp->left = cur->left;
        *cur = *temp;
        cur = temp;
        *cur = val;
        cur->right = temp_right;
        cur->left = temp_left;
    }
    //deleting extra node
    if (prev->left == cur) {
        delete prev->left;
        prev->left = NULL;
    }
    else {
        delete prev->right;
        prev->right = NULL;
    }
    size--;
    return true;
}

void find_and_print_sum_of_nodes (BinarySearchTree::Node* T, int desired_sum, int cur_sum, string buffer){
    //exit if T is NULL
    if(!T) return;

    //update the ongoing sum with the current value for T
    int new_sum = cur_sum + T -> value;

    //update the current path string
    string digit = to_string(T->value);
    string new_buffer = buffer + "" + digit;

    //if the desired sum is found, print the corresponding path
    if(new_sum == desired_sum)
        cout << new_buffer << endl;
    
    //todo: continue down left subtree
    if((T ->left ->value + cur_sum) >= cur_sum && (T ->left ->value + cur_sum) > (T ->right ->value + cur_sum))
        return find_and_print_sum_of_nodes (T ->left, desired_sum, cur_sum, buffer);
    
    //todo: continue down right subtree
    if((T ->right ->value + cur_sum) >= cur_sum && (T ->right ->value + cur_sum) > (T ->left ->value + cur_sum))
        return find_and_print_sum_of_nodes (T ->right, desired_sum, cur_sum, buffer);
    
       //todo: restart from the left subtree is buffer == ""
    if((T ->left ->value + cur_sum) >= cur_sum && (T ->left ->value + cur_sum) > (T ->right ->value + cur_sum) && buffer == "")
        return find_and_print_sum_of_nodes (T ->left, desired_sum, cur_sum, buffer);
       //todo: restart from the right subtree is buffer == ""
    if((T ->right ->value + cur_sum) >= cur_sum && (T ->right ->value + cur_sum) > (T ->left ->value + cur_sum) && buffer == "")
        return find_and_print_sum_of_nodes (T ->right, desired_sum, cur_sum, buffer);

}

int find_max_sum(BinarySearchTree::Node* T, int &cur_max_sum){
    if(!T)
        return 0;
    int left_sum = find_max_sum(T->left, cur_max_sum);
    int right_sum = find_max_sum(T->right,cur_max_sum);
    
    int subtree_max = max(left_sum,right_sum);
    
    int max1 = max( T ->value, subtree_max + T ->value);
    int max2 = max(max1, left_sum + right_sum + T->value);
    
    cur_max_sum = max(max2, cur_max_sum);
    
    return max1;
}

int find_max_sum(BinarySearchTree::Node*T) {
    int temp_max_sum = INT_MIN;
    find_max_sum(T, temp_max_sum);
    return temp_max_sum;
}



