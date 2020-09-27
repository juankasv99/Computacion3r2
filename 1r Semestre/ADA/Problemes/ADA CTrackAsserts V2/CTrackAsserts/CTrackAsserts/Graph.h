// AssertsMaximFluxe.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <minmax.h>

using namespace std;
//#undef max
//#undef min

// =============================================================================
// UTILITATS ===================================================================
// =============================================================================

/*
template<class T> T max(T a, T b) 
{
	if (a > b) return a;
	else return b;
}

template<class T> T min(T a, T b)
{
	if (a < b) return a;
	else return b;
}
*/

// =============================================================================
// DEBUG =======================================================================
// =============================================================================

enum AssertValue {
	AssertNULL,
	AssertTrackSenseGraf,
	AssertGrafsDiferents,
	AssertNoArestaDelGraf,
	AssertArestesDesconectades
};

bool MyAssertFunction(const char*strcond, const AssertValue value, const char* function, const char*FileName, int line);

#ifdef NDEBUG
#define MyAssert(cond,value)
#else
#define MyAssert(cond,value) ((void) ((cond) || MyAssertFunction(#cond,value, __FUNCTION__, __FILE__, __LINE__)))
#endif

// =============================================================================
// EXCEPCIONS ==================================================================
// =============================================================================

class MyException : public exception {
public:
private:
	// Campos
	char m_Message[256];
public:
	MyException() {}
	MyException(const char *Format, ...);
	MyException(const MyException& rhs);
	virtual const char *what() const throw() { return m_Message; }
};


// =============================================================================
// CGPoint =====================================================================
// =============================================================================

class CGPoint
{

public:
	double m_X, m_Y;

	CGPoint() : m_X(0.0), m_Y(0.0) {}
	CGPoint(const double x, const double y = 0) : m_X(x), m_Y(y) {}
	CGPoint(const CGPoint&p) : m_X(p.m_X), m_Y(p.m_Y) {}
	//CGPoint(const CPoint &p) : m_X(p.x), m_Y(p.y) {}
	//operator CPoint() { return CPoint(int(m_X), int(m_Y)); }
	CGPoint& operator=(const CGPoint &p) {
		m_X = p.m_X;
		m_Y = p.m_Y;
		return *this;
	}
	CGPoint operator+(const CGPoint &p2)  const {
		return CGPoint(m_X + p2.m_X, m_Y + p2.m_Y);
	}
	CGPoint operator+=(const CGPoint &p2) {
		m_X += p2.m_X;
		m_Y += p2.m_Y;
		return *this;
	}
	CGPoint operator-(const CGPoint &p2)  const {
		return CGPoint(m_X - p2.m_X, m_Y - p2.m_Y);
	}
	CGPoint operator-=(const CGPoint &p2) {
		m_X -= p2.m_X;
		m_Y -= p2.m_Y;
		return *this;
	}
	CGPoint operator*(const double n) {
		return CGPoint(m_X*n,m_Y*n);
	}
	CGPoint operator*=(const double n) {
		m_X *= n;
		m_Y *= n;
		return *this;
	}
	CGPoint operator/(const double n) {
		return CGPoint(m_X/n, m_Y/n);
	}
	CGPoint operator/=(const double n) {
		m_X /= n;
		m_Y /= n;
		return *this;
	}
	CGPoint operator-()  const {
		return CGPoint(-m_X, -m_Y);
	}
	double operator*(const CGPoint &p2)  const {
		return m_X * p2.m_X + m_Y * p2.m_Y;
	}
	bool operator==(const CGPoint& p)  const {
		return m_X == p.m_X && m_Y == p.m_Y;
	}
	bool operator!=(const CGPoint& p)  const {
		return m_X != p.m_X || m_Y != p.m_Y;
	}
	double Module() { return sqrt(m_X*m_X + m_Y * m_Y); }
	double Distance(CGPoint &p2) { return sqrt((m_X - p2.m_X)*(m_X - p2.m_X) + (m_Y - p2.m_Y)*(m_Y - p2.m_Y)); }
};

inline CGPoint operator*(double v, const CGPoint& p) {
	return CGPoint(v*p.m_X, v*p.m_Y);
}

inline CGPoint operator*(const CGPoint& p, double v) {
	return CGPoint(v*p.m_X, v*p.m_Y);
}

inline CGPoint operator/(const CGPoint& p, double v) {
	return CGPoint(p.m_X / v, p.m_Y / v);
}

inline ostream& operator<< (ostream& s, const CGPoint& p) {
	s << "(" << p.m_X << ", " << p.m_Y << ")";
	return s;
}

inline CGPoint Min(const CGPoint& p1, const CGPoint& p2) {
	return CGPoint(min(p1.m_X, p2.m_X), min(p1.m_Y, p2.m_Y));
}

