/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 03:23:02 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/02 14:02:46 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "structs.h"

int		ft_isexpansible(char *str);
int		ft_isseparable(char *str);
int		ft_isvarchar(int c);
//char	*remove_quotes(char *string);
char	**remove_quotes(char **split_str);
char	*search_envvar(char *key, t_data *data);
char	**expand_envvar_string(char *string, t_data *data);
char	**expand_asterisk(char *string);
char	**expand_and_replace(char **expansion, int *index,
			char **(*creat_array)(char *, int *));
char	*unspecialize_set(char *str, char *set);
char	*remove_unspecializer(char *str);

#endif
