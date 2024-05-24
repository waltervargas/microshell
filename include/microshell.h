// 
#ifndef MICROSHELL_H
#define MICROSHELL_H

typedef struct s_ast
{
    char			*value;
    struct	s_ast	*left;
    struct	s_ast	*right;
} 	t_ast;

typedef struct s_token
{
	char 			*value;
	struct 	s_token	*next;
}	t_token;

// AST
void	free_ast(t_ast *root);
t_ast	*new_ast_node(char *value);

// TOKEN
void	add_token(t_token **head, char *value);
void	free_tokens(t_token *head);
t_token	*new_token(char *value);
t_token	*tokenize(char *input);

// PARSER 
t_ast *parse(t_token *tokens);
t_ast *parse_pipeline(t_token **tokens);
t_ast *parse_command(t_token **tokens);

// RUN 
void panic(char *msg);
void run_command(t_ast *node);
void run_ast(t_ast *root);

#endif // MICROSHELL_H


