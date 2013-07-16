/*
 * SCCSSEQ.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */

list<SCC*> SCCSSEQ(AF gamma){

	stack<DFS_node*> G = initialize_stack(gamma);
	DFS(G);

	// Faccio una copia di G
	stack<DFS_node*> Gt = G;
	// l'idea è quella di iterare su G e invertire per ogni DFS_node gli attaccanti con gli attaccati, 
	// alla fine G sarà vuota però in Gt avremo gli elementi con i lati girati. E' corretto!?
	while(!G.empty()){
		u = G.top();
		G.pop();
		SetArguments attackers = u.argument->getAttackers();
		SetArguments attacked = u.argument->getAttacks();
		u.argument.
	}


}


list<SCC*> DFS(stack<DFS_node*> S){

	int time = 0;
	DFS_node* u;

	//copio la stack S, in modo tale che anche se estraiamo gli elementi da S, la stack G rimane inalterata	
	stack<DFS_node*> G = S;

	while(!S.empty()){
		u = S.top();
		S.pop();
		if( u.color == 0 )	
			DFS_visit(G,u,&time);
	}

}

list <SCC*> DFS_visit(stack<DFS_node*> S, DFS_node* u, int* time){
	time++;
	u.d = time;
	u.color = 1;

	SetArgument adj_u, attackers, attack;
	attackers = u.get_attackers();
	attacks = u.get_attacks();
	attackers.setunion(&attacks, &adj_u);

	for(SetArgumentsIterator it = adj_u.begin(); it != adj_u.end(); it++ ){
		if( (*it)->color == 0 ){
			(*it)->p = u;
			DFS_visit(S,it,time);
		}
	}

	u.color = 2;
	time++;
	u.f = time;
}


stack<DFS_node*> initialize_stack(AF gamma){

	SetArguments args;
	stack<DFS_node*> stack = stack<DFS_node*>();

	arg = gamma.get_arguments();

	for(SetArgumentsIterator it = arg.begin(); it != arg.end(); it++){
		 stack = push(*it);
	}

}

