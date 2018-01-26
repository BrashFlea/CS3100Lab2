/* 
 CS 3100 Lab 2 - by Jonathan Mirabile
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void cmdExit(int argc, char **argv) {
	exit(0);
}

// getParameters returns the argc, the number of words found in cmd
//  while populating argv with pointers to each word
int getParameters(char *cmd, char **argv) {
	char *token;
	int argc = 0;
	token = strtok(cmd, " \t\n");
	while (token != NULL) {
		argv[argc] = token;
		argc++;
		token = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;		// set last + 1 argument to NULL
	return argc;
}

int main(int argc, char **argv) {

	char cmd[1024];
	char *rc;
	int myArgc = 0;
	char *myArgv[1000];
    char cwd[1024];

	while (1) {
		printf("nanosh: ");
		fflush(stdout);
		rc = fgets(cmd, sizeof(cmd), stdin);
		if (rc == NULL) {
			exit(0);
		}
		myArgc = getParameters(cmd, myArgv);

		// if no words typed: restart loop
		if (myArgc == 0) {			
			continue;
		}

		// if the first word is "exit", terminate the program
		if (strcmp(myArgv[0], "exit") == 0 && (myArgc == 1)) {
			cmdExit(myArgc, myArgv);
			continue;
		}

        // EXIT ERROR
        if (strcmp(myArgv[0], "exit") == 0 && (myArgc > 1)) {
            //PRINT ERROR
            errno = EINVAL;
            perror("Error: exit takes zero arguments");
            continue;ls
        }

		// add if statements here for the other internal commands
		//   and a default action that calls a function to fork()
		//   and exec() while the parent issues waitpid()

        // PWD no args
		if (strcmp(myArgv[0], "pwd") == 0 && (myArgc == 1)) {
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);
            continue;
		}

        // PWD with args (error)
        if ((strcmp(myArgv[0], "pwd") == 0) && (myArgc > 1)) {
            //PRINT ERROR
            errno = EINVAL;
            perror("Error: pwd takes zero arguments");
            continue;
        }

        //Default CD
		if ((strcmp(myArgv[0], "cd") == 0) && (myArgc == 1)) {
            chdir(getenv("HOME"));
            continue;
		}

        //CD NEWDIR
		if ((strcmp(myArgv[0], "cd") == 0) && (myArgc == 2)) {
            chdir(myArgv[1]);
            continue;
		}

        //CD ERROR
        if ((strcmp(myArgv[0], "cd") == 0) && (myArgc > 2)) {
            //PRINT ERROR
            errno = EINVAL;
            perror("Error: cwd takes 1 optional argument");
            continue;
        }

        //ANYOTHERCOMMAND
        


	}

	return 0;
} 
