#include "boundcond.h"

 /**
 * @brief 				modify O,I based on two conditions
 * @param gamma 		the AF in which we are operating
 * @param SCC [in]		SetArguments S[i] in pref
 * @param e	[in]		SetArguments e in pref
 * @param O	[out]		SetArguments O in pref
 * @param I	[out]		SetArguments I in pref
 */

void boundcond(AF gamma, SetArguments SCC, SetArguments e, SetArguments *O, SetArguments *I){
	SetArguments SCC_except_O,gamma_except_SCC,A,B1,B2, gamma_except_SCC_U_e, SCC_U_e;

	//O is the subset of Arguments of S[i] which are attacked by Arguments in e;
	*O=get_attacked_from(SCC,e);
	//cout << "boundcond: O"<<*O<<endl;

	//I is the subset of Arguments of S[i]\O which: condition (A) or condition (B)
	//(A) Are not attacked by Arguments in gamma extern of S[i]
	SCC.setminus(O,&SCC_except_O); //S[i]\O

	(gamma.get_arguments())->setminus(&SCC,&gamma_except_SCC);

	A=get_not_attacked_nodes(SCC_except_O,gamma_except_SCC);
cout <<"A: "<< A<< endl;
	//(B) are possibly attacked only by arguments which: condition (i) (ii)
	SCC.setunion(&e,&SCC_U_e);

	(gamma.get_arguments())->setminus(&SCC_U_e,&gamma_except_SCC_U_e);

	//(i) are in gamma but non in (S[i] joint e)
	B1=get_attacked_from(SCC_except_O,gamma_except_SCC_U_e);
	cout <<"B1: "<< B1<< endl;

	//(ii) are attacked by Arguments in e
	SetArguments B=SetArguments();
	SetArguments * intersect = new SetArguments();
	SetArguments * it_attackers;
	for(SetArgumentsIterator it = B1.begin(); it != B1.end(); it++){
		cout << "it: "<<(*it)->getName() <<endl;
		it_attackers=(*it)->get_attackers();
		cout << "attackers"<<*it_attackers<<endl;
		SetArguments * attackers_union = new SetArguments();
		for(SetArgumentsIterator jt = it_attackers->begin(); jt != it_attackers->end(); jt++){
			attackers_union->setunion((*jt)->get_attackers(),attackers_union);
		}
		attackers_union->intersect(&e, intersect);
		if(!intersect->empty())
			B.add_Argument(*it);
	}

	cout <<"B: "<< B<< endl;
	//final Boundcond in I 
	A.setunion(&B,I);
}
