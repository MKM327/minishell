/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 05:10:28 by kali              #+#    #+#             */
/*   Updated: 2023/03/16 16:57:53 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	pwd(t_node *node)
{
	int	pid;
	int	i;

	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		close_all_fds(node->execute->top_node);
		i = 0;
		while (node->execute->env[i] != NULL)
		{
			if (ft_strncmp(node->execute->env[i], "PWD=", 4) == 0)
			{
				printf("%s\n", node->execute->env[i] + 4);
				return (1);
			}
			i++;
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (1);
}
