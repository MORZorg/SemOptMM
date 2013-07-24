/*
 * SCCSSEQ.h
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */

#ifndef SCCSSEQ_H_
#define SCCSSEQ_H_
#include "Argument.h"
#include <list>
#include <stack>

//DFS();
//DFS_visit()
//topological_sort();
//stongly_connected_components();

typedef

struct DFS_node{
	Argument * argument;
	int color; //0, 1, 2 -> white, gray, black
	int d; //discovery time
	int f; //finishing time
	struct DFS_node * p;

	DFS_node( Argument* _argument ) {
		this->argument = _argument;
		this->color = 0;
		this->p = NULL;
	}
	DFS_node(){}
};

struct SCC{
	SetArguments set;
	SCC(){}
	SCC(SetArguments _set){
		this->set=_set;
	}
};
bool compareTime(DFS_node* a,DFS_node* b);
list<SCC*> SCCSSEQ(AF gamma);
void DFS(stack<DFS_node*> S, bool first, list<SCC*> *SCCSSEQ);
void DFS_visit(stack<DFS_node*> S, DFS_node* u, int* time, bool first, SCC *tmp_scc);
stack<DFS_node*> initialize_stack(AF gamma);
DFS_node* get_DFS_node(stack<DFS_node*> S, Argument a );

#endif /* SCCSSEQ_H_ */
