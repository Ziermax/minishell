/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 03:23:02 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/11 22:14:36 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "structs.h"

/*int		ft_isexpansible(char *str);
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
char	*remove_unspecializer(char *str);*/
int		xp_ft_isvarchar(int c);
int		ft_isasterisk(char *str);
int		ft_isonly_asterisk(char *str);
char	*remove_slash(char *str, void *keep);
char	*add_slash(char *str, void *keep);
char	*xp_next_var(char *str);
char	*next_asterisk(char *str);
char	*xp_next_word(char *str);
char	*xp_next_string(char *str);
char	*remove_quotes_string(char *string);
char	*remove_quotes_split(char **split_string);
char	**expand_envvar(char *string, t_data *data);
char	**expand_asterisk(char *string);

#endif
