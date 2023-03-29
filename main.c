/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 12:20:30 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// void	print_token(t_token *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token[i].token != UNKNOWN)
// 	{
// 		printf("value: %s id : %d token : ", token[i].str, token[i].id);
// 		switch (token[i].token)
// 		{
// 		case PIPE:
// 			printf("PIPE\n");
// 			break ;
// 		case UNKNOWN:
// 			printf("UNKNOWN\n");
// 			break ;
// 		case I_REDIRECTION:
// 			printf("I_REDIRECTION\n");
// 			break ;
// 		case O_REDIRECTION:
// 			printf("O_REDIRECTION\n");
// 			break ;
// 		case APPEND_RED:
// 			printf("APPEND_RED\n");
// 			break ;
// 		case HERE_DOC:
// 			printf("HERE_DOC\n");
// 			break ;
// 		case COMMAND:
// 			printf("COMMAND\n");
// 			break ;
// 		case ARG:
// 			printf("ARG\n");
// 			break ;
// 		case OPTION:
// 			printf("OPTION\n");
// 			break ;
// 		case AND:
// 			printf("AND\n");
// 			break ;
// 		case OR:
// 			printf("OR\n");
// 			break ;
// 		case ENV_COMMAND:
// 			printf("ENV_COMMAND\n");
// 			break ;
// 		case ENV:
// 			printf("ENV\n");
// 			break ;
// 		case RED_FILE:
// 			printf("RED_FILE\n");
// 			break ;
// 		case OPEN_PAR:
// 			printf("OPEN_PAR\n");
// 			break ;
// 		case CLOSE_PAR:
// 			printf("CLOSE_PAR\n");
// 			break ;
// 		case UNKNOWN_TOKEN:
// 			printf("UNKNOWN_TOKEN\n");
// 			break ;
// 		default:
// 			printf("UNKNOWN\n");
// 			break ;
// 		}
// 		i++;
// 	}
// }
// void	print_redirections(t_redirections *redirection)
// {
// 	int	i;

// 	i = 0;
// 	printf("--------\n");
// 	while (i < redirection->infile_count)
// 	{
// 		printf("infile: %s ", redirection->infile[i]);
// 		switch (redirection->infile_type[i])
// 		{
// 		case I_REDIRECTION:
// 			printf("I_REDIRECTION\n");
// 			break ;
// 		case HERE_DOC:
// 			printf("HERE_DOC\n");
// 			break ;
// 		default:
// 			printf("UNKNOWN\n");
// 			break ;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < redirection->outfile_count)
// 	{
// 		printf("outfile: %s ", redirection->outfile[i]);
// 		switch (redirection->outfile_type[i])
// 		{
// 		case O_REDIRECTION:
// 			printf("O_REDIRECTION\n");
// 			break ;
// 		case APPEND_RED:
// 			printf("APPEND_RED\n");
// 			break ;
// 		default:
// 			printf("UNKNOWN\n");
// 			break ;
// 		}
// 		i++;
// 	}
// }
// void	print_tree(t_node *head)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (head->connection_count == 0)
// 	{
// 		j = 0;
// 		if (head->command == NULL)
// 		{
// 			print_token(head->tokens);
// 			return ;
// 		}
// 		printf("command : %s ", head->command->command);
// 		printf("\n");
// 		while (j < head->command->argument_count)
// 		{
// 			printf("argument : %s \n", head->command->arguments[j]);
// 			j++;
// 		}
// 		printf("\n");
// 		j = 0;
// 		if (head->redirections != NULL)
// 			print_redirections(head->redirections);
// 		printf("\n*************\n");
// 		printf("left_operator : %d\n", head->left_operator);
// 		printf("right_operator : %d\n", head->right_operator);
// 		printf("\n*************\n");
// 		return ;
// 	}
// 	else
// 		while (i < head->connection_count)
// 		{
// 			if (i == 0)
// 			{
// 				// 	print_token(head->tokens);
// 				if (head->redirections != NULL)
// 					print_redirections(head->redirections);
// 				printf("\n*************\n");
// 				printf("left_operator : %d\n", head->left_operator);
// 				printf("right_operator : %d\n", head->right_operator);
// 				printf("\n*************\n");
// 			}
// 			print_tree(head->connections[i]);
// 			i++;
// 		}
// }

char	**init_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_execute	*init_execute(char **env)
{
	t_execute	*execute_struct;

	execute_struct = malloc(sizeof(t_execute));
	execute_struct->last_exit_code = 0;
	execute_struct->env = init_env(env);
	execute_struct->export = init_env(env);
	execute_struct->only_red_count = 0;
	return (execute_struct);
}

void	main_loop(t_execute *execute_struct)
{
	t_node	*head;
	t_token	*tokens;

	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		execute_struct->input = readline("minishell: ");
		add_history(execute_struct->input);
		ctrl_d(execute_struct);
		tokens = lexer(execute_struct->input);
		if (tokens == NULL)
		{
			free(execute_struct->input);
			continue ;
		}
		if (first_check_free(tokens, execute_struct->input) == 1)
			continue ;
		head = parser(tokens, execute_struct);
		if (parse_error_free(head, tokens, execute_struct->input) == 1)
			continue ;
		exec_rest(head);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_execute	*execute_struct;

	if (argc != 1)
		return (0);
	(void)argv;
	execute_struct = init_execute(env);
	main_loop(execute_struct);
	return (0);
}
