// NReinas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <queue>
#include <fstream>
#include <iostream>
using namespace std;

// =============================================================================
// ALUMNOS =====================================================================
// =============================================================================


char* NomAlumne = "Juan Carlos";
char* CognomsAlumne = "Soriano Valle";
char* NIUAlumne = "1493037"; // NIA alumno

bool CheckNIU(const char* niu)
{
	char* filename= "Alumnes.csv";
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
// PROBLEMA ====================================================================
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

// CConfiguracio ===================================================================

class CConfiguracio {
public:
	int m_n;
	int *m_pReines; // Posicions de les reines (nomes les files)
	int *m_pFiles; // Files atacades per x reines 
	int *m_pDiag1; // Diagonals principals atacades per x reines
	int *m_pDiag2; // Diagonals segundaries atacades per x reines
	int m_Atacs; // Número d'atacs entre reines

public:
	CConfiguracio(int n) {
		m_n = n;
		m_pReines = new int[m_n];
		m_pFiles = new int[m_n]; 
		m_pDiag1 = new int[m_n*2-1]; 
		m_pDiag2 = new int[m_n * 2 - 1]; 
	}
	CConfiguracio(const CConfiguracio&c) {
		m_n = c.m_n;
		m_pReines = new int[m_n]; memcpy_s(m_pReines, sizeof(int)*m_n, c.m_pReines, sizeof(int)*m_n);
		m_pFiles = new int[m_n]; memcpy_s(m_pFiles, sizeof(int)*m_n, c.m_pFiles, sizeof(int)*m_n);
		m_pDiag1 = new int[m_n * 2 - 1]; memcpy_s(m_pDiag1, sizeof(int)*(m_n * 2 - 1), c.m_pDiag1, sizeof(int)*(m_n * 2 - 1));
		m_pDiag2 = new int[m_n * 2 - 1]; memcpy_s(m_pDiag2, sizeof(int)*(m_n * 2 - 1), c.m_pDiag2, sizeof(int)*(m_n * 2 - 1));
		m_Atacs = c.m_Atacs;
	}
	CConfiguracio &operator=(const CConfiguracio &c) {
		//m_n = c.m_n;
		memcpy_s(m_pReines, sizeof(int)*m_n, c.m_pReines, sizeof(int)*m_n);
		memcpy_s(m_pFiles, sizeof(int)*m_n, c.m_pFiles, sizeof(int)*m_n);
		memcpy_s(m_pDiag1, sizeof(int)*(m_n * 2 - 1), c.m_pDiag1, sizeof(int)*(m_n * 2 - 1));
		memcpy_s(m_pDiag2, sizeof(int)*(m_n * 2 - 1), c.m_pDiag2, sizeof(int)*(m_n * 2 - 1));
		m_Atacs = c.m_Atacs;
		return  *this;
	}
	~CConfiguracio() {
		delete[] m_pReines;
		delete[] m_pFiles;
		delete[] m_pDiag1;
		delete[] m_pDiag2;
	}
	void ConfiguracioAleatoria() {
		// Colocar les reines aleatoriament
		m_Atacs = 0;
		memset(m_pFiles, 0, sizeof(int)*m_n);
		memset(m_pDiag1, 0, sizeof(int)*(2 * m_n - 1));
		memset(m_pDiag2, 0, sizeof(int)*(2 * m_n - 1));
		for (int columna = 0; columna < m_n; ++columna) {
			int fila = rand() % m_n;
			m_pReines[columna] = fila;
			++m_pFiles[fila]; if (m_pFiles[fila] > 1) ++m_Atacs;
			++m_pDiag1[columna - fila + m_n - 1]; if (m_pDiag1[columna - fila + m_n - 1] > 1) ++m_Atacs;
			++m_pDiag2[columna + fila]; if (m_pDiag2[columna + fila] > 1) ++m_Atacs;
		}
	}
	void MoureA(int fila, int columna) {
		int antFila = m_pReines[columna];
		--m_pFiles[antFila]; if (m_pFiles[antFila] >= 1) --m_Atacs;
		--m_pDiag1[columna - antFila + m_n - 1]; if (m_pDiag1[columna - antFila + m_n - 1] >= 1) --m_Atacs;
		--m_pDiag2[columna + antFila]; if (m_pDiag2[columna + antFila] >= 1) --m_Atacs;

		m_pReines[columna] = fila;
		++m_pFiles[fila]; if (m_pFiles[fila] > 1) ++m_Atacs;
		++m_pDiag1[columna - fila + m_n - 1]; if (m_pDiag1[columna - fila + m_n - 1] > 1) ++m_Atacs;
		++m_pDiag2[columna + fila]; if (m_pDiag2[columna + fila] > 1) ++m_Atacs;
	}
	bool SolucioP() {
		for (int i = 0; i < m_n; ++i) {
			if (m_pReines[i] < 0 || m_pReines[i] >= m_n) return false;
			for (int j = i + 1; j < m_n; ++j) {
				if (m_pReines[i] == m_pReines[j]) return false;
				if (j - i == abs(m_pReines[j] - m_pReines[i])) return false;
			}
		}
		return true;
	}
};

// Solucionador ================================================================
int Iteracions = 0;

bool SolucionadorGreedy(int n, CConfiguracio &conf)
{
	conf.ConfiguracioAleatoria();
	while (conf.m_Atacs > 0) {
		++Iteracions;
		int antAtacs = conf.m_Atacs;
		CConfiguracio millorConf(conf);
		for (int columna = 0; columna < n; ++columna) {
			int antFila = conf.m_pReines[columna];
			if (conf.m_pFiles[antFila] > 0 || conf.m_pDiag1[columna - antFila + n - 1] > 0 || conf.m_pDiag2[columna + antFila] > 0)
			{
				for (int fila = 0; fila < n; ++fila) {
					if (antFila != fila && conf.m_pFiles[fila] == 0 && conf.m_pDiag1[columna - fila + n - 1] == 0 && conf.m_pDiag2[columna + fila] == 0) { //conf.m_pFiles[fila]==0 --> MOVER A FILAS QUE NO ESTAN SIENDO ATACADAS
						conf.MoureA(fila, columna);
						//conf.m_pFiles[fila] == 0;
						if (conf.m_Atacs < millorConf.m_Atacs) millorConf = conf;
						conf.MoureA(antFila, columna);
					}
				}
			}
		}
		if (millorConf.m_Atacs == antAtacs) break;
		conf = millorConf;
	}
	if (conf.m_Atacs == 0) {
		// Solució trobada
		return true;
	}
	else {
		return false;
	}
}

// main ========================================================================

int main(int argc, char *argv[])
{
	if (!CheckNIU(NIUAlumne)) {
		puts("Indentificacio dels alumnes incorrecte");
		return 1;
	}
	printf("NIU: %s\n", NIUAlumne);
	printf("NOM: %s\n", NomAlumne);
	printf("COGNOMS: %s\n", CognomsAlumne);

	if (argc != 3 && argc != 1) {
		puts("Us per probar un cas concret: NReinas N Intents\n");
		puts("Us per competicio: NReinas\n");
		return 1;
	}
	if (argc == 3) {
		// Cas concret ---------------------------------------------------------
		int n = atoi(argv[1]);
		int intents = atoi(argv[2]);
		printf_s("PARAMETRES N=%d INTENTS=%d\n", n, intents);
		printf_s("Col.locar %d reines en un taulell de %dx%d\n", n, n, n);
		srand(time(NULL));
		Iteracions = 0;
		double t0 = Clock();
		int intent;
		bool solucio = false;
		CConfiguracio resultat(n);
		for (intent = 1; intent <= intents; ++intent) {
			solucio = SolucionadorGreedy(n, resultat);
			if (solucio) break;

		}
		double t1 = Clock();
		if (solucio) {
			puts("SOLUCIO:");
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) if (resultat.m_pReines[j]==i) putchar('X'); else putchar('-');
				putchar('\n');
			}
			printf("TEMPS: %lf (%lf seg./iteracio)\n", t1 - t0, (t1 - t0) / Iteracions);
			printf("INTENT: %d\n", intent);
			printf("ITERACIONS: %d (%lf iteracions/intents)\n", Iteracions, double(Iteracions) / intents);
			if (!resultat.SolucioP()) puts("ERROR: NO ES SOLUCIO!\n");
		}
		else {
			puts("SOLUCIO NO TROBADA!");
			printf("TEMPS: %lf (%lf seg./iteracio)\n", t1 - t0, (t1 - t0) / Iteracions);
			printf("INTENTS: %d\n", intents);
			printf("ITERACIONS: %d (%lf iteracions/intents)\n", Iteracions, double(Iteracions) / intents);
		}
	}
	else {
		// Competició ----------------------------------------------------------------
		FILE *fp;
		fopen_s(&fp, "Sortida.txt", "w");
		fprintf(fp, "NIU: %s\n", NIUAlumne);
		fprintf(fp, "NOM: %s\n", NomAlumne);
		fprintf(fp, "COGNOMS: %s\n", CognomsAlumne);
		fputs("\n", fp);
		srand(time(NULL));
		int intent;
		double t0 = Clock();
		for (int n = 100; ; ++n) {
			bool solucio;
			CConfiguracio resultat(n);
			Iteracions = 0;
			double t1 = Clock();
			for (intent = 1; intent <= 100000; ++intent) {
				solucio = SolucionadorGreedy(n, resultat);
				if (solucio) break;
			}
			double t2 = Clock();
			if (solucio) {
				printf("%6.2f seg. (%6.2f seg.): Solucio trobada per %3d reines en el intent %6d amb %7d iteracions\n", Clock() - t0,t2-t1, n, intent, Iteracions);
				if (!resultat.SolucioP()) {
					puts("ERROR: NO ES SOLUCIO!\n");
					return 0;
				}
				fprintf(fp, "n-reines: %d\n", n);
				fprintf(fp, "TEMPS TOTAL: %f\n", Clock() - t0);
				fprintf(fp, "TEMPS SOLUCIO: %f\n", t2-t1);
				fprintf(fp, "INTENT: %d\n", intent);
				fprintf(fp, "ITERACIONS: %d\n", Iteracions);
				fputs("SOLUCIO: ",fp);
				for (int i=0; i<n; ++i) fprintf(fp, "%3d ",resultat.m_pReines[i]);
				fputs("\n\n",fp);
				fflush(fp);
			}
			else {
				printf("NO HA TROBAT SOLUCIO PER %d REINES!\n", n);
				return 0;
			}
		}
		return 0;
	}
}