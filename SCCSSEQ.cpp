/*
 * SCCSSEQ.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */
#include "SCCSSEQ.h"
#include <iostream>

list<SCC*> SCCSSEQ(AF gamma){
	list<SCC*> list_SCC;
	stack<DFS_node*> G = initialize_stack(gamma);
	cout<<"DFS first start"<<endl;
	DFS(G,true);
	cout<<"DFS second start"<<endl;

	DFS(G,false);
	cout<<"DFS finish"<<endl;


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

bool compareTime(DFS_node* a,DFS_node* b){
    return (a->f)>(b->f);
}

void DFS(stack<DFS_node*> S, bool first){
	list<SCC*> SCCSSEQ;
	int time = 0;
	DFS_node* u;
	SCC scc_tmp;

	//copio la stack S, in modo tale che anche se estraiamo gli elementi da S, la stack G rimane inalterata	
	stack<DFS_node*> G = stack<DFS_node*>(S);

	if(!first){
		S=sort_stack(S);
	}
	int scc_num = 0;
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

SCC DFS_visit(stack<DFS_node*> S, DFS_node* u, int* time, bool first){
	SCC tmp_scc, tmp_scc2;
	(*time)++;
	u->d = *time;
	u->color = 1;//gray
	//cout << (u->argument->getName())<<" set gray"<<endl;
	DFS_node * temp;

	SetArguments * adj;
	if(first){
		adj = u->argument->get_attacks();
	}
	else{
		adj = u->argument->get_attackers();
	}

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


stack<DFS_node*> initialize_stack(AF gamma){

	SetArguments* args;
	stack<DFS_node*> stack;

	args = gamma.get_arguments();

	for(SetArgumentsIterator it = args->begin(); it != args->end(); it++){
		stack.push( new DFS_node(*it));
	}
	return stack;
}

