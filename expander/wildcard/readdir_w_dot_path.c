/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_w_dot_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:23:50 by eablak            #+#    #+#             */
/*   Updated: 2023/03/24 11:49:29 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	get_wpcount2_process(t_get *get, unsigned char d_type)
{
	if (d_type != 100)
	{
		if (get->dir->d_name[0] != '.' && get->dir->d_type == d_type)
			get->i++;
	}
	else
	{
		if (get->dir->d_name[0] != '.')
			get->i++;
	}
}

int	get_w_path_count2(char *path, unsigned char d_type)
{
	t_get	*get;

	get = malloc(sizeof(t_get) * 1);
	get->i = 0;
	get->d = opendir(path);
	if (get->d)
	{
		while (1)
		{
			get->dir = readdir(get->d);
			if (get->dir == NULL)
				break ;
			get_wpcount2_process(get, d_type);
		}
	}
	free(get->dir);
	return (get->i);
}

void	get_wdot_files_process(t_get *get, unsigned char d_type)
{
	if (d_type != 100)
	{
		if (get->dir->d_name[0] != '.' && get->dir->d_type == d_type)
		{
			get->files[get->i] = get->dir->d_name;
			get->i++;
		}
	}
	else
	{
		if (get->dir->d_name[0] != '.')
		{
			get->files[get->i] = get->dir->d_name;
			get->i++;
		}
	}
}

char	**get_w_dot_files2(char *path, unsigned char d_type)
{
	t_get	*get;

	get = malloc(sizeof(t_get) * 1);
	get->count = get_w_path_count2(path, d_type);
	get->files = (char **)malloc(sizeof(char *) * (get->count + 1));
	get->d = opendir(path);
	if (get->d)
	{
		get->i = 0;
		while (1)
		{
			get->dir = readdir(get->d);
			if (get->dir == NULL)
				break ;
			get_wdot_files_process(get, d_type);
		}
	}
	free(get->dir);
	get->files[get->i] = NULL;
	return (get->files);
}
