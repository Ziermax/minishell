/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:53:27 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/01 14:52:22 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

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
	print_env(envp);
	return (0);
}
