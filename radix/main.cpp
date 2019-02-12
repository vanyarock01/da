#include <cstdlib>
#include <iostream>
#include <climits>
#include <cmath>
#include <cstdio>
#include "TVector.h"



int main(void)
{

    TVector *a = new TVector();
    while(a->Push());
    a->RadixSort();
    a->Print();

    delete a;
    return 0;
}

