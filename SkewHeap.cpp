#include "SkewHeap.h"

// SkewHeap constructor
SkewHeap::SkewHeap(pri_fn pri){
  m_heap = nullptr;
  priority = pri;
}

// SkewHeap destructor
SkewHeap::~SkewHeap(){
  
  // while the heap is not empty, deleting the top node
  while ( m_heap != nullptr ){
    removeTop();
  }
}

// SkewHeap Copy Constructor
SkewHeap::SkewHeap(const SkewHeap& rhs){
  
  // set the priority function of the Skew Heap
  priority = rhs.getPriFn();
  
  // if the rhs is just null, set to null
  if (rhs.m_heap == nullptr){
    m_heap = nullptr;
  }
  else{
    // call a helper function to deep copy data
    m_heap = copyFunc(m_heap, rhs.m_heap);
  }
}

// SkewHeap Assignment Operator
const SkewHeap& SkewHeap::operator=(const SkewHeap& rhs){

  // empty the skewHeap this was called on
  this->~SkewHeap();
  
  // set the priority function of the SkewHeap
  priority = rhs.getPriFn();
  
  // if the rhs is just null, set to null
  if (rhs.m_heap == nullptr){
    m_heap = nullptr;
  }
  else{
    // call a helper function to deep copy data
    m_heap = copyFunc(m_heap, rhs.m_heap);
  }

  // return the new skewHeap
  return *this;
}

// copies a SkewHeap when passed in the head of the heap
// to be copied, and the head of the heap it should be copied to
Node* SkewHeap::copyFunc(Node* node, Node* copied){
  
  // if the node is null, return null
  if (copied == nullptr){
    return nullptr;
  }

  // if the data type is a string, create a new node
  if ( copied->tagged_union == ISSTRING ){
    node = new Node(copied->data_string);
  }
  // if the data type is an int, create a new node
  if ( copied->tagged_union == ISINT ){
    node = new Node(copied->data_int);
  }

  // recursively call to left
  node->left = copyFunc(node->left, copied->left);
  // recursively call to right
  node->right = copyFunc(node->right, copied->right);

  return node;
}

// returns the priority of a current function
pri_fn SkewHeap::getPriFn() const{
  return priority;
}

// changes the priority of a function, and makes sure it maintains
// the max heap property
void SkewHeap::setPriFn(pri_fn pri){

  // copy the old tree
  SkewHeap temp = *this;
  // set the priority function to pri
  priority = pri;

  // empty the skewHeap
  this->~SkewHeap();

  // recursively remove top from temp, and insert the new m_heap
  while(temp.m_heap != nullptr){    
    // insert if the data is a string
    if ( temp.m_heap->tagged_union == ISSTRING ){
      insert(temp.m_heap->data_string);
    }
    // insert if the data is an int          
    if ( temp.m_heap->tagged_union == ISINT ){
      insert(temp.m_heap->data_int);
    }

    temp.removeTop();
  }
}

// checks if a skewHeap is empty
bool SkewHeap::empty() const{

  // if the root is null, return true
  if (m_heap == nullptr){
    return true;
  }
  else{
    return false;
  }
  
}

// inserts string into the skewHeap
void SkewHeap::insert(string data){

  // if the node is empty, just make the root
  if( empty() == true ){
    m_heap = new Node(data);
  }
  else{
    // create new node with string data
    Node* temp = new Node(data);
    // merge the new node with the current heap
    m_heap = recursiveMerge(m_heap, temp);
  }

}

// inserts int data into the skewHeap
void SkewHeap::insert(int data){

  // if the heap is empty, just make the root
  if( empty() == true ){
    m_heap = new Node(data);
  }
  else{
    // create new node with data
    Node* temp = new Node(data);
    // merge the new node with the current heap
    m_heap = recursiveMerge(m_heap, temp);
  }

}

// returns the root of a skewHeap (greatest priority)
Node* SkewHeap::front() const{
  
  // if the heap is empty, return nullptr
  if (m_heap == nullptr){
    return nullptr;
  }
  else{
    return m_heap;
  }
  
}

// removes the root of the skewHeap (greatest priority)
void SkewHeap::removeTop(){

  // if the skewHeap is empty, just return
  if( empty() == true ){
    return;
  }

  // hold the left and right nodes
  Node* leftNode = m_heap->left;
  Node* rightNode = m_heap->right;
    
  // delete the root
  delete m_heap;
  m_heap = nullptr;
  
  // merge the left and right children
  m_heap = recursiveMerge(leftNode, rightNode);
}

// takes in two nodes to merge two heaps into one valid heap
Node* SkewHeap::recursiveMerge(Node* p1, Node* p2){

  // if p1 is empty, return p2
  if (p1 == nullptr){
    return p2;
  }
  // if p2 is empty, return p1
  if (p2 == nullptr){
    return p1;
  }

  // ensure p1 has a higher priority
  if (priority(p1) < priority(p2)){
    swap(p1, p2);
  }

  // swap the left and right child of p1
  swap( p1->left, p1->right );

  // recursively merge p1's left child with p2
  p1->left = recursiveMerge(p1->left, p2);

  return p1;
}

// merges two skewHeaps into one valid skewHeap
void SkewHeap::skewHeapMerge(SkewHeap& sh){

  // if the two skewHeaps have different priority functions, throw a domain error
  if (priority != sh.priority){
    throw domain_error("SkewHeap::skewHeapMerge(): merging with different priorities");
  }
  
  // merge the two skewHeaps
  m_heap = recursiveMerge(m_heap, sh.m_heap);

  // clear the heap passed in
  sh.m_heap = nullptr;
}

// print inorder traversal
void SkewHeap::inorder() const{
  
  // call helper to print inorder
  printInorder(m_heap);
}

// recursively prints an inorder traversal
void SkewHeap::printInorder(Node* node) const{

  // if the node is empty, just return
  if (node == nullptr){
    return;
  }
  
  cout << "(";
  
  // call recursively to the left
  printInorder(node->left);

  // print the data if its a string
  if (node->tagged_union == ISSTRING){
    cout << node->data_string;
  }
  // print the data if its an integer
  if (node->tagged_union == ISINT){
    cout << node->data_int;
  }

  // call recursively to the right
  printInorder(node->right);

  cout << ")";
  return;
}

// Dump the contents of the heap in decreasing priority order.
void SkewHeap::dump() const{

  // store the skewHeap in temp
  SkewHeap temp = *this;

  // while the heap is not empty
  while( temp.m_heap != nullptr ){

    // print output, if the data is a string
    if (temp.m_heap->tagged_union == ISSTRING){
      cout << "Data is: " << setw(10) << temp.m_heap->data_string << setw(35)
	   << "Priority is: " << setw(10) << priority(temp.m_heap) << endl;
    }
    // print output, if the data is an integer
    if (temp.m_heap->tagged_union == ISINT){
      cout << "Data is: " << setw(10) << temp.m_heap->data_int << setw(35)
	   << "Priority is: " << setw(10) << priority(temp.m_heap) << endl;
    }

    // keep calling removeTop until temp is empty
    temp.removeTop();
  }
}

