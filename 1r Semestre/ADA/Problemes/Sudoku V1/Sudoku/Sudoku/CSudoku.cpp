// Sudoku.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "CSudoku.h"



// =============================================================================
// ALUMNO =====================================================================
// =============================================================================

bool CheckNIU(const char* niu)
{
	char* filename = "Alumnes.csv";
	ifstream nius(filename);

	if (!nius.good()) {
		cout << "Error opening file Alumnes.csv" << endl;
		filename = "..\\Alumnes.csv";
		nius.open(filename);
		if (!nius.good()) {
			cout << "Error opening file ..\\Alumnes.csv" << endl;
			filename = "..\\..\\Alumnes.csv";
			nius.open(filename);
			if (!nius.good()) {
				cout << "Error opening file ..\\..\\Alumnes.csv" << endl;
				filename = "..\\..\\..\\Alumnes.csv";
				nius.open(filename);
				if (!nius.good()) {
					cout << "Error opening file ..\\..\\..\\Alumnes.csv" << endl;
					return false;
				}
			}
		}
	}
	cout << filename << " readed" << endl;
	char buf[256];
	while (!nius.eof()) {
		nius.getline(buf, 256);
		if (buf[0] == '\0') break;
		if (strncmp(niu, buf, 7) == 0) return true;
	}
	return false;
}

// =============================================================================
// UTILIDADES ==================================================================
// =============================================================================

// Clock =======================================================================

double Clock()
{
	LARGE_INTEGER cnt;
	LARGE_INTEGER fre;

	if (QueryPerformanceFrequency(&fre) && QueryPerformanceCounter(&cnt)) {
		return (double)cnt.QuadPart / (double)fre.QuadPart;
	}
	else return (double)clock() / (double)CLOCKS_PER_SEC;
}

// StrPrint ====================================================================

string StrPrint(const char* Format, ...)
{
	va_list al;
	va_start(al, Format);
	char buf[1024];
	_vsnprintf_s(buf, 1024, Format, al);
	buf[1023] = 0;
	va_end(al);
	return buf;
}

// =============================================================================
// EXCEPCIONS ==================================================================
// =============================================================================

// MyException =================================================================

MyException::MyException(const char* Format, ...)
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
// CSudoku =====================================================================
// =============================================================================

// CSudoku =====================================================================

CSudoku::CSudoku(int n)
{
	m_n = n;
	m_Dim = n * n;
	m_Taulell = new int[m_Dim*m_Dim];
	for (int i = 0; i < m_Dim * m_Dim; ++i) m_Taulell[i] = 0;
}

// ~CSudoku ====================================================================

CSudoku::~CSudoku()
{
	delete[] m_Taulell;
}

// SetMidaTaulell ==============================================================

void CSudoku::SetMidaTaulell(int n)
{
	delete[] m_Taulell;
	m_n = n;
	m_Dim = n * n;
	m_Taulell = new int[m_Dim * m_Dim];
	for (int i = 0; i < m_Dim * m_Dim; ++i) m_Taulell[i] = 0;
}

// Load ========================================================================

void CSudoku::Load(const char* filename)
{
	ifstream file(filename);
	if (!file.good()) throw MyException("Error obrint graf %s", filename);
	// Llegir la capcelera
	char buff[255];
	file.getline(buff, 255);
	if (strcmp("SUDOKU 1.0", buff) != 0) throw MyException("Falta la capcalera SUDOKU 1.0 al fitxer %s", filename);
	int n;
	file >> n;
	SetMidaTaulell(n);
	for (int i = 0; i < m_Dim * m_Dim; ++i) {
		file >> m_Taulell[i];
	}
	file.close();
}

// Save ========================================================================

void CSudoku::Save(const char* filename)
{
	ofstream file(filename);
	if (!file.good()) throw MyException("Error obrint fitxer %s", filename);
	file << "SUDOKU 1.0" << endl;
	file << m_n << endl;
	for (int i = 0; i < m_Dim * m_Dim; ++i) {
		file << m_Taulell[i];
		if ((i+1) % m_Dim == 0) file << endl;
		else file << " ";
	}
	file.close();
}


// Print =======================================================================

ostream& operator<< (ostream& s, CSudoku &sudoku) {
	for (int i = 0; i < sudoku.m_Dim; ++i) {
		for (int j = 0; j < sudoku.m_Dim; ++j) {
			s << sudoku(i, j) << " ";
		}
		s << endl;
	}
	return s;
}

