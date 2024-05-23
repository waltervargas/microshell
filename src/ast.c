#include "microshell.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

t_ast	*new_ast_node(char *value) 
{
	t_ast *node = (t_ast *)malloc(sizeof(t_ast));
	if (!node) return NULL;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	return node;
}

void	free_ast(t_ast *root) 
{
	if (root)
	{
		free(root->value);
		free_ast(root->left);
		free_ast(root->right);
		free(root);
	}
}