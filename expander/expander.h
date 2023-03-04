/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:52:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/04 05:27:11 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "../minishell.h"
typedef struct s_env
{
	char	*name;
	char	*value;
}			t_env;
void		handle_env(t_node *node, char **env);
t_env		*get_env_variables(char **env);
char		*find_env_variable(char *value, t_env *env);
char		*get_env_location(char *str);
char		*assign_env(char *str, char *env_value);
void		handle_node_env(t_node *node, t_env *env);
void		free_env(t_env *env);
char		*delete_quotes(char *str);
#endif