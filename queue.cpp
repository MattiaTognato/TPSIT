#include <iostream>
using namespace std;
struct cell {
	int val = 0;			//valore della cella
	cell* next = nullptr;	//puntatore alla cella successiva
};

struct queue {
	cell* first = nullptr;	//valore inserito per primo
	cell* last = nullptr;	//valore inserito per ultimo
};

void enqueue(queue*& _q, int n) {
	cell* c = new cell;			//creo nuova cella
	c->val = n;					//inserisco valore alla nuova cella

	if (_q->first == nullptr)	//caso particolare in cui la coda è 
	{
		_q->first = c;			//la prima e l'ultima cella corrisponderanno alla stessa cella
		_q->last = c;
	}
	else
	{
		_q->last->next = c;		//aggiungo alla coda la nuova cella
		_q->last = c;			//ora l'ultima cella è quella nuova
	}
}

int dequeue(queue*& _q)
{
	if (_q->first == nullptr)
	{
		throw invalid_argument("The queue is empty");	//lancia un'eccezione nel caso la coda sia vuota
	}
	int val = _q->first->val;		//salvo il valore in una variabile temporanea

	cell* tmp = _q->first;			//creo un puntatore temporaneo che punta alla cella da eliminare

	_q->first = _q->first->next;	//ora la prima cella deve essere quella successiva

	delete tmp;						//rimuove la cella dalla memoria

	return val;
}
int getQueueLength(queue*& _q)
{
	int length = 0;
	if (_q->first == nullptr)		//se la coda è vuota ritorno 0
	{
		return length;
	}
	for (cell* tmp = _q->first; tmp != nullptr; tmp = tmp->next)	//ciclo per scorrere tutta la coda
	{
		length++;		//incremento la lunghezza ad ogni ciclo
	}
	return length;
}
void deleteQueue(queue*& _q)
{
	int lenght = getQueueLength(_q);	//prendo la lunghezza della coda
	for (int i = 0; i < lenght; i++)
	{
		dequeue(_q);					//dequeue di tutte le celle della coda
	}
}
void showVal(queue*& _q)
{
	int i = 0;
	cout << endl;
	for (cell* tmp = _q->first; tmp != nullptr; tmp = tmp->next)
	{
		printf("cell[%d]: %d\n", i, tmp->val);		//scorro la coda e stampo tutti i valori
		i++;
	}
}

int main() {
	queue* q = new queue;
	cout << "Tognato Mattia 4CII\n---------------------------------";
	cout << "\nEnqueue 1,2,3";
	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);

	cout << "\nDequeue()-->" << dequeue(q);

	cout << "\nshowVal()";
	showVal(q);

	cout << "length: " << getQueueLength(q);

	cout << "\nclearQueue()";
	deleteQueue(q);

	cout << "\nlength: " << getQueueLength(q)<<endl;
	cout << "--------------------------------";
	return 0;
}