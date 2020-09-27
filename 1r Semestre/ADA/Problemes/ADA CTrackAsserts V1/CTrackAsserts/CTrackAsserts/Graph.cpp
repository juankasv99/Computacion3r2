// AssertsMaximFluxe.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "Graph.h"
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <assert.h>
using namespace std;

// =============================================================================
// UTILITATS ===================================================================
// =============================================================================

// =============================================================================
// DEBUG =======================================================================
// =============================================================================

bool MyAssertFunction(const char* strCond, const AssertValue value, const char* function, const char* filename, int line)
{
	char buf[1024];
	const char* valueStr = "Assert no definido";
	switch (value) {
	case AssertNULL: valueStr = "AssertNULL"; break;
	case AssertTrackSenseGraf: valueStr = "AssertTrackSenseGraf"; break;
	case AssertNoArestaDelGraf: valueStr = "AssertNoArestaDelGraf"; break;
	case AssertArestesDesconectades: valueStr = "AssertArestesDesconectades"; break;
	case AssertGrafsDiferents: valueStr = "AssertGrafsDiferents"; break;
	}
	sprintf_s(buf, "ASSERT %s a %s %s (%d). Cond: %s", valueStr, function, filename, line, strCond);
	throw exception(buf);
	return false;
}

// =============================================================================
// EXCEPCIONS ==================================================================
// =============================================================================

// MyException =================================================================

MyException::MyException(const char *Format, ...)
{
	va_list al;
	va_start(al, Format);
	_vsnprintf_s(m_Message, 255, Format, al);
	m_Message[255] = 0;
	va_end(al);
}

// MyException =================================================================

MyException::MyException(const MyException& rhs) : exception(rhs)
{
	memcpy(m_Message, rhs.m_Message, sizeof m_Message);
}

// =============================================================================
// CGPoint =====================================================================
// =============================================================================

// =============================================================================
// CVertex =====================================================================
// =============================================================================

// MemberP =====================================================================

bool CVertex::MemberP(CEdge* pEdge)
{
	for (auto pA : m_Edges) if (pA == pEdge) return true;
	return false;
}

// FindEdge =====================================================================

CEdge* CVertex::FindEdge(const char* name)
{
	for (CEdge* pEdge : m_Edges) {
		if (strcmp(pEdge->m_Name.c_str(), name)==0) return pEdge;
	}
	return NULL;
}

// Unlink ======================================================================

void CVertex::Unlink(CEdge *pEdge)
{
	for (list<CEdge*>::iterator it = m_Edges.begin(); it != m_Edges.end(); ++it) {
		if (pEdge == *it) {
			m_Edges.erase(it);
			break;
		}
	}
}

// =============================================================================
// CGraph ======================================================================
// =============================================================================

// CGraph ======================================================================

CGraph::CGraph(bool directed)
{
	m_Directed=directed;
}

// ~CGraph =====================================================================

CGraph::~CGraph()
{
}

// Clear =======================================================================

void CGraph::Clear()
{
	m_Vertices.clear();
	m_Edges.clear();
}

// NewVertex ==================================================================

CVertex* CGraph::NewVertex(const char* name, double x, double y)
{
	m_Vertices.push_back(CVertex(name, x, y));
	return &m_Vertices.back();
}

// NewVertex ==================================================================

CVertex* CGraph::NewVertex(const CGPoint &point)
{
	char name[10];
	size_t i = m_Vertices.size()+1;
	for (;;) {
		sprintf_s(name, "V%04llu", i);
		if (FindVertex(name) == NULL) break;
		++i;
	}
	m_Vertices.push_back(CVertex(name, point.m_X, point.m_Y));
	return &m_Vertices.back();
}

// DeleteVertex ==================================================================

void CGraph::DeleteVertex(CVertex *pVertex)
{
	for (list<CVertex>::iterator it = m_Vertices.begin(); it != m_Vertices.end(); ++it) {
		if (pVertex == &*it) {
			while (!pVertex->m_Edges.empty()) {
				DeleteEdge(pVertex->m_Edges.front());
			}
			m_Vertices.erase(it);
			break;
		}
	}
}

// FindVertex =================================================================

CVertex* CGraph::FindVertex(const char* name)
{
	for (CVertex &v : m_Vertices) {
		if (strcmp(v.m_Name.c_str(),name)==0) return &v;
	}
	return NULL;
}

// FindVertex =================================================================

CVertex* CGraph::FindVertex(const CGPoint &point,double radius)
{
	CVertex *pSel = NULL;
	double dMin = numeric_limits<double>::max();
	for (CVertex &v : m_Vertices) {
		double d = (v.m_Point - point).Module();
		if (d < dMin) {
			dMin = d;
			pSel = &v;
		}
	}
	if (dMin <= radius) return pSel;
	return NULL;
}

