#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
 
#define NUM 200
 
struct edge {
	int vertex;
	struct edge * next;
};
 
void contraction(struct edge ** graph);
int * randomPick(struct edge ** graph);
void mergeVertices(struct edge ** graph, int * pair);
struct edge ** fetchGraph();
void deleteSelfLoop(struct edge ** graph);
int solveMincut(struct edge ** graph);
 
int main() {
	srand(time(0));
 
	//read data, build graph
	
 
	int j, newAns;
	int MinCut = 100000;
	for(j = 0; j < 1000; j++) {
		struct edge ** graph = fetchGraph();
		newAns = solveMincut(graph);
		MinCut = (MinCut < newAns)  ? MinCut : newAns;
		free(graph);
	}
 
	cout<<MinCut<<endl;
	return 0;
}
 
int solveMincut(struct edge ** graph) {
	int i, k, m = 0 ;
	struct edge * node;
	for(i = NUM; i > 2; i--) {
		contraction(graph);
	}
	for(k = 1; k <= NUM; k++) {
		for(node = graph[k]; node->next; node = node->next) {
			m++;
		}
	}
	return m / 2;
}
 
void deleteSelfLoop(struct edge ** graph) {
	struct edge * node;
	int i;
	for(i = 1; i <= NUM; i++) {
		for(node = graph[i]; node->next; )
			if(node->next->vertex == graph[i]->vertex) {
				node->next = node->next->next;
			} else {
				node = node->next;
			}
	}
}
 
void mergeVertices(struct edge ** graph, int * pair) {
	struct edge * node;
	int i;
	for(i = 1; i <= NUM; i++) {
		for(node = graph[i]; node->next; node = node->next)
			if(node->next->vertex == pair[0])
				node->next->vertex = pair[1];
	}
 
	node = graph[pair[1]];
	while(node->next) {
		node = node->next;
	}
	node->next = graph[pair[0]]->next;
	graph[pair[0]]->next = NULL;
}
 
void contraction(struct edge ** graph) {
	int * pair;
	pair = randomPick(graph);
	mergeVertices(graph, pair);
	deleteSelfLoop(graph);
	free(pair);
}
 
int * randomPick(struct edge ** graph) {
	int * pair = (int *) calloc(2, sizeof(int));
	int i, j, m = 0, pick = 0;
	struct edge * node;
	for(i = 1; i <= NUM; i++) {
		for(node = graph[i]; node->next; node = node->next)
			m++;
	}
	pick = rand() % m + 1;
 
	node = (struct edge*) calloc(1, sizeof(struct edge));
	node->next = NULL;
	for(i = 1, j = 0; j < pick; ) {
		if(node->next) { 
			node = node->next;
			j++;
		} else {
			node = graph[i++];
		}
	}
	pair[0] = i;
	pair[1] = node->vertex;
	
	return pair;
}
 

struct edge ** fetchGraph() {
	struct edge ** graph = (struct edge **) calloc(NUM + 1, sizeof(struct edge *));
	struct edge *node;
	ifstream fin("kargerMinCut.txt");
	string line;
	int row;
	
	while(!fin.eof()) {
		getline(fin, line);
		stringstream st(line);
		st>>row;
		
		node = (struct edge *) malloc(sizeof(struct edge));
		node->vertex = row;
		node->next = NULL;
		graph[row] = node;
 
		int token;
		while(st>>token) {
			//free(node);
			node = (struct edge*) calloc(1, sizeof(struct edge));
			node->vertex = token;
			node->next = graph[row]->next;
			graph[row]->next = node;
		}
	}
	fin.close();
	//free(node);
	return graph;
}
