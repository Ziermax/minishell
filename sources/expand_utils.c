/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:39:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/10 21:52:53 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

int	only_asterisk(char *str)
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
	}
	return (0);
}

int	ft_isvarchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*remove_quotes_string(char *string)
{
	int	len;
	int	quote;

	if (!string)
		return (NULL);
	quote = *string;
	if (quote != '\'' && quote != '\"')
		return (ft_strdup(string));
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
		string = add_slash(string, " *\"'");
	else if (quote == '\"')
		string = add_slash(string, " *\"'");
	return (string);
}

char	*remove_quotes(char *string)
{
	char	**split_string;
	int		i;

	split_string = ultra_split(string, no_skip, xp_next_string);
	if (!split_string)
		return (NULL);
	i = -1;
	while (split_string[++i])
	{
		if (split_string[i][0] != '\'' && split_string[i][0] != '\"')
			continue ;
		string = remove_quotes_string(split_string[i]);
		if (!string)
			return (free_split(split_string), NULL);
		free(split_string[i]);
		split_string[i] = string;
	}
	string = ft_splitjoin(split_string);
	free_split(split_string);
	return (string);
}
