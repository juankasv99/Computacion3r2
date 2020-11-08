// Sudoku.cpp: define el punto de entrada de la aplicación de consola.
//

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;



// =============================================================================
// ALUMNO =====================================================================
// =============================================================================

bool CheckNIU(const char* niu);

// =============================================================================
// UTILIDADES ==================================================================
// =============================================================================

// Clock =======================================================================

double Clock();

// StrPrint ====================================================================

string StrPrint(const char* Format, ...);

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
	MyException(const char* Format, ...);
	MyException(const MyException& rhs);
	virtual const char* what() const throw() { return m_Message; }
};

// =============================================================================
// CSudoku =====================================================================
// =============================================================================

class CSudoku {
public:
	int m_n; // Tamaño del lado del cuadrado pequeño
	int m_Dim;
	int* m_Taulell;
	// Soluciona3
	bool* m_DigitsFiles;
	bool* m_DigitsColumnes;
	bool* m_DigitsCuadrats;
public:
	CSudoku(int n=3);
	~CSudoku();
	void SetMidaTaulell(int n);
	int& operator()(int i, int j) { return m_Taulell[i * m_Dim + j]; }
	int& Casella(int i, int j) { return m_Taulell[i * m_Dim + j]; }
	void Load(const char* filename);
	void Save(const char* filename);
	bool Soluciona();
};


// Print =======================================================================

ostream& operator<< (ostream& s, CSudoku& sudoku);
