#ifndef TLONGNUMBER_H
#define TLONGNUMBER_H

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class TLongNumber {
public:
  TLongNumber(std::istream &is,      int base);
  TLongNumber(std::string  num,      int base);
  TLongNumber(std::vector <int> num, int base);
  TLongNumber(int size,              int base);

   TLongNumber(){};
  ~TLongNumber(){};

  int  Size        ()      const { return number.size(); }
  bool Divisibility(int a) const;

  friend std::ostream& operator<<(std::ostream& os, const TLongNumber &a);

  bool operator ==(const TLongNumber &x) const;
  bool operator > (const TLongNumber &x) const;
  bool operator < (const TLongNumber &x) const;

  TLongNumber operator + (const TLongNumber &a) const;
  TLongNumber operator - (const TLongNumber &a) const;
  TLongNumber operator * (const TLongNumber &a) const;
  TLongNumber operator / (const TLongNumber &a) const;
  TLongNumber operator ^ (const TLongNumber &a) const;

  TLongNumber operator * (const int &a) const;



private:
  void ShiftUp  ();
  void ZeroSplit();
  int base;
  std::vector<int> number;


};

#endif
