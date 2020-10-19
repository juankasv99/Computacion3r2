#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int is_pal(int start, int end, string str) {

	if (start >= end)
		return 1;
	if (str[start] != str[end])
		return 0;
	return is_pal(start++, end--, str);
}

void main() {
	string input;

	cout << "Introdueix nombre: ";
	cin >> input;

	int resultat = is_pal(0, input.length()-1, input);

	if (resultat == 0)
		cout << "Resultat NO capicua";
	else
		cout << "Resultat capicua :)";


}