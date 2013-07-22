/*
 * SCCSSEQ.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */
#include "SCCSSEQ.h"
#include <iostream>

/**
 * @brief 				Method for computing the the sequence of SCC sorted in a topological way
 * @param gamma			the framework which contains the graph
 * @retval 				a list of pointer to SCC
 */

list<SCC*> SCCSSEQ(AF gamma){
	stack<DFS_node*> G = initialize_stack(gamma);
	list<SCC*> list_SCC,dummy_list;
	// first call of DFS
	cout<<"primo DFS"<<endl;
	DFS(G,true,&dummy_list);
	// second call of DFS, considering edges in the opposite direction
	cout<<"secondo DFS"<<endl;
	DFS(G,false,&list_SCC);
	list<SCC*>::iterator it;
	SCC* temp;

	for(it=list_SCC.begin();it!=list_SCC.end();it++){
		temp=*it;
		cout<<temp->set<<endl;

	}
	cout<<"terzo DFS"<<endl;
	DFS(G,true,&dummy_list);

	cout<<endl;

	return list_SCC;
}

/**
 * @brief 				compute the removal of a node from the stack
 * @param remove		node to remove
 * @retval void
 */
void remove_stack(stack<DFS_node*> * S, DFS_node * remove){
	stack<DFS_node*> temp;
	while(!S->empty()){
		if(S->top() != remove){//funziona davvero?
			temp.push(S->top());
		}
		S->pop();
	}
	while(!temp.empty()){
		S->push(temp.top());
		temp.pop();
	}
}

/**
 * @brief 				sort of the stack
 * @param S				stack which is to sort
 * @retval 				the sorted stack
 */
stack<DFS_node*> sort_stack(stack<DFS_node*> S){//e azzero colore
	DFS_node * temp_node;
	stack<DFS_node*> stack;
	list<DFS_node*> list;
	while(!S.empty()){
		temp_node=S.top();
		temp_node->color=0;
		list.push_back(temp_node);
		S.pop();
	}
	list.sort(compareTime);
	while(!list.empty()){
		stack.push(list.back());
		list.pop_back();
	}
	return stack;
}

/**
 * @brief 				Criterion used to compare two nodes: finish time
 * @param a				first node to compare
 * @param b				second node to compare
 * @retval 				true if the first is greater then the second
 */

bool compareTime(DFS_node* a,DFS_node* b){
    return (a->f)>(b->f);
}

/**
 * @brief 				depth first search
 * @param S				Stack in which we have to do the DFS
 * @param first			true if is the first time which we are using this method in the SCCSSEQ method
 * @retval void
 */

void DFS(stack<DFS_node*> S, bool first, list<SCC*> *SCCSSEQ){
	int time = 0;
	DFS_node* u;
	SCC * scc_tmp;

	//copy of S stack, in this way we can extract element from S, and G doesn't change
	stack<DFS_node*> G = stack<DFS_node*>(S);

	// if is the second time, we sort the stack
	if(!first){
		S=sort_stack(S);
	}
	// visit every node of the stack if the color is white
	while(!S.empty()){
		u = S.top();
		S.pop();
		if( u->color == 0 ){
			scc_tmp=new SCC;
			//cout << u->argument->getName() << " ";
			DFS_visit(G,u,&time, first, scc_tmp);
			if(!first){
				SCCSSEQ->push_back(scc_tmp);
				//cout<<scc_tmp->set<<endl;
			}
		}
	}
}

/**
 * @brief 				visit in the depth first search
 * @param u				node which we are visiting
 * @param first			true if is the first time which we are using DFS in the SCCSSEQ method
 * @retval SCC			return the SCC computed
 */
void DFS_visit(stack<DFS_node*> S, DFS_node* u, int* time, bool first, SCC *tmp_scc){
	SCC tmp_scc2;
	(*time)++;
	u->d = *time;
	u->color = 1;//gray
	//cout << (u->argument->getName())<<" set gray"<<endl;
	DFS_node * temp;

	// if is the first time we consider the attacked nodes, otherwise we consider the attackers ( way to compute G trasposed )
	SetArguments * adj;
	if(first){
		adj = u->argument->get_attacks();
	}
	else{
		adj = u->argument->get_attackers();
	}

	// if the color is white call DFS_visit, compute SCC by union 
	for(SetArgumentsIterator it = adj->begin(); it != adj->end(); it++ ){
		temp = get_DFS_node(S, **it );
		//cout << (temp->argument->getName())<<" sub"<<endl;
		if( temp->color == 0 ){
			temp->p = u;
			DFS_visit(S,temp,time,first,&tmp_scc2);
			if(!first){
				tmp_scc->set.setunion(&(tmp_scc2.set),&(tmp_scc->set));
			}
		}
	}

	u->color = 2;

	if (!first){
		tmp_scc->set.add_Argument(u->argument);
	}

	(*time)++;
	u->f = *time;
	cout << u->argument->getName() <<" : "<< u->f << endl;
}

/**
 * @brief 				get a DFS_node if is present in the stack a node with the corresponding Argument
 * @param a				argument which we are looking for
 * @retval DFS_node*	pointer of the corresponding DFS_node if is presente in the stack, otherwise NULL
 */

DFS_node* get_DFS_node(stack<DFS_node*> S, Argument  a ){
	DFS_node * u;
	while(!S.empty()){
		u = S.top();
		S.pop();
		if( *(u->argument) == a )
			return u;
	}
	return NULL;
}


/**
 * @brief 				initialization of the stack 
 * @param gamma			framework
 * @retval stack		corresponding stack of DFS_node initialized
 */

stack<DFS_node*> initialize_stack(AF gamma){

	SetArguments* args;
	stack<DFS_node*> stack;

	args = gamma.get_arguments();

	for(SetArgumentsIterator it = args->begin(); it != args->end(); it++){
		stack.push( new DFS_node(*it));
	}
	return stack;
}

