#include <stdio.h>
#include "microshell.h"
#include "libft.h"

int	main(void)
{
	char input[1024];
	ft_printf("microshell> ");
	while (fgets(input, sizeof(input), stdin))
	{
		input[strcspn(input, "\n")] = '\0'; //remove newline char
		t_token *tokens = tokenize(input);
		t_ast *ast = parse(tokens);
		if (ast)
		{
			if (fork() == 0)
			{
				run_ast(ast);
				exit(0);
			}
			else
				wait(NULL);
		}
		free_tokens(tokens);
		free_ast(ast);
		ft_printf("minshell> ");
	}
	return 0;
}