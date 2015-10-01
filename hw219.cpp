//
// Created by Jesse Roe, Tyler Paquet, Brandon Attala on 9/28/2015.
//
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>

using namespace std;

// Method that finds the largest of three tuples
tuple<int,int,int> max3(tuple<int, int, int> a, tuple<int, int, int> b, tuple<int, int , int> c) {
    vector<tuple<int,int,int>> temp;
    temp.push_back(a);
    temp.push_back(b);
    temp.push_back(c);
    tuple<int,int,int> outputTuple = temp.at(0);
    for(tuple<int,int,int> i : temp) {
        if(get<0>(i) > get<0>(outputTuple)) {
            outputTuple = i;
        }
    }
    return outputTuple;
}

// Method to generate the sum of two tuples.
tuple<int, int ,int> compoundTuple(tuple<int,int,int>& left, tuple<int,int,int>& right) {
    int total = get<0>(left) + get<0>(right);
    int min = get<1>(left);
    int max = get<2>(right);
    return make_tuple(total,min,max);
};

tuple<int,int,int> maxSumRec(vector<int>& a, int left, int right) {
    if (left == right) // Base case
    if (a[left] > 0)
        return make_tuple(a[left], left, right);
    else
        return make_tuple(a[left], 0, 1);

    int center = (left + right) / 2;

//  Recursive call back on the left and right array segments
    auto maxLeftSum = maxSumRec(a, left, center);
    auto maxRightSum = maxSumRec(a, center + 1, right);

    tuple<int,int,int> maxLeft; // Tuple that contains the left border case data
    int leftBorderSum = 0, maxLeftBorderSum = 0;

    for (int i = center; i >= left; --i) {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum) {
            maxLeftBorderSum = leftBorderSum;
            maxLeft = make_tuple(maxLeftBorderSum, i, center + 1); // Contains offset to add exclusivity to lt index
        }
    }

    tuple<int,int,int> maxRight; // Tuple that contains the right border case data
    int rightBorderSum = 0, maxRightBorderSum = 0;

    for (int j = center + 1; j <= right; ++j) {
        rightBorderSum += a[j];
        if (rightBorderSum > maxRightBorderSum) {
            maxRightBorderSum = rightBorderSum;
            maxRight = make_tuple(maxRightBorderSum, center + 1, j + 1); // Contains offset to add exclusivity to rt index
        }
    }

//  Create a tuple that represents the sum of the left and right border cases
    tuple<int,int,int> maxBorder = compoundTuple(maxLeft, maxRight);
    return max3(maxLeftSum, maxRightSum,
                maxBorder);
}

/**
* Driver for divide-and-conquer maximum contiguous
* subsequence sum algorithm.
*/
tuple<int,int,int> maxSubSum3(vector<int> &a) {
    return maxSumRec(a, 0, a.size() - 1);
}

// Main method for testing
int main() {
    vector<int> delta {1,2,-15,3,4,16,-22,48, 100, 2000, -1000, 2, -107, 21, 80};
    auto temp = maxSubSum3(delta);
    cout << to_string(get<0>(temp)) << ", " << to_string(get<1>(temp)) << ", " << to_string(get<2>(temp)) << endl;
    return 0;
}