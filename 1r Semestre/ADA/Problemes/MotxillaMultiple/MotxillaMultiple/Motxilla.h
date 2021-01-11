#pragma once
#include<vector>

using namespace std;

class Motxilla
{
public:
	Motxilla();
	Motxilla(vector<int> valors, vector<int> pesos, int capacitat_total, int n_elements);
	~Motxilla();
	int knapSack_multiple(vector<vector<int>>& K);
private:
	vector<int> m_valors;
	vector<int> m_pesos;
	int m_capacitat_total;
	int m_num_elements;

	// retorna el maxim entre dos enters
	int max(int a, int b) { return (a > b) ? a : b; }
};
