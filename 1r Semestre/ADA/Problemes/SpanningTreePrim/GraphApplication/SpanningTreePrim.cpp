#include "pch.h"
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

// =============================================================================
// SpanningTreePrim ============================================================
// =============================================================================

struct comparator {
	bool operator()(CEdge* pE1, CEdge* pE2) { return pE1->m_Length > pE2->m_Length; }
};




CSpanningTree SpanningTreePrim(CGraph &graph)
{

	for (CVertex& v : graph.m_Vertices) { v.m_inSpamTree = false; }
	CSpanningTree tree(&graph);
	int nVertex = graph.GetNVertices();
	int nEdges = graph.GetNEdges();

	priority_queue<CEdge*, std::vector<CEdge*>, comparator> edgeList;
	bool prev = true;
	int counter = 1;

	graph.m_Vertices.front().m_inSpamTree = true;
	CVertex* lastV = &graph.m_Vertices.front();

	list<CEdge> eList;

	while (counter < nVertex && nEdges >= nVertex - 1) {
		if (prev) {
			for (CEdge* e : lastV->m_Edges) {
				if (e->m_pDestination->m_inSpamTree == false) edgeList.push(e);
			}
		}

		prev = false;
		

		CEdge* pE = edgeList.top();

		if (pE->m_pDestination->m_inSpamTree == false) {
			prev = true;

			tree.m_Edges.push_back(pE);
			pE->m_pDestination->m_inSpamTree = true;
			lastV = pE->m_pDestination;
			counter++;
		}

		edgeList.pop();

	}

	

	return tree;
}
