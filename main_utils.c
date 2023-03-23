/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:09:51 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/23 13:52:56 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_node_tokens(t_node *node)
{
	int	i;

	i = 0;
	if (node->connection_count == 0)
		free_tokens(node->tokens);
	else
	{
		while (i < node->connection_count)
		{
			free_all_node_tokens(node->connections[i]);
			i++;
		}
		free_tokens(node->tokens);
	}
}

int	parse_error_free(t_node *head, t_token *tokens, char *inpt)
{
	if (head == NULL)
	{
		free(inpt);
		free_tokens(tokens);
		free(tokens);
		return (1);
	}
	return (0);
}

int	first_check_free(t_token *tokens, char *inpt)
{
	if (check_first(tokens) == 1)
	{
		free(inpt);
		free_tokens(tokens);
		free(tokens);
		return (1);
	}
}

void	exec_rest(t_node *head, t_token *tokens)
{
	expander(head);
	execute(head);
	free(head->execute->input);
	free_tree(head);
}
