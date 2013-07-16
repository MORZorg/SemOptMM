/*
 * SCCSSEQ.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */

list<SCC*> SCCSSEQ(AF gamma){


}


list <SCC*> DFS(AF gamma){
		stack<DFS_node*> S = initialize_stack(gamma);

}

stack<DFS_node*> initialize_stack(AF gamma){

	SetArguments args;
	stack<DFS_node*> stack = stack<DFS_node*>();

	arg = gamma.get_arguments();

	for(SetArgumentsIterator it = arg.begin(); it != arg.end(); it++){
		 stack = push(*it);
	}


}

