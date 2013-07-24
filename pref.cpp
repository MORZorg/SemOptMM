#include "pref.h"

/**
 * brief				algorithm used to compute the set of Preferred Extension
 * @param gamma[in]		the AF in which we are working
 * @param C[in]			C = A, at the first call. A is the entire set of Arguments.
 * @retval 				the resulting set of SetArguments
 */

set<SetArguments*> pref(AF gamma, SetArguments C, vector<OI_pair> * OI_pairs){
	set<SetArguments*> Ep = set<SetArguments*>();
	SetArguments *e=new SetArguments();
	SetArguments *I=new SetArguments();
	SetArguments *in_args;

	// in the first call, grounded has I = A
	*I = *new SetArguments(*gamma.get_arguments());
	cout << "prima di grounded"<<endl;
	cout << "C:"<<C <<endl;
	cout << "e:"<<*e <<endl;
	cout << "I:"<<*I<<endl;

	grounded(C,e,I);
	cout << "dopo di grounded"<<endl;
	cout << "C:"<<C <<endl;
	cout << "e:"<<*e <<endl;
	cout << "I:"<<*I<<endl;


	// the Preferred Extension set has e as first element
	Ep.insert(e);

	if(I->empty()){
		return Ep;
	}

	cout <<gamma<<endl;

	// reduction of gamma with the only nodes which stay in I. Removal of the suspend attacks
	gamma=gamma.reduceAF(*I);

	// Computation of the sequence of SCC which are in gamma, sorted in a topological way
	list<SCC*> S = SCCSSEQ(gamma);
	
	/*cout << "sequenza SCC"<<endl;
	list<SCC*>::iterator a;

	int cont3=0;
	for(a=S.begin();a!=S.end();a++){
		cout <<"----"<< ++cont3 << (*a)->set <<endl;
	}*/

	list<SCC*> :: iterator it;
	int cont=0, cont2=0;

	for( it = S.begin(); it != S.end(); it++ ){
		bool modifica=false;
		bool Estar_exists=false;
		SCC* Si = *it;
		cout << cont++ << " Si: "<< Si->set <<endl;
		set<SetArguments*> E1p = set<SetArguments*>();

		set<SetArguments*> :: iterator jt;
		for( jt = Ep.begin(); jt != Ep.end(); jt++ ){
			e = *jt;
			cout << cont2++ << " e: "<< *e<<endl;
			SetArguments *O = new SetArguments();
			SetArguments *I = new SetArguments();

			e = e->adjust_set(gamma.get_arguments());

			set<SetArguments*> Estar = set<SetArguments*>();

			boundcond( gamma, Si->set, *e, O, I );

			cout << "boundcond results"<<endl;
			cout << "O: "<< *O<<endl;
			cout << "I: "<< *I<<endl;
			Estar_exists = lookup(O, I, &Estar, OI_pairs);

			if(!Estar_exists){
				if( O->empty() ){
					// cout << "O empty"<<endl;
					if( !I->empty() ){
						// cout << "I not empty"<<endl;

						cout << "--- gamma ---"<<gamma<<endl;

						AF gamma_reduced = gamma.reduceAF(Si->set);

						cout << "--- gamma reduce ---"<<gamma_reduced<<endl;

						SetArguments *temp2 = new SetArguments();

						SetArguments *temp_C, *temp_I;

						temp_C = C.adjust_set(gamma_reduced.get_arguments());
						temp_I = I->adjust_set(gamma_reduced.get_arguments());
						temp_I->intersect(temp_C,temp2);

						temp2 = temp2->adjust_set(gamma_reduced.get_arguments());

						Preferred p = Preferred();

						cout << "Invocazione prefSAT"<<endl;
						p.prefSAT(gamma_reduced.get_arguments(),temp2);
						cout << "termine prefSAT"<<endl;

						int extension_counter = 1;

						for (Preferred::iterator it = p.begin(); it != p.end(); it++){
							cout << "Extension number " << extension_counter++ << endl;
							cout <<*(*it).inargs()<<endl;
							in_args=new SetArguments(*(*it).inargs());
							Estar.insert(in_args);
						}

					} else{
						//cout << "I empty"<<endl;
						Estar = set<SetArguments*>();
						cout << "ESTAR "<<Estar.empty() << endl;
					}
				} else {
					// cout << "O not empty"<<endl;
					SetArguments *temp = new SetArguments();
					SetArguments *temp2 = new SetArguments();
					SetArguments Si_set;

					Si_set = Si->set;

					Si_set.setminus(O, temp);

					I->intersect(&C, temp2);

					AF gamma_reduced = gamma.reduceAF(*temp);
					Estar = pref(gamma_reduced, *temp2, OI_pairs);
				}
				insert(O,I,&Estar,OI_pairs);
				cout << "INSERITO :)"<<endl;
			}// end !Estar_exists


			// cout<< "before union" <<endl;
			set<SetArguments*> :: iterator kt;

			if(!Estar.empty()){
				modifica = true;
			}
			else
				cout<< "{{}}"<<endl;
			for( kt = Estar.begin(); kt != Estar.end(); kt++ ){
				SetArguments * e_tmp = new SetArguments();
				cout<< "e: "<<*e <<endl;
				cout<< "estar: "<<**kt <<endl;

				(*kt)->setunion(e,e_tmp);

				cout << *e_tmp<<endl;
				E1p.insert(e_tmp);
			}
			// cout<< "after union" <<endl;
		}
		
		if(modifica)
			Ep = E1p;
	}

	return Ep;
}

bool lookup(SetArguments * O, SetArguments * I, set<SetArguments*> *Estar, vector<OI_pair> * OI_pairs){
	for(int i=0; i<OI_pairs->size(); i++){
		if(*(OI_pairs->at(i).O) == *O)
			if(*(OI_pairs->at(i).I) == *I){
				Estar=OI_pairs->at(i).Estar;
				cout<<"TROVATOOO :)"<<endl;
				return true;
			}
	}
	return false;
}

void insert(SetArguments * O, SetArguments * I, set<SetArguments*> *Estar, vector<OI_pair> * OI_pairs){
	OI_pair pair = OI_pair(O,I,Estar);
	OI_pairs->push_back(pair);
}
