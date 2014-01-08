////////////////////////////////////////////////////////////////////////////////
// BM string matching algorithm
//
// Time complexity: best O(n/m), worst O(nm)?, where m, n is the length of pattern and text respectively 
//
// Author: Tiansheng(Chinson) Liu, liutiansheng@gmail.com, 2013 - . 
//
// You may freely use or modify the code provided this copyright is included
// in all derived versions.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Usage:
// > g++ -o bm bm.cpp
// > ./bm
// > 2
// or
// > ./bm <own-defined pattern> <own-defined text>
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
/// @brief get dist based on good suffix rule 
///
/// @reference http://www.searchtb.com/2011/07/字符串匹配那些事(-).html
///
void get_dist2(char *pattern, int_vector &dist2, int M)
{
  //pattern[m - suffix[m] + 1,...,m] == pattern[M - suffix[m],...,M - 1]
  int_vector suffix(M);
  suffix[M - 1] = M;
  for (int m = M - 2; m >= 0; --m) {
    int i = m;
    for (; i >= 0 && pattern[i] == pattern[M - 1 - (m - i)]; --i);
    suffix[m] = m - i;
  }
#ifdef DEBUG
  cout<<"suffix: \n";
  for (int m = 0; m < M; ++m) {
    cout<<suffix[m]<<" ";
  }
  cout<<endl;
#endif

  //initialize
  for (int m = 0; m < M; ++m) dist2[m] = M;

  //suffix is not matched a substing, but a suffix is matched a prefix
  int j = 0;
  for (int m = M - 1; m >= 0; --m) {
    if (suffix[m] == m + 1) { //suffix is matched prefix
      for (; j < M - 1 - m; ++j) {
        dist2[j] = min(dist2[j], M - 1 - m);
      }
    }
  }
  //suffix is matched substring
  for (int m = 0; m <= M - 2; ++m) {
    j = M - 1 - suffix[m];
    dist2[j] = min(dist2[j], M - 1 - m);
  }

#ifdef DEBUG
  cout<<"dist2 : \n";
  for(int m = 0; m < M; ++m) cout<<dist2[m]<<" ";
  cout<<endl;
#endif
}

///
/// @brief find the first index of @a pattern in string @a text using bm string matching
/// @retval -1 if not found
int bm_match(char *pattern, char *text)
{
  static const int not_found = -1;

  int M = strlen(pattern);
  int N = strlen(text);
  if (N < M)
    return not_found;

  //get dist based on bad character shifting rule
  c_map dist1; //map: a character <-> the last occurrence of character in pattern
  get_dist1(pattern, M, dist1);

  //get dist based on good suffix shifting rule
  int_vector dist2(M);
  get_dist2(pattern, dist2, M);

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
      c_map::iterator it_f = dist1.find(text[i]);
      d1 = (it_f != dist1.end())? it_f->second : M;
      n += max(dist2[m], d1 - (M - 1 - m));
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

  cout<<"find "<<pattern<<" in "<<text<<" (zero-based) : "<<bm_match(pattern, text)<<endl;
  return 0;
}
