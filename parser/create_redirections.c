/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/25 13:23:45 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	does_include(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		pass_parantheses(tokens, &i);
		if (tokens[i].token == I_REDIRECTION || tokens[i].token == O_REDIRECTION
			|| tokens[i].token == APPEND_RED || tokens[i].token == HERE_DOC)
			return (1);
		if (tokens[i].token != UNKNOWN)
			i++;
	}
	return (0);
}

void	check_if_only_red(t_token *token, t_node *node)
{
	if (token[0].token == UNKNOWN)
	{
		node->connection_count = 1;
		free_tokens(node->tokens);
		node->connections = malloc(sizeof(t_node *));
		node->command = NULL;
	}
}

t_token	*create_redirections(t_node *node)
{
	enum e_token	split_type;
	t_token			*token;

	if (does_priority(node->tokens, 100) == 1)
		split_type = 100;
	else if (does_priority(node->tokens, PIPE) == 1)
		split_type = PIPE;
	else
		split_type = UNKNOWN;
	if (does_include(node->tokens) && split_type == UNKNOWN)
	{
		node->redirections = malloc(sizeof(t_redirections));
		handle_redirection(node);
		token = clear_redirections(node);
		check_if_only_red(token, node);
		return (token);
	}
	else
		return (NULL);
}