inline CGPoint Max(const CGPoint& p1, const CGPoint& p2) {
	return CGPoint(max(p1.m_X, p2.m_X), max(p1.m_Y, p2.m_Y));
}

// =============================================================================
// CGRect ======================================================================
// =============================================================================

class CGRect {
public:
	CGPoint m_P0;
	CGPoint m_P1;
	explicit CGRect(double x0, double y0, double x1, double y1) : m_P0(x0, y0), m_P1(x1, y1) {}
	explicit CGRect(const CGPoint &p0, const CGPoint &p1) : m_P0(p0), m_P1(p1) {}
	CGRect() {}
	CGRect(const CGRect &r) {
		m_P0 = r.m_P0;
		m_P1 = r.m_P1;
	}
#ifdef _MFC_VER
	CGRect(const CRect &r) {
		m_P0.m_X = r.left;
		m_P0.m_Y = r.top;
		m_P1.m_X = r.right;
		m_P1.m_Y = r.bottom;
	}
	operator CRect() {
		return CRect(int(m_P0.m_X), int(m_P0.m_Y), int(m_P1.m_X), int(m_P1.m_Y));
	}
#endif
	CGRect& operator=(const CGRect &r) {
		m_P0 = r.m_P0;
		m_P1 = r.m_P1;
		return *this;
	}
	void SetRectEmpty() {
		m_P0.m_X = 1;
		m_P0.m_Y = 1;
		m_P1.m_X = 0;
		m_P1.m_Y = 0;
	}
	bool EmptyP() const {
		return m_P0.m_X > m_P1.m_X ||
			m_P0.m_Y > m_P1.m_Y;
	}
	CGRect operator|(const CGRect &r) const {
		if (EmptyP()) return r;
		else if (r.EmptyP()) return *this;
		else return CGRect(
			min(m_P0.m_X, r.m_P0.m_X),
			min(m_P0.m_Y, r.m_P0.m_Y),
			max(m_P1.m_X, r.m_P1.m_X),
			max(m_P1.m_Y, r.m_P1.m_Y));
	}
	CGRect &operator|=(const CGRect &r) {
		if (EmptyP()) *this = r;
		else if (r.EmptyP());
		else *this = CGRect(
			min(m_P0.m_X, r.m_P0.m_X),
			min(m_P0.m_Y, r.m_P0.m_Y),
			max(m_P1.m_X, r.m_P1.m_X),
			max(m_P1.m_Y, r.m_P1.m_Y));
		return *this;
	}
	CGRect operator&(const CGRect &r) const {
		return CGRect(
			max(m_P0.m_X, r.m_P0.m_X),
			max(m_P0.m_Y, r.m_P0.m_Y),
			min(m_P1.m_X, r.m_P1.m_X),
			min(m_P1.m_Y, r.m_P1.m_Y));
	}
	CGRect &operator&=(const CGRect &r) {
		*this = CGRect(
			max(m_P0.m_X, r.m_P0.m_X),
			max(m_P0.m_Y, r.m_P0.m_Y),
			min(m_P1.m_X, r.m_P1.m_X),
			min(m_P1.m_Y, r.m_P1.m_Y));
		return *this;
	}
	void NormalizeRect()
	{
		if (m_P0.m_X > m_P1.m_X) {
			double tmp = m_P0.m_X;
			m_P0.m_X = m_P1.m_X;
			m_P1.m_X = tmp;
		}
		if (m_P0.m_Y > m_P1.m_Y) {
			double tmp = m_P0.m_Y;
			m_P0.m_Y = m_P1.m_Y;
			m_P1.m_Y = tmp;
		}
	}
	bool PtInRect(CGPoint point) const
	{
		return point.m_X >= m_P0.m_X && point.m_X < m_P1.m_X
			&& point.m_Y >= m_P0.m_Y && point.m_Y < m_P1.m_Y;
	}

	// Las medidas de ancho, alto y area
	double Area() const { return (m_P1.m_X - m_P0.m_X)*(m_P1.m_Y - m_P0.m_Y); }
	double Width() const { return m_P1.m_X - m_P0.m_X; }
	double Height() const { return m_P1.m_Y - m_P0.m_Y; }
	bool operator==(const CGRect& r)  const {
		return m_P0 == r.m_P0 && m_P1 == r.m_P1;
	}
	bool operator!=(const CGRect& r)  const {
		return m_P0 != r.m_P0 || m_P1 != r.m_P1;
	}
};

inline ostream& operator<< (ostream& s, const CGRect &r) {
	s << "(" << r.m_P0 << "-" << r.m_P1 << ")";
	return s;
}

// =============================================================================
// GRAPH Classes ===============================================================
// =============================================================================
/*
Els grafs son dirigits. Per construir un graf no dirigit hi ha dos arestes que
conecten els vertexs en les dos direccions. Aquetes arestes estan relacionades
amb apuntadors.
*/

class CEdge;
class CGraph;

