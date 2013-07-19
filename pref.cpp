#include "pref.h"

set<SetArguments*> pref(AF gamma, SetArguments C){
	set<SetArguments*> Ep;
	SetArguments *e;
	SetArguments *I;
	I=gamma.get_arguments();
	grounded(C,e,I);
	Ep.insert(e);
	if(I->empty()){
		return Ep;
	}

	//...
}
