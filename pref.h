/*
 * pref.h
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */

#ifndef PREF_H_
#define PREF_H_
#include "SetArguments.h"
#include "Preferred.h"
#include "grounded.h"
#include "SCCSSEQ.h"
#include "boundcond.h"
#include <set>

struct OI_pair{
	SetArguments * O;
	SetArguments * I;
	set<SetArguments *> * Estar;

	OI_pair(SetArguments * _O, SetArguments * _I, set<SetArguments *>* _Estar){
		this->O=_O;
		this->I=_I;
		this->Estar=_Estar;
	}
};

set<SetArguments*> pref(AF gamma, SetArguments C, vector<OI_pair> * OI_pairs);
bool lookup(SetArguments * O, SetArguments * I, set<SetArguments*> *Estar, vector<OI_pair> * OI_pairs);
void insert(SetArguments * O, SetArguments * I, set<SetArguments*> *Estar, vector<OI_pair> * OI_pairs);
void assign_parent(list<SCC*> *S);

#endif /* PREF_H_ */
