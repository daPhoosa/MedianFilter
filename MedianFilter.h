/*
  MedianFilter.h - Median Filter for the Arduino platform.
  Copyright (c) 2013 Phillip Schmidt.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
   A median filter object is created by by passing the desired filter window size on object creation.
   The window size should be an odd number between 3 and 255.

   New data is added to the median filter by passing the data through the in() function.  The new medial value is returned.
   The new data will over-write the oldest data point, then be shifted in the array to place it in the correct location.

   The current median value is returned by the out() function for situations where the result is desired without passing in new data.

   !!! All data must be type INT.  !!!
 */

#ifndef MedianFilter_h

   #define MedianFilter_h

   #include "Arduino.h"

   class MedianFilter
   {
      public:
         MedianFilter(int size, int seed);
         int in(const int & value);
         int out();

         int getMin();
         int getMax();
         int getMean();
         int getStDev();

         /*
         void printData();		// used for debugging
         void printSizeMap();
         void printLocationMap();
         void printSortedData();
         */

      private:
         uint8_t medFilterWin;      // number of samples in sliding median filter window - usually odd #
         uint8_t medDataPointer;	   // mid point of window
         int     * data;			   // array pointer for data sorted by age in ring buffer
         uint8_t * sizeMap;			// array pointer for locations data in sorted by size
         uint8_t * locationMap;		// array pointer for data locations in history map
         uint8_t oldestDataPoint;	// oldest data point location in ring buffer
         int32_t totalSum;
   };

#endif
