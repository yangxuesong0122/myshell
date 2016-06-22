#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void swap(char** val1,char** val2)
{
	char *tmp=*val1;
	*val1=*val2;
	*val2=tmp;
}

int main()
{
	pid_t id;
	while(1)
	{
		printf("[@localyyxxsshost shell]$ ");
		fflush(stdout);
		char cmd_str[100];
		memset(cmd_str,'\0',sizeof(cmd_str));
		ssize_t _size=read(0,cmd_str,sizeof(cmd_str)-1);
		if(_size>=0)
		{
			cmd_str[_size-1]='\0';
		}
		char* my_argv[32];
		int index=0;
		int i=strlen(cmd_str)-1;
		while(i-->=0)
		{
			if(cmd_str[i]==' ')
			{
				my_argv[index++]=&cmd_str[i+1];
				cmd_str[i]='\0';
			}
		}
		my_argv[index++]=cmd_str;
		my_argv[index]='\0';
		i=0;
		int j=index-1;
		while(i<j)
		{
			swap(&my_argv[i++],&my_argv[j--]);
		}
		if(strcmp("cd",my_argv[0])==0)
		{
			chdir(my_argv[1]);
			continue;
		}
		id=fork();
		if(id<0)
		{
			perror("fork");
		}
		else if(id==0)
		{
			execvp(my_argv[0],my_argv);
			exit(1);
		}
		else
		{
			pid_t wait_pid=waitpid(id,NULL,0);
		}
	}
	return 0;
}
