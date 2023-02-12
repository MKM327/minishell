/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:47:38 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/12 15:48:29 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
typedef struct s_struct
{
	char		start[2];
	char		*command;
	char		*option;
	char		*argument;
	char		end[2];
}				t_command;

enum			token
{
	I_REDIRECTION,
	O_REDIRECTION,
	HERE_DOC,
	APPEND_RED,
	PIPE,
	COMMAND,
	ARG,
	OPTION,
	AND,
	OR,
	ENV,
	UNKNOWN
};
typedef struct s_token
{
	enum token	token;
	int			start_index;
	int			end_index;
}				t_token;
t_token			*lexer(char *str);
int				my_alpha(char c);
int				is_redirection(char c);
int				get_token_count(char *str);
#endif
