/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fstream>

using namespace std;

int main()
{
    string nomefile = "file.txt";
    
    key_t key = ftok("shared", 0);  //creazione di un token univoco
    int shmid = shmget(key, sizeof(nomefile), 0666|IPC_CREAT); // richiedo al sistema un blocco di memoria
    string* shared_memory = (string*)shmat(shmid, NULL, 0); // mappo la memoria codivisa nella memoria del processo
    
    *shared_memory = nomefile;
    
    key_t p = fork();
    
    if(p == 0)
    {
        //figlio
        string nome_file = *shared_memory;
        cout << "nomefile da shared_memory: " << nome_file << endl;
        
        string line;
        ifstream myfile (nome_file);
        if (myfile.is_open())
        {
            while ( getline (myfile, line) )
            {
              cout << line << '\n';
            }
            myfile.close();
        }
    }
    else if(p > 0)
    {
        //padre
        waitpid(p, nullptr, 0);
    }
    
    shmdt(shared_memory); //rilascia il blocco di memoria
    shmctl(shmid, IPC_RMID, NULL); //rimuove completamente il blocco di memoria
    
    return 0;
}