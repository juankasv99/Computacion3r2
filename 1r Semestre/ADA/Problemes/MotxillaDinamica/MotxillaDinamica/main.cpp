#include<stdio.h> 
#include<iostream>
#include <iomanip>
#include<vector>
#include "Motxilla.h"

using namespace std;

bool Iguals(vector<bool> sol_ob, vector<bool> t_Solucio)
{
	int i = 0;
	bool diferents = false;
	while ((i < t_Solucio.size()) && !diferents)
	{
		if (t_Solucio[i] != sol_ob[i])
			{
				diferents = true;
			}
		i++;
	}
	return !diferents;
}

void mostraMatriu(vector<vector<int>>& k) {

	cout << setw(3) << " ";
	for (int j = 0; j < k[0].size(); j++)
		cout << setw(4) << j;
	cout << endl;
	for (int i = 0; i < k.size(); i++) {

		cout << setw(3) << i << " ";
		for (int j = 0; j < k[0].size(); j++) {
			cout << setw(3) << k[i][j] << " ";
		}
		cout << endl;
	}
}

void swap(vector<float>& v, int pos1, int pos2)
{
	float aux = v[pos1];
	v[pos1] = v[pos2];
	v[pos2] = aux;
}
int divideixArray(vector<float>& v1, vector<float>& v2, vector<float>& vRef, vector<float>& enters, int indexInici, int indexFinal)
{
	int posPivot = indexInici;
	int inici = indexInici;
	int final = indexFinal;
	
	while (inici < final)
	{
		while ((vRef[final] <= vRef[posPivot]) && (inici < final))
			final--;
		while ((vRef[inici] > vRef[posPivot]) && (inici < final))
			inici++;
		if (vRef[final] > vRef[inici])
		{
			swap(vRef, inici, final);
			swap(v1, inici, final);
			swap(v2, inici, final);
			swap(enters, inici, final);
		}
	}
	swap(vRef, inici, posPivot);
	swap(v1, inici, posPivot);
	swap(v2, inici, posPivot);
	swap(enters, inici, final);

	return inici;
}

void ordena(vector<float>& v1, vector<float>& v2, vector<float>& vRef, vector<float>& enters, int indexInici, int indexFinal)
{
	if (indexInici < indexFinal)
	{
		int PosPivot = divideixArray(v1, v2, vRef, enters, indexInici, indexFinal);
		ordena(v1, v2, vRef, enters, indexInici, PosPivot - 1);
		ordena(v1, v2, vRef, enters, PosPivot + 1, indexFinal);
	}
}



int main() 
{ 
	bool valid = true;
	float reduccio = 2.0;
	float grade = 10.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	vector<vector<float>> t_Benefici;
	vector<vector<float>> valors;
	vector<vector<float>> pesos;
	vector<bool> solucio;

	valors = { {60, 100, 120},{ 12,10,20,15 },{ 7,5,12,23,20 },{37,12,500,50,41},{30,14,16,9},{48,44, 9,10,21,26,16,17,34,41,22,24,65,43,23,34,56,7,21,22,31,1,12,10,5,13,21,45,43,11,3,1}};
	pesos = { {10, 20, 30},{ 2, 1, 3, 2 },{ 3, 2, 4, 7,6 },{21,11,51,26,30},{6,3,4,2},{10,11,7,6,11,7,9,10,8,7,4,10,11,6,12,11,8,17,8,3,13,9,4,5,2,4,7,15, 13, 1, 2,1}};
	vector<int>  Cap_tot = { 50,5,10,50,10,33 };

	vector<vector<bool>> t_sol = { { 0,1,1 },{1,1,0,1},{0,0,1,0,1},{1,0,0,1,0},{1,0,1,0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0} };

	for (int test = 0; test < valors.size(); test++)
	{
		cout << endl << endl;
		cout << "Comment :=>> Iniciant test " << test + 1 << endl;
		cout << "Comment :=>> ===============" << endl;
		int n_elements = valors[test].size();
		Motxilla m(valors[test], pesos[test], Cap_tot[test], n_elements);
		

	    int numElements = m.getNumElements();
	    int cap_t = m.getCapacitat();
	    
	    t_Benefici.resize(numElements + 1);
	    for (int i = 0; i <= numElements; i++)
		    t_Benefici[i].resize(cap_t + 1, 0);
	
	    float val_max = m.knapSack(t_Benefici);
		

	    solucio.resize(numElements, false);

	    m.reconstruccio(t_Benefici, solucio);
	

		if (Iguals(solucio, t_sol[test]))
		{
			cout << "Comment :=>> Test correcte" << endl;
			cout << "Comment :=>> =============" << endl;
		}
		else
		{
			cout << "Comment :=>> Test incorrecte" << endl;
			cout << "Comment :=>> Solucio obtinguda: ";
			for (int ob = 0; ob < n_elements; ob++)
				cout << solucio[ob] << " ";
			cout << endl;
			cout << "Comment :=>> Solucio esperada: ";
			for (int ob = 0; ob < n_elements; ob++)
				cout << t_sol[test][ob] << " ";
			cout << endl;
			grade = grade - reduccio;
			cout << "Grade :=>>  " << grade << endl << endl;
			
		}
		t_Benefici.clear();
		solucio.clear();
	}
	
	cout << "Grade :=>>  " << grade << endl << endl;
	system("PAUSE");
	
	return 0;
	
} 