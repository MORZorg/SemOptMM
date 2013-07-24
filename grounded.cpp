/*
 * grounded.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */
#include "grounded.h"


/**
 * @brief 				get the subset of Arguments of C which are not attacked by Arguments in I
 * @retval 				the resulting subset
 */
SetArguments get_not_attacked_nodes(SetArguments C, SetArguments I){

	SetArguments N, intersect, result;
	SetArguments * attacks;
	C.clone(&N);
	for (SetArgumentsIterator it = I.begin(); it != I.end(); it++){
		attacks=(*it)->get_attacks();
		for (SetArgumentsIterator jt = attacks->begin(); jt != attacks->end(); jt++){
			if (N.exists((*jt)))
				N.remove((*jt));
		}
		if(N.empty()) break;
	}

	return N;
}


/**
 * @brief 				get the subset of Arguments of set which are attacked by Arguments in N
 * @retval 				the resulting subset
 */
SetArguments get_attacked_from(SetArguments set, SetArguments N){
	SetArguments intersect,result,tmp;
	SetArguments * attacks;
	for(SetArgumentsIterator it=N.begin();it!=N.end();it++){
		attacks=(*it)->get_attacks();
		tmp.setunion(attacks,&tmp);
	}

	tmp.intersect(&set,&result);
	return result;
}

/**
 * @brief 				first call I = A
 */
void grounded(SetArguments C, SetArguments *e, SetArguments *I) {
	SetArguments N,ANC,ANI,temp;
	*e = SetArguments();

	int iter=0;
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
	
		//cout<<"e: "<<*e<<endl;
		//cout<<"I: "<<*I<<endl;
	}

}
