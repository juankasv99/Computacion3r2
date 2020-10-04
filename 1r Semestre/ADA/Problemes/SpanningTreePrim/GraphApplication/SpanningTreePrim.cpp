#include "pch.h"
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

// =============================================================================
// SpanningTreePrim ============================================================
// =============================================================================

struct comparator {
	bool operator()(CEdge &pE1, CEdge &pE2) { return pE1.m_Length > pE2.m_Length; }
};



CSpanningTree SpanningTreePrim(CGraph &graph)
{
	for (CVertex& v : graph.m_Vertices) { v.inSpamTree = false; }

	CSpanningTree tree(&graph);
	int nVertex = graph.GetNVertices();
	
	priority_queue<CEdge, std::vector<CEdge>, comparator> availableEdges;
	bool valid = true;
	int addedVertex = 1;

	graph.m_Vertices.front().inSpamTree = true;

	CVertex* lastVertex = &graph.m_Vertices.front();

	while (addedVertex < nVertex) {
		if (valid) {
			for (CEdge* e : lastVertex->m_Edges) {
				if (e->m_pDestination->inSpamTree == false) availableEdges.push(*e);
			}
		}
		valid = false;

		CEdge edges = availableEdges.top();
		if (edges.m_pDestination->inSpamTree == false) {
			valid = true;
			tree.m_Edges.push_back(&(edges));
			edges.m_pDestination->inSpamTree = true;
			lastVertex = edges.m_pDestination;
			addedVertex++;
		}

		availableEdges.pop();
	}




	return tree;
}
