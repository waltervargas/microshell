#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"
#include "microshell.h"

t_token *new_token(char *value) 
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	if (!token) return NULL;
	token->value = ft_strdup(value);
	token->next = NULL;
	return token;
}

void add_token(t_token **head, char *value)
{
	t_token *new = new_token(value);
	if (!new) return;
	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		t_token *temp = *head;
		while (temp->next) 
			temp = temp->next;
		temp->next = new;
	}
}

t_token *tokenize(char *input)
{
	t_token *head = NULL;
	char *token = strtok(input, " ");
	while (token)
	{
		add_token(&head, token);
		token = strtok(NULL, " ");
	}
	return head;
}

void free_tokens(t_token *head)
{
	t_token *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