// GetVertex ===================================================================

CVertex* CGraph::GetVertex(const int index)
{
	int i = index;
	for (CVertex& v : m_Vertices) {
		if (i == 0) return &v;
		--i;
	}
	throw MyException("CGraph::GetVertex: no se ha encontrado un vértice del grafo con indice: %d", index);

}

// GetVertexIndex ==============================================================

int CGraph::GetVertexIndex(const CVertex* pVertex)
{
	int indice = 0;
	for (CVertex& v : m_Vertices) {
		if (&v == pVertex) return indice;
		++indice;
	}
	throw exception("CGraph::GetVertexIndex: no ha encontrado el vértice");
}

// MemberP =====================================================================

bool CGraph::MemberP(CVertex* pVertex)
{
	for (CVertex &v : m_Vertices) {
		if (&v==pVertex) return true;
	}
	return false;
}

// NewEdge =====================================================================

CEdge* CGraph::NewEdge(const char* name, double value, const char* originName, const char* destionatioName)
{
	CVertex* pVOrigin = FindVertex(originName);
	CVertex* pVDestination = FindVertex(destionatioName);
	if (m_Directed) {
		m_Edges.push_back(CEdge(name, value, pVOrigin, pVDestination, NULL));
		CEdge* pEdge = &m_Edges.back();
		pVOrigin->m_Edges.push_back(pEdge);
		return pEdge;
	}
	else {
		m_Edges.push_back(CEdge(name, value, pVOrigin, pVDestination, NULL));
		CEdge* pEdge = &m_Edges.back();
		pVOrigin->m_Edges.push_back(pEdge);
		string name2(name);
		name2 += "_R";
		m_Edges.push_back(CEdge(name2.c_str(), value, pVDestination, pVOrigin, NULL));
		CEdge* pRevEdge = &m_Edges.back();
		pVDestination->m_Edges.push_back(pRevEdge);
		pEdge->m_pReverseEdge = pRevEdge;
		pRevEdge->m_pReverseEdge = pEdge;
		return pEdge;
	}
}

// NewEdge =====================================================================

CEdge* CGraph::NewEdge(CVertex *pVOrigin, CVertex* pVDestination)
{
	if (m_Directed) {
		char name[10];
		size_t i = m_Edges.size() + 1;
		for (;;) {
			sprintf_s(name, "E%04llu", i);
			if (FindEdge(name) == NULL) break;
			++i;
		}
		m_Edges.push_back(CEdge(name, 0.0, pVOrigin, pVDestination, NULL));
		CEdge* pEdge = &m_Edges.back();
		pVOrigin->m_Edges.push_back(pEdge);
		return pEdge;
	}
	else {
		char name[10];
		size_t i = m_Edges.size() + 1;
		for (;;) {
			sprintf_s(name, "E%04llu", i);
			if (FindEdge(name) == NULL) break;
			++i;
		}
		m_Edges.push_back(CEdge(name, 0.0, pVOrigin, pVDestination, NULL));
		CEdge* pEdge = &m_Edges.back();
		pVOrigin->m_Edges.push_back(pEdge);
		strcat_s(name, "_R");
		m_Edges.push_back(CEdge(name, 0.0, pVDestination, pVOrigin, NULL));
		CEdge* pRevEdge = &m_Edges.back();
		pVDestination->m_Edges.push_back(pRevEdge);
		pEdge->m_pReverseEdge = pRevEdge;
		pRevEdge->m_pReverseEdge = pEdge;
		return pEdge;
	}
}

// DeleteEdge ==================================================================
// borra areste en graf dirigits y borra parelles d'arestes en graf no dirigits

void CGraph::DeleteEdge(CEdge *pEdge)
{
	assert(invariant());

	for (list<CEdge>::iterator it = m_Edges.begin(); it != m_Edges.end(); ++it) {
		if (pEdge == &*it) {
			if (pEdge->m_pReverseEdge) {
				CEdge* pRevEdge = pEdge->m_pReverseEdge;
				pEdge->m_pOrigin->Unlink(pEdge);
				m_Edges.erase(it);
				for (list<CEdge>::iterator itr = m_Edges.begin(); itr != m_Edges.end(); ++itr) {
					if (pRevEdge == &*itr) {
						pRevEdge->m_pOrigin->Unlink(pRevEdge);
						m_Edges.erase(itr);
						break;
					}
				}
			}
			else {
				pEdge->m_pOrigin->Unlink(pEdge);
				m_Edges.erase(it);
			}
			break;
		}
	}

	assert(invariant());
}

