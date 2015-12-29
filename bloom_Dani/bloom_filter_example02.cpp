
#include "bloom_inout.hpp"
using namespace std;


int main(int argc, char* argv[]) {
   vector<unsigned int> word_list;
	bloom_inout inout;
	//LOAD WORD LIST
	if (!inout.load_word_list(argc,argv,word_list)) return 1;

   return 0;
}



