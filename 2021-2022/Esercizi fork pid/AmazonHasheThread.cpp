
// AmazonHasheThread.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

mutex mutex_ordine_singolo;

condition_variable cv;

map<string, string> ordini_map;

void inserisci_ordine(string studente) {
    //  blocco la risorsa in modo da 
    //  accedervi solamente da un thread alla volta
    mutex_ordine_singolo.lock();
    cout << "\n" << studente << ", inserisci l'ordine: " << endl;
    
    //input ordine
    string ordine;
    string articolo;
    cout << "\t- Articolo : ";
    cin >> articolo;
    ordine = articolo;
    while (articolo != ".") {
        cout << "\t- Articolo : ";
        cin >> articolo;
        if (articolo == ".") {
            break;
        }
        ordine += " - " + articolo;
    }
    //salvo l'ordine sulla hashmap degli ordini
    ordini_map[studente] = ordine;
    //rilascio la risorsa
    mutex_ordine_singolo.unlock();
    cv.notify_one();
}

void invia_ordini(int numero_minimo) {
    unique_lock<mutex> lk(mutex_ordine_singolo);
    //aspetto che la risorsa sia disponnibile e che ci siano almeno tre ordini
    cv.wait(lk, [numero_minimo]() {
            return ordini_map.size() >= numero_minimo;
        });

    //faccio vedere gli ordini contenuti nella hashmap
    cout<<"\n Ordini in preparazione:\n"<<endl;
    this_thread::sleep_for(chrono::milliseconds(numero_minimo*1000));

    for (auto ordine : ordini_map) {
        cout << ordine.first << " ordine spedito" << ":\t" << ordine.second << endl;
        this_thread::sleep_for(chrono::milliseconds(700));
    }
}
int main()
{
    //creo il thread che aspetta almeno tre ordini prima di inviarli
    thread t_prof(invia_ordini, 3);

    //creo i thread che inseriscono gli ordini
    thread t1(inserisci_ordine, "studente1");
    thread t2(inserisci_ordine, "studente2");
    thread t3(inserisci_ordine, "studente3");

    //prima di terminare il programma aspetto che i thread si chiudano
    t1.join();
    t2.join();
    t3.join();
    t_prof.join();

    return 0;
}