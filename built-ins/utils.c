/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:38:28 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 18:33:59 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_utils.h"
#include "../Libft/includes/libft.h"

char	*put_quots(char *s)
{
	char	*new;
	int		i;
	int		j;
	int		equal;

	new = ft_calloc(ft_strlen(s) + 3, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	equal = 0;
	while (s[i])
	{
		new[j++] = s[i];
		if (s[i] == '=' && !equal)
		{
			new[j++] = '\"';
			equal = 1;
		}
		i++;
	}
	if (equal)
		new[j] = '\"';
	return (new);
}

char	*get_var(char *s)
{
	char	*var;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] != '=')
		return (ft_strdup(s));
	var = ft_calloc(i + 1, sizeof(char));
	if (!var)
		return (NULL);
	i = 0;
	while (s[i] != '=')
	{
		var[i] = s[i];
		i++;
	}
	return (var);
}

int	check_var(char **s, char *var)
{
	int	i;
	int	len;

	if (!var || !s || !*s)
		return (-1);
	len = ft_strlen(var);
	i = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], var, len))
			return (i);
		i++;
	}
	return (-1);
}

int	get_index_var(char **var, char *to_find)
{
	int	i;
	int	len;

	len = ft_strlen(to_find);
	i = 0;
	while (var[i])
	{
		if (!ft_strncmp(to_find, var[i], len))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_split_message(char **split, const char *s1, const char *s2)
{
	int	i;

	if (!split || !*split)
		return (1);
	i = 0;
	while (split[i])
	{
		if (s1)
			fd_printf(1, "%s", s1);
		fd_printf(1, "%s", split[i]);
		if (s2)
			fd_printf(1, "%s", s2);
		fd_printf(1, "\n");
		i++;
	}
	return (0);
}
