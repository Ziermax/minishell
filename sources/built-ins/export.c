/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:53:27 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/30 19:56:00 by adrmarqu         ###   ########.fr       */
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

static void	sort(char **s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i] && s[i + 1])
	{
		if (strcmp(s[i], s[i + 1]) > 0)
		{
			tmp = s[i];
			s[i] = s[i + 1];
			s[i + 1] = tmp;
		}
		i++;
	}
}

static void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

static void	put_quotts(char *s)
{
	char	**r;

	r = split(s, '=');
	printf("declare -x %s", r[0]);
	if (r[1])
		printf("=\"%s\"\n", r[1]);
	ft_free(r);
	free(s);
	s = NULL;
}

static void	print_variables(char **envp)
{
	int		i;
	char	**s;

	s = get_dup(envp);
	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		sort(s);
		i++;
	}
	i = 0;
	while (s[i])
	{
		put_quotts(s[i]);
		i++;
	}
	free(s);
	s = NULL;
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
	else
	{
		while (*s)
		{
			set_variable(*s, envp);
			s++;
		}
	}
	return (0);
}
