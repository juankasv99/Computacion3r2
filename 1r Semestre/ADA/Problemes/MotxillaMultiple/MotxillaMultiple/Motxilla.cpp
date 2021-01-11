#include "Motxilla.h"
#include<stdio.h> 
#include<iostream>
#include <iomanip>



Motxilla::Motxilla()
{
}

Motxilla::Motxilla(vector<int> valors, vector<int> pesos, int capacitat_total, int n_elements)
{
	m_num_elements = n_elements;

	m_valors.resize(m_num_elements);
	m_pesos.resize(m_num_elements);

	for (int i = 0; i < m_num_elements; i++) {
		m_valors[i] = valors[i];
		m_pesos[i] = pesos[i];
	}
	m_capacitat_total = capacitat_total;

}

Motxilla::~Motxilla()
{
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

int Motxilla::knapSack_multiple(vector<vector<int>>& K)
{
	vector<int> nTimes;
	nTimes.resize(this->m_num_elements);
	int i, w;
	for (i = 1; i <= this->m_num_elements; i++) {

		for (w = 1; w <= this->m_capacitat_total; w++) {
			if (this->m_pesos[i - 1] <= w)
			{
				K[i][w] = max(this->m_valors[i - 1] + K[i][w - this->m_pesos[i - 1]], K[i - 1][w]);
				if (this->m_valors[i - 1] + K[i][w - this->m_pesos[i - 1]] > K[i - 1][w])
					nTimes[i - 1]++;
			}
			else
				K[i][w] = K[i - 1][w];

		}
	}
	mostraMatriu(K);
	return K[this->m_num_elements][this->m_capacitat_total];
}