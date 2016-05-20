/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 2 -*-  */
/*
 * espresso.cpp
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

#include "espresso.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <set>
#define DO_NOTHING
#define IN
#define OUT

using namespace std;

enum matrix_type{F, R, Z, D};

set<int> make_by_other(
        const set<int> &vec1,
        const set<int> &vec2);

set<int> make_by_other(
        const set<int> &vec1);

struct vector_with_indikator;

bool vectors_have_collision(
        vector_with_indikator &vec1,
        vector_with_indikator &vec2);

vector<matrix> get_f_and_r(
        vector_with_indikator &vec1,
        vector_with_indikator &vec2);

int invert(const int val);

vector<matrix> get_matrix_b(const vector<matrix> &fr);

vector<vector<int> > get_ones_positions_from_matrix(
        const matrix &B);

vector<vector<int> > cross_out_implicants(
        vector<vector<int> > in_ones);

vector<vector<int> > only_minimal_implicants(
        vector<vector<int> > in_im);

vector<vector<int> > open_brackets(
        vector<vector<int> > in_ones);

struct matrix_b;

struct vec_of_impl;

bool cmp_vec_of_impl(
        vec_of_impl A,
        vec_of_impl B);

bool cmp_for_same_vec_of_impl(
        vec_of_impl A,
        vec_of_impl B);

vector<vec_of_impl> get_vector_of_implicants(
        IN const vector<matrix> &fr,
        OUT vector<matrix_b> &mat_b);

vector<matrix_b> get_matrixes_b(
        IN const vector<matrix> &fr);

bool current_b_has_this_implicant(
        const vector<vec_of_impl> &vector_of_implicants,
        const vector<matrix_b> &vector_of_b,
        int row,
        int column);

matrix get_result_matrix(
        const vector<vec_of_impl> &vector_of_implicants,
        const vector<matrix> &fr,
        const vector<matrix_b> &vector_of_b);

vector<string> get_finally_functions(const vector<matrix> &fr,
        const matrix &result_matr,
        vector<vec_of_impl> &vector_of_implicants);

void delete_vector_of_matrix_b(vector<matrix_b> &);

/*
 * End of prototypes
 * ----------------------------------------------------------------------------------------------------*/


set<int> make_by_other(
  const set<int> &vec1,
  const set<int> &vec2)
{
  set<int> result;
  result.insert(vec1.begin(), vec1.end());
  result.insert(vec2.begin(), vec2.end());

  return make_by_other(result);
}


set<int> make_by_other(const set<int> &vec1)
{
  set<int> result;
  int max = *vec1.rbegin();

  for(int i=0; i<max; i++){
    if(vec1.count(i) == 0){
      result.insert(i);
    }
  }
  return result;
}


struct vector_with_indikator{
  set<int> vec;
  matrix_type indikator; //F- ones R-zeros other- don't carry
};


bool vectors_have_collision(
  vector_with_indikator &vec1,
  vector_with_indikator &vec2)
{

  bool have_collision = false;
  for(set<int>::iterator ite = vec1.vec.begin(); ite != vec1.vec.end(); ++ite){
    if(vec2.vec.count(*ite) != 0){
      have_collision = true;
      break;
    }
  }
  return have_collision;
}


vector<matrix> get_f_and_r(
  vector_with_indikator &vec1,
  vector_with_indikator &vec2)
{

  matrix r,f;
  vector<int> comp;
  if(vec1.indikator == Z) {
    vec1.vec=make_by_other(vec2.vec);
    if(vec2.indikator == F) vec1.indikator = R;
    else if(vec2.indikator == R) vec1.indikator = F;
    else exit(1);
  }
  if(vec2.indikator == Z){
    vec2.vec=make_by_other(vec1.vec);
    if(vec1.indikator == F) vec2.indikator= R;
    else if(vec1.indikator == R) vec2.indikator = F;
    else exit(1);
  }
  
  if(vectors_have_collision(vec1, vec2)){
    cout<<"Error! Vektors have collision! Exiting!\n";
    exit(1);
  }
  comp.push_back(*max_element(vec1.vec.begin(),vec1.vec.end()));
  comp.push_back(*max_element(vec2.vec.begin(),vec2.vec.end()));
  int max = *max_element(comp.begin(),comp.end());
  comp.clear();

  switch (vec1.indikator) {
  case R:
    r = make_bin_matrix_by_dec_vec(vec1.vec,max);
    break;
  case F:
    f = make_bin_matrix_by_dec_vec(vec1.vec,max);
    break;
  default:
    DO_NOTHING
    break;
  }

  switch (vec2.indikator) {
  case R:
    r = make_bin_matrix_by_dec_vec(vec2.vec,max);
    break;
  case F:
    f = make_bin_matrix_by_dec_vec(vec2.vec,max);
    break;
  default:
    DO_NOTHING
    break;
  }

  vector<matrix> fr;
  if(vec1.indikator==vec2.indikator){
    exit(1);
  }
  else if(vec1.indikator == F||vec2.indikator == F){
    if(vec1.indikator == R||vec2.indikator == R){
      fr.push_back(f);
      fr.push_back(r);
    }
    else{
      r = make_bin_matrix_by_dec_vec(make_by_other(vec1.vec,vec2.vec), max);
      fr.push_back(f);
      fr.push_back(r);
    }
  }
  else if(vec1.indikator == R||vec2.indikator == R){
    f = make_bin_matrix_by_dec_vec(make_by_other(vec1.vec,vec2.vec),max);
    fr.push_back(f);
    fr.push_back(r);
  }
  else{
    exit(1);
  }

  return fr;  //fr[0] is F, fr[1] is R, use only this sequence!
}


