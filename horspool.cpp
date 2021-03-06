////////////////////////////////////////////////////////////////////////////////
// horspool string matching algorithm
//
// Time complexity: best O(n/m), worst O(nm)?, where m, n is the length of pattern and text respectively 
//
// Author: Tiansheng(Chinson) Liu, 2013 - . 
//
// You may freely use or modify the code provided this copyright is included
// in all derived versions.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Usage:
// > g++ -o horspool horspool.cpp
// > ./horspool
// > 2
// or
// >./horspool announce CPM_annual_conference_announce
// or
// >./horspool ATATA AGATACGATATATAC
// or
// > ./horspool <own-defined pattern> <own-defined text>
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define DEBUG

typedef map<char, int> c_map;
typedef vector<int> int_vector;

///
/// @brief get dist based on bad character rule 
///
void get_dist1(char *pattern, int M, c_map &dist1)
{
  for (int m = 0; m < M - 1; ++m) {
    dist1[pattern[m]] = M - m - 1;
  }

#ifdef DEBUG
  cout<<"dist1 : \n";
  for (c_map::iterator it = dist1.begin(); it != dist1.end(); ++it)
    cout<<it->first<<" "<<it->second<<" ";
  cout<<endl;
#endif
}

///
/// @brief find the first index of @a pattern in string @a text using horspool string matching
/// @retval -1 if not found
int horspool_match(char *pattern, char *text)
{
  static const int not_found = -1;

  int M = strlen(pattern);
  int N = strlen(text);
  if (N < M)
    return not_found;

  //get dist based on bad character shifting rule
  c_map dist1; //map: a character <-> the last occurrence of character in pattern
  get_dist1(pattern, M, dist1);

  //suffix searching
  int n = M - 1, i, m, d1;
  while (n < N) {
#ifdef DEBUG
    cout<<"\nsearching position: n = "<<n<<endl;
#endif

    i = n;
    m = M - 1;
    for (; m >= 0 && pattern[m] == text[i]; --i, --m);
    if (m < 0) {//matched
      return i + 1;
    }
    else {
      c_map::iterator it_f = dist1.find(text[n]);
      d1 = (it_f != dist1.end())? it_f->second : M;
      n += d1;
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

  cout<<"find "<<pattern<<" in "<<text<<" (zero-based) : "<<horspool_match(pattern, text)<<endl;
  return 0;
}
