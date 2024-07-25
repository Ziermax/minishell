/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:49:22 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/25 17:56:52 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"
/*
=======================
TEST = "ho la"
Input: "*$TEST'*$TEST*'\"$TEST\"*$TEST*"
Result: [0]: "*ho"
		[1]: "ls'*$TEST*'\"ho la\"*ho"
		[2]: "la*"
		[3]: (null)
=======================
*/

static char	*search_envvar(char *key, t_data *data)
{
	char	*value;
	int		len;

	if (!key)
		return (NULL);
	if (*key == '?')
		return (ft_itoa(data->exit));
	if (!data->envp)
		return (ft_strdup(""));
	key = ft_strjoin(key, "=");
	if (!key)
		return (NULL);
	len = ft_strlen(key);
	value = search_word_in_split(key, data->envp, len);
	if (!value)
		return (free(key), ft_strdup(""));
	return (free(key), ft_strdup(&value[len]));
}

static char	*next_var(char *str)
{
	if (*str == '$'
		&& ((ft_isvarchar(str[1]) && !ft_isdigit(str[1])) || str[1] == '?'))
	{
		str++;
		if (*str == '?')
			return (str + 1);
		while (ft_isvarchar(*str))
			str++;
		return (str);
	}
	while (*str)
	{
		if (*str == '$' && ((ft_isvarchar(str[1]) && !ft_isdigit(str[1]))
				|| str[1] == '?'))
			break ;
		str++;
	}
	return (str);
}

static char	*expand_var(char *string, t_data *data)
{
	char	**split_string;
	char	*tmp;
	int		i;

	split_string = ultra_split(string, no_skip, next_var);
	if (!split_string)
		return (NULL);
	i = -1;
	while (split_string[++i])
	{
		if (!split_string[i][0] != '$' || (split_string[i][0] &&
				!ft_isvarchar(split_string[i][1]) && split_string[i][1] != '?'))
			continue ;
		tmp = search_envvar(&split_string[i][1], data);
		if (!tmp)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = tmp;
	}
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);
}

static char	*expand_envvar(char *string, t_data *data)
{
	char	**split_string;
	char	*tmp;
	int		i;

	split_string = ultra_split(string, no_skip, next_string);
	if (!split_string)
		return (NULL);
	i = -1;
	while (split_string[++i])
	{
		if (split_string[i][0] == '\'')
			continue ;
		tmp = expand_var(split_string[i], data);
		if (!tmp)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = tmp;
	}
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);
}

char	**expansion_envvar(char *string, t_data *data)
{
	char	**split_string;
	char	*tmp;

	tmp = expand_envvar(string, data);
	if (!tmp)
		return (NULL);
	split_string = ultra_split(tmp, skip_spaces, next_word);
	free(tmp);
	return (split_string);
}
//	if (!split_string)
//		return (NULL);
//	i = -1;
//	while (split_string[++i])
//	{
//		if (!ft_isseparable(split_string[i]))
//			continue ;
//	}
