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
	bool gamma_C = false;

	// if in this call of pref gamma and C are the same set of arguments we could have an optimitation 
	if(*gamma.get_arguments()==C){
					gamma_C = true;
	}
	SetArguments *in_args;

	// in the first call, grounded has I = A
	*I = *new SetArguments(*gamma.get_arguments());
	cout << "C:"<<C <<endl;
	cout << "e:"<<*e <<endl;
	cout << "I:"<<*I<<endl;

	bool last_opt = false;
	if(gamma_C == true && C.cardinality() <= 1){
		last_opt = true;
		*e=C;
		I=new SetArguments();
	}
	else
		grounded(C,e,I);

	cout << "grounded:"<<endl;
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

	list<SCC*> :: iterator it;
	int cont=0;

	// iteration on the list of SCC 
	for( it = S.begin(); it != S.end(); it++ ){
		bool modifica=false;
		bool Estar_exists=false;
		SCC* Si = *it;
		int cont2=0;


		cout << cont++ << " Si: "<< Si->set <<endl;
		set<SetArguments*> E1p = set<SetArguments*>();

		set<SetArguments*> :: iterator jt;

		// iteration on the e which are in Ep
		for( jt = Ep.begin(); jt != Ep.end(); jt++ ){
			e = *jt;
			cout << cont2++ << " e: "<< *e<<endl;
			SetArguments *O = new SetArguments();
			SetArguments *I = new SetArguments();

			e = e->adjust_set(gamma.get_arguments());

			set<SetArguments*> Estar = set<SetArguments*>();

			
			if(gamma_C){
				SetArguments *kt_attackers = new SetArguments();
				for(SetArgumentsIterator kt = Si->set.begin(); kt != Si->set.end(); kt++ ){
					kt_attackers->setunion((*kt)->get_attackers(),kt_attackers);
				}
				kt_attackers->setminus(&Si->set,kt_attackers);


				if(kt_attackers->empty()){
					// if S[i] hasn't got a father
					//O is empty
					//I =Si
					*I = Si->set;
				}
				else{
					// if S[i] has a father we need to compute boundcond
					boundcond( gamma, Si->set, *e, O, I );
				}
			}
			else{
				// if gamma != C we need to calculate boundcond
				boundcond( gamma, Si->set, *e, O, I );
			}

			cout << "boundcond results"<<endl;
			cout << "O: "<< *O<<endl;
			cout << "I: "<< *I<<endl;

			// look if the OI_pair has already been computed
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

						bool do_prefSAT = true;

						// if the first parameter of prefSAT is equal to the second we could avoid to compute prefSAT
						if(*(gamma_reduced.get_arguments()) == *temp2){
							if(Si->set.cardinality() == 1){
								// Si has got one element, Estar contains a set with the only element of Si
								in_args=new SetArguments();
								in_args->add_Argument(*Si->set.begin());
								Estar.insert(in_args);
								do_prefSAT=false;
							}
							if(Si->set.cardinality() == 2){
								// Si has got two elements, Estar contains two set, one with only the first element of Si, and the other with the second one
								for(SetArgumentsIterator rt=Si->set.begin();rt!=Si->set.end();rt++){
									in_args=new SetArguments();
									in_args->add_Argument(*rt);
									Estar.insert(in_args);
								}
								do_prefSAT=false;
							}
						}

						// if the conditions necessary to avoid computation of prefSAT are false we must compute it
						if( do_prefSAT ){
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
						}
					} else{
						//cout << "I empty"<<endl;
						Estar = set<SetArguments*>();
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

					if(last_opt){
						Estar = set<SetArguments*>();
						Estar.insert(new SetArguments(C));
					}else
						Estar = pref(gamma_reduced, *temp2, OI_pairs);
				}

				//if the OI_pair has been computed for the first time, we insert the OI_pair and the relative Estar in OI_pairs
				insert(O,I,&Estar,OI_pairs);
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

		} //end of for on Ep 
		
		// if Estar is not empty we need to modify Ep, otherwise Ep remains the same computed at the last iteration
		if(modifica)
			Ep = E1p;
	}// end of for on the list of SCC 

	return Ep;
}

/**
 * brief				look into OI_pairs if Estar has already been computed 
 * @param O[in]			the current O computed by boundcond
 * @param I[in]			the current I computed by boundcond
 * @param OI_pairs[in]	vector of OI_pairs, which has got the reference to the relative Estar
 * @param Estar[out]	if the retval is true Estar contains the Estar relative to this OI_pairs
 * @retval 				true if the OI_pairs has already been computed, otherwise false
 */

bool lookup(SetArguments * O, SetArguments * I, set<SetArguments*> *Estar, vector<OI_pair> * OI_pairs){
	for(int i=0; i<OI_pairs->size(); i++){
		if(*(OI_pairs->at(i).O) == *O)
			if(*(OI_pairs->at(i).I) == *I){
				Estar=OI_pairs->at(i).Estar;
				return true;
			}
	}
	return false;
}

/**
 * brief				insert into OI_pairs the OI_pair and the relative Estar 
 * details				is not necessary to look if the pair has already been inserted because, the lookup is done before the call of insert inside pref
 * @param O[in]			the current O computed by boundcond
 * @param I[in]			the current I computed by boundcond
 * @param Estar[in]		the Estar relative to the current OI_pair
 * @param OI_pairs[in]	vector of OI_pairs
 */

void insert(SetArguments * O, SetArguments * I, set<SetArguments*> *Estar, vector<OI_pair> * OI_pairs){
	OI_pair pair = OI_pair(O,I,Estar);
	OI_pairs->push_back(pair);
}
