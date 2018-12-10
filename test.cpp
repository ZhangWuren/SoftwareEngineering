#include "time.h"
#include "iostream"
#include "algorithm"
using namespace std;

int main()
{
    char a[8]={'a','b','c','d','e','f','g','h'};
    clock_t startT, finishT;
    double totalTime;
    startT = clock();
    while(next_permutation(a,a+8)){

    }
    finishT = clock();
    totalTime = (double)(finishT - startT) / CLOCKS_PER_SEC;
    cout << "The total time is " << totalTime << "s!" << endl;
}