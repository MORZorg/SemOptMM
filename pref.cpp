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
/*
	// reduction of gamma with the only nodes which stay in I. Removal of the suspend attacks
	gamma.reduceAF(I);
	
	// Computation of the sequence of SCC which are in gamma, sorted in a topological way
	list<SCC*> S = SCCSSEQ(gamma);

	list<SCC*> :: iterator it;

	for( it = S.begin(); it != S.end(); it++ ){
		Si = *it;
		set<SetArguments*> E1p;

		set<SetArguments*> :: iterator jt;

		for( jt = Ep.begin(); it != Ep.end(); it++ ){
			e = *jt;
			SetArguments *O, *I;

			boundcond( gamma, Si, e, O, I );
			
			set<SetArguments*> Estar;
			
			if( O->empty() ){
				if( !I->empty() ){
					// Estar = SATPref
				} else{
					// Estar = vuoto
				}
			} else {
				// Si->setminus( O, temp )
				// I->intersect( C, temp2 )
				// Estar = pref( gamma.reduceAF(temp), temp2 );
				
				// unione strana
			}

		}
	// Ep = E1p;

	}

	return Ep:
*/
	//...
}
