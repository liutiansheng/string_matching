////////////////////////////////////////////////////////////////////////////////
// BF string matching - a simplest and brute force algorithm
//
// Time complexity: O(mn) where m, n is the length of pattern and text respectively 
//
// Author: Tiansheng(Chinson) Liu, 2013 - . 
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
int bf_match(char *pattern, char *text)
{
  static const int not_found = -1;

  if (!pattern || !(*pattern) || !text)
    return not_found;

  int n = 0, m = 0;
  for (int j = 0; text[j] != '\0'; ++j) {
    for (n = j, m = 0; text[n] != '\0' && text[n] == pattern[m]; ++n, ++m);
    if (pattern[m] == '\0') { //matched
      return j;
    }
    if (text[n] == '\0') {
      break;
    }
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

  cout<<"find "<<pattern<<" in "<<text<<" (zero-based) : "<<bf_match(pattern, text)<<endl;
  return 0;
}
