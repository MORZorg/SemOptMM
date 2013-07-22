#include "boundcond.h"

void boundcond(AF gamma, SetArguments SCC, SetArguments e, SetArguments *O, SetArguments *I){
	SetArguments SCC_except_O,gamma_except_SCC,A,B1,B2, gamma_except_SCC_U_e, SCC_U_e;

	//O è il sottoinsieme dei nodi di S[i] che sono attaccati da nodi in e;
	*O=get_attacked_from(SCC,e);
	cout << "boundcond: O"<<*O<<endl;

	//I è il sottoinsieme dei nodi di S[i]\O che o
	//(A) non subiscono attacchi da parte di nodi in gamma esterni a S[i]
	SCC.setminus(O,&SCC_except_O); //S[i]\O
	cout << "boundcond: SCC_except_O"<<SCC_except_O<<endl;
	(gamma.get_arguments())->setminus(&SCC,&gamma_except_SCC);
	cout << "boundcond: gamma_except_SCC"<<gamma_except_SCC<<endl;
	A=get_not_attacked_nodes(SCC_except_O,gamma_except_SCC);
	cout << "boundcond: A"<<A<<endl;


	//o (B) subiscono eventuali attacchi solo da parte di nodi che
	SCC.setunion(&e,&SCC_U_e);
	cout << "boundcond: SCC_U_e"<<SCC_U_e<<endl;
	(gamma.get_arguments())->setminus(&SCC_U_e,&gamma_except_SCC_U_e);
	cout << "boundcond: gamma_except_SCC_U_e"<<gamma_except_SCC_U_e<<endl;
	//(i) sono contenuti in gamma ma non in (S[i] unito e)
	B1=get_attacked_from(SCC_except_O,gamma_except_SCC_U_e);
	cout << "boundcond: 1"<<B1<<endl;
	//(ii) sono attaccati da nodi in e
	B2=get_attacked_from(B1,e);
	cout << "boundcond: 2"<<B2<<endl;

	A.setunion(&B2,I);
}
