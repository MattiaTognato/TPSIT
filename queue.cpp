/**
 * @file queue.cpp
 * @author Tognato Mattia (6190097@itisrossi.vi.it)
 * @brief 
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
using namespace std; //commento per provare git
/**
 * @brief Single Node of the queue
 * 
 */
struct cell {
	int val = 0;			//!Value of the node
	cell* next = nullptr;	//!<Point to next node of the queue
};
/**
 * @brief Queue
 * 
 */
struct queue {
	cell* first = nullptr;	//!<Point to the first node of the queue
	cell* last = nullptr;	//!<Point to the last node of the queue
};
/**
 * @brief Add a node at the end of the queue
 * 
 * @param _q 
 * @param n 
 */
void enqueue(queue*& _q, int n) {
	cell* c = new cell;			//creo nuova cella
	c->val = n;					//inserisco valore alla nuova cella

	if (_q->first == nullptr)	//caso particolare in cui la coda � 
	{
		_q->first = c;			//la prima e l'ultima cella corrisponderanno alla stessa cella
		_q->last = c;
	}
	else
	{
		_q->last->next = c;		//aggiungo alla coda la nuova cella
		_q->last = c;			//ora l'ultima cella � quella nuova
	}
}
/**
 * @brief Remove the firt node of the queue and return its value
 * 
 * @param _q 
 * @return int 
 */
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
/**
 * @brief Return the number of node in the Queue
 * 
 * @param _q 
 * @return int 
 */
int getQueueLength(queue*& _q)
{
	int length = 0;
	if (_q->first == nullptr)		//se la coda � vuota ritorno 0
	{
		return length;
	}
	for (cell* tmp = _q->first; tmp != nullptr; tmp = tmp->next)	//ciclo per scorrere tutta la coda
	{
		length++;		//incremento la lunghezza ad ogni ciclo
	}
	return length;
}
/**
 * @brief Remove all node from the Queue
 * 
 * @param _q 
 */
void deleteQueue(queue*& _q)
{
	int lenght = getQueueLength(_q);	//prendo la lunghezza della coda
	for (int i = 0; i < lenght; i++)
	{
		dequeue(_q);					//dequeue di tutte le celle della coda
	}
}
/**
 * @brief Print in console all value in the Stack
 * 
 * @param _q 
 */
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