// CVertex =====================================================================

class CVertex {
public:
	string m_Name; // Nom del vertex
	CGPoint m_Point; 
	list<CEdge*> m_Edges;
	CEdge* FindEdge(const char* name);
	bool MemberP(CEdge *pEdge);
	void Unlink(CEdge *pEdge);
	CVertex(const char *name, double x, double y) : m_Name(name), m_Point(x, y) {}
};

// CEdge =======================================================================

class CEdge {
public:
	string m_Name; // Nom del edge
	double m_Value; // Valor que se le asocia al edge: longitud, peso, coste, etc.
	CVertex* m_pOrigin;
	CVertex* m_pDestination;
	CEdge* m_pReverseEdge; // En caso de grafo no dirigido cada arista tiene su inverso.
	bool m_Processed;
public:
	CEdge(const char *name, double value, CVertex* pOrigin, CVertex* pDestination, CEdge *pReverseEdge)  
		: m_Name(name)
		, m_Value(value)
		, m_pOrigin(pOrigin)
		, m_pDestination(pDestination)
		, m_pReverseEdge(pReverseEdge)
	{}
};

// CGraph ======================================================================

class CGraph {
public:
	list<CVertex> m_Vertices;
	list<CEdge> m_Edges;
	string m_Filename;
	bool m_Directed; // Directed graph o undirected graph

public:
	CGraph(bool directed);
	~CGraph();
	void Clear();

	// Vertices
	CVertex* NewVertex(const char *name, double x, double y);
	CVertex* NewVertex(const CGPoint &point);
	void DeleteVertex(CVertex *pVertex);
	CVertex* FindVertex(const char *name);
	CVertex* FindVertex(const CGPoint &point, double radius);
	CVertex* GetVertex(const int index);
	int GetVertexIndex(const CVertex* pVertex);

	bool MemberP(CVertex *pVertex);
	size_t GetNVertices() { return m_Vertices.size(); }

	// Edges
	CEdge* NewEdge(const char* name, double value, const char* originName, const char* destionatioName);
	CEdge* NewEdge(CVertex *pOrigin, CVertex* pDestination);
	void DeleteEdge(CEdge *pEdge);
	CEdge* FindEdge(CVertex* pVOrigin, CVertex* pVDestination);
	CEdge* FindEdge(const char* name);
	CEdge* FindEdge(const CGPoint &point, double radius);
	bool MemberP(CVertex* pVOrigin, CVertex* pVDestination) { return FindEdge(pVOrigin, pVDestination) != NULL; }
	bool MemberP(CEdge *pEdge);
	size_t GetNEdges() { return m_Edges.size(); }
};

// =============================================================================
// CTrack ======================================================================
// =============================================================================

class CTrack {
public:
	list<CEdge*> m_Edges;
	CGraph* m_pGraph;
	//CTrack() { m_pGraph = NULL; }
	CTrack(CGraph* pGraph) {
		m_pGraph = pGraph;
	}
	void SetGraph(CGraph* pGraph) {
		Clear();
		m_pGraph = pGraph;

	}
	CTrack(const CTrack& t) : m_pGraph(t.m_pGraph), m_Edges(t.m_Edges) {}
	CTrack operator=(const CTrack& t) {
		m_pGraph = t.m_pGraph;
		m_Edges = t.m_Edges;
		return *this;
	}
	void AddFirst(CEdge* pEdge) {
		MyAssert(pEdge != NULL, AssertNULL); //No hi ha aresta
		MyAssert(this != NULL, AssertNULL); //Objecte propi no existeix
		MyAssert(m_pGraph != NULL, AssertTrackSenseGraf); //No existeix el graf
		MyAssert(m_pGraph->MemberP(pEdge), AssertNoArestaDelGraf); //Aresta no es del graf
		MyAssert(m_Edges.empty() || pEdge->m_pDestination == m_Edges.front()->m_pOrigin, AssertArestesDesconectades); //Arestes sense arestes o no connectades
		m_Edges.push_front(pEdge);
	}
	void AddLast(CEdge* pEdge) {
		MyAssert(pEdge != NULL, AssertNULL);
		MyAssert(this != NULL, AssertNULL);
		MyAssert(m_pGraph != NULL, AssertTrackSenseGraf);
		MyAssert(m_pGraph->MemberP(pEdge), AssertNoArestaDelGraf);
		MyAssert(m_Edges.empty() || pEdge->m_pDestination == m_Edges.front()->m_pOrigin, AssertArestesDesconectades);


		m_Edges.push_back(pEdge);
	}
	void Clear() {
		m_Edges.clear();
	}
	void AppendBefore(CTrack& t);
	void Append(CTrack& t);
	size_t GetNEdges() { return m_Edges.size(); }

	double Length();

	bool MemberP(CEdge* pE);
};

ostream& operator<< (ostream& s, const CTrack& track);

