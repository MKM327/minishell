/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 07:12:13 by kali              #+#    #+#             */
/*   Updated: 2023/03/14 14:19:33 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_right_operator(t_token token, t_token *tokens, int is_subshell)
{
	int	i;

	i = get_in_all_tokens(token, tokens);
	if (is_subshell == 1)
	{
		while (tokens[i].token != UNKNOWN && tokens[i].token != PIPE
			&& tokens[i].token != AND && tokens[i].token != OR)
			i++;
		return (tokens[i].token);
	}
	else
	{
		while (tokens[i].token != UNKNOWN && tokens[i].token != PIPE
			&& tokens[i].token != AND && tokens[i].token != OR)
		{
			if (tokens[i].token == CLOSE_PAR || tokens[i].token == OPEN_PAR)
				return (UNKNOWN);
			i++;
		}
		return (tokens[i].token);
	}
	return (UNKNOWN);
}

int	get_left_operator(t_token token, t_token *tokens, int is_subshell)
{
	int	i;

	i = get_in_all_tokens(token, tokens);
	if (is_subshell == 1)
		return (left_is_subshell_handle(token, tokens, i));
	else
	{
		while (i >= 0 && tokens[i].token != UNKNOWN && tokens[i].token != PIPE
			&& tokens[i].token != AND && tokens[i].token != OR)
		{
			if (tokens[i].token == CLOSE_PAR || tokens[i].token == OPEN_PAR)
				return (UNKNOWN);
			i--;
		}
		if (i < 0)
			return (UNKNOWN);
		return (tokens[i].token);
	}
	return (UNKNOWN);
}

void	handle_operators(t_node *head, t_token *tokens)
{
	int	i;

	i = 0;
	while (head->tokens[i].token != UNKNOWN)
		i++;
	i--;
	head->right_operator = get_right_operator(head->tokens[i], tokens,
			head->is_subshell);
	head->left_operator = get_left_operator(head->tokens[0], tokens,
			head->is_subshell);
}

void	assign_operators(t_node *head, t_token *tokens)
{
	int	i;

	if (head->connection_count == 1)
	{
		handle_operators(head, tokens);
		return ;
	}
	else
	{
		handle_operators(head, tokens);
		i = -1;
		while (++i < head->connection_count)
			assign_operators(head->connections[i], tokens);
	}
}
