#ifndef TVECTOR_H
#define TVECTOR_H

#include <iostream>

struct Note {
    char day[3];
    char month[3];
    char year[5];
    unsigned long long data;
};


class TVector{
public:
    TVector(size_t initSize);
    TVector(); 
    bool Push();
    void Insert(size_t index, Note *elem);
    void RadixSort();
    void Print();
    ~TVector();
  
private:

    static const size_t MAX_YEARS = 9999;
    static const size_t MAX_MONTH = 12;
    static const size_t MAX_DAY = 31;

    static const size_t DEC_M_D = 3;
    static const size_t DEC_Y = 5;
    int GetInt(char *x);
    Note **array;
    size_t used;
    size_t size;
};

#endif /* TVECTOR_H */
