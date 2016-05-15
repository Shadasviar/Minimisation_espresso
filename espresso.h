/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 2 -*-  */
/*
 * espresso.h
 * Copyright (C) Uladzislau Harbuz 2016 
 * 
 * Minimisation is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Minimisation is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
