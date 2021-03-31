# How fast can you compute all the primes less than 1000?
Inspired from https://youtu.be/D3h62rgewZM

This program takes a different approach than Dave's algotithm.

Here, the algorithm maintains a list of primes found, and for
each odd number search through the list of found primes up to
the square-root of that number and if a prime is found to be a
factor then don't add it to the list.  If no factor is found
to evenly divide a number, then it is appended to the list of
found primes.

# License

Public Domain
