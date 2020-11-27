#pragma once
#include<stdio.h> 
#include<iostream>
#include <iomanip>
#include<vector>

using namespace std;


class Motxilla
{
public:
	Motxilla();
	Motxilla(vector<float> valors, vector<float> pesos, int capacitat_total, int n_elements);
	~Motxilla();

	int getCapacitat() const { return m_capacitat_total; };
	int getNumElements() const { return m_num_elements; };

	float knapSack(vector<vector<float>>& K);
	void reconstruccio(vector<vector<float>>& K, vector<bool>& solucio);
	int knapSack_multiple(vector<vector<int>>& K);
	int knapSack_multiple_opt(vector<vector<int>>& K);

	void AvaluaMotxilla_back(int nivell, float pes_act, float valor_act, vector<int>& sol_act, vector<int>& sol_opt, float& ben_opt, float& pes_opt);
	void knapsack_back(vector<int>& sol_act, vector<int>& sol_opt, float ben_act, float pes_act, int k, float& ben_opt);
	void knapsack_back_forw(vector<int>& sol_act, vector<int>& sol_opt, float ben_act, float pes_act, int k, float& ben_opt);

private:
	vector<int> m_valors;
	vector<int> m_pesos;
	int m_capacitat_total;
	int m_num_elements;

	// retorna el maxim entre dos enters
	int max(int a, int b) { return (a > b) ? a : b; }
	float cota(float cap_act, float ben_act, int k);
};