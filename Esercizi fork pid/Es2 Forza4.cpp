#include <iostream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

struct F4Info{
    char Nome1[50];
    char Pedina1;
    char Nome2[50];
    char Pedina2;
};
void fork_nome_giocatore(int n, F4Info* shared_struct){
    pid_t p = fork();
    
    if(p == 0){
        //figlio
        cout << "Inserire il nome del giocatore : " << endl;
        if(n == 1){
            cin >> shared_struct -> Nome1;
        }
        if(n == 2){
            cin >> shared_struct -> Nome2;
        }
        exit(EXIT_SUCCESS);
    }
    else if(p > 0){
        //padre
        waitpid(p, nullptr, 0);
    }
}

int main()
{
    key_t key = ftok("shared", 0);  //creazione di un token univoco
    int shmid = shmget(key, sizeof(F4Info), 0666|IPC_CREAT); // richiedo al sistema un blocco di memoria
    F4Info* shared_struct = (F4Info*)shmat(shmid, NULL, 0); // mappo la memoria codivisa nella memoria del processo
    shared_struct -> Pedina1 = 'O';
    shared_struct -> Pedina2 = 'X';
    
    fork_nome_giocatore(1, shared_struct);
    fork_nome_giocatore(2, shared_struct);
    
    cout << "Nome1: " << shared_struct -> Nome1 << endl;
    cout << "Pedina1: " << shared_struct -> Pedina1 << endl;
    cout << "Nome2: " << shared_struct -> Nome2 << endl;
    cout << "Pedina2: " << shared_struct -> Pedina2 << endl;
    
    shmdt(shared_struct); //rilascia il blocco di memoria
    shmctl(shmid, IPC_RMID, NULL); //rimuove completamente il blocco di memoria
    return 0;
}
