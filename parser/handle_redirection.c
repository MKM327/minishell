/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:55:12 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/11 11:54:06 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_input_count(t_node *node)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		pass_parantheses(node->tokens, &i);
		if (node->tokens[i].token == HERE_DOC
			|| node->tokens[i].token == I_REDIRECTION)
			count++;
		i++;
	}
	node->redirections->infile_count = count;
}

void	find_output_count(t_node *node)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		pass_parantheses(node->tokens, &i);
		if (node->tokens[i].token == APPEND_RED
			|| node->tokens[i].token == O_REDIRECTION)
			count++;
		i++;
	}
	node->redirections->outfile_count = count;
}

void	handle_input(t_node *node)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	find_input_count(node);
	node->redirections->infile = malloc(node->redirections->infile_count
			* sizeof(char *));
	node->redirections->infile_type = malloc(node->redirections->infile_count
			* sizeof(enum e_token));
	while (node->tokens[i].token != UNKNOWN)
	{
		pass_parantheses(node->tokens, &i);
		if (node->tokens[i].token == I_REDIRECTION
			|| node->tokens[i].token == HERE_DOC)
		{
			node->redirections->infile[index] = node->tokens[i + 1].str;
			node->redirections->infile_type[index] = node->tokens[i].token;
			index++;
		}
		i++;
	}
}

void	handle_output(t_node *node)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	find_output_count(node);
	node->redirections->outfile = malloc(node->redirections->outfile_count
			* sizeof(char *));
	node->redirections->outfile_type = malloc(node->redirections->outfile_count
			* sizeof(enum e_token));
	while (node->tokens[i].token != UNKNOWN)
	{
		pass_parantheses(node->tokens, &i);
		if (node->tokens[i].token == O_REDIRECTION
			|| node->tokens[i].token == APPEND_RED)
		{
			node->redirections->outfile[index] = node->tokens[i + 1].str;
			node->redirections->outfile_type[index] = node->tokens[i].token;
			index++;
		}
		i++;
	}
}

void	handle_redirection(t_node *node)
{
	handle_input(node);
	handle_output(node);
}