int invert(const int val){
  if(val==1)return 0;
  if(val==0)return 1;
  else exit(1);
}


vector<matrix> get_matrix_b(
  const vector<matrix> &fr)
{

  vector<matrix> vector_of_b;
  matrix B = createMatrix(fr[1].numOfRows, fr[1].numOfColumns);

  for(int i=0; i<fr[0].numOfRows; i++){
    for(int j=0;j<B.numOfColumns; j++){
      if(fr[0].array[i][j]==1){
        for(int k=0;k<B.numOfRows;k++){
          B.array[k][j]=invert(fr[1].array[k][j]);
        }
        continue;
      }
      if(fr[0].array[i][j]==0){
        for(int k=0;k<B.numOfRows;k++){
          B.array[k][j]=fr[1].array[k][j];
        }
        continue;
      }else exit(1);
    }
    matrix tmp = B;
    vector_of_b.push_back(tmp);
  }
  //delete_matrix(B);
  return vector_of_b;
}


vector<vector<int> > get_ones_positions_from_matrix(
  const matrix &B)
{

  vector<int> vector_of_ones;
  vector<vector<int> > result;

  for(int i=0;i<B.numOfRows;i++){
    for(int j=0;j<B.numOfColumns;j++){
      if(B.array[i][j]==1){
        vector_of_ones.push_back(j);
      }
      else{
        continue;
      }
    }
    result.push_back(vector_of_ones);
    vector_of_ones.clear();
  }

  return result;
}


vector<vector<int> > cross_out_implicants(
  vector<vector<int> > in_ones)
{

  vector<int> bufer;
  vector<size_t> ind_to_del;
   
  for(size_t s = 0; s < in_ones.size(); s++){
    sort(in_ones[s].begin(),in_ones[s].end());
    in_ones[s].resize(distance(in_ones[s].begin(),unique(in_ones[s].begin(),in_ones[s].end())));
  }

  sort(in_ones.begin(),in_ones.end());
  in_ones.resize(distance(in_ones.begin(),unique(in_ones.begin(),in_ones.end())));

  for(size_t i = 0; i < in_ones.size(); i++){
    bufer=in_ones[i];
    for(size_t k = 0; k < in_ones.size(); k++){
      if(k == i){
        continue;
      }
      sort(bufer.begin(),bufer.end());
      sort(in_ones.at(k).begin(),in_ones.at(k).end());
      if(includes(in_ones.at(k).begin(),in_ones.at(k).end(),bufer.begin(),bufer.end())){
        ind_to_del.push_back(k);
      }
    }       
    bufer.clear();
  }

  int h=0;
  for(size_t g = 0; g < ind_to_del.size(); g++){
    sort(ind_to_del.begin(),ind_to_del.end());
    ind_to_del.resize(unique(ind_to_del.begin(),ind_to_del.end())-ind_to_del.begin());
    in_ones.erase(in_ones.begin()+ind_to_del.at(g)-h++);
  }

    return in_ones;
}


vector<vector<int> > only_minimal_implicants(
  vector<vector<int> > in_im)
{

  vector<int> vector_of_min;
  vector<vector<int> > result;

  for(size_t i=0; i < in_im.size(); i++){
    vector_of_min.push_back(in_im[i].size());
  }

  size_t min = *min_element(vector_of_min.begin(),vector_of_min.end());
  for(size_t i=0; i < in_im.size(); i++){
    if(in_im[i].size() == min) result.push_back(in_im[i]);
  }
  return result;
}


