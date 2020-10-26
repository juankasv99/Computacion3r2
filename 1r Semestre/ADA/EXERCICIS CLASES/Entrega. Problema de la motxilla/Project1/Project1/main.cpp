#include<stdio.h> 
#include<iostream>
#include <iomanip>
#include<vector>
#include "Motxilla.h"

using namespace std;

bool Iguals(vector<int> sol_ob, vector<int> t_Solucio)
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

int main() 
{ 
	bool valid = true;
	float reduccio = 2.0;
	float grau1 = 10.0;
	float grau2 = 10.0;
	cout << endl << "Grade :=>> " << grau1 << endl << endl;

	vector<vector<int>> valors;
	vector<vector<int>> pesos;
	vector<vector<int>> t_Benefici;
	vector<vector<int>> t_sol;

	valors = { {60, 100, 120},{ 12,10,20,15 },{ 7,5,12,23,20 },{37,12,500,50,41},{30,14,16,9},{48,44, 9,10,21,26,16,17,34,41,22,24,65,43,23,34,56,7,21,22,31,1,12,10,5,13,21,45,43,11,3,1}};
	pesos = { {10, 20, 30},{ 2, 1, 3, 2 },{ 3, 2, 4, 7,6 },{21,11,51,26,30},{6,3,4,2},{10,11,7,6,11,7,9,10,8,7,4,10,11,6,12,11,8,17,8,3,13,9,4,5,2,4,7,15, 13, 1, 2,1}};
	vector<int>  Cap_tot = { 50,5,10,50,10,33 };

	t_sol = { { 0,1,1 },{1,1,0,1},{0,0,1,0,1},{1,0,0,1,0},{1,0,1,0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0} };

	for (int test = 0; test < valors.size(); test++)
	{
		cout << endl << endl;
		cout << "Comment :=>> Iniciant test " << test + 1 << endl;
		cout << "Comment :=>> ===============" << endl;
		int n_elements = valors[test].size();
		Motxilla m(valors[test], pesos[test], Cap_tot[test], n_elements);
		

		vector<int> sol_act;
	    vector<int> sol_opt;
	    int ben_optim;
	    
	    sol_act.resize(n_elements, 0);
	    sol_opt.resize(n_elements, 0);
	    ben_optim = 0;
	    
	    
	    m.knapsack_back(sol_act,sol_opt, 0, 0, 0, ben_optim);
	

		if (Iguals(sol_opt, t_sol[test]))
		{
			cout << "Comment :=>> Test correcte" << endl;
			cout << "Comment :=>> =============" << endl;
		}
		else
		{
			cout << "Comment :=>> Test incorrecte" << endl;
			cout << "Comment :=>> Solucio obtinguda: ";
			for (int ob = 0; ob < n_elements; ob++)
				cout << sol_opt[ob] << " ";
			cout << endl;
			cout << "Comment :=>> Solucio esperada: ";
			for (int ob = 0; ob < n_elements; ob++)
				cout << t_sol[test][ob] << " ";
			cout << endl;
			grau1 = grau1 - reduccio;
			cout << "Grade :=>>  " << grau1 << endl << endl;
			
		}
	}
	
	for (int test = 0; test < valors.size(); test++)
	{
		cout << endl << endl;
		cout << "Comment :=>> Iniciant test " << test + 1 << endl;
		cout << "Comment :=>> ===============" << endl;
		int n_elements = valors[test].size();
		Motxilla m(valors[test], pesos[test], Cap_tot[test], n_elements);
		

		vector<int> sol_act;
	    vector<int> sol_opt;
	    int ben_optim = 0;
	    int pes_optim = 0;
	    
	    sol_act.resize(n_elements, 0);
	    sol_opt.resize(n_elements, 0);
	    
	    m.AvaluaMotxilla_back(0, 0, 0, sol_act, sol_opt, ben_optim, pes_optim);
	

		if (Iguals(sol_opt, t_sol[test]))
		{
			cout << "Comment :=>> Test correcte" << endl;
			cout << "Comment :=>> =============" << endl;
		}
		else
		{
			cout << "Comment :=>> Test incorrecte" << endl;
			cout << "Comment :=>> Solucio obtinguda: ";
			for (int ob = 0; ob < n_elements; ob++)
				cout << sol_opt[ob] << " ";
			cout << endl;
			cout << "Comment :=>> Solucio esperada: ";
			for (int ob = 0; ob < n_elements; ob++)
				cout << t_sol[test][ob] << " ";
			cout << endl;
			grau2 = grau2 - reduccio;
			cout << "Grade :=>>  " << grau2 << endl << endl;
			
		}
	}
    float grade = max(grau1,grau2);
	cout << "Grade :=>>  " << grade << endl << endl;
	system("PAUSE");
	
	return 0;
	
} 
