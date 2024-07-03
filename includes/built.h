/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:48:29 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/03 13:30:17 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# define MAX_PATH 1024

# include "../Libft/includes/libft.h"
# include <errno.h>
# include "structs.h"
# include <unistd.h>
# include <string.h>

int			ft_cd(t_data *data, char **input);
int			print_pwd(void);
int			ft_export(t_data *data, char **input);
int			ft_unset(t_data *data, char **input);
int			ft_delete_var(char ***str, char *var);
int			print_echo(char **s);

char		*get_var(char *s);
int			ft_free(char ***s);
int			check_var(char **s, char *var);
char		*put_quots(char *s);
int			get_index_var(char **var, char *to_find);

#endif
