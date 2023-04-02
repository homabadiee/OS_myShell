
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

void welcome()
{
	
	printf("\n\n\n\n******************"
		"************************");
	printf("\n\n\n\t****	MY SHELL	****");
	printf("\n\n\n\n*******************"
		"***********************");
	printf("\n");
	sleep(1);
	
}

int getCommand(char* str)
{
	char* buffer;
	buffer = readline(NULL);
	if (strlen(buffer) != 0) 
    {
		add_history(buffer);
		strcpy(str, buffer);
		return 0;
	} 
    else
    {
		return 1;
	}
}


void printPrompt()
{
	char cwd[512] ,prompt[512];
	memset(&prompt[0], 0, sizeof(prompt));
	getcwd(cwd, sizeof(cwd));
	strcat(prompt,"\n");
	strcat(prompt,cwd);
	strcat(prompt,">");
	printf("\n%s", prompt);
}


void exeLinuxCommand(char** parsed)
{
	pid_t pid = fork();

	if (pid == -1) {
		printf("\nFailed forking child..");
		return;
	} else if (pid == 0) {
		if (execvp(parsed[0], parsed) < 0) {
			printf("\nCould not execute command..");
		}
		exit(0);
	} else {
		
		wait(NULL);
		return;
	}
}


void exePipeCommand(char** parsed, char** parsedpipe)
{
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0) 
	{
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0) 
	{
		printf("\nCould not fork");
		return;
	}

	if (p1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parsed[0], parsed) < 0) {
			printf("\nCould not execute command 1..");
			exit(0);
		}
	} 
	else
	{
		
		p2 = fork();

		if (p2 < 0)
		{
			printf("\nCould not fork");
			return;
		}

		
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(parsedpipe[0], parsedpipe) < 0) {
				printf("\nCould not execute command 2..");
				exit(0);
			}
		}
		else
		{
			wait(NULL);
			wait(NULL);
		}
	}
}

void execMyCommands(char** parsed)
{
	pid_t pid = fork();
	
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return;
	}
	else if (pid == 0)
	{
		char file[20] = "./";
    	strcat(file,parsed[0]);
    	char *args[]={file,NULL};
		printf("%s",file);
		if (execvp(args[0],args) < 0)
		{
			printf("\nCould not execute command..");
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		return;
	}
}


void help()
{
	puts("\n***WELCOME TO MY SHELL HELP***"
		"\nCopyright @ Suprotik Dey"
		"\n-Use the shell at your own risk..."
		"\nList of Commands supported:"
		"\n>cd"
		"\n>ls"
		"\n>exit"
		"\n>all general commands available in UNIX shell"
		"\n>sbfs"
		"\n>esRemov"
		"\n>suncom"
		"\n>lineCounter"
		"\n>firstTenLines"
		"\n>mrepWord");

}

int commandGuide(char** parsed)
{
	int commandsCount = 10, i, swCmd = 0;
	char* commands[commandsCount];

	commands[0] = "exit";
	commands[1] = "cd";
	commands[2] = "help";
	commands[3] = "pwd";
	commands[4] = "sbfs";
	commands[5] = "mrepWord";
	commands[6] = "esRemov";
	commands[7] = "suncom";
	commands[8] = "lineCounter";
	commands[9] = "firstTenLines";



	for (i = 0; i < commandsCount; i++)
	{
		if (strcmp(parsed[0], commands[i]) == 0)
		{
			swCmd = i + 1;
			break;
		}
	}

	switch (swCmd)
	{
	case 1: //exit
		exit(0);
	case 2://cd
		chdir(parsed[1]);
		return 1;
	case 3://help
		help();
		return 1;
	case 4://pwd
		char cwd[512];
		getcwd(cwd, sizeof(cwd));
		printf("\n%s",cwd);
		return 1;
	default://my commands
		if (5 <= swCmd && swCmd <= 10)
		{
			return 2;
		}
		
		break;
	}

	return 0;//linux commands
}

int parsePipe(char* str, char** strpiped)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			return 0;
	}
	return 1;
}

void parseSpace(char* str, char** parsed)
{
	int i;

	for (i = 0; i < MAXLIST; i++)
	{
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}

int commandProcess(char* str, char** parsed, char** parsedpipe)
{

	char* strpiped[2];
	int piped = 0;

	piped = parsePipe(str, strpiped);

	if (piped) 
	{
		parseSpace(strpiped[0], parsed);
		parseSpace(strpiped[1], parsedpipe);
	} 
	else
	{
		parseSpace(str, parsed);
	}
	switch (commandGuide(parsed))
	{
		case 0:
			return 1 + piped;
		case 1:
			return 0;	
		default:
			break;
	}
	return 3;
}

void executeCmd(char* command, char** parsed, char** parsedpipe)
{
	int commandType = 0;
	commandType = commandProcess(command, parsed, parsedpipe);

	switch (commandType)
	{
	case 1:
		exeLinuxCommand(parsed);
		break;
	case 2:
		exePipeCommand(parsed, parsedpipe);
		break;
	case 3:
		execMyCommands(parsed);
		break;
	default:
		break;
	}

}

void handler()
{
	printPrompt();
}

int main()
{
	char command[MAXCOM], *parsedArgs[MAXLIST];
	char* parsedArgsPiped[MAXLIST];
	
	welcome();

	while (1)
	{
		signal(SIGINT, handler);
		printPrompt();
		if (getCommand(command))
			continue;
		
		executeCmd(command ,parsedArgs ,parsedArgsPiped);
		
	}
	return 0;
}
