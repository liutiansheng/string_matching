////////////////////////////////////////////////////////////////////////////////
// BF string matching - a simplest and brute force algorithm
//
// Time complexity: O(mn) where m, n is the length of pattern and text respectively 
//
// Author: Tiansheng(Chinson) Liu, liutiansheng@gmail.com, 2013 - . 
//
// You may freely use or modify the code provided this copyright is included
// in all derived versions.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Usage:
// > g++ -o bf bf.cpp
// > ./bf
// > 2
// or
// > ./bf <own-defined pattern> <own-defined text>
////////////////////////////////////////////////////////////////////////////////
#include<iostream>

using namespace std;

///
/// @brief find the first index of @a pattern in string @a text using BF string matching
/// @retval -1 if not found
/// @retval >= 0 if found
/// 
int bf_match(char *pattern, char *text) {
  if (!pattern || !(*pattern) || !text)
    return -1;

  int k = 0;
  for (int j = 0; text[j] != '\0'; ++j) {
    if (text[j] == pattern[k]) {
      int m = j + 1; k += 1;
      for (; text[m] != '\0' && pattern[k] != '\0'; ++m, ++k) {
        if (text[m] != pattern[k]) break;
      }
      if (text[m] == '\0' && pattern[k] != '\0') {
        return -1;
      }
      if (pattern[k] == '\0') { //matched
        return j;
      }
      k = 0;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {

  char default_text[] = "asdfasdfa";
  char default_pattern[] = "dfas";

  char *text = default_text, *pattern = default_pattern;
  if (argc == 3) {
    text = argv[2];
    pattern = argv[1];
  }

  cout<<"find "<<pattern<<" in "<<text<<" : "<<bf_match(pattern, text)<<endl;
  return 0;
}