vector<vector<int> > open_brackets(
  vector<vector<int> > in_ones)
{

  if(in_ones.size()<2){
    return in_ones;
  }
  else{

    vector<vector<int> > first_col,buf_2;
    vector<int> bufer, first_col_buf;

    for(size_t j = 0; j < in_ones.at(0).size(); j++){
      for(size_t i = 0; i < in_ones.at(1).size(); i++){
        bufer.push_back(in_ones.at(0).at(j));
        bufer.push_back(in_ones.at(1).at(i));
        first_col.push_back(bufer);
        bufer.clear();
      }
    }

    for(size_t m = 1; m < in_ones.size()-1; m++){
      for(size_t i=0;i < first_col.size(); i++){
        bufer=in_ones[m+1];
        for(size_t k=0; k < bufer.size(); k++){
          first_col_buf=first_col[i];
          first_col_buf.push_back(bufer[k]);
          buf_2.push_back(first_col_buf);
        }
      }
      first_col=cross_out_implicants(buf_2);
      buf_2.clear();
    }

    first_col=cross_out_implicants(first_col);
    first_col=only_minimal_implicants(first_col);

    return first_col;
  }
}


struct matrix_b{
  matrix matr;
  vector<vector<int> > implicants;
};


struct vec_of_impl{
  int num_of_line_from_F;
  vector<int> vec;
};


bool cmp_vec_of_impl(
  vec_of_impl A,
  vec_of_impl B)
{
  return A.vec<B.vec;
}


bool cmp_for_same_vec_of_impl(
  vec_of_impl A,
  vec_of_impl B)
{
  return A.vec==B.vec;
}


vector<vec_of_impl> get_vector_of_implicants(
  IN const vector<matrix> &fr,
  OUT vector<matrix_b> &mat_b)
{
  vector<vec_of_impl> result;
  vector<vector<int> > bufer;
  vec_of_impl vec_buf;
  vector<matrix> B_sigma = get_matrix_b(fr);
  matrix_b m_b;

  for(int i = 0; i < fr[0].numOfRows; i++){
    bufer = get_ones_positions_from_matrix(B_sigma.at(i));
    bufer = open_brackets(bufer);
    m_b.matr = B_sigma.at(i);
    for(size_t j = 0; j < bufer.size(); j++){
      vec_buf.vec = bufer.at(j);
      vec_buf.num_of_line_from_F = i;
      result.push_back(vec_buf);
      m_b.implicants.push_back(bufer.at(j));
    }
    mat_b.push_back(m_b);
    m_b.implicants.clear();
  }

  sort(result.begin(),result.end(),cmp_vec_of_impl);
  result.resize(distance(result.begin(),unique(result.begin(),result.end(),cmp_for_same_vec_of_impl)));

  return result;
}


bool current_b_has_this_implicant(
  const vector<vec_of_impl> &vector_of_implicants,
  const vector<matrix_b> &vector_of_b,
  int row,
  int column)

{
  return find(vector_of_b[row].implicants.begin(),vector_of_b[row].implicants.end(),vector_of_implicants[column].vec)
    != vector_of_b[row].implicants.end();
}


matrix get_result_matrix(
  const vector<vec_of_impl> &vector_of_implicants,
  const vector<matrix> &fr,
  const vector<matrix_b> &vector_of_b)
{
  int num_of_unique_implicamts = vector_of_implicants.size();
  matrix result = createMatrix(fr[0].numOfRows,num_of_unique_implicamts);
  for(int i=0;i<result.numOfRows;i++){
    for(int j=0;j<result.numOfColumns;j++){
      if(current_b_has_this_implicant(vector_of_implicants, vector_of_b, i, j)){
        result.array[i][j]=1;
      }
      else{
        result.array[i][j]=0;
      }
    }
  }
  return result;
}


