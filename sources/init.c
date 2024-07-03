/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:52:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/03 15:27:38 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"

static void	sort(char **s)
{
	int		i;
	int		j;
	char	*tmp;

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
}

static int	init_exp(char ***exp, char **envp)
{
	size_t			i;
	const size_t	size = ft_arraylen(envp);

	*exp = ft_calloc(size + 1, sizeof(char *));
	if (!*exp)
		return (-1);
	i = 0;
	while (i < size)
	{
		(*exp)[i] = put_quots(envp[i]);
		if (!(*exp)[i])
			return (-ft_free(exp));
		i++;
	}
	(*exp)[i] = NULL;
	sort(*exp);
	return (0);
}

static int	init_env(char ***env, char **envp)
{
	size_t			i;
	const size_t	size = ft_arraylen(envp);

	*env = ft_calloc(size + 1, sizeof(char *));
	if (!*env)
		return (-1);
	i = 0;
	while (i < size)
	{
		(*env)[i] = ft_strdup(envp[i]);
		if (!(*env)[i])
			return (-ft_free(env));
		i++;
	}
	(*env)[i] = NULL;
	return (0);
}

int	init_data(t_data *data, char **envp)
{
	if (init_env(&(data->env), envp) == -1)
		return (-1);
	if (init_exp(&(data->exp), envp) == -1)
		return (-1);
	data->exit = 0;
	return (0);
}
