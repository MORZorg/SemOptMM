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
	SetArguments * attacks;
	C.clone(&N);
	for (SetArgumentsIterator it = I.begin(); it != I.end(); it++){
		attacks=(*it)->get_attacks();
		for (SetArgumentsIterator jt = attacks->begin(); jt != attacks->end(); jt++){
			if (N.exists((*jt)))
				N.remove((*jt));
		}
		if(N.empty()) break;//improvement :)
	}
	//cout <<"get_not_attacked_nodes_N: "<< N<<endl;
	return N;
}

/**
 * Returns a subset of Set containing all nodes that are attacked from nodes in N
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
 * to be called with I=A
 */
void grounded(SetArguments C, SetArguments *e, SetArguments *I) {
	SetArguments N,ANC,ANI,temp;
	*e = SetArguments();

	//cout << "I: "<<*I<<endl;
	int iter=0;
	N=get_not_attacked_nodes(C, *I);
	while(!N.empty()){
/*		cout <<"N: "<<N<<endl;
		cout <<"C: "<<C<<endl;
		cout <<"I: "<<*I<<endl;
		cout <<"iter"<<endl;*/
		e->setunion(&N,e);
		ANC=get_attacked_from(C,N);
		//cout <<"ANC intermedio: "<<ANC<<endl;
		ANI=get_attacked_from(*I,N);
		//cout <<"ANI intermedio: "<<ANI<<endl;
		N.setunion(&ANC,&temp);
		C.setminus(&temp,&C);
		N.setunion(&ANI,&temp);
		I->setminus(&temp,I);
		//cout <<"I intermedio: "<<*I<<endl;
		N=get_not_attacked_nodes(C, *I);
		cout<<"grounded iter: "<<++iter<<endl;
		cout<<"e: "<<*e<<endl;
		cout<<"I: "<<*I<<endl;
	}
	/*
	cout<<"e finale"<<*e<<endl;
	cout<<"I finale"<<*I<<endl;
	*/
}


