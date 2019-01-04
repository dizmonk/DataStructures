// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_FA2018
{
   // CONSTRUCTORS and DESTRUCTOR
   sequence::sequence(size_type initial_capacity):used(0),current_index(0),
      capacity(initial_capacity)
   {
      data = new value_type[capacity];
   }

   sequence::sequence(const sequence& source):capacity(source.capacity),
      used(source.used),current_index(source.current_index)
   {
      data = new value_type[capacity];

      for(size_type i = 0; i < used; i++)
          data[i] = source.data[i];
   }

   sequence::~sequence()
   {
      delete []data;
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
      if(new_capacity < used)
          new_capacity = used;

      capacity = new_capacity;

      value_type* tempArray = new value_type[capacity];

      for(size_type i = 0; i < used; i++)
          tempArray[i] = data[i];

      delete [] data;

      data = tempArray;
   }

   void sequence::start()
   {
      current_index = 0;
   }

   //advance() increments the current index 
   void sequence::advance()
   {          
      current_index++;   
   }

   //insert() takes entry as an argument and inserts it
   //into the invoking object's data array before the
   //current item if it exists and at the beginning if 
   //it doesn't exist
   void sequence::insert(const value_type& entry)
   {

      if(used == capacity)
          resize(capacity * 1.25);

      //check if there is a current item in the sequence
      if(!is_item()){

          //no current item
          if(current_index > 0){

             //assign the current_index to the first element 
             start(); 

             //shift elements and insert the entry at beginning
             for(size_type i = used; i > current_index; i--){
                 data[i] = data[i - 1];
             }

             data[current_index] = entry;
             used++;
          }//current index == 0
          else{
              data[current_index] = entry;
              used++;
          }
      }//there is a current item
      else{

          for(size_type i = used; i > current_index; i--){
              data[i] = data[i - 1];
          }

          data[current_index] = entry;
          used++;
      }
   }

   //attach() takes entry as an argument and places it 
   //after the current item if it exists and makes it the 
   //current item
   void sequence::attach(const value_type& entry)
   {

       if(used == capacity)
           resize(capacity * 1.25);

       if(!is_item()){
           data[current_index] = entry;
           used++;
       }

      else{
         for(size_type i = used; i > current_index + 1; i--){
             data[i] = data[i - 1];
         }

         //increment the current index
         advance();

         data[current_index] = entry;
         used++;
      }
   }

   //remove_current() removes the element at the current index location 
   void sequence::remove_current()
   {
      //if current is the last element, decrement used 
      if(current_index == used - 1)
          used--;
      else{
          for(size_type i = current_index; i < used - 1; i++){
              data[i] = data[i + 1];
          }
          used--;
      }
   }

   //the overloaded operator=() function takes a new iteration of
   //the class and copies the invoking objects data into it
   sequence& sequence::operator=(const sequence& source)
   {
      value_type* tempArray = new value_type[source.capacity]; 
      
      for(size_type i = 0; i < source.used; i++)
          tempArray[i] = source.data[i];

      delete []data;

      data = tempArray;
      capacity = source.capacity;
      used = source.used;
      current_index = source.current_index;

      return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used;
   }

   bool sequence::is_item() const
   {
      bool flag;

      (used > 0 && current_index < used) ? flag = true: flag = false; 
          
      return flag;
   }

   //current() returns the value at the element located at the 
   //current index
   sequence::value_type sequence::current() const
   {  
      return data[current_index];
   }
}

