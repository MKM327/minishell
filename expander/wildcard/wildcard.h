/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:36 by eablak            #+#    #+#             */
/*   Updated: 2023/03/14 12:58:59 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "../../minishell.h"
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

void	handle_node_wildcard(t_node *node);
int		is_asterisk(char *str);
int		asterisk_slash(char *str);
void	handle_arg_asterisk(t_command *command);
void	handle_command_asterisk(t_command *command);
int		get_path_count(void);
char	**get_files(void);
int		is_right_side(char *str, int index);
char	*right_side(char *str, int *index);
int		is_left_side(char *str, int index);
char	*left_side(char *str, int *index);
int		is_middle(char *str, int index);
char	*middle(char *str, int *index);
void	print_files(char **files);
char	**right_side_files(char **files, char *str);
char	**left_side_files(char **files, char *str);
char	**middle_files(char **files, char *str);
void	match_arg_files(char **files, t_command *command, int i);
void	print_arg(char **arg);
char	**just_asterisk(char *command);
char	**sort_files(char **files, char *str);
char	**command_file(char *prefix, char *suffix, char *path);
char	**only_files(char *path);
char	**take_file(char **files, char *command);

int		countWildcard(char *prefix, char *suffix, int *count);
int		get_dir_count(char *path);
char	**get_dir(char *path);
int		get_all_count(char *path);
char	**get_all(char *path);
void	expandWildcard(char *prefix, char *suffix, char **return_files,
			int *index);
int		files_count(char **files);
char	**get_w_dot_files2(char *path, unsigned char d_type);

int		get_w_path_count2(char *path, unsigned char d_type);

#endif
