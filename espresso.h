#include "matrix.h"
#include <string>
#ifndef ESPRESSO
#define ESPRESSO

void show_finally_functions(const vector<int> &vec1,
  const vector<int> &vec2,
  char *chose
);


void write_to_file(
  const vector<int> &vec1,
  const vector<int> &vec2,
  char *chose,
  const char *filename
);


void write_to_file(
  const string &in_string,
  const char *filename
);


string get_finally_functions_as_str(const vector<int> &vec1,
  const vector<int> &vec2,
  char *chose
);

#endif //ESPRESSO
