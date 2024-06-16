/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:48:29 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/14 16:44:21 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <ctype.h>
# include <sys/errno.h>
//# include "../../Libft/includes/libft.h"

# define MAX_PATH 1024

typedef struct	s_data
{
	char	**env;
	char	**exp;
}	t_data;

int			ft_cd(t_data *data, char **input);
int			print_pwd(void);
int			ft_export(t_data *data, char **input);
int			ft_unset(t_data *data, char **input);
int			ft_delete_var(char ***str, char *var);

// Utils

int			ft_free(char ***s);
size_t		get_size(char **s);
char		*get_var(char *s);
int			check_var(char **s, char *var);
char		*put_quots(char *s);
int			print_char(char **s);
int			get_index_var(char **var, const char *to_find);
char		*ft_join(char *s1, char *s2);

#endif
