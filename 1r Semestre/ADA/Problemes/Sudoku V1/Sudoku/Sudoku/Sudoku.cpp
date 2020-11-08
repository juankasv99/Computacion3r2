// Sudoku.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "CSudoku.h"
#include <vector>

// =============================================================================
// ALUMNO =====================================================================
// =============================================================================

string NombreAlumno = "Juan Carlos";
string ApellidosAlumno = "Soriano Valle";
string NIUAlumno = "1493037"; // NIU alumno

// =============================================================================
// SOLUCIONADOR DE SODOKU ======================================================
// =============================================================================

// Soluciona ===================================================================

bool CSudoku::Soluciona()
{
	return true;
}


// =============================================================================
// main ========================================================================
// =============================================================================

int main(int argc, char *argv[])
{
	if (!CheckNIU(NIUAlumno.c_str())) {
		cout << "Indentificacio dels alumnes incorrecte" << endl;
		return 1;
	}
	cout << "Nom Alumne .....: " << NombreAlumno << endl;
	cout << "Cognoms Alumne .: " << ApellidosAlumno << endl;
	cout << "NIU Alumne .....: " << NIUAlumno << endl;
	/*if (argc != 3) {
		cout << "Uso: Sudoku FicheroSudoku FitxerSolucioSudoku" << endl;
		return 1;
	}*/
	CSudoku taulell;
	taulell.Load(argv[1]);
	cout << "SUDOKU:" << endl;
	cout << taulell;
	double t0 = Clock();
	// Solucionar 
	bool HiHaSolucio = taulell.Soluciona();
	double t1 = Clock();
	if (HiHaSolucio) {
		cout << "SOLUCIO:" << endl;
		cout << taulell;
		taulell.Save(argv[2]);
	}
	else {
		cout << "NO TE SOLUCIO" << endl;
	}
	cout << "TIEMPO DE EJECUCION: " << t1 - t0 << endl;
    return 0;
}