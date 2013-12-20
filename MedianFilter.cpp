/*
  MedianFilter.cpp - Median Filter for the Arduino platform.
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
  
	New data is added to the median filter by passing the data through the write() method.
	The new data will over-write the oldest data point, then be shifted in the array to place it in the correct location. 
  
	The current median value is returned by the read() method.
 
	!!! All data must be type INT.  !!!
 
*/

#include "MedianFilter.h"

	
MedianFilter::MedianFilter(byte size)
{

	if(size < 3){size = 3;}  //  prevent undersized windows
	if(size > 255){size = 255;}  //  prevent oversized windows
	
	medFilterWin = size;				// number of samples in sliding median filter window - usually odd #
	medDataPointer = size >> 1;			// mid point of window
	sortedData = (int*) calloc (size, sizeof(int));		// array for data sorted by size
	historyMap = (byte*) calloc (size, sizeof(byte));	// array for locations of data in sorted list (arranged in looped age order)
	locationMap = (byte*) calloc (size, sizeof(byte));	// array for locations of history data in map list
	ODP = 0;							// oldest data point location in historyMap
	
	for(byte i=0; i<medFilterWin; i++){ // initialize the arrays
		historyMap[i] = i;				// start map with straight run
		locationMap[i] = i;				// start map with straight run
		sortedData[i] = 0;				// populate with zeros
	}
	
}

int MedianFilter::in(int value)
{  
	sortedData[historyMap[ODP]] = value;  // store new data in location of oldest data

	dataMoved = false;
	
	if(historyMap[ODP] != 0){ // don't check left neighbours if at the extreme left
		for(int i=historyMap[ODP]; i>0; i--){	//index through left adjacent data
			int j = i - 1;	// neighbour location
			if(sortedData[i] < sortedData[j]){
				//Serial.print("<");
				tempData = sortedData[j];		// store neighbour data in temp
				tempMap = locationMap[j];		// store position of adjacent data in historyMap
			
				sortedData[j] = sortedData[i];	// move new data to neighbour location
				historyMap[ODP] = j;
				locationMap[j] = ODP;
				
				sortedData[i] = tempData;		// swap neighbour data back in
				historyMap[tempMap] = i;
				locationMap[i] = tempMap;
				
				dataMoved = true; 
			}
			else{
				i=0; // abort loop if neighbour is larger
			}
		}
	} // end shift data to left

	if(historyMap[ODP] != medFilterWin - 1 && dataMoved == false){ // don't check right neighbours if at the extreme right or data already moved
		for(int i=historyMap[ODP]; i<medFilterWin-1; i++){ //index through right adjacent data
			int j = i + 1;	// neighbour location
			if(sortedData[i] > sortedData[j]){
				//Serial.print(">");
				tempData = sortedData[j]; // store neighbour data in temp
				tempMap = locationMap[j];	// store position of adjacent data in historyMap
			
				sortedData[j] = sortedData[i];// move new data to neighbour location
				historyMap[ODP] = j;
				locationMap[j] = ODP;
				
				sortedData[i] = tempData; // swap neighbour data back in
				historyMap[tempMap] = i;
				locationMap[i] = tempMap;
			}
			else{
				i=medFilterWin; // abort loop if neighbour is smaller
			}
		}
	} // end shift data to right
	
	ODP++;
	if(ODP >= medFilterWin){ODP = 0;} // reset after oldest data point to ring history
	
	return sortedData[medDataPointer];
}


int MedianFilter::out() // return the value of the median data sample
{
	return  sortedData[medDataPointer];     
}

/*
void MedianFilter::printData() // display sorting data for debugging
{
	for(int i=0; i<medFilterWin; i++){
		Serial.print(sortedData[i]);
		Serial.print("\t");
	}
	Serial.print("\t");
	Serial.println("Data sorted by size");
	
	for(int i=0; i<medFilterWin; i++){
		Serial.print(historyMap[i]);
		Serial.print("\t");
	}
	Serial.print("\t");
	Serial.println("Locations of data sorted by age");
	
	for(int i=0; i<medFilterWin; i++){
		Serial.print(locationMap[i]);
		Serial.print("\t");
	}
	Serial.print("\t");
	Serial.println("Location of age data in age list sorted by data size");
	Serial.println("");
}  
*/

