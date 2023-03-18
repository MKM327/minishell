/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:49:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/18 06:43:20 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_subshell(t_node *node)
{
	int	pid;
	int	next_exec_index;

	next_exec_index = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		if (node->connection_count == 1)
			execute_node(node);
		else if (node->connection_count > 1)
		{
			while (next_exec_index != -1)
			{
				exec_all(node->connections[next_exec_index]);
				close_node_fds(node->connections[next_exec_index]);
				next_exec_index = handle_priority(node, next_exec_index);
			}
		}
		exit(get_last_execute_code(node));
	}
	close_all_fds(node);
	waitpid(pid, &node->execute->last_exit_code, 0);
}