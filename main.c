/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/13 16:33:07 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*inpt;
	t_token	*tokens;

	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		inpt = readline("minishell: ");
		add_history(inpt);
		tokens = lexer(inpt);
		parser(tokens);
		free(inpt);
	}
	return (0);
}
