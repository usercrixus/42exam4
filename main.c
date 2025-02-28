#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int std_in;
int std_out;

void printt_err(char *str)
{
	int i = 0;
	while (str[i])
	{
		write(2, str + i, 1);
		i++;
	}
}

void ft_exec(char **argv, int limit, char **envp)
{
	int i = 0;

	while (i < limit && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
		i++;
	
	if (strcmp(argv[0], "cd") == 0)
	{
		if (i != 2)
			printt_err("error: cd: bad arguments\n");
		else if (chdir(argv[1]) == -1)
		{
			printt_err("error: cd: cannot change directory to ");
			printt_err(argv[1]);
			printt_err("\n");
		}
		return ;
	}


	int pipe_fd[2];
	pipe(pipe_fd);
	int pid = fork();
	if (!pid)
	{
		if (i < limit && strcmp(argv[i], "|") == 0)
		{
			dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		else
		{
			dup2(std_out, 1);
		}
		argv[i] = 0;
		if (execve(argv[0], argv, envp) == -1)
		{
			printt_err("error: cannot execute ");
			printt_err(argv[0]);
			printt_err("\n");
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (i < limit && strcmp(argv[i], "|") == 0)
		{
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		else
		{
			dup2(std_in, 0);
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		return (0);
	
	argv++;
	argc--;
	
	std_in = dup(0);
	std_out = dup(1);

	char **argv_buffer;
	int i = 0;
	while (i < argc)
	{
		if (i < argc && (strcmp(argv[i], ";") == 0 || strcmp(argv[i], "|") == 0))
		{
			i++;
			continue;
		}
		argv_buffer = argv + i;
		ft_exec(argv_buffer, argc - i, envp);
		while (i < argc && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;		
		i++;
	}
	return (0);
}
