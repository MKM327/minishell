/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:22:18 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/15 12:51:08 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*find_in_path(char *command, char **env)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	path = ft_split(env[i], ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, command);
		if (access(tmp2, F_OK) == 0)
		{
			free(tmp);
			free_double_ptr(path);
			return (tmp2);
		}
		i++;
		free(tmp);
		free(tmp2);
	}
	free_double_ptr(path);
	return (NULL);
}
void	print_new_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
}

char	**modified_args(t_node *node)
{
	char	**new_args;
	int		i;
	int		j;

	i = 1;
	j = 0;
	new_args = malloc(sizeof(char *) * (node->command->argument_count + 2));
	new_args[0] = ft_strdup(node->command->command);
	while (j < node->command->argument_count)
	{
		new_args[i] = ft_strdup(node->command->arguments[j]);
		i++;
		j++;
	}
	new_args[i] = NULL;
	return (new_args);
}

void	exec_builtin(t_node *node, char **env)
{
	char	*path;
	int		pid;
	int		return_value;
	char	**new_args;

	new_args = modified_args(node);
	return_value = 0;
	path = NULL;
	if (ft_strchr(node->command->command, '/') == NULL)
		path = find_in_path(node->command->command, env);
	else
		path = ft_strdup(node->command->command);
	pid = fork();
	if (pid == 0)
	{
		if (node->right_operator == PIPE)
		{
			dup2(node->pipe_fd[1], STDOUT_FILENO);
			close(node->pipe_fd[1]);
		}
		if (node->left_operator == PIPE)
		{
			dup2(node->pipe_fd[0], STDIN_FILENO);
			close(node->pipe_fd[0]);
		}
		execve(path, new_args, env);
	}
	if (node->right_operator == PIPE && node->left_operator == PIPE)
	{
		close(node->pipe_fd[1]);
		close(node->pipe_fd[0]);
	}
	if (node->right_operator == PIPE)
		close(node->pipe_fd[1]);
	if (node->left_operator == PIPE)
		close(node->pipe_fd[0]);
	free(path);
	waitpid(pid, &return_value, 0);
	free_double_ptr(new_args);
}
