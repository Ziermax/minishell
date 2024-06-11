/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:06:33 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/11 17:40:52 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"
#include "lib2.h"

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
	size_t	i;
	size_t	size;

	size = get_size(envp);
	*exp = calloc(size + 1, sizeof(char *));
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
	size_t	i;
	size_t	size;
	  
	size = get_size(envp);
	*env = calloc(size + 1, sizeof(char *));
	if (!*env)
		return (-1);
	i = 0;
	while (i < size)
	{
		(*env)[i] = strdup(envp[i]);
		if (!(*env)[i])
			return (-ft_free(env));
		i++;
	}
	(*env)[i] = NULL;
	return (0);
}

static int	init_data(t_data *data, char **envp)
{
	if (init_env(&(data->env), envp) == -1)
		return (-1);
	if (init_exp(&(data->exp), envp) == -1)
		return (-1);
	data->flag = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	if (init_data(&data, envp) == -1)
		return (1);
	while (1)
	{
		printf("minishell: ", get_pwd());
	}
	(void)argc;
	(void)argv;
	return (data.flag);
}
