#pragma once
#include<vector>

using namespace std;

class Motxilla
{
public:
	Motxilla();
	Motxilla(vector<int> valors, vector<int> pesos, int capacitat_total, int n_elements);
	~Motxilla();
	void AvaluaMotxilla_back(int nivell, int pes_act, int valor_act, vector<int>& sol_act, vector<int>& sol_opt, int& ben_opt, int& pes_opt);
	void knapsack_back(vector<int>& sol_act, vector<int>& sol_opt, int ben_act, int pes_act, int k, int& ben_opt);
	
private:
	vector<int> m_valors;
	vector<int> m_pesos;
	int m_capacitat_total;
	int m_num_elements;

	// retorna el maxim entre dos enters
	int max(int a, int b) { return (a > b) ? a : b; }
};
