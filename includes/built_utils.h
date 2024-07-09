/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:39:52 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/08 18:42:35 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_UTILS_H
# define BUILT_UTILS_H

# define MAX_PATH 1024

# include <errno.h>
# include <unistd.h>
# include <string.h>

int			ft_delete_var(char ***str, char *var);
char		*get_var(char *s);
int			ft_free(char ***s);
int			check_var(char **s, char *var);
char		*put_quots(char *s);
int			get_index_var(char **var, char *to_find);

#endif

