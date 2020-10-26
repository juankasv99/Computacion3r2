#include "Motxilla.h"


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

void Motxilla::AvaluaMotxilla_back(int nivell, int pes_act, int valor_act, vector<int>& sol_act, vector<int>& sol_opt, int& ben_opt, int& pes_opt) {

	//IMPLEMENTAR
}


void Motxilla::knapsack_back(vector<int>& sol_act, vector<int>& sol_opt, int ben_act, int pes_act, int k, int& ben_opt) {

	for (int v = 1; v >= 0; v--) {
		sol_act[k] = v;
		pes_act = pes_act + v * m_pesos[k];
		ben_act = ben_act + v * m_valors[k];
		if (pes_act <= m_capacitat_total) {
			if (k == m_num_elements - 1) {
				if (ben_act > ben_opt) {
					ben_opt = ben_act;
					for (int i = 0; i < m_num_elements; i++) { sol_opt[i] = sol_act[i]; }
				}
			}
			else
				knapsack_back(sol_act, sol_opt, ben_act, pes_act, k + 1, ben_opt);
		}
		sol_act[k] = 0;
		pes_act = pes_act - v * m_pesos[k];
		ben_act = ben_act - v * m_valors[k];
	}
}