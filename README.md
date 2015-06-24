MedianFilter
============

Simple Median Filter library designed for the Arduino platform.

Written by Phillip Schmidt


LIMITATIONS:
----------------------

1) Minimum window size is 3

2) Maximum window size is 255

3) Only accepts arduino data type INT


USAGE:
----------

Object Creation:
  MedianFilter filterObject(size, seed); 
    (Use the smallest window that provides acceptable results, large windows use more memory and take more time)
    (Seed allows for initializing the filer to the desired or expected starting value)
    
Input Data:
  filterObject.in(newValue);
    (this will return the median value after the new sample has been processed)
    
Read Current Value:
  filterObject.out();
    (this allows for reading the current median value without submitting a new sample)
  
OPERATION OVERVIEW
-------------------

  This median filter attempts to minimize processing time by maintaining a data list that is sorted from smallest value to largest value.  When a new sample is submitted, it replaces the oldest sample.  The new sample is then shifted in the sorted list to bring it to the correct location.  Map arrays are used to track the age and location of each sample.
  
  Static memory usage grows linearly with window size at a rate of 4bytes per window width unit (for 16bit int data types).  A filter with window size of 7 will require 28bytes plus a couple more bytes for other variables.  At maximum window size of 255, the filter will require over 1KB of memory.  If this large of a filter is needed, then a median filter is probably not the right tool.
  
  Processing time of any single sample is random but bounded.  Best case is where the old sample that is replaced is where the new sample needs to be, requiring no shifting.  The worst case is where the new sample needs to travers the entire list to get sorted into it's place.  Regardless of this variability, over a large number of samples the average time required by the filter increases proprtionately to the square of the window size. (ToDo: add table of average processing time based on window size)
