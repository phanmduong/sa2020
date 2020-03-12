#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    char input[30];
    char *command[30];
    
    
    while(1){
        printf("Enter you commands: ");
        gets(&input);
       
        if (strcmp(input, "quit") == 0) {
            return 0;
        }

        // read arguments
        int i = 0;
        char *args[30];
        command[i] = strtok(input, " ");
        
        ++i;

        while(( command[i] = strtok(NULL, " ")) != NULL ) 
        {
            args[i-1] = command[i];
            ++i;
        }
        //read arguments

        int pid = fork();

        if (pid == 0){
            execlp(command[0], args);
        }
         else{
            wait(NULL);
        }
    }

    
    return 0;
}