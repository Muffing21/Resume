#include "radix.h"
#include <string>
#include <map>
#include <iostream>
#include <array>
#include <algorithm>
#include <thread>
#include <atomic>

using namespace std;



//https://www.ime.usp.br/~yoshi/Sedgewick/Algs4th/Slides/51StringSorts.pdf
int charAt(string s, unsigned int d){
  if(d < s.size()){
    return s.at(d) - '0';
  }
  else{
    return -1;
  }
}

vector<std::string> int_to_string(std::vector<unsigned int> &list){
  std::vector<std::string> temp;
  for(unsigned int i = 0; i < list.size(); i++){
    temp.push_back(std::to_string(list[i]));
  }
  return temp;
}

vector<unsigned int> string_to_int2(vector<string> &string_list){
  std::vector<unsigned int> temp;
  for(unsigned int i = 0; i < string_list.size(); i++){
    temp.push_back(stoul(string_list[i], nullptr));
  }
  return temp;
}

vector<vector<unsigned int>> string_to_int(vector<vector<string>> &string_list){
  vector<vector<unsigned int>> temp(string_list.size());
  for(unsigned int i = 0; i < string_list.size(); i++){
    for(unsigned int j = 0; j < string_list[i].size(); j++){
      temp[i].push_back(stoul(string_list[i][j], nullptr));
    }
  }
  return temp;
}


//https://www.ime.usp.br/~yoshi/Sedgewick/Algs4th/Slides/51StringSorts.pdf
void radixSort(vector<string> &a, unordered_map<unsigned int, string> &aux, int lo, int hi, int d){
  if(hi <= lo){
    return;
  }
  //storing how many times MSD occurred in the index respective to their MSD
  int count[10+2] = {0};
  for(int i = lo; i <= hi; i++){
      count[charAt(a[i], d) + 2]++;
  }
  for(int r = 0; r < 10+1; ++r){  //increment current element based on previous element
    count[r+1] += count[r];
  }
  for(int i = lo; i <= hi; i++){
    aux[count[charAt(a[i], d) + 1]++] = a[i]; //problem with this
  }
  for(int i = lo; i <= hi; i++){
    a[i] = aux[i - lo];
  }
  for(int r = 0; r < 10; r++){
    radixSort(a, aux, lo + count[r], lo + count[r+1] - 1, d + 1);
  }
}

void RadixSorter::sequentialMSD(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists){
  for(unsigned int i = 0; i < lists.size(); i++){
    vector<std::string> a = int_to_string(lists[i].get());
    unordered_map<unsigned int, string> aux;
    radixSort(a, aux, 0, lists[i].get().size()-1, 0);
    lists[i].get() = string_to_int2(a);
  }
  return;
}

//    
void RadixSorter::embarrassinglyParallelMSD(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists, const unsigned int cores){
  thread threads[cores];
  atomic<unsigned int> counter(0);
  
  auto lambdaFunc = [&](){
    unsigned int copy = counter.fetch_add(1);
    while(copy < lists.size()){
      vector<std::string> a = int_to_string(lists[copy].get());
      unordered_map<unsigned int, string> aux;
      radixSort(a, aux, 0, lists[copy].get().size()-1, 0);
      lists[copy].get() = string_to_int2(a);
      copy = counter.fetch_add(1);
    }
  };
  for(unsigned int j = 0; j < cores; j++){
    threads[j] = thread(lambdaFunc);
  }
  
  for(unsigned int i = 0; i < cores; i++){
    threads[i].join();
  }
  return;
}

//not exactly truly parallel, this works for 10 cores
//we are basically sorting vectors according to their MSD before running RadixSort (for potential speedup)
vector<vector<string>> sublist(vector<string> &a, int hi){
  //storing how many times MSD occurred in the index respective to their MSD
  vector<vector<string>> sub_list(99);
  for(int i = 0; i <= hi; i++){
    sub_list[a[i].at(0) - '0' - 1].push_back(a[i]);
  }
  return sub_list;
}

//attempt on truly parallel
//given vector in vectors, the subspace for vectors are divided depending on the number of cores available
void RadixSorter::trulyParallelMSD(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists, unsigned int cores){
  for(unsigned int i = 0; i < lists.size(); i++){
      vector<std::string> a = int_to_string(lists[i].get());
      vector<vector<string>> sub_list = sublist(a, lists[i].get().size()-1);
      vector<vector<unsigned int>> sub_list_int = string_to_int(sub_list);
      vector<std::reference_wrapper<std::vector<unsigned int>>> wrapper(sub_list_int.begin(), sub_list_int.end());
      embarrassinglyParallelMSD(wrapper, cores);
      lists[i].get().clear();
      for(unsigned int j = 0; j < wrapper.size(); j++){
        for(unsigned int k = 0; k < wrapper[j].get().size(); k++){
          lists[i].get().push_back(wrapper[j].get()[k]);
        }
      }
      
  }
}
