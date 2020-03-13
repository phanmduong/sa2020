#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <signal.h>

int pid = 0;

void handler(int signal_num){
    printf("\npaused\n");
    switch (signal_num)
    {
    case SIGTSTP:
        if (pid != 0){
            kill(pid, SIGTERM);
        }
        exit(0);
    default:
        break;
    }
}

int main(int argc, char const *argv[]) {
	char input[100];
	char *args[10];
    signal(SIGTSTP, handler);
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
	printf("Terminating.\n");
	return 0;
}

// #include <stdio.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <string.h>
// #include <signal.h>

// int pid = 0;

// void handler(int signal_num){
//     printf("\npaused\n");
//     switch (signal_num)
//     {
//     case SIGTSTP:
//         if (pid != 0){
//             kill(pid, SIGTERM);
//         }
//         exit(0);
//     default:
//         break;
//     }
// }

// int main() {
//     char input[100];
//     char *command[100];
//     signal(SIGTSTP, handler);
//     while(1){
//         printf("Enter you commands: ");
//         gets(&input);
       
//         if (strcmp(input, "quit") == 0) {
//             return 0;
//         }

//         int i = 0;
//         char *args[100];
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
//             execvp(command[0], args);
//         }
//          else{
//             wait(NULL);
//         }
//     }

//     	printf("Terminating.\n");
//     return 0;
// }
