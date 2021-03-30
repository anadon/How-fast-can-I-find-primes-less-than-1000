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

I've found this code to be 3610.4517312542994X faster.
*/

#include <array>
#include <cmath>
#include <iostream>
#include <chrono>


template<
  int upper_bound>
std::array<int, 1+(upper_bound/2)>
find_primes_less_than(){
  std::array<int, 1+(upper_bound/2)> found_primes;
  size_t end_index = 0;
  found_primes[end_index++] = 2;

  for(int number = 3; number <= upper_bound; number += 2){
    bool factor_found = false;
    for(auto possible_factor_itr = found_primes.begin(); *possible_factor_itr < floor(sqrt(number)); ++possible_factor_itr){
      if(! number % *possible_factor_itr){
        factor_found = true;
        break;
      }
    }
    if(!factor_found)
      found_primes[end_index++] = number;
  }

  return found_primes;
}


int main(int argc, char **argv){
  using namespace std::chrono_literals;

  int iterations = 0;
  std::chrono::time_point<std::chrono::system_clock> time_end;
  auto time_start = std::chrono::system_clock::now();
  do{
    find_primes_less_than<1000>();
    iterations++;
  }while((time_end = std::chrono::system_clock::now()) - time_start < 5s );

  double time_duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(time_end-time_start)).count();

  std::cout << time_duration / iterations << " seconds per prime-finding, with " << iterations << " iterations completed." << std::endl;

  return 0;
}
