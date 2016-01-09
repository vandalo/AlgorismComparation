#
# Open Bloom Filter Master MakeFile
# By Arash Partow - 2000
#
# URL: http://www.partow.net/programming/hashfunctions/index.html
#
# Copyright Notice:
# Free use of this library is permitted under the guidelines
# and in accordance with the most current version of the
# Common Public License.
# http://www.opensource.org/licenses/cpl1.0.php
#

COMPILER         = -c++ 
OPTIMIZATION_OPT = -O3
OPTIONS          = -pedantic-errors -ansi -Wall -Wextra -Werror -Wno-long-long $(OPTIMIZATION_OPT) -o
LINKER_OPT       = -L/usr/lib -lstdc++ -std=c++0x

BUILD+=main_01

all: $(BUILD)

main_01: bloom/bloom_filter.hpp bloom/bloom_parameters.hpp bloom/bloom_filter.cpp bloom/bloom_parameters.cpp hash/Hash.cpp hash/Hash.hpp trie/trie.hpp cercabinaria/CercaBinaria.cpp cercabinaria/CercaBinaria.hpp mainGeneral.cpp
	$(COMPILER) $(OPTIONS) test1 bloom/bloom_filter.cpp bloom/bloom_parameters.cpp cercabinaria/CercaBinaria.cpp trie/trie.cpp hash/Hash.cpp mainGeneral.cpp $(LINKER_OPT)

clean:
	rm -f core *.o *.bak *stackdump *#


#
# The End !
#
