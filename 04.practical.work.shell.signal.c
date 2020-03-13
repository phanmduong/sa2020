#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

int pid = 0;

void handler(int signal_num){
    switch (signal_num)
    {
    case SIGTSTP:
        kill(pid, SIGTERM);
        exit(0);
    default:
        break;
    }
}

int main() {
    char input[100];
    char *command[100];
    signal(SIGTSTP, handler);
    while(1){
        printf("Enter you commands: ");
        gets(&input);
       
        if (strcmp(input, "quit") == 0) {
            return 0;
        }

        int i = 0;
        char *args[30];
        command[i] = strtok(input, " ");
        
        ++i;

        while(( command[i] = strtok(NULL, " ")) != NULL ) 
        {
            args[i-1] = command[i];
            ++i;
        }

        pid = fork();

        if (pid == 0){
            printf("%s\n", command[0]);
            execlp(command[0], args);
        }
         else{
            wait(NULL);
        }
    }

    
    return 0;
}