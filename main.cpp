/**
 * @file 		SemOpt.cpp
 * @brief 		Main file
 * @author 		Federico Cerutti <f.cerutti@abdn.ac.uk> and
 * 				Mauro Vallati <m.vallati@hud.ac.uk>
 * @copyright	GNU Public License v2
 */

#include "semopt.h"

/**
 * @brief Configuration variables
 */
bool debug = false;
bool externalsat = true;
string satsolver;
int labellingconditions = 0;
bool manualopt = false;
string inputfile;
string semantics;

time_t start;

#ifndef UNIT_TEST




int main(int argc, char *argv[]){

	//debug = true; // more verbose
	debug=false;
	inputfile = string("test-input/esempio2-lucidi.dl");
	AF gamma = AF();
	if (!gamma.readFile(inputfile))
	{
		return EXIT_FAILURE;
	}

	SetArguments *A = new SetArguments();
	*A=SetArguments(*gamma.get_arguments());

	set<SetArguments*> res;

	res=pref(gamma,*A);

	set<SetArguments*> :: iterator kt;
	for( kt = res.begin(); kt != res.end(); kt++ ){
		cout << **kt << endl;
	}

	return EXIT_SUCCESS;
}
#endif
