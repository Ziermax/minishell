/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:39:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/11 22:14:11 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

int	ft_isonly_asterisk(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (*(str++) != '*')
			return (0);
	return (1);
}

int	ft_isasterisk(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\\' && str[1])
			str += 2;
		if (!*str)
			break ;
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}

int	xp_ft_isvarchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*remove_quotes(char *string)
{
	char	*tmp;
	int		len;
	int		quote;

	if (!string)
		return (NULL);
	if (*string != '\'' && *string != '\"')
		return (ft_strdup(string));
	quote = *string;
	len = ft_strlen(string);
	if (len < 2)
		return (ft_calloc(sizeof(char), 1));
	if (string[len - 1] == '\'' || string[len - 1] == '\"')
		len -= 2;
	else
		len -= 1;
	string = ft_substr(string, 1, len);
	if (!string)
		return (NULL);
	if (quote == '\'')
		tmp = add_slash(string, " *\"'");
	else
		tmp = add_slash(string, " *\"'");
	return (free(string), tmp);
}

char	*remove_quotes_string(char *string)
{
	char	**split_string;
	char	**tmp;

	split_string = ultra_split(string, no_skip, xp_next_string);
	if (!split_string)
		return (NULL);
	tmp = split_for_each(split_string, remove_quotes);
	free_split(split_string);
	if (!tmp)
		return (NULL);
	split_string = tmp;
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);
}
/*
char	*remove_quotes_split(char **split_string)
{
	char	*tmp;
	int		i;

	i = -1;
	while (split_string[++i])
	{
		tmp = remove_quotes_string(split_string[i]);
		if (!tmp)
			return (free_split(split_string), NULL);
		free(split_string[i]);
	}
}*/
/*	int		i;

	i = -1;
	while (split_string[++i])
	{
		if (split_string[i][0] != '\'' && split_string[i][0] != '\"')
			continue ;
		string = remove_quotes(split_string[i]);
		if (!string)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = string;
	}
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);*/
