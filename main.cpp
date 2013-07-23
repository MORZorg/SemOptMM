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
/*
	SetArguments e, *C=gamma.get_arguments();
	//SetArguments *I=new SetArguments();
	SetArguments *I=new SetArguments();
	gamma.get_arguments()->clone(I);
	grounded(*C, &e, I);

	cout << "e: "<<e<<endl;
	cout << "I: "<<*I<<endl;

	cout<<gamma<<endl;
	gamma.reduceAF(*I);
	cout << "after reduction "<<endl;
	cout<<gamma<<endl;

	cout <<"pippo"<<endl;*/


	SetArguments *A = new SetArguments();
	*A=SetArguments(*gamma.get_arguments());

/*	list<SCC*> S = SCCSSEQ(gamma);//E' DA VALUTARE SE SIA ORDINATA O NO!!
		cout << "sequenza SCC"<<endl;
		list<SCC*>::iterator a;

		int cont3=0;
		for(a=S.begin();a!=S.end();a++){
			cout <<"----"<< ++cont3 << (*a)->set <<endl;
		}*/

	set<SetArguments*> res;

	cout << "prima "<<endl;
	res=pref(gamma,*A);
	cout << "dopo "<<endl;
	set<SetArguments*> :: iterator kt;
	for( kt = res.begin(); kt != res.end(); kt++ ){
		cout << **kt << endl;
	}
cout<<"ciao ciao"<<endl;
	return EXIT_SUCCESS;
}
#endif
