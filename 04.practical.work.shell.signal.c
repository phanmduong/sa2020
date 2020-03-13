#include <stdio.h>
#include <signal.h>

int pid;

void parentPaused(int signal_num){
    printf("paused\n");
    kill(pid, SIGINT);
}

void childKilled(int signal_num) {
    printf("Child killed");
    exit(0);
}

int main(void) {

    pid = fork();

    if (pid == 0){
        signal(SIGINT, childKilled); 
        while (1) {
            sleep(1);
            printf("child\n");
        }
    } else {
        signal(SIGTSTP, parentPaused);
        wait(NULL);
    }
    
    return 0;
}