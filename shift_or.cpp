////////////////////////////////////////////////////////////////////////////////
// Shift-Or string matching algorithm using bitwise operation
//
// Time complexity: O(m+n) where m, n is the length of pattern and text respectively 
//
// Author: Tiansheng(Chinson) Liu, 2013 - . 
//
// You may freely use or modify the code provided this copyright is included
// in all derived versions.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Usage:
// > g++ -o shift_or shift_or.cpp
// > ./shift_or
// > 2
// or
// > ./shift_or <own-defined pattern> <own-defined text>
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

#define DEBUG

using namespace std;

typedef vector<bool> bit_vector;//not use bitset which needs fixed size
typedef map<char, bit_vector> b_map;

///
/// @brief shift a bit vector to left or right @a num times
///
void shift_bit_vector(bit_vector &v, int num, bool to_left)
{
#ifdef DEBUG
  cout<<"before shifting to "<<(to_left? "left" : "right")<<" : ";
  for (int i = v.size() - 1; i >= 0; --i) {
  cout<<(v[i]? 1 : 0);
  }
  cout<<endl;
#endif

  if (to_left) {
    for (int i = v.size() - 1; i >= num; --i) {
      v[i] = v[i - num];
    }
    for (int i = 0; i < num; ++i) {
      v[i] = 0;
    }
  } else {
    for (int i = 0; i < v.size() - num; ++i) {
      v[i] = v[i + num];
    }
    for (int i = v.size() - num; i < v.size(); ++i) {
      v[i] = 0;
    }
  }

#ifdef DEBUG
  cout<<"after  shifting to "<<(to_left? "left" : "right")<<" : ";
  for (int i = v.size() - 1; i >= 0; --i) {
  cout<<(v[i]? 1 : 0);
  }
  cout<<endl;
#endif
}

///
/// @brief generate preprocess data: B array to record the flag for each charactar in pattern
///
void generate_B(char *pattern, int M, b_map &B)
{
  bit_vector empty(M, true);
  bit_vector *b = NULL;
  for (int m = 0; m < M; ++m) {
    char p = pattern[m];
    b_map::iterator it_f = B.find(p);
    if (it_f == B.end()) {
      B[p] = empty;
      b = &(B[p]);
    } else {
      b = &it_f->second;
    }
    (*b)[m] = false;
  }

#ifdef DEBUG
  cout<<"B array for debug:\n";
  for (b_map::iterator it = B.begin(); it != B.end(); ++it) {
    cout<<it->first<<" ";
    bit_vector &b = it->second;
    for (int m = M - 1; m >= 0; --m) {
      cout<<(b[m]? 1 : 0);
    }
    cout<<"\n";
  }
  cout<<endl;
#endif
}

///
/// @brief find the first index of @a pattern in string @a text using Shift-Or string matching
/// @retval -1 if not found
/// @retval >= 0 if found
/// 
int shift_or_match(char *pattern, char *text)
{
  static const int not_found = -1;

  if (!pattern || !(*pattern) || !text)
    return not_found;

  //preprocess
  b_map B;
  int M = strlen(pattern);
  generate_B(pattern, M, B);

  //matching
  bit_vector empty(M, true);
  bit_vector D(empty);
  bit_vector *b = NULL;
  //D' = ((D << 1) | 0x1) & B[text[n]]
  for (int n = 0; text[n] != '\0'; ++n) {
    shift_bit_vector(D, 1, true);

    //find the b related to text[n], if no, use empty
    b_map::iterator it_f = B.find(text[n]);
    if (it_f == B.end())
      b = &empty;
    else
      b = &it_f->second;

    transform(D.begin(), D.end(), b->begin(), D.begin(), logical_or<bool>());
    if (!D[M-1])
      return n - M + 1;
  }
  return not_found;
}

int main(int argc, char *argv[])
{
  char default_text[]    = "asdfasdfa";
  char default_pattern[] = "dfas";

  char *text = default_text, *pattern = default_pattern;
  if (argc == 3) {
    text    = argv[2];
    pattern = argv[1];
  }

  cout<<"find "<<pattern<<" in "<<text<<" (zero-based) :\n"<<shift_or_match(pattern, text)<<endl;
  return 0;
}
