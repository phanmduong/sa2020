#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    char *command[100];
    
    
    while(1){
        printf("Enter you commands: ");
        // scanf("%s",&input);
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

        int pid = fork();

        if (pid == 0){
            printf("%s\n", command[0]);
            printf("%s\n", args[0]);
            execlp(command[0], args);
        }
         else{
            wait(NULL);
        }
    }

    
    return 0;
}