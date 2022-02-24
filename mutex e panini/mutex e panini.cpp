#include <iostream>
#include <list>
#include <thread>
#include <mutex>

using namespace std;

mutex m;
string nome_ricetta;
list<string> ordine;

void inserisci_ordine(string ricetta) 
{
	m.lock();
	cout << "\n---------------\n";
	nome_ricetta = ricetta;
	cout << "Ordine per " << nome_ricetta << "\n";
	string ingrediente;
	do {
		cout << "ingrediente: ";
		cin >> ingrediente;
		if (ingrediente != "fine")
			ordine.push_back(ingrediente);
	} while (ingrediente != "fine");
	m.unlock();
}
void prepara_ordine() {
	m.lock();
	cout << "\n---------------\n";
	cout << "Preparazione " << nome_ricetta << "\n";
	while (ordine.empty() != true) {
		cout << ordine.front() << "\n";
		ordine.pop_front();
	}
	m.unlock();
}
void ordina(string ricetta) {
	inserisci_ordine(ricetta);
	prepara_ordine();
}

int main()
{
	thread th1(ordina, "Cotto e funghi");
	cout << "thread th1(ordina, 'Cotto e funghi');\n";
	thread th2(ordina, "Cetrioli");
	cout << "thread th2(ordina, 'Cetrioli');\n";

	th1.join();
	th2.join();

	return 0;
}