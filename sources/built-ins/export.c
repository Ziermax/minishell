/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:53:27 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/30 16:58:28 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static size_t	ft_size(char **s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

static char	**get_dup(char **envp)
{
	int		i;
	char	**s;

	s = (char **)malloc((ft_size(envp) + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		s[i] = strdup(envp[i]);
		if (!s[i])
			return (NULL);
		i++;
	}
	s[i] = NULL;
	return (s);
}

static void	print_variables(char **envp)
{
	int		i;
	int		j;
	char	**s;
	char	*tmp;

	s = get_dup(envp);
	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[j] && s[j + 1])
		{
			if (strcmp(s[j], s[j + 1]) > 0)
			{
				tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	while (*s)
	{
		printf("%s\n", *s);
		s++;
	}
}

static void	set_variable(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = var;
	envp[i + 1] = NULL;
}

int	ft_export(char **s, char **envp)
{
	if (!s || !(*s))
		print_variables(envp);
	while (*s)
	{
		set_variable(*s, envp);
		s++;
	}
	return (0);
}
