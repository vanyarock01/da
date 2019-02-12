#include <cstdlib>
#include <iostream>
#include <cmath>
#include "TVector.h"

TVector::TVector(size_t initSize)
{
    array = (Note**) malloc (initSize * sizeof(Note*));
    used = 0;
    size = initSize;
}

TVector::TVector()
{
    size_t initSize = 1;
    array = (Note**) malloc (initSize * sizeof(Note*));
    used = 0;
    size = initSize;
}
  
bool TVector::Push()
{

    if (used == size) {
        size *= 2;
        array = (Note**) realloc(array, size * sizeof(Note*));
    }

    char point;
    
    array[used] = new Note;
    
    for(int i = 0; i < DEC_M_D; i++) {
        array[used]->day[i] = '\0';
        array[used]->month[i] = '\0';
    }

    for(int i = 0; i < DEC_Y; i++) {
        array[used]->year[i] = '\0'; 
    }

    for(int i = 0;;i++) {
        //printf("%c %d\n", point, i);
       // scanf("%c", &point);
        point=std::cin.get();
        if(point == '.') {
            break;
        }else if(point == '\n'){
            return true;
        }else if(point == EOF) {
            delete array[used];
            return false;
        }else {
            array[used]->day[i] = point;
        }
    }

    for(int i = 0;;i++) {
        point=std::cin.get();
        if(point == '.') {
            break;
        }else {
            array[used]->month[i] = point;
        }
    }

    for(int i = 0;;i++) {
        point=std::cin.get();
        if(point == '\t' || point == ' ') {
            break;
        }else {
            array[used]->year[i] = point;
        }
    }
    
    scanf("%llu", &array[used]->data);
    used++;

    point=std::cin.get();
    if(point == EOF) {
        return false;
    }else {
        return true;
    }
    
}

int TVector::GetInt(char *x)
{
    int res = 0;
    for(int i = 0; ; i++) {
        if (x[i] == '\0') break;
        int tmp = x[i] - '0';
        res = res * 10 + tmp;
    }
    return res;
}

void TVector::Insert(size_t index, Note* elem)
{
    used++;
    array[index] = elem;
}


void TVector::RadixSort()
{
    Note **result;
    result = (Note**) malloc ((used) * sizeof(Note*));


    size_t thd[MAX_DAY + 1];

    for(int i = 0; i <= MAX_DAY; i++) {
        thd[i] = 0;
    }

    for(int i = 0; i < used; i++) {
        (thd[GetInt(array[i]->day)])++; 
    }

    size_t temp = 0, carry = 0;

    for(int i = 0; i <= MAX_DAY; i++) {
        temp = thd[i];
        thd[i] = carry;
        carry += temp;
    }

    for(int i = 0; i < used; i++) {
        result[thd[GetInt(array[i]->day)]] =  array[i];  
        (thd[GetInt(array[i]->day)])++;
    }
    
    for(int i = 0; i < used; i++) {
        array[i] = result[i];
    }
//
    size_t thm[MAX_MONTH + 1];

    for(int i = 0; i <= MAX_MONTH; i++) {
        thm[i] = 0;
    }

    for(int i = 0; i < used; i++) {
        (thm[GetInt(array[i]->month)])++; 
    }

    temp = 0, carry = 0;

    for(int i = 0; i <= MAX_MONTH; i++) {
        temp = thm[i];
        thm[i] = carry;
        carry += temp;
    }

    for(int i = 0; i < used; i++) {
        result[thm[GetInt(array[i]->month)]] = array[i];  
        (thm[GetInt(array[i]->month)])++;
    }
    
    for(int i = 0; i < used; i++) {
        array[i] = result[i];
    }
//
    size_t thy[MAX_YEARS + 1];
    
    for(int i = 0; i <= MAX_YEARS; i++) {
        thy[i] = 0;
    }

    for(int i = 0; i < used; i++) {
        (thy[GetInt(array[i]->year)])++; 
    }

    temp = 0, carry = 0;

    for(int i = 0; i <= MAX_YEARS; i++) {
        temp = thy[i];
        thy[i] = carry;
        carry += temp;
    }

    for(int i = 0; i < used; i++) {
        result[thy[GetInt(array[i]->year)]] =  array[i];  
        (thy[GetInt(array[i]->year)])++;
    }
    
    for(int i = 0; i < used; i++) {
        array[i] = result[i];
    }
    delete[] result;
}


void TVector::Print()
{
    for(int i = 0; i < used; i++) {
        printf("%s.%s.%s\t%llu\n", array[i]->day, array[i]->month, array[i]->year, array[i]->data);
    }
}


TVector::~TVector()
{
    for(int i = 0; i < used; i++) {
        delete array[i];
    }
    delete []array; // mismathed !!!
    used = 0;
    size = 0;
}
