/*
How fast can you compute all the primes less than 1000?
Inspired from https://youtu.be/D3h62rgewZM

This program takes a different approach than Dave's algotithm.

Here, the algorithm maintains a list of primes found, and for
each odd number search through the list of found primes up to
the square-root of that number and if a prime is found to be a
factor then don't add it to the list.  If no factor is found
to evenly divide a number, then it is appended to the list of
found primes.

NOTE: Added a comparison algorithm a friend contributed, and it makes a very
strong argument that the sieve approach is faster.
*/

#include <array>
#include <cmath>
#include <iostream>
#include <chrono>
#include <utility>
#include <vector>
#include <string>


template<
  int upper_bound>
std::vector<bool>
prime_sieve_less_than(){
  std::vector<bool> prime_listing(1+(upper_bound/2), true); // All odd primes, by 2n+1 index.

  constexpr int sieve_input_upper_bound = ((int)sqrt(upper_bound))/2;

  prime_listing[0] = false; // 1 is not prime.
  for(size_t prime_idx = 1; prime_idx < sieve_input_upper_bound; prime_idx++) {
    if(!prime_listing[prime_idx]) {
      continue;
    }
    size_t iter = prime_idx * 2 + 1;
    for(size_t i = prime_idx + iter; i < (1+(upper_bound/2)); i += iter) {
      prime_listing[i] = false;
    }
  }

  return prime_listing;
}


template<
  int upper_bound>
std::vector<int>
find_primes_less_than(){
  std::vector<int> found_primes;
  found_primes.reserve(1+(upper_bound/log(upper_bound)));
  found_primes.push_back(2);
  found_primes.push_back(3);

  for(int number = 6; number <= upper_bound; number += 6){
    const int num_m_one = number-1;
    bool factor_found = false;
    for(auto itr = found_primes.begin(); *itr <= (int)sqrt(num_m_one); ++itr){
      if(! (num_m_one % *itr)){
        factor_found = true;
        break;
      }
    }
    if(!factor_found)
      found_primes.push_back(num_m_one);

    const int num_p_one = number+1;
    factor_found = false;
    for(auto itr = found_primes.begin(); *itr <= (int)sqrt(num_p_one); ++itr){
      if(! (num_p_one % *itr)){
        factor_found = true;
        break;
      }
    }
    if(!factor_found)
      found_primes.push_back(num_p_one);
  }

  return found_primes;
}


template<class return_type>
void run_primes_time_experiment(const char* desc, return_type (*prime_func) () ){
  using namespace std::chrono;

  return_type found;
  int iterations = 0;
  std::chrono::time_point<std::chrono::system_clock> time_end;
  auto time_start = std::chrono::system_clock::now();
  do{
    found = prime_func();
    iterations++;
  }while((time_end = std::chrono::system_clock::now()) - time_start < 5s );

  double time_duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(time_end-time_start)).count();

  std::cout << "With approach \"" << desc << "\": " << time_duration / iterations << " seconds per prime-finding, with " << iterations << " iterations completed." << std::endl;
  // for(int i : found){
  //   std::cout << i << ", ";
  // }
  // std::cout << std::endl;
}


int main(){
  constexpr int upper_bound = 1000000;

  run_primes_time_experiment<std::vector<int>>("list", find_primes_less_than<upper_bound>);
  run_primes_time_experiment<std::vector<bool>>("sieve", prime_sieve_less_than<upper_bound>);

  return 0;
}
