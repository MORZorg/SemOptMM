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
	list<SCC*> list_SCC;
	stack<DFS_node*> G = initialize_stack(gamma);
	cout<<"DFS first start"<<endl;
	// first call of DFS
	DFS(G,true);
	cout<<"DFS second start"<<endl;
	// second call of DFS, considering edges in the opposite direction
	DFS(G,false);
	cout<<"DFS finish"<<endl;

	// remove from the stack root DFS_node which are not root of the tree
	DFS_node* u;
	stack<DFS_node*> root = stack<DFS_node*>(G);
	while(!G.empty()){
		u = G.top();
		G.pop();
		if( u->p != NULL ){
			remove_stack(&root,u);
		}
	}
	cout<<"1* while finish"<<endl;
	int k=0;

	// create from every root the sequence of SCC
	while(!root.empty()){//puntatori??
		cout<<k++<<endl;
		DFS_node* temp = new DFS_node();
		SCC *scc = new SCC();
		temp=root.top();
		do{
			scc->set.add_Argument(temp->argument);
			cout << scc->set<<endl;
			temp=temp->p;
		}while(temp!=NULL);
		cout<<"fine una root"<<endl;
		root.pop();
		list_SCC.push_back(scc);
	}
	cout<<"2* while"<<endl;

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

void DFS(stack<DFS_node*> S, bool first){
	list<SCC*> SCCSSEQ;
	int time = 0;
	DFS_node* u;
	SCC scc_tmp;

	//copy of S stack, in this way we can extract element from S, and G doesn't change
	stack<DFS_node*> G = stack<DFS_node*>(S);

	// if is the second time, we sort the stack
	if(!first){
		S=sort_stack(S);
	}
	int scc_num = 0;
	// visit every node of the stack if the color is white
	while(!S.empty()){
		u = S.top();
		S.pop();
		if( u->color == 0 ){
			cout << "SCC " << scc_num++ << ": ";
			//cout << u->argument->getName() << " ";

			scc_tmp=DFS_visit(G,u,&time, first);
			if(!first){
				SCCSSEQ.push_back(&scc_tmp);
				cout<<scc_tmp.set<<endl;
			}
			cout << endl;
		}
	}
}

/**
 * @brief 				visit in the depth first search
 * @param u				node which we are visiting
 * @param first			true if is the first time which we are using DFS in the SCCSSEQ method
 * @retval SCC			return the SCC computed
 */


SCC DFS_visit(stack<DFS_node*> S, DFS_node* u, int* time, bool first){
	SCC tmp_scc, tmp_scc2;
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
			tmp_scc2=DFS_visit(S,temp,time,first);
			if(!first){
				tmp_scc.set.setunion(&(tmp_scc2.set),&(tmp_scc.set));
			}
		}
	}

	u->color = 2;
	if (!first){
		tmp_scc.set.add_Argument(u->argument);
		cout << u->argument->getName() <<" ";
	}
	(*time)++;
	u->f = *time;
	return tmp_scc;
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

