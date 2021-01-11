#include<stdio.h> 
#include<iostream>
#include <iomanip>
#include<vector>
#include "Motxilla.h"

using namespace std;

bool Iguals(vector<vector<int>> t_Benefici, vector<int> t_Solucio)
{
	int i = 0;
	bool diferents = false;
	int cap_tot = t_Benefici[0].size();
	while ((i < t_Solucio.size()) && !diferents)
	{
		if (t_Solucio[i] != t_Benefici[i][cap_tot-1])
			{
				diferents = true;
			}
		i++;
	}
	return !diferents;
}

int main() 
{ 
	bool valid = true;
	float reduccio = 2.0;
	float grade = 10.0;
	cout << endl << "Grade :=>> " << grade << endl << endl;

	vector<vector<int>> valors;
	vector<vector<int>> pesos;
	vector<vector<int>> t_Benefici;
	vector<vector<int>> t_sol;

	valors = { {60, 100, 120},{ 12,10,20,15 },{ 7,5,12,23,20 },{37,12,500,50,41},{30,14,16,9} };
	pesos = { {10, 20, 30},{ 2, 1, 3, 2 },{ 3, 2, 4, 7,6 },{21,11,51,26,30},{6,3,4,2} };
	vector<int>  Cap_tot = { 50,5,10,50,10 };

	vector<int> b_max_sol = { 300,50,32,87,48 };
	t_sol = { { 5,0,0 },{0,5,0,0},{0,0,1,0,1},{1,0,0,1,0},{1,0,0,2} };

	for (int test = 0; test < valors.size(); test++)
	{
		cout << endl << endl;
		cout << "Comment :=>> Iniciant test " << test + 1 << endl;
		cout << "Comment :=>> ===============" << endl;
		int n_elements = valors[test].size();
		Motxilla m(valors[test], pesos[test], Cap_tot[test], n_elements);
		t_Benefici.resize(n_elements + 1);

		for (int i = 0; i <= n_elements; i++)
			t_Benefici[i].resize(Cap_tot[test] + 1, 0);

		int b_max = m.knapSack_multiple(t_Benefici);
	

		if ((b_max == b_max_sol[test]) && (Iguals(t_Benefici, t_sol[test])))
		{
			cout << "Comment :=>> Test correcte" << endl;
			cout << "Comment :=>> =============" << endl;
		}
		else
		{
			cout << "Comment :=>> Test incorrecte" << endl;
			cout << "Comment :=>> Benefici obtingut: ";
			cout << b_max << endl;
			cout << "Comment :=>> Solucio obtinguda: ";
			for (int ob = 0; ob < n_elements; ob++)
				cout << t_Benefici[ob][Cap_tot[test]] << " ";
			cout << endl;
			cout << "Comment :=>> Benefici esperat: " ;
			cout << b_max_sol[test] << endl;
			cout << "Comment :=>> Solucio esperada: ";
			for (int ob = 0; ob < n_elements; ob++)
				cout << t_sol[test][ob] << " ";
			cout << endl;
			grade = grade - reduccio;
			cout << "Grade :=>>  " << grade << endl << endl;
			
		}
	}
	cout << "Grade :=>>  " << grade << endl << endl;
	system("PAUSE");
	
	return 0;
	
} 
