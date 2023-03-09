/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:26:17 by kali              #+#    #+#             */
/*   Updated: 2023/03/09 04:40:23 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	get_length(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}
char	*delete_quotes(char *str, t_node *node, int index,
		enum e_token token_type)
{
	char	*new_str;
	int		i;
	int		j;
	t_token	*token;

	new_str = malloc(sizeof(char) * (get_length(str) + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	token = get_token(node, str, token_type, index);
	if (token != NULL)
		token->str = new_str;
	else
		printf("token is NULL\n");
	free(str);
	printf("token : %s\n", token->str);
	return (new_str);
}
