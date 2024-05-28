/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:53:27 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/28 18:21:47 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

/*	Hay que printar las variables por orden alfabetico	*/

static char	*get_lower(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] <= s2[i] && s1[i] && s2[i])
		i++;
	if (s1[i] && s2[i])
		return (s2);
	else if (s2[i] && !s1[i])
		return (s1);
}

static int	print_variable(char **envp)
{
	int		i;
	int		j;
	char	*lower;
	char	*prev;

	i = 0;
	while (envp[i])
	{
		lower = envp[i];
		j = i + 1;
		while (envp[j])
		{
			lower = get_lower(lower, envp[j]);
			j++;
		}
		printf("declare -x %s\n", lower);
		prev = strdup(lower);
		i++;
	}
	return (0);
}

static int	set_variable(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	envp[i] = var;
	envp[i + 1] = NULL;
	return (0);
}

int	ft_export(char **s, char **envp)
{
	if (!*s)
		print_variable(envp);
	while (*s)
	{
		set_variable(*s, envp);
		s++;
	}
	return (0);
}
