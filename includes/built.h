/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:48:29 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/24 14:52:42 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# define MAX_PATH 1024

# include "minishell.h"

int			ft_cd(t_data *data, char **input);
int			print_pwd(void);
int			ft_export(t_data *data, char **input);
int			ft_unset(t_data *data, char **input);
int			ft_delete_var(char ***str, char *var);
int			print_echo(char **s);

// Utils

size_t		get_size(char **s);
char		*get_var(char *s);
int			check_var(char **s, char *var);
char		*put_quots(char *s);
int			print_char(char **s);
int			get_index_var(char **var, const char *to_find);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
