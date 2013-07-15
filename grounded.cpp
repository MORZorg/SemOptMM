/*
 * grounded.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */
#include "grounded.h"

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


