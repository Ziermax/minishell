/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:54:11 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/09 12:02:00 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace(*str))
		str++;
	return (str);
}

char	*no_skip(char *str)
{
	return (str);
}

char	*next_string(char *str)
{
	int	quote;

	if (!str)
		return (NULL);
	quote = 0;
	if (*str == '\"' || *str == '\'')
		quote = *str++;
	if (quote == '\"')
		while (*str && *str != '\"')
			str++;
	else if (quote == '\'')
		while (*str && *str != '\'')
			str++;
	else
		while (*str && *str != '\'' && *str != '\"')
			str++;
	if (quote && (*str == '\'' || *str == '\"'))
		str++;
	return (str);
}

char	**ft_splitdup(char **split)
{
	char	**dup;
	int		i;
	int		size;

	size = ft_arraylen(split);
	dup = ft_calloc(size + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = ft_strdup(split[i]);
		if (!dup[i])
		{
			free_split(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
