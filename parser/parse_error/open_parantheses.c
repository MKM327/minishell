#include "parse_error.h"

int	open_parantheses(t_token *tokens)
{
	int	open_par;
	int	close_par;

	open_par = search_token_count(tokens, OPEN_PAR);
	close_par = search_token_count(tokens, CLOSE_PAR);
	if (close_par > open_par)
	{
		printf("minishell: syntax error near unexpected token `)'\n");
		return (1);
	}
	else if (open_par > close_par)
	{
		printf("minishell: syntax error near unexpected token `('\n");
		return (1);
	}
	return (0);
}

int	is_real_subshell(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR && i != 0)
		{
			if (tokens[i - 1].token != AND && tokens[i - 1].token != OR
				&& tokens[i - 1].token != PIPE)
			{
				printf("minishell: syntax error near unexpected token `('\n");
				return (1);
			}
		}
		if (tokens[i].token == OPEN_PAR && i == 0)
			return (0);
		i++;
	}
	return (0);
}

int	out_of_use(t_token *tokens)
{
	int open_par;
	int close_par;

	open_par = search_token_count(tokens, OPEN_PAR);
	close_par = search_token_count(tokens, CLOSE_PAR);
	if (open_par == close_par && open_par != 1)
	{
		if (tokens[open_par + 1].token == CLOSE_PAR )
			return (1);
	}
	if(tokens[0].token == OPEN_PAR && tokens[1].token == CLOSE_PAR && tokens[2].token == UNKNOWN)
	{
		printf("minishell: syntax error near unexpected token `('\n");
		return (1);
	}
	return (0);
}