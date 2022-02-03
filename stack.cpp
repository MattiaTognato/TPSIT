/*! \mainpage Stack & Queue
 *
 *
 * Stack and Queue in cpp
 *
 */

/**
 * @file stack.cpp
 * @author Tognato Mattia (6190097@itisrossi.vi.it)
 * @brief 
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
using namespace std;
/**
 * @brief Single Node of the stack
 * 
 */
struct cell {
	int val = 0;			//!Value of the node
	cell* next = nullptr;	//!<Point to next node of the stack
};

/**
 * @brief Push a value in the stack.
 * 
 * 
 * First parameter is the root of the stack
 * second parameter is the int value.
 * 
 * @param _r root of the stack
 * @param n value
 */
void push(cell*& _r, int n) {
	cell* c = new cell;			//creo nuova cella
	c->val = n;					//inserisco valore alla nuova cella
	if (_r == nullptr)
	{
		_r = c;					//se lo stack � vuoto aggiungi la cella
	}
	else
	{
		c->next = _r;			//la nuova cella deve puntare alla prima cella attuale dello stack
		_r = c;					//la radice deve puntare alla nuova cella
	}

}
/**
 * @brief Remove a node and return the value 
 * 
 * @param _r root of the stack
 * @return int value of the popped node
 */
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
/**
 * @brief Return the number of node in the Stack
 * 
 * @param _r root of the stack
 * @return lenght
 */
int getStackLength(cell*& _r)
{
	int length = 0;
	if (_r == nullptr)		//se lo stack � vuoto ritorno 0
	{
		return length;
	}
	for (cell* tmp = _r; tmp != nullptr; tmp = tmp->next)	//ciclo per scorrere tutto lo stack
	{
		length++;		//incremento la lunghezza ad ogni ciclo
	}
	return length;
}
/**
 * @brief Remove all node from the Stack
 * 
 * @param _r root of the stack
 */
void deleteStack(cell*& _r)
{
	int lenght = getStackLength(_r);	//prendo la lunghezza dello stack
	for (int i = 0; i < lenght; i++)
	{
		pop(_r);					//pop di tutte le celle dello stack
	}
}
/**
 * @brief Print in console all value in the Stack
 * 
 * @param _r root of the stack
 */
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