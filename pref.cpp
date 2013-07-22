#include "pref.h"

set<SetArguments*> pref(AF gamma, SetArguments C){
	set<SetArguments*> Ep;
	SetArguments *e=new SetArguments();
	SetArguments *I=new SetArguments();
	SetArguments *in_args;

	// in the first call, grounded has I = A
	*I = *new SetArguments(*gamma.get_arguments());
	cout << "prima grounded"<<endl;
	cout << "C:"<<C <<endl;
	cout << "e:"<<*e <<endl;
	cout << "I:"<<*I<<endl;

	grounded(C,e,I);
	cout << "dopo grounded"<<endl;
	cout << "C:"<<C <<endl;
	cout << "e:"<<*e <<endl;
	cout << "I:"<<*I<<endl;


	// the Preferred Extension set has e as first element
	cout << Ep.empty() <<endl;
	Ep.insert(e);
	cout << "dopo insert Ep"<<endl;

	if(I->empty()){
		return Ep;
	}
	cout << "dopo if I empty"<<endl;
	cout <<gamma<<endl;
	// reduction of gamma with the only nodes which stay in I. Removal of the suspend attacks
	//gamma.reduceAF(*I);
	gamma=gamma.reduceAF(*I);
	cout << "dopo reduced"<<endl;
	cout <<gamma<<endl;

	// Computation of the sequence of SCC which are in gamma, sorted in a topological way
	list<SCC*> S = SCCSSEQ(gamma);//E' DA VALUTARE SE SIA ORDINATA O NO!!
	cout << "sequenza SCC"<<endl;
	list<SCC*>::iterator a;




	SCC* b=	*S.begin();
	S.pop_front();
	SCC* b1=*S.begin();
	S.pop_front();
	S.push_front(b);
	S.push_front(b1);

	int cont3=0;
	for(a=S.begin();a!=S.end();a++){
		cout <<"----"<< ++cont3 << (*a)->set <<endl;
	}

	list<SCC*> :: iterator it;
	int cont=0, cont2=0;

	for( it = S.begin(); it != S.end(); it++ ){
		SCC* Si = *it;
		cout << cont++ << " Si: "<< Si->set <<endl;
		set<SetArguments*> E1p = set<SetArguments*>();

		set<SetArguments*> :: iterator jt;
		for( jt = Ep.begin(); jt != Ep.end(); jt++ ){
			e = *jt;
			cout << cont2++ << " e: "<< *e<<endl;
			SetArguments *O = new SetArguments();
			SetArguments *I = new SetArguments();

			boundcond( gamma, Si->set, *e, O, I ); //ANCORA DA TESTARE
			cout << "boundcond results"<<endl;
			cout << "O: "<< *O<<endl;
			cout << "I: "<< *I<<endl;

			set<SetArguments*> Estar = set<SetArguments*>();
			
			if( O->empty() ){
				cout << "O empty"<<endl;
				if( !I->empty() ){
					cout << "I not empty"<<endl;
					SetArguments *temp2 = new SetArguments();
					I->intersect( &C, temp2 );


					//AF gamma_reduced = AF(gamma);
					AF gamma_reduced = gamma.reduceAF(Si->set);
					//cout << "--- gamma reduce ---"<<gamma_reduced<<endl;
					//cout << "--- gamma ---"<<gamma<<endl;
					//gamma_reduced.reduceAF(Si->set);
					cout << "--- gamma ---"<<gamma<<endl;
					cout << "--- gamma reduce ---"<<gamma_reduced<<endl;
					//cout << "--- gamma ---"<<gamma<<endl;

					Preferred p=Preferred();
					cout << "prima SAT"<<endl;
					p.prefSAT(gamma_reduced.get_arguments(),temp2);
					cout << "dopo SAT"<<endl;

					int extension_counter = 1;

					for (Preferred::iterator it = p.begin(); it != p.end(); it++){
						cout << "Extension number " << extension_counter++ << endl;
						cout <<*(*it).inargs()<<endl;
						in_args=new SetArguments(*(*it).inargs());
						Estar.insert(in_args);
					}
					// Estar = SATPref
					cout << "fine if"<<endl;
				} else{
					cout << "I empty"<<endl;
					Estar=set<SetArguments*>();
					cout << "ESTAR "<<Estar.empty() << endl;
					// Estar = vuoto
				}
			} else {
				cout << "O not empty"<<endl;
				SetArguments *temp, *temp2, Si_set;
				Si_set=Si->set;
				Si_set.setminus( O, temp );
				I->intersect( &C, temp2 );
				//AF gamma_reduced = AF(gamma);
				//gamma_reduced.reduceAF(*temp);
				AF gamma_reduced=gamma.reduceAF(*temp);
				Estar = pref( gamma_reduced, *temp2 );
			}

			// unione strana
			cout<< "prima unione strana" <<endl;
			set<SetArguments*> :: iterator kt;
			cout << "empty? "<<Estar.empty()<<endl;
			for( kt = Estar.begin(); kt != Estar.end(); kt++ ){
				SetArguments * e_tmp = new SetArguments();
				cout<< "e: "<<*e <<endl;
				cout<< "*kt: "<<**kt <<endl;


				(*kt)->setunion(e,e_tmp);
				cout<< "dopo  setunion" <<endl;
				cout << *e_tmp<<endl;
				E1p.insert(e_tmp);
			}
			cout<< "dopo unione strana" <<endl;
		}
	// Ep = E1p;
		Ep=E1p;

	}

	return Ep;
}
