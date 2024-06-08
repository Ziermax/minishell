/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:31:35 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/08 13:23:06 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

// getcwd(NULL, 0)

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

char *put_quots(char *s)
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

int ft_free(char ***s)
{
    char **ptr;

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
