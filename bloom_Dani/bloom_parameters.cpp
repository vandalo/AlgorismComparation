#define maxSize 10000000
#include "bloom_parameters.hpp"
using namespace std;


bloom_parameters::bloom_parameters():min_size(1),
     max_size(maxSize),
     min_hashes(1),
     max_hashes(maxSize) {}





