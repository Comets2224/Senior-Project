#include <iostream>
#include <string>
#include "bits/stdc++.h"
using namespace std;

vector<int> distances = {23,12,62,34};
int distanceMMStorage[180] = {0};
int scansPerformed = 0;

int findMinimumValue(vector<int> vect) {
    
    int minVal = 6001;
    
    for (int i : vect) {
        
        if (minVal > i) {
            
            minVal = i;
            
        }   
    }
    
    return minVal;
    
}

vector<int> slicing(vector<int>& arr,
                    int X, int Y)
{
 
    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;
 
    vector<int> result(Y - X + 1);
 
    copy(start, end, result.begin());

    return result;
}
 
void printResult(vector<int>& ans)
{
 
    for (auto& it : ans) {
 
        cout << it << ' ';
    }
}

int main()
{
    
    for(;;) {
        
        //int b = Ord(Serial.read())
        int b = 250; //Temporary declaration
        
        int data[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //21 data values for testing
        
        for(;;) {
            
            if (b == 250 && sizeof(data)/sizeof(data[0]) > 20) {
                
                break;
                
            }
            
            distances.push_back(b); //append b to the dataset
            
            //b = Ord(Serial.read())
        }
        
        if (sizeof(data)/sizeof(data[0]) == 21) {
            
            data[0] = ((data[0]) - 160);
            
            for (int i = 1; i < 5; i++) {
                
                if (data[i*4] != 128) {
                    
                    int distanceMM = data[4*i-1] | (( data[4*i] & 0x3f) << 8);
                    
                    int angle = data[0]*4+i+1;
                    
                    if (angle < 181) {
                        
                        distanceMMStorage[angle] = distanceMM;
                        
                    }
                } 
            }
        }
        
        int quad1 = findMinimumValue(slicing(distances, 0, 44));
        int quad2 = findMinimumValue(slicing(distances, 45, 89));
        int quad3 = findMinimumValue(slicing(distances, 90, 134));
        int quad4 = findMinimumValue(slicing(distances, 135, 179)); 
        //int quad5 = findMinimumValue(slicing(distances, 180, 224));
        //int quad6 = findMinimumValue(slicing(distances, 225, 269));
        //int quad7 = findMinimumValue(slicing(distances, 270, 314));
        //int quad8 = findMinimumValue(slicing(distances, 315, 359)); 
        
        if (scansPerformed % 360 == 0) {
            
            cout<<quad1, quad2, quad3, quad4;
            
            int minVal = 6001;
            int minQuad = 0;
            
            if (minVal > quad1) {
                
                minVal = quad1;
                minQuad = 1;
                
            }
            
            if (minVal > quad2) {
                
                minVal = quad2;
                minQuad = 2;
                
            }
            
            if (minVal > quad3) {
                
                minVal = quad3;
                minQuad = 3;
                
            }
            
            if (minVal > quad4) {
                
                minVal = quad4;
                minQuad = 4;
                
            }
            
            //include conditional statements for the quads 5-8 later.
            
        }
    }
    return 0; 
}
