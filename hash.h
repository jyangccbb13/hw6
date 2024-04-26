#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
        // Add your code here
        std::vector<HASH_INDEX_T> w(5, 0);

        int length = k.length();

        for (int i = 0; i < 5; ++i) 
        {
            HASH_INDEX_T value = 0;
            int start = length - (i + 1) * 6;

            for (int j = 0; j < 6; ++j) 
            {
                int charIdx = start + j;
                if (charIdx >= 0) 
                {
                    char c = k[charIdx];
                    HASH_INDEX_T charValue = letterDigitToNumber(c);
                    value += charValue * static_cast<HASH_INDEX_T>(std::pow(36, 5 - j));
                }
            }
            w[4 - i] = value;
        }

        HASH_INDEX_T hash = 0;
        for (int i = 0; i < 5; ++i) 
        {
            hash += rValues[i] * w[i];
        }

        return hash;
    }
        // unsigned long long w[5] = {0};
        // int index = k.size() - 1;

        // for (int i = 4; i >= 0; --i)
        // {
        //     int sixChunk = std::min(6, static_cast<int>(k.length() - index));
        //     unsigned long long base_power = 1;

        //     for (int j = 0; j < sixChunk; ++j)
        //     {
        //         int val = letterDigitToNumber(k[index + j]);
        //         w[i] += static_cast<unsigned long long>(val) * base_power;
        //         base_power *= 36;
        //     }
            
        //     index += sixChunk;
        //     if(index >= k.length())
        //     {
        //         break;
        //     }

        // }

        // HASH_INDEX_T hash = 0;
        // for (int i = 0; i < 5; ++i)
        // {
        //     hash += rValues[i] * w[i];
        // }
        // return hash;

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = std::tolower(letter);
        if (letter >= '0' && letter <= '9')
        {
            return 26 + (letter - '0');
        }
        else
        {
            return letter - 'a';
        }
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
