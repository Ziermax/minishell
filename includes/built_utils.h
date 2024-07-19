/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:39:52 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/19 13:45:29 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_UTILS_H
# define BUILT_UTILS_H

# define MAX_PATH 1024

# include <errno.h>
# include <unistd.h>
# include <string.h>
# include "structs.h"

int		ft_split_message(char **split, const char *s1, const char *s2);
char	*get_var(char *s);
int		check_var(char **s, char *var);
char	*put_quots(char *s);
int		get_index_var(char **var, char *to_find);
char	*get_pwd(char **envp, char *path);
int		get_type(char *var);
void	sort(char **s);
int		ft_append(t_data *data, char *var);
int		check_mode(char **data, char *var);
char	*delete_plus(char *var);
int		print_export(char **exp);
char	**add_created_data(char **data, char *var);
char	*get_value(char *var);
int		export_array(t_data *data, char *var);
int		export_array_append(t_data *data, char *var);
int		update_value(t_data *data, char *var, int idx);
char	*ft_itoa_brackets(int n);

#endif
