/*
 * SCCSSEQ.h
 *
 *  Created on: 15/lug/2013
 *      Author: ilariamartinelli
 */

#ifndef SCCSSEQ_H_
#define SCCSSEQ_H_

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
};


#endif /* SCCSSEQ_H_ */
