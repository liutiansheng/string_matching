////////////////////////////////////////////////////////////////////////////////
// KMP string matching algorithm
//
// Time complexity: O(m + n) where m, n is the length of pattern and text respectively 
//
// Author: Tiansheng(Chinson) Liu, liutiansheng@gmail.com, 2013 - . 
//
// You may freely use or modify the code provided this copyright is included
// in all derived versions.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Usage:
// > g++ -o kmp kmp.cpp
// > ./kmp
// > 2
// or
// > ./kmp <own-defined pattern> <own-defined text>
////////////////////////////////////////////////////////////////////////////////
#include<iostream>

using namespace std;


///
/// @brief get the next longest match length 
///        if next[m] = k, it means pattern[0...k-1] = pattern[m-k...m-1]
/// @param M the length of pattern string
/// 
void calc_next_longest_matchs(char *pattern, int next[], int M)
{
  next[0] = -1;
  int k = next[0];
  for (int m = 1; m < M; ++m) {
    if (k == -1 || pattern[k] == pattern[m - 1]) {
      k = k + 1;
    } else {
      k = next[k];
      if (k == -1) {
        k = 0;
      }
    }
    next[m] = k;
  }
//  output for debug
//  cout<<"\n next array is:\n";
//  for (int m = 0; m < M; ++m) {
//    cout<<next[m];
//  }
//  cout<<endl;
}

///
/// @brief find the first index of @a pattern in string @a text using kmp string matching
/// @retval -1 if not found
/// @retval >= 0 if found
/// 
int kmp_match(char *pattern, char *text)
{
  static const int not_found = -1;

  if (!pattern || !(*pattern) || !text)
    return not_found;

  int M = strlen(pattern);
  int *next = new int[M];
  if (!next) { //out of memory
    return not_found;
  }
  calc_next_longest_matchs(pattern, next, M);

  int m = 0;
  for (int n = 0; text[n] != '\0';) {
    if (m == -1 || text[n] == pattern[m]) {
      if (m == M - 1)
        return n - M + 1;
      ++n; ++m;
    } else {
      m = next[m];
    }
  }

  delete[] next; next = NULL;
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

  cout<<"find "<<pattern<<" in "<<text<<" (zero-based) : "<<kmp_match(pattern, text)<<endl;
  return 0;
}
