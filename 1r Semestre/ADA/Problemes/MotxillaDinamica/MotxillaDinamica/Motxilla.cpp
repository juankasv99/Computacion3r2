#include "Motxilla.h"



Motxilla::Motxilla()
{
	m_num_elements = 0;
	m_capacitat_total = 0;
}

Motxilla::Motxilla(vector<float> valors, vector<float> pesos, int capacitat_total, int n_elements)
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

// Retorna el valor màxim que hi pot haver a la motxilla de capacitat Cap_tot amb els elements del main
float Motxilla::knapSack(vector<vector<float>>& K)
{
	//cap_tot = m_capacitat_total; pes = m_pesos, val = m_valors, n = m_num_elements
	int cap_total = this->m_capacitat_total;
	int i, w;
	for (i = 1; i <= this->m_num_elements; i++) {
		for (w = 1; w <= cap_total; w++) {
			if (this->m_pesos[i - 1] <= w)
				K[i][w] = max(this->m_valors[i - 1] + K[i - 1][w - this->m_pesos[i - 1]], K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}
	
	

	return K[this->m_num_elements][cap_total];
}

void Motxilla::reconstruccio(vector<vector<float>>& K, vector<bool>& solucio)
{
	int beneficiTotal = K[this->m_pesos.size()][this->m_capacitat_total];
	for (int i = this->m_pesos.size(); i > 0; i--) {
		if (beneficiTotal != K[i - 1][this->m_capacitat_total]) {
			cout << " " << this->m_pesos[i-1];
			solucio[i - 1] = true;
			this->m_capacitat_total -= this->m_pesos[i-1];
			beneficiTotal -= this->m_valors[i-1];
		}
	}
	if (beneficiTotal != 0) {
		cout << " " << this->m_pesos[0];
		solucio[0] = true;
	}
	cout << "" << endl;
}

int Motxilla::knapSack_multiple(vector<vector<int>>& K)
{
    //IMPLEMENTAR
	return 0;
}




void Motxilla::AvaluaMotxilla_back(int nivell, float pes_act, float valor_act, vector<int>& sol_act, vector<int>& sol_opt, float& ben_opt, float& pes_opt) {

	for (int i = nivell; i < m_num_elements; i++) {
		if (m_pesos[i] + pes_act <= m_capacitat_total) {
			pes_act = m_pesos[i] + pes_act;
			sol_act[i] = sol_act[i] + 1;
			valor_act = valor_act + m_valors[i];
			if (valor_act >= ben_opt) {
				ben_opt = valor_act;
				pes_opt = pes_act;
				for (int j = 0; j < m_num_elements; j++) {
					sol_opt[j] = sol_act[j];
				}
			}
			AvaluaMotxilla_back(i + 1, pes_act, valor_act, sol_act, sol_opt, ben_opt, pes_opt);
			valor_act = valor_act - m_valors[i];
			pes_act = pes_act - m_pesos[i];
			sol_act[i] = sol_act[i] - 1;
		}
	}
}


void Motxilla::knapsack_back(vector<int>& sol_act, vector<int>& sol_opt, float ben_act, float pes_act, int k, float& ben_opt) {

	for (int v = 1; v >= 0; v--) {
		sol_act[k] = v;
		pes_act = pes_act + v * m_pesos[k];
		ben_act = ben_act + v * m_valors[k];
		if (pes_act <= m_capacitat_total) {
			if (k ==m_num_elements-1) {
				if (ben_act > ben_opt) {
					ben_opt = ben_act;
					for (int i = 0; i < m_num_elements; i++) {
						sol_opt[i] = sol_act[i];
					}
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

void Motxilla::knapsack_back_forw(vector<int>& sol_act, vector<int>& sol_opt, float ben_act, float pes_act, int k, float& ben_opt) {


	for (int v = 1; v >= 0; v--) {
		sol_act[k] = v;
		pes_act = pes_act + v * m_pesos[k];
		ben_act = ben_act + v * m_valors[k];
		float c = cota(m_capacitat_total - pes_act, ben_act, k + 1);		
		if ((pes_act <= m_capacitat_total) && (ben_opt < c)) {
			if (k == m_num_elements - 1) {
				if (ben_act > ben_opt) {
					ben_opt = ben_act;
					for (int i = 0; i < m_num_elements; i++) {
						sol_opt[i] = sol_act[i];
					}
				}
			}
			else
				knapsack_back_forw(sol_act, sol_opt, ben_act, pes_act, k + 1, ben_opt);
		}
		sol_act[k] = 0;
		pes_act = pes_act - v * m_pesos[k];
		ben_act = ben_act - v * m_valors[k];
	}
}

float Motxilla::cota(float cap_act, float ben_act, int k)
{
	//cap_act = capacitat encara lliure de la motxilla; k = índex del primer objecte a considerar }
	if ((k >= m_num_elements) || (cap_act <= 0.0)) {
		return ben_act;
	}
	else {
		if (m_pesos[k] > cap_act)
			return ben_act + cap_act / m_pesos[k] * m_valors[k];
		else
			return cota(cap_act - m_pesos[k], ben_act + m_valors[k], k + 1);
	}
}