/*
 * grounded.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */
#include "grounded.h"

/**
 * Returns a subset of C containing all nodes that are not attacked from nodes in I
 */
SetArguments get_not_attacked_nodes(SetArguments C, SetArguments I){
	SetArguments N, intersect, result;
	SetArguments * attackers;
	C.clone(&N);
	for (SetArgumentsIterator it = C.begin(); it != C.end(); it++){
		attackers=(*it)->get_attackers();
		(attackers)->intersect(&I, &intersect);
		for (SetArgumentsIterator it = intersect.begin(); it != intersect.end(); it++){
			if (N.exists((*it)))
				N.remove((*it));
		}
		if(N.empty()) break;//improvement :)
	}
	return N;
}

/**
 * Returns a subset of set containing all nodes that are attacked from nodes in N
 */
SetArguments get_attacked_from(SetArguments set, SetArguments N){
	SetArguments intersect,result;
	SetArguments * attackers;
	for(SetArgumentsIterator it=set.begin();it!=set.end();it++){
		attackers=(*it)->get_attackers();
		attackers->intersect(&N, &intersect);
		if(!intersect.empty()){
			result.add_Argument(*it);
		}
	}
	return result;
}

void grounded(AF gamma, SetArguments C, SetArguments *e, SetArguments *I) {
	SetArguments N,ANC,ANI,temp;
	*e = SetArguments();
	I=gamma.get_arguments();
	N=get_not_attacked_nodes(C, *I);
	while(!N.empty()){
		e->setunion(&N,e);
		ANC=get_attacked_from(C,N);
		ANI=get_attacked_from(*I,N);
		N.setunion(&ANC,&temp);
		C.setminus(&temp,&C);
		N.setunion(&ANI,&temp);
		I->setminus(&temp,I);
		N=get_not_attacked_nodes(C, *I);
	}
}