vector<string> get_finally_functions(
  const vector<matrix> &fr,
  const matrix &result_matr,
  vector<vec_of_impl> &vector_of_implicants)
{

  vector<vector<int> > vec=get_ones_positions_from_matrix(result_matr);
  vec=open_brackets(vec);
  string min_func;
  vector<string> result;

  for(size_t v=0; v<vec.size();v++){
    for(size_t i=0; i<vec[v].size();i++){
      for(int j=0;j<fr[0].numOfRows;j++){
        if(j==vector_of_implicants[vec[v][i]].num_of_line_from_F){
          for(size_t k=0;k<vector_of_implicants[vec[v][i]].vec.size();k++){
            if(fr[0].array[vector_of_implicants[vec[v][i]].num_of_line_from_F][vector_of_implicants[vec[v][i]].vec[k]]==1){
              min_func.append("X");
              min_func.append(std::to_string(vector_of_implicants[vec[v][i]].vec[k]));
            }
            else{
              min_func.append("!X");
              min_func.append(std::to_string(vector_of_implicants[vec[v][i]].vec[k]));
            }
          }
        }
      }
      min_func.append("+");
    }
    min_func.resize(min_func.size()-1);
    result.push_back(min_func);
    min_func.clear();
  }

  return result;
}


void print_implicant(
  vector<matrix_b> mat_b,
  int n_line,
  int j,
  vector<matrix> fr)
{

  for(int i = 0; i < mat_b.at(n_line).matr.numOfColumns; i++){
    if(find(mat_b.at(n_line).implicants.at(j).begin(), mat_b.at(n_line).implicants.at(j).end(), i) 
      != mat_b.at(n_line).implicants.at(j).end())
    {
      cout<<fr.at(0).array[n_line][i];
    }
    else{
      cout<<"-";
    }
  }
}


string print_implicant_as_string(
  vector<matrix_b> mat_b,
  int n_line,
  int j,
  vector<matrix> fr)
{

	string res;
  for(int i = 0; i < mat_b.at(n_line).matr.numOfColumns; i++){
    if(find(mat_b.at(n_line).implicants.at(j).begin(), mat_b.at(n_line).implicants.at(j).end(), i) 
      != mat_b.at(n_line).implicants.at(j).end())
    {
      res.append(to_string(fr.at(0).array[n_line][i]));
    }
    else{
      res.append("-");
    }
  }
  return res;
}


void write_to_file(const set<int> &vec1,
  const set<int> &vec2,
  char *chose,
  const char *filename)
{  
    ofstream ofile;
    ofile.open(filename);
    ofile << get_finally_functions_as_str(vec1, vec2, chose);
    ofile.close();
}


void show_finally_functions(
  const set<int> &vec1,
  const set<int> &vec2,
  char *chose)
{
  cout<<get_finally_functions_as_str(vec1, vec2, chose);
}

string get_finally_functions_as_str(const set<int> &vec1, const set<int> &vec2, char *chose){

    vector<vector_with_indikator> vec;
    vector_with_indikator vin;
    set<int> tmp[2];
    string result;

    tmp[0] = vec1;
    tmp[1] = vec2;
    for(int i = 0; i < 2; i++){
      switch (chose[i]) {
        case 'F':
          vin.indikator = F;
          vin.vec = tmp[i];
          vec.push_back(vin);
          break;
        case 'R':
          vin.indikator = R;
          vin.vec = tmp[i];
          vec.push_back(vin);
          break;
        case 'Z':
          vin.indikator = Z;
          vec.push_back(vin);
          break;
        default:
          vin.indikator = D;
          vin.vec = tmp[i];
          vec.push_back(vin);
          break;
      }
    }

    vector<matrix> mat = get_f_and_r(vec[0],vec[1]);
    result.append("\nMatrix of ones: \n\n");
    result.append(show_matrix_as_string(mat[0]).c_str());
    result.append("\nMatrix of zeros: \n\n");
    result.append(show_matrix_as_string(mat[1]).c_str());
    matrix res;

    vector<vec_of_impl> vim;
    vector<matrix_b> mat_b;
    vim=get_vector_of_implicants(mat,mat_b);
    result.append("Block matrixes:");
    for(size_t i = 0; i < mat_b.size(); i++){
      result.append("\nB");
      result.append(to_string(i).c_str());
      result.append("\n\n");
      result.append(show_matrix_as_string(mat_b[i].matr).c_str());
      result.append("\nimplicants:\n\n");
      for(size_t j = 0; j < mat_b[i].implicants.size(); j++){
        result.append(print_implicant_as_string(mat_b, i, j, mat).c_str());
        result.append("\n\n");
      }
    }

    res = get_result_matrix(vim,mat,mat_b);
    result.append("FUNCTIONS are:\n");
    vector<string> s = get_finally_functions(mat,res,vim);
    for(size_t i = 0; i < s.size(); i++){
      result.append(s[i].c_str());
    }
    return result;

}

void write_to_file(const string &in_string, const char *filename)
{
    ofstream ofile;
    ofile.open(filename);
    ofile << in_string;
    ofile.close();
}
