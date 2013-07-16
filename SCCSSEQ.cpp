/*
 * SCCSSEQ.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */

list<SCC*> SCCSSEQ(AF gamma){
	return DFS(gamma);	
}


list<SCC*> DFS(AF gamma){
	stack<DFS_node*> S = initialize_stack(gamma);
	// qua credo che bisognerà fare una funzione che clona la pila, e poi svolgere il ciclo su quella clonata, 
	// perchè altrimenti poi quando si fa il pop degli elementi si andrebbe a modificare la pila. Oppure hai altre idee??
	int time = 0;
	DFS_node* u;
	while(!S.empty()){
		u = S.top();
		S.pop();
		if( u.color == 0 )	
			DFS_visit(S,u,&time);
	}

}

list <SCC*> DFS_visit(stack<DFS_node*> S, DFS_node* u, int* time){
	time++;
	u.d = time;
	u.color = 1;

	// ciclo

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

