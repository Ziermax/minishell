/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:31:35 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/24 17:36:02 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built.h"

int	print_char(char **s)
{
	while (*s)
	{
		if (printf("%s\n", *s) == -1)
			return (1);
		s++;
	}
	return (0);
}

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
			new[j] = '\"';
			j++;
			equal = 1;
		}
		i++;
	}
	if (equal)
		new[j++] = '\"';
	return (new);
}

size_t	get_size(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_free(char ***s)
{
	char	**ptr;

	ptr = *s;
	if (!ptr || !*ptr)
		return (0);
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(*s);
	*s = NULL;
	return (1);
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
	var[i] = '\0';
	return (var);
}

int	check_var(char **s, char *var)
{
	int		idx;
	size_t	len;

	if (!var || !s || !*s)
		return (-1);
	len = ft_strlen(var);
	idx = 0;
	while (s[idx])
	{
		if (ft_strncmp(s[idx], var, len) == 0)
			return (idx);
		idx++;
	}
	return (-1);
}

int	get_index_var(char **var, const char *to_find)
{
	int	i;
	int	len;

	len = ft_strlen((char *)to_find);
	i = 0;
	while (var[i])
	{
		if (ft_strncmp(to_find, var[i], len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
