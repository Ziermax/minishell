/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:31:35 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/14 13:46:21 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

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

	new = calloc(strlen(s) + 3, sizeof(char));
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
		return (strdup(s));
	var = calloc(i + 1, sizeof(char));
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
	len = strlen(var);
	idx = 0;
	while (s[idx])
	{
		if (strncmp(s[idx], var, len) == 0)
			return (idx);
		idx++;
	}
	return (-1);
}

int	get_index_var(char **var, const char *to_find)
{
	int	i;
	int	len;

	len = strlen(to_find);
	i = 0;
	while (var[i])
	{
		if (strncmp(to_find, var[i], len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*r;

	if (!s1 || !s2)
		return (NULL);
	r = (char *)calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		r[i] = s2[j];
		i++;
		j++;
	}
	return (r);
}
