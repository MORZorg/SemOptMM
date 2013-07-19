#include "pref.h"

set<SetArguments*> pref(AF gamma, SetArguments C){
	set<SetArguments*> Ep;
	SetArguments *e;
	SetArguments *I;

	// in the first call, grounded has I = A
	I = gamma.get_arguments();

	grounded(C,e,I);

	// the Preferred Extension set has e as first element
	Ep.insert(e);

	if(I->empty()){
		return Ep;
	}

	// reduction of gamma with the only nodes which stay in I. Removal of the suspend attacks
	gamma.reduceAF(*I);
	
	// Computation of the sequence of SCC which are in gamma, sorted in a topological way
	list<SCC*> S = SCCSSEQ(gamma);

	list<SCC*> :: iterator it;

	for( it = S.begin(); it != S.end(); it++ ){
		SCC* Si = *it;
		set<SetArguments*> E1p;

		set<SetArguments*> :: iterator jt;

		for( jt = Ep.begin(); jt != Ep.end(); jt++ ){
			e = *jt;
			SetArguments *O, *I;

			boundcond( gamma, Si->set, *e, O, I );
			
			set<SetArguments*> Estar;
			
			if( O->empty() ){
				if( !I->empty() ){
					SetArguments *temp2;
					I->intersect( &C, temp2 );
					AF gamma_reduced = AF(gamma);
					gamma_reduced.reduceAF(Si->set);

					Preferred p=Preferred();
					p.prefSAT(gamma_reduced.get_arguments(),temp2);

					int extension_counter = 1;

					for (Preferred::iterator it = p.begin(); it != p.end(); it++){
						cout << "Extension number " << extension_counter++ << endl;
						cout <<(*it).inargs()<<endl;
						Estar.insert((*it).inargs());
					}
					// Estar = SATPref
				} else{
					Estar=set<SetArguments*>();
					// Estar = vuoto
				}
			} else {
				SetArguments *temp, *temp2, Si_set;
				Si_set=Si->set;
				Si_set.setminus( O, temp );
				I->intersect( &C, temp2 );
				AF gamma_reduced = AF(gamma);
				gamma_reduced.reduceAF(*temp);
				Estar = pref( gamma, *temp2 );
			}

			// unione strana

			set<SetArguments*> :: iterator kt;
			for( kt = Estar.begin(); kt != Estar.end(); kt++ ){
				SetArguments * e_tmp;
				(*kt)->setunion(e,e_tmp);
				E1p.insert(e_tmp);
			}
		}
	// Ep = E1p;
		Ep=E1p;
	}

	return Ep;
}
