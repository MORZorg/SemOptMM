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
	inputfile = string("test-input/esempio3-test.dl");
	AF framework = AF();
	if (!framework.readFile(inputfile))
	{
		return -1;
	}
	//list<SCC*> a=SCCSSEQ(framework);

	SetArguments e, *I, *C=framework.get_arguments();
	//SetArguments *I=new SetArguments();
	I=framework.get_arguments();
	grounded(*C, &e, I);

	cout << "e: "<<e<<endl;
	cout << "I: "<<*I<<endl;
/*
 * 	Preferred p = Preferred();
	SetArguments A_set1 = SetArguments();
	A_set1.add_Argument(framework.getArgumentByName("a1"));
	A_set1.add_Argument(framework.getArgumentByName("a2"));
	A_set1.add_Argument(framework.getArgumentByName("a3"));
	A_set1.add_Argument(framework.getArgumentByName("a4"));
	A_set1.add_Argument(framework.getArgumentByName("a5"));
	A_set1.add_Argument(framework.getArgumentByName("a6"));

	SetArguments C_set1 = SetArguments();
	C_set1.add_Argument(framework.getArgumentByName("a1"));
	C_set1.add_Argument(framework.getArgumentByName("a6"));

	p.prefSAT(&A_set1, &C_set1);

	cout << "First example" << endl;
	int extension_counter = 1;

	for (Preferred::iterator it = p.begin(); it != p.end(); it++)
	{
		cout << "Extension number " << extension_counter++ << endl;
		for (SetArgumentsIterator itarg = (*it).inargs()->begin();
				itarg != (*it).inargs()->end(); itarg++)
		{
			cout << (*itarg)->getName() << endl;
		}
		cout << "An alternative way to print out this extension" << endl;
		cout << *((*it).inargs()) << endl;
	}
	cout << "End of first example" << endl << endl;


	SetArguments A_set2 = SetArguments();
	A_set2.add_Argument(framework.getArgumentByName("a1"));
	A_set2.add_Argument(framework.getArgumentByName("a2"));
	A_set2.add_Argument(framework.getArgumentByName("a3"));
	A_set2.add_Argument(framework.getArgumentByName("a4"));
	A_set2.add_Argument(framework.getArgumentByName("a5"));
	A_set2.add_Argument(framework.getArgumentByName("a6"));

	SetArguments C_set2 = SetArguments();
	C_set2.add_Argument(framework.getArgumentByName("a2"));
	C_set2.add_Argument(framework.getArgumentByName("a3"));
	C_set2.add_Argument(framework.getArgumentByName("a4"));

	p.prefSAT(&A_set2, &C_set2);

	cout << "Second example" << endl;
	extension_counter = 1;
	for (Preferred::iterator it = p.begin(); it != p.end(); it++)
	{
		cout << "Extension number " << extension_counter++ << endl;
		cout << *((*it).inargs()) << endl;
	}
	cout << "End of second example" << endl << endl;

*/

	return 0;
}
#endif
