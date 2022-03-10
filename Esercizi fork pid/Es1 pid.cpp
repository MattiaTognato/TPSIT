/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <unistd.h>
#include <wait.h>

using namespace std;




void print_info_thread(string info){
    int this_pid = getpid();
    cout << info << " PID: " << this_pid << "\n";
}
int main()
{
    pid_t pid = fork();
    
    if(pid < 0){
        cout<<"Impossibile eseguire il fork\n";    
        return -1;
    }
    
    if(pid == 0){
        print_info_thread("Figlio");    
    }
    else{
        print_info_thread("Padre");
        int* status;
        waitpid(pid, status, 0);
    }

    return 0;
}
