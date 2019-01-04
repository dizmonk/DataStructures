// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[capacity - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

//The resize() function takes the argument new_capacity
//and creates a new temp array that can hold that 
//amount of elements. The invoking object's data array
//is then copied into the temp array, after which,
//the data is then destroyed and then a new data array
//is created and the temp array is copied into the
//new data array for the invoking object. 
void IntSet::resize(int new_capacity)
{
   int* tempArray = new int[new_capacity];

   for(int i = 0; i < used; i++){
       tempArray[i] = data[i];
   }

   delete []data;

   data = tempArray;
   capacity = new_capacity;
}

//default constructor
IntSet::IntSet(int initial_capacity):used(0)
{
   //allocate memory for the invoking object's array. If no value
   //is passed when the class is instantiated than the initial
   //capacity the array can hold will be 1 element.
   data = new int[initial_capacity];
   capacity = initial_capacity;
}

//copy constructor
IntSet::IntSet(const IntSet& src):capacity(src.capacity),used(src.used)
{
  
   data = new int[capacity];

   for(int i = 0; i < used; i++){
       data[i] = src.data[i];
   }
}

//destructor
IntSet::~IntSet()
{
   //free the memory
   delete [] data;
}

//overloaded assignment operator
IntSet& IntSet::operator=(const IntSet& rhs)
{
   //create temp array and give it the same 
   //capacity as the object that is passed in
   int* tempArr = new int[rhs.capacity];
 
   //assign the data from the rhs object's
   //array into the temp array
   for(int i = 0; i < rhs.used; i++){
       tempArr[i] = rhs.data[i];
   }

   //free the memory
   delete []data;

   //create new array and assign the temp array 
   //to it, get the capacity and used values
   data = tempArr;
   capacity = rhs.capacity;
   used = rhs.used;
  
   //return the modified invoking object
   return *this;
}

//size returns the used value of the invoking object
int IntSet::size() const
{
   return used;
}

//isEmpty() checks if the invoking object's used
//value is 0 and returns a boolean
bool IntSet::isEmpty() const
{
   bool flag = true;
   if(used != 0)
       flag = false;
   return flag;
}

//contains() checks the invoking object's data array
//for empty or if the argument passed in matches
//any of the array's element and returns a boolean
bool IntSet::contains(int anInt) const
{
   bool flag = false;

   if(isEmpty())
       return flag;
   else{
       for(int i = 0; i < used; i++){
           if(anInt == data[i])
               flag = true;
       }
   }
   return flag; 
}


bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   int i = 0;
   int j = 0;
   for(i = 0; i < used; i++){

       for(j = 0; j < otherIntSet.used; j++){

           if(data[i] == otherIntSet.data[j])
               break;
       }

       if(j == otherIntSet.used)
           return false;
   } 
   return true;
}

//display
void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

//unionWith() takes an object as an argument, creates a 
//temp object that is assigned the invoking object and
//the otherIntSet object's data array is added to the
//end of the temp object and then the temp object is
//returned
IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{

   IntSet tempSet = *this;
   for(int i = 0; i < otherIntSet.used; i++){
       tempSet.add(otherIntSet.data[i]);
   } 

   return tempSet;
}

//The function intersect() takes an object as an argument, 
//creates a temporary object to hold the values, if any, 
//that intersect between the invoking object and the object 
//that is passed into the function. The temp object is returned.
IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   IntSet tempIntSet;

   int i = 0;
   int j = 0;
   for(i = 0; i < used; i++){

       for(j = 0; j < otherIntSet.used; j++){

           if(data[i] == otherIntSet.data[j]){
               tempIntSet.add(data[i]);
           }
       }
   }
   return tempIntSet; 
}

//The function subtract() takes an object as an argument, 
//creates a temporary object to hold the difference 
//between the invoking object and object that is passed into the function.
IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   IntSet tempSet;
   tempSet.used = 0;
   bool flag = false;

   int i = 0;
   int j = 0;
   for(i = 0; i < used; i++){

       for(j = 0; j < otherIntSet.used; j++){

           if(data[i] == otherIntSet.data[j]){
               flag = true;
               break;
           }
       }
           if(!flag){
               tempSet.add(data[i]);
           }

           flag = false;
   }

   return tempSet; 
}

//sets the used variable back to zero for the invoking object
void IntSet::reset()
{
   used = 0;
}

//add() takes an int as an argument, and after
//it is verified that it isn't already in the
//invoking object's array, it is added to the 
//array and a boolean is returned
bool IntSet::add(int anInt)
{
   if(contains(anInt))
       return false;

   if(used == capacity){

       //resize array if capacity too small
       resize(capacity * 2);

       data[used] = anInt;
       used++;

       return true;
   }

   else{

       data[used] = anInt;
       used++;
       return true;
   }
}

//remove() takes user input and tests to see if it is in the
//invoking object's array and returns true if it is found, 
//false if not found
bool IntSet::remove(int anInt)
{
   bool flag = false;

   if(!contains(anInt))
      return false;

   else if(data[used-1] == anInt){
      used--;
      return true;
   }
   else{  
      for(int i = 0; i < used-1; i++){

          if(data[i] == anInt){
              data[i] = data[used - 1];
              flag = true;
              used--;
              break;
          }
      }
   }
   return flag;
}

//the overloaded == function takes two objects as arguments and 
//tests them to see if they are equal and returns a boolean
bool operator==(const IntSet& is1, const IntSet& is2)
{
   if(is1.size() == is2.size() && is1.isSubsetOf(is2))
       return true;
   else 
       return false;
}