// FindEdge ====================================================================

CEdge* CGraph::FindEdge(CVertex* pVOrigin, CVertex* pVDestination)
{
	for (CEdge &e : m_Edges) {
		if (e.m_pOrigin == pVOrigin && e.m_pDestination == pVDestination) return &e;
	}
	return NULL;
}

// FindEdge ====================================================================

CEdge* CGraph::FindEdge(const char* name)
{
	for (CEdge &e : m_Edges) {
		if (strcmp(e.m_Name.c_str(), name) == 0) return &e;
	}
	return NULL;
}

// FindEdge ====================================================================

CEdge* CGraph::FindEdge(const CGPoint &point, double radius)
{
	CEdge *pEdge = NULL;
	double minD = numeric_limits<double>::max();
	for (CEdge &e : m_Edges) {
		CGPoint u = e.m_pDestination->m_Point - e.m_pOrigin->m_Point;
		u /= u.Module();
		CGPoint v2 = point - e.m_pOrigin->m_Point;
		double a = v2 * u;
		double d = (v2 - u * a).Module();
		if (d < minD) {
			minD = d;
			pEdge = &e;
		}
	}
	if (minD <= radius) return pEdge;
	return NULL;
}

// MemberP =====================================================================

bool CGraph::MemberP(CEdge *pEdge)
{
	for (CEdge &e : m_Edges) {
		if (&e == pEdge) return true;
	}
	return false;
}


// Invariant ===================================================================

bool CGraph::invariant()
{
	for (CVertex& v : m_Vertices) {
		for (CEdge* pE : v.m_Edges) {
			if (!MemberP(pE)) return false;
			if (pE->m_pOrigin != &v) return false;
		}
	}

	for (CEdge& e : m_Edges) {
		if (!MemberP(e.m_pOrigin)) return false;
		if (!MemberP(e.m_pDestination)) return false;
		if (m_Directed) {
			if (e.m_pReverseEdge != NULL) return false;
		}
		else {
			if (e.m_pReverseEdge == NULL) return false;
			if (!MemberP(e.m_pReverseEdge)) return false;
			if (e.m_pOrigin != e.m_pReverseEdge->m_pDestination) return false;
			if (e.m_pDestination != e.m_pReverseEdge->m_pOrigin) return false;
		}
		if (e.m_pOrigin == e.m_pDestination) return false;
	}
	for (list<CVertex>::iterator i = m_Vertices.begin(); i != m_Vertices.end();) {
		CVertex& v = *i;
		++i;
		for (list<CVertex>::iterator i2 = i; i2 != m_Vertices.end(); ++i2) {
			if (v.m_Name == i2->m_Name) return false;
		}
	}
	for (list<CEdge>::iterator i = m_Edges.begin(); i != m_Edges.end();) {
		CEdge& e = *i;
		++i;
		for (list<CEdge>::iterator i2 = i; i2 != m_Edges.end(); ++i2) {
			if (e.m_Name == i2->m_Name) return false;
		}
	}
	return true;
}

// =============================================================================
// CTrack ======================================================================
// =============================================================================
// Lista de aristas que forman un camino

// Append ======================================================================

void CTrack::Append(CTrack& t)
{
	for (list<CEdge*>::const_iterator iter = t.m_Edges.cbegin(); iter != t.m_Edges.cend(); ++iter) {
		m_Edges.push_back(*iter);
	}
}

// AppendBefore ================================================================

void CTrack::AppendBefore(CTrack& t)
{
	for (list<CEdge*>::const_reverse_iterator iter = t.m_Edges.crbegin(); iter != t.m_Edges.crend(); ++iter) {
		m_Edges.push_front(*iter);
	}
}

// Length ======================================================================

double CTrack::Length() {
	double l = 0.0;
	for (CEdge* pE : m_Edges) {
		l += pE->m_pOrigin->m_Point.Distance(pE->m_pDestination->m_Point);
	}
	return l;
}

// MemberP =====================================================================

bool CTrack::MemberP(CEdge* pE) {
	for (CEdge* pE2 : m_Edges) {
		if (pE2 == pE) return true;
	}
	return false;
}

// << ==========================================================================

ostream& operator<< (ostream& s, const CTrack& track)
{
	s << "[";
	if (!track.m_Edges.empty()) {
		for (CEdge* pE : track.m_Edges) {
			s << pE->m_pOrigin->m_Name << " -(" << pE->m_Name << ")->";
		}
		s << track.m_Edges.back()->m_pDestination->m_Name;
	}
	s << "]";
	return s;
}
