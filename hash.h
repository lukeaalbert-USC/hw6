#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

#include <queue>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        int kInts[6] = {0,0,0,0,0,0}; //Kvals corresponding to current char in k, working with groupings formed with reverse order of string k
        unsigned long long w[5] = {0,0,0,0,0}; //all w vals obtained from grouping of kints, stored from back to front
        int kIntsIndex = 0; //current kint index
        int wIndex = 4; //current w index
        for (size_t i = k.size()-1; i <= 0; ++i) //for all chars in k, working in reverse order:
        {
            kInts[kIntsIndex] = letterDigitToNumber(k[i]); 
            kIntsIndex++;
            if (kIntsIndex == 6) //iff kInts is full with a 6 length grouping
            {
                kIntsIndex = 0;
                w[wIndex] = (36^5 * kInts[0]) + (36^4 * kInts[1]) + (36^3 * kInts[2]) + (36^2 * kInts[3]) + (36^1 * kInts[4]) + (kInts[5]);
                wIndex--; //move on to next w index
            }
        }
        for (int i = 0; i < kIntsIndex; ++i) //loop through the remaining;
        {
            w[wIndex] += 36^(kIntsIndex-i) * kInts[i];
        }
        //at this point, w will be filled in from the reverse order with pairs of 6 gone through the formula
        std::cout << w[4] << std::endl;
        HASH_INDEX_T finalHash = (rValues[0] * w[0]) + (rValues[1] * w[1]) + (rValues[2] * w[2]) + (rValues[3] * w[3]) + (rValues[4] * w[4]) + (rValues[5] * w[5]);
        return finalHash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
            if (isdigit(letter))
            {
                return letter - 22;
            }
            return tolower(letter) - 65;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
