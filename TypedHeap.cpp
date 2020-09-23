#include "TypedHeap.h"

// inserts strings into either intHeap or stringHeap depending on
// the contents of the strings
void TypedHeap::insertToHeaps(vector<string> vec){

  bool digit = true;
  
  // iterate over the vector
  for(unsigned int i = 0; i < vec.size(); i++){
    // if string has digit or a space, mark it true
    digit = true;
    
    for(unsigned int j = 0; j < vec.at(i).size(); j++){

      // if the character is a digit
      if( isdigit(vec.at(i)[j]) ){
	// create a temporary string to modify, incase it is actually a string
	// in that case, we don't want to modify it
	string tempString = vec.at(i);
	// clear the leading and trailing whitespacee
	tempString.erase(tempString.find_last_not_of(" \v\t\f\n\r") + 1);
	tempString.erase(0, tempString.find_first_not_of(" \v\t\f\n\r"));

	// if the digit has no whitespace in the middle, its a digit
	if ( tempString == to_string(stoi(tempString)) ){
	  // set digit to true
	  digit = true;
	  // clear the leading and trailing whitespace of the digit strings
	  vec.at(i).erase(vec.at(i).find_last_not_of(" \v\t\f\n\r") + 1);
	  vec.at(i).erase(0, vec.at(i).find_first_not_of(" \v\t\f\n\r"));
	}
	
      }
      // if it has any chars or non-leading or non-trailing whitspace, mark it false
      else{
	digit = false;
      }
    }
    // if the string only consists of digits and spaces, insert to intHeap
    if (digit == true){
      intHeap.insert(stoi(vec.at(i)));
    }
    // if the string has different characters, insert to stringHeap
    if (digit == false){
      stringHeap.insert(vec.at(i));
    }
  }
}

// merges both intHeap and stringHeap with totalHeap
void TypedHeap::combineHeaps(){
  // merge intHeap and totalHeap
  totalHeap.skewHeapMerge(intHeap);
  // empty intHeap
  intHeap = nullptr;

  // merge stringHeap and totalHeap
  totalHeap.skewHeapMerge(stringHeap);
  // empty stringHeap
  stringHeap = nullptr;
}

// prints the contents of all three skew heaps
void TypedHeap::printHeaps() const{
  cout << "IntHeap Holds:" << endl;
  intHeap.dump();
  cout << "StringHeap Holds:" << endl;
  stringHeap.dump();
  cout << "TotalHeap Holds:" << endl;
  totalHeap.dump();
}

// changes the priority function for all three skew heaps
void TypedHeap::changePriority(pri_fn pri){
  intHeap.setPriFn(pri);
  stringHeap.setPriFn(pri);
  totalHeap.setPriFn(pri);
}
