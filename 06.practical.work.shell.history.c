#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
    printf("------------------\n");

    while (fgets(currentline, sizeof(currentline), fptr) != NULL) {
        printf("%s", currentline);
    }   

    printf("------------------\n");

    fclose(fptr);
}

void handler(int signal_num){
    switch (signal_num)
    {
    case SIGTSTP:
        printf("\npaused\n");
        if (pid != 0){
            kill(pid, SIGTERM);
        }
        exit(0);
    case SIGTERM: 
        quitListener();
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char const *argv[]) {
	char input[100];
	char *args[10];
    
    signal(SIGTSTP, handler);
    signal(SIGTERM, handler);

    fptr = fopen("./command.log","w");

    if(fptr == NULL)
    {
        printf("Error! open file");   
        exit(1);             
    }

	while (1) {
		// ask for command
		printf("Enter command:");
		fgets(input, sizeof(input), stdin);

		// initialization of args everytime
		memset(args, 0, sizeof(args));
		
		// transform the input string
		// to array of args
		// so that execvp can use
		int argc = 0;
		int len = strlen(input);
		char *prevArg = input;
		for (int i = 0; i < len; i++) {
			if (input[i] == ' ') {
				args[argc++] = prevArg;
				prevArg = &input[i+1];
				input[i] = '\0';
			}
			if (input[i] == '\n') {
				input[i] = '\0';
			}
		}
		args[argc++] = prevArg;

		// dump the info for debugging purpose
		printf("Input : %s\n", input);
		if (strcmp(input, "quit") == 0) {
			break;
		}

        fprintf(fptr, "%s\n", input);

		printf("- argc : %d\n", argc);
		printf("- args : \n");
		for (int i = 0; i <= argc; i++) {
			printf("  + args[%d]=%s\n", i, args[i]);
		}

		// fork() + exec() combo
		int pid = fork();
		if (pid == 0) {
			execvp(args[0], args);
		}
		else {
			waitpid(pid, NULL, 0);
		}
	}

    quitListener();
	printf("\nTerminating.\n");
	return 0;
}


// #include <stdio.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <string.h>
// #include <signal.h>

// int pid = 0;
// FILE *fptr;

// void quitListener(){
//     printf("\nHistory:\n");
//     char currentline[100];
//     fclose(fptr);

//     fptr = fopen("./command.log","r");

//     if(fptr == NULL)
//     {
//         printf("Error! open file");   
//         exit(1);             
//     }

//     while (fgets(currentline, sizeof(currentline), fptr) != NULL) {
//         printf("%s", currentline);
//     }   
//     fclose(fptr);
// }

// void handler(int signal_num){
//     switch (signal_num)
//     {
//     case SIGTSTP:
//         kill(pid, SIGTERM);
//         exit(0);
//     case SIGTERM: 
//         quitListener();
//         exit(0);
//         break;
//     default:
//         break;
//     }
// }

// int main() {
//     char input[100];
//     char *command[100];

//     signal(SIGTSTP, handler);
//     signal(SIGTERM, handler);
    
//     fptr = fopen("./command.log","w");

//     if(fptr == NULL)
//     {
//         printf("Error! open file");   
//         exit(1);             
//     }


//     while(1){
//         printf("Enter you commands: ");
//         gets(&input);

//         if (strcmp(input, "quit") == 0) {
//             break;
//         }

//         fprintf(fptr, "%s\n", input);

//         int i = 0;
//         char *args[30];
//         command[i] = strtok(input, " ");
        
//         ++i;

//         while(( command[i] = strtok(NULL, " ")) != NULL ) 
//         {
//             args[i-1] = command[i];
//             ++i;
//         }

//         pid = fork();

//         if (pid == 0){
//             printf("%s\n", command[0]);
//             execlp(command[0], args);
//         }
//          else{
//             wait(NULL);
//         }
//     }

//     quitListener();
    
    
//     return 0;
// }