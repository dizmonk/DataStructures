// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
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
//     from data[used] through data[IntSet::MAX_SIZE - 1].
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

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

//default constructor initializes the used variable to 0
IntSet::IntSet():used(0){}

//accessor function size() returns the used variable value for size
int IntSet::size() const
{
   return used; 
}

//isEmpty() checks the instantiated object's used variable value and returns 
//true for a value > 0
bool IntSet::isEmpty() const
{
   bool flag = true;
   if(used != 0)
       flag = false;
   return flag;
}

//The function contains() takes an int as an argument, checks if the instantiated array empty,
//and if it is not empty than a for loop iterates through the array. If it is found than
//the function returns true.  
bool IntSet::contains(int anInt) const
{
   bool flag = false;

   if(isEmpty())
       cout << "That list is empty!" << endl;
   else{
       for(int i = 0; i < used; i++){
           if(anInt == data[i])
               flag = true;
       }
   }
   return flag; 
}

//The function isSubsetOf() takes an object as an argument and tests it with the current
//instantiated object to see if there is a successive match of elements between the two
//arrays
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

//The DumpData() function displays the data
void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

//The functon unionWith() takes an object as an argument, creates two temporary objects. One temp
//object is a copy of the invoking object and the other holds the desired union of the invoking
//oject with the object passed into the function.
IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   IntSet tempSet1;
   IntSet tempSet2;
   tempSet1.used = used;

   for(int i = 0; i < used; i++){
       tempSet1.data[i] = data[i];
   }

   for(int i = 0; i < otherIntSet.used; i++){
       tempSet1.data[tempSet1.used] = otherIntSet.data[i];
       tempSet1.used++;
   } 
   int count = 0;
   tempSet2.used = count;

   for(int i = 0; i < tempSet1.used; i++){
       int number = tempSet1.data[i];
       bool exists = false;
       
       for(int j = 0; j < tempSet2.used; j++){

           if(tempSet1.data[j] == number){
               exists = true;
               break;
           }
       }
      if(!exists){
          tempSet2.data[tempSet2.used] = number;
          tempSet2.used++;
      } 
   }

   return tempSet2; 
}

//The function intersect() takes an object as an argument, creates a temporary object to hold the 
//values, if any, that intersect between the invoking object and the object that is passed into
//the function. The temp object is returned.
IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   IntSet tempIntSet;

   tempIntSet.used = 0;

   int i = 0;
   int j = 0;
   for(i = 0; i < used; i++){

       for(j = 0; j < otherIntSet.used; j++){

           if(data[i] == otherIntSet.data[j]){
               tempIntSet.data[tempIntSet.used] = data[i];
               tempIntSet.used++;
           }
       }
   }
   return tempIntSet; 
}

//The function subtract() takes an object as an argument, creates a temporary object to hold the
//difference between the invoking object and object that is passed into the function.
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
               tempSet.data[tempSet.used] = data[i];
               tempSet.used++;
           }

           flag = false;
   }

   return tempSet; 
}

//reset() simply sets the invoking object's used value to 0. 
void IntSet::reset()
{
   used = 0;
}

//add() populates an element of the array associated with the invoking object and increments the
//used count
bool IntSet::add(int anInt)
{

   for(int i = 0; i < used; i++){

       if(data[i] == anInt){
           return false;
       }
   }

   data[used] = anInt;
   used++;

   return true; 
}

//remove() takes user input and tests to see if it is in the invoking object's array and returns
//true if it is found, false if not found
bool IntSet::remove(int anInt)
{
   bool flag = false;
  
   for(int i = 0; i < used; i++){

       if(data[i] == anInt){
           data[i] = data[used - 1];
           flag = true;
           used--;
           break;
       }
   }

   return flag;
}

//equal() takes two objects as arguments and tests if they are the same size first and uses the
//isSubsetOf() function to finish checking if they are equal. It returns true if equal and false
//if not equal.
bool equal(const IntSet& is1, const IntSet& is2)
{
   bool flag = false;

   if(is1.size() == is2.size() && is1.isSubsetOf(is2))
       flag = true;
   
   return flag;
       
}
