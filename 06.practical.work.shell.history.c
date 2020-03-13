#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

int pid = 0;
FILE *fptr;

void quitListener(){
    printf("\nHistory:\n");
    char currentline[100];
    fclose(fptr);

    fptr = fopen("./command.log","r");

    if(fptr == NULL)
    {
        printf("Error! open file");   
        exit(1);             
    }

    while (fgets(currentline, sizeof(currentline), fptr) != NULL) {
        printf("%s", currentline);
    }   
    fclose(fptr);
}

void handler(int signal_num){
    switch (signal_num)
    {
    case SIGTSTP:
        if (pid !=0 ){
            kill(pid, SIGTERM);
            exit(0);
        }
    case SIGTERM: 
        quitListener();
        exit(0);
        break;
    default:
        break;
    }
}

int main() {
    char input[100];
    char *command[100];

    signal(SIGTSTP, handler);
    signal(SIGTERM, handler);
    
    fptr = fopen("./command.log","w");

    if(fptr == NULL)
    {
        printf("Error! open file");   
        exit(1);             
    }


    while(1){
        printf("Enter you commands: ");
        gets(&input);

        if (strcmp(input, "quit") == 0) {
            break;
        }

        fprintf(fptr, "%s\n", input);

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

    quitListener();
    
    
    return 0;
}