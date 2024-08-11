/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:53:13 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/11 22:15:00 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/expand.h"

static char	*xp_next_char(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str && *str != c)
	{
		if (*str == '\\')
			str++;
		if (str)
			str++;
	}
	return (str);
}

char	*xp_next_word(char *str)
{
	if (!str)
		return (NULL);
	while (*str && !ft_isspace(*str))
	{
		if (*str == '\\' && str[1])
			str += 2;
		if (!*str || ft_isspace(*str))
			break ;
		if (*str != '\'' && *str != '\"')
			str++;
		else
			str = xp_next_string(str);
	}
	return (str);
}

char	*xp_next_string(char *str)
{
	int	quote;

	if (!str)
		return (NULL);
	quote = 0;
	if (*str == '\"' || *str == '\'')
		quote = *str++;
	if (quote == '\"')
		str = xp_next_char(str, '\"');
	else if (quote == '\'')
		str = xp_next_char(str, '\'');
	else
	{
		while (*str && *str != '\'' && *str != '\"')
		{
			if (*str == '\\')
				str++;
			if (*str)
				str++;
		}
	}
	if (quote && (*str == '\'' || *str == '\"'))
		str++;
	return (str);
}

char	*xp_next_var(char *str)
{
	if (*str == '$'
		&& ((xp_ft_isvarchar(str[1]) && !ft_isdigit(str[1])) || str[1] == '?'))
	{
		str++;
		if (*str == '?')
			return (str + 1);
		while (xp_ft_isvarchar(*str))
			str++;
		return (str);
	}
	while (*str)
	{
		if (*str == '\\' && str[1])
			str += 2;
		if (*str == '$' && ((xp_ft_isvarchar(str[1]) && !ft_isdigit(str[1]))
				|| str[1] == '?'))
			break ;
		if (*str)
			str++;
	}
	return (str);
}

char	*next_asterisk(char *str)
{
	if (!str)
		return (NULL);
	if (*str == '*')
	{
		while (*str == '*')
			str++;
		return (str);
	}
	while (*str && *str != '*')
	{
		if (*str == '\\' && str[1])
			str += 2;
		if (*str == '\"' || *str == '\'')
			str = xp_next_string(str);
		if (*str && *str != '*')
			str++;
	}
	return (str);
}
//			else if (*str == '\'' || *str == '\"')
//				str = xp_next_string(str);
