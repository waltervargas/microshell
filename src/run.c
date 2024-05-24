#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "microshell.h"
#include "libft.h"

void panic(char *msg)
{
	perror(msg);
	exit(1);
}

void run_command(t_ast *node)
{
	if (!node) return;
	char *args[] = {node->value, NULL};
	if (execvp(args[0], args) == -1)
		panic("execvp");

}

void run_ast(t_ast *root)
{
	if (!root) return;
	if (ft_strncmp(root->value, "|", 2) == 0)
	{
		int	pipefd[2];
		pid_t	p1, p2;
		if (pipe(pipefd) == -1)
			panic("error in pipe");
		if ((p1 = fork()) == -1)
			panic("error fork p1");
		if (p1 == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			run_ast(root->left);
			exit(0);
		}
		if ((p2 = fork()) == -1)
			panic("error fork p2");
		if (p2 == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			run_ast(root->right);
			exit(0);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(p1, NULL, 0);
		waitpid(p2, NULL, 0);
	}
	else 
		run_command(root);
}
