#include <iostream>
using namespace std;
struct cell {
	int val = 0;			//valore della cella
	cell* next = nullptr;	//puntatore alla cella successiva
};


void push(cell*& _r, int n) {
	cell* c = new cell;			//creo nuova cella
	c->val = n;					//inserisco valore alla nuova cella
	if (_r == nullptr)
	{
		_r = c;					//se lo stack è vuoto aggiungi la cella
	}
	else
	{
		c->next = _r;			//la nuova cella deve puntare alla prima cella attuale dello stack
		_r = c;					//la radice deve puntare alla nuova cella
	}

}
int pop(cell*& _r)
{
	if (_r == nullptr)
	{
		throw invalid_argument("The queue is empty");	//lancia un'eccezione nel caso lo stack sia vuoto
	}
	int val = _r->val;		//salvo il valore da restituire in una variabile temporanea

	cell* tmp = _r;			//creo un puntatore temporaneo che punta alla cella da eliminare
	_r = _r->next;
	delete tmp;				//rimuove la cella dalla memoria

	return val;
}
int getStackLength(cell*& _r)
{
	int length = 0;
	if (_r == nullptr)		//se lo stack è vuoto ritorno 0
	{
		return length;
	}
	for (cell* tmp = _r; tmp != nullptr; tmp = tmp->next)	//ciclo per scorrere tutto lo stack
	{
		length++;		//incremento la lunghezza ad ogni ciclo
	}
	return length;
}
void deleteStack(cell*& _r)
{
	int lenght = getStackLength(_r);	//prendo la lunghezza dello stack
	for (int i = 0; i < lenght; i++)
	{
		pop(_r);					//pop di tutte le celle dello stack
	}
}
void showVal(cell*& _r)
{
	int i = 0;
	cout << endl;
	for (cell* tmp = _r; tmp != nullptr; tmp = tmp->next)
	{
		printf("cell[%d]: %d\n", i, tmp->val);		//scorro lo stack e stampo tutti i valori
		i++;
	}
}

int main() {
	cell* r = nullptr;
	push(r, 1);
	push(r, 2);
	push(r, 3);
	cout << "Tognato Mattia 4CII\n--------------------------------------------";
	cout << "\nPush 1,2,3";

	cout << "\nPop()-->" << pop(r);
	cout << "\nshowVal()";
	showVal(r);
	cout << "length: " << getStackLength(r);
	
	cout << "\nclearStack()";
	deleteStack(r);

	cout << "\nlength: " << getStackLength(r);
	cout << "\n--------------------------------------------\n";

	return 0;
}