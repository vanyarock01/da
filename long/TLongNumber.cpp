#include "TLongNumber.h"

TLongNumber::TLongNumber(std::istream &is, int base): base(base) {
  
  std::string str;
  int base_size = std::to_string(base).length() - 1;

  is >> str;

  for (int i = (int)str.length(); i > 0; i = i - base_size) { 
    if (i < base_size) {
      number.push_back(std::stoi(str.substr(0, i)));
    } else {
      number.push_back(std::stoi(str.substr(i - base_size, base_size)));
    }
  }
  ZeroSplit();
}

TLongNumber::TLongNumber(std::string  num, int base): base(base) {

  int base_size = std::to_string(base).length() - 1;

  for (int i = (int)num.length(); i > 0; i = i - base_size) { 
    if (i < base_size) {
      number.push_back(std::stoi(num.substr(0, i)));
    } else {
      number.push_back(std::stoi(num.substr(i - base_size, base_size)));
    }
  }
  ZeroSplit();
}

TLongNumber::TLongNumber(int size, int base): base(base) {
  for (int i = 0; i < size; i++) number.push_back(0);
}


TLongNumber::TLongNumber(std::vector <int> num, int base):
  base(base), number(num) {} 

std::ostream& operator << (std::ostream &os, const TLongNumber &a) {

  int len = a.number.size();
  int base_size = std::to_string(a.base).length() - 1;

  std::vector <int> num = a.number;
  if (len) os << num[len - 1]; 
  
  for (int i = len - 2; i >= 0; i--) {
    os  << std::setw   (base_size)
        << std::setfill('0')
        << num[i];
  }
  return os;
}

void TLongNumber::ZeroSplit() {
  while (number.back() == 0 && number.size() - 1)
    number.pop_back();  
}

/* 
 *  if a > b ->  1 
 *  else 
 *  if a < b -> -1 
 *  else
 *  if a = b ->  0
 *
 */

int Comparison(const std::vector<int> &a, const std::vector<int> &b) {

  int a_len = a.size();
  int b_len = b.size();

  if (a_len < b_len) return -1;
  else
  if (a_len > b_len) return  1;
      
  for (int i = a_len - 1; i >= 0; i--) {
    if (a[i] > b[i]) return  1;
    else
    if (a[i] < b[i]) return -1;
  }

  return 0;
}

bool TLongNumber::operator == (const TLongNumber &x) const {

  if (this->base != x.base) return false; 

  return !Comparison(this->number, x.number);
}

bool TLongNumber::operator > (const TLongNumber &x) const {

  if (this->base != x.base) return false; 

  return Comparison(this->number, x.number) > 0;
}

bool TLongNumber::operator < (const TLongNumber &x) const {

  if (this->base != x.base) return false; 

  return Comparison(this->number, x.number) < 0;
}

TLongNumber TLongNumber::operator + (const TLongNumber &a) const {
  
  std::vector<int> result;

  int base_t = this->base;

  int x_len = this->number.size();
  int y_len = a.number.size();
      
  int max_len = std::max(x_len, y_len);

  int remainder = 0;

  for (int i = 0; (i < max_len) || (remainder); i++) {
   
    result.push_back((i >= x_len ? 0 : this->number[i]) + (i >= y_len ? 0 : a.number[i]) + remainder);
    if (result.back() >= base_t) {
      remainder = 1;
      result.back() -= base;
    } else {
      remainder = 0;
    }
  }
  TLongNumber x(result, base_t);
  x.ZeroSplit();
  return x;
}

TLongNumber TLongNumber::operator - (const TLongNumber &a) const {

  std::vector<int> result;

  int base_t = this->base;

  int compare = Comparison(this->number, a.number);
  if (compare < 1) {
    result.push_back(compare);

  } else {  
    int x_len = this->number.size();
    int y_len = a.number.size();

    int remainder = 0;

    for (int i = 0; (i < x_len) || (remainder); i++) {
      result.push_back((this->number[i]) - (i >= y_len ? 0 : a.number[i]) - remainder);
      if (result[i] < 0) {
        remainder  = 1;
        result[i] += base;  
      } else {
        remainder = 0;
      }
    }
  }
  TLongNumber x(result, base_t);
  x.ZeroSplit();
  return x;
}

TLongNumber TLongNumber::operator * (const TLongNumber &a) const {
  
  std::vector <int> result;
  int base_t = this->base;

  int x_len = this->number.size();
  int y_len = a.number.size();

  for (int i = 0; i < (x_len + y_len); i++) result.push_back(0);

  int remainder;

  for (int i = 0; i < x_len; i++) {
    remainder = 0;

    for (int j = 0; j < y_len || remainder; j++) {
      long part = result[i + j] + this->number[i] * (j < y_len ? a.number[j] : 0) + remainder;
      
      result[i + j] = (int) (part % base_t);
      remainder     = (int) (part / base_t);
    }
  }
  TLongNumber x(result, base_t);
  x.ZeroSplit();
  return x;
}

TLongNumber TLongNumber::operator * (const int &a) const {
  
  std::vector <int> result;
  int base_t = this->base;

  int x_len = this->number.size();
  int y_len = 1;

  for (int i = 0; i < (x_len + y_len); i++) result.push_back(0);

  int remainder;

  for (int i = 0; i < x_len; i++) {
    remainder = 0;

    for (int j = 0; j < y_len || remainder; j++) {
      long part = result[i + j] + this->number[i] * (j < y_len ? a : 0) + remainder;
      
      result[i + j] = (int) (part % base_t);
      remainder     = (int) (part / base_t);
    }
  }
  TLongNumber x(result, base_t);
  x.ZeroSplit();
  return x;
}


TLongNumber TLongNumber::operator / (const TLongNumber &a) const {

  int base_t = this->base;
  int x_len  = (int)this->number.size();


  TLongNumber current(std::string("0"), base_t);

  if (a == current) {
    TLongNumber z(std::string("-1"), base_t);
    return z;
  }

  TLongNumber result (x_len, base_t);
  for (int i = x_len - 1; i >= 0; i--) {

    current.number.insert(current.number.begin(), this->number[i]);

    if (!current.number.back())
      current.number.pop_back();

    int part = 0;
    int left = 0, right = base_t;

    while (left <= right) {

      int middle = (left + right) / 2;

      TLongNumber tmp = a * middle;

      if (current == tmp || tmp < current) {
        part = middle;
        left = middle + 1;

      } else {
        right = middle - 1;
      }
    }
    result.number[i] = part;
    current = current - a * part;
  }
  result.ZeroSplit();
  return result;
}

/*
TLongNumber TLongNumber::operator ^ (int a) const {

  TLongNumber result(std::string("1"), this->base);
  TLongNumber zero  (std::string("0"), this->base);

  if ((*this) == zero && a == 0) {
    TLongNumber z(std::string("-1"), this->base);
    return z;
  }

  TLongNumber x  = *this;

  while (a > 0) {
    if (a % 2)
      result = result * x;
    x = x * x;
    a /= 2;
  }

  return result;
}
*/

bool TLongNumber::Divisibility(int a) const {
  if (number[0] % a == 0)
    return true;
  else
    return false;
}


TLongNumber TLongNumber::operator ^ (const TLongNumber &a) const {

  TLongNumber two   (std::string("2"), this->base);
  TLongNumber result(std::string("1"), this->base);
  TLongNumber zero  (std::string("0"), this->base);

  TLongNumber tmp = a;

  if ((*this) == zero && a == zero) {
    TLongNumber z(std::string("-1"), this->base);
    return z;

  } else if ((*this) == zero) {
    TLongNumber z(std::string("0"), this->base);
    return z;

  }

  TLongNumber x  = *this;

  while (tmp > zero) {
    if (!tmp.Divisibility(2)) {
      result = result * x;
    }
    x = x * x;
    tmp = tmp / two;
  }

  return result;

}
