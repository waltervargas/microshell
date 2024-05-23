#include "microshell.h"
#include <unistd.h>
#include "libft.h"

t_ast *parse_command(t_token **tokens)
{
	if (!tokens || !*tokens) return NULL;
	t_ast *node = new_ast_node((*tokens)->value);
	*tokens = (*tokens)->next;
	return node;
}

t_ast *parse_pipeline(t_token **tokens)
{
	if (!tokens || !*tokens) return NULL;
	t_ast *left = parse_command(tokens);
	while (*tokens && ft_strncmp((*tokens)->value, "|", 2) == 0)
	{
		t_ast *pipe_node = new_ast_node((*tokens)->value);
		*tokens = (*tokens)->next;
		t_ast *right = parse_command(tokens);
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return left;
}

t_ast *parse(t_token *tokens)
{
	return parse_pipeline(&tokens);
}