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

SetArguments get_not_attacked_nodes(SetArguments C, SetArguments I){
	SetArguments N, attackers, intersect, result;
	C.clone(&N);
	for (SetArgumentsIterator it = C.begin(); it != C.end(); it++){
		attackers=(*it)->get_attackers();
		attackers.intersect(&I, &intersect);
		for (SetArgumentsIterator it = intersect.begin(); it != intersect.end(); it++){
			if (N.exists((*it)))
				N.remove((*it));
		}
		if(N.empty()) break;//improvement :)
	}
	return N;
}

void grounded(AF gamma, SetArguments C, Preferred *e, SetArguments *I) {
	SetArguments N;
	e=Preferred();
	I=gamma.get_arguments();
	N=get_not_attacked_nodes(C, *I);
	while(!N.empty()){

	}
}
Preferred pref(AF gamma, SetArguments C){
	Preferred e;
	SetArguments I;
	grounded(gamma,C,&e,&I);
	//...
}

int main(int argc, char *argv[])
{


	//debug = true; // more verbose
	debug=false;
	inputfile = string("test-input/scc-test.dl");
	AF framework = AF();
	if (!framework.readFile(inputfile))
	{

		return -1;
	}

	Preferred p = Preferred();

	SetArguments C_set1 = SetArguments();
	C_set1.add_Argument(framework.getArgumentByName("a1"));
	C_set1.add_Argument(framework.getArgumentByName("a6"));

	p.prefSAT(&framework, &C_set1);

	for (Preferred::iterator it = p.begin(); it != p.end(); it++)
	{
		cout << "First extension " << endl;
		for (SetArgumentsIterator itarg = (*it).inargs()->begin();
				itarg != (*it).inargs()->end(); itarg++)
		{
			cout << (*itarg)->getName() << endl;
		}
		cout << "Or even " << endl;
		cout << *((*it).inargs()) << endl;
	}

	SetArguments C_set2 = SetArguments();
	C_set2.add_Argument(framework.getArgumentByName("a2"));
	C_set2.add_Argument(framework.getArgumentByName("a3"));
	C_set2.add_Argument(framework.getArgumentByName("a4"));

	p.prefSAT(&framework, &C_set2);

	for (Preferred::iterator it = p.begin(); it != p.end(); it++)
	{
		cout << "Second extension " << endl;
		cout << *((*it).inargs()) << endl;
	}

	return 0;
}
#endif
