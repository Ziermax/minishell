/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:26:49 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/06 15:48:27 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	print_exp(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (printf("declare -x %s\n", s[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

static int	add_to_exp(char ***exp, char *s)
{
	char	**new;
	int		i;

	new = calloc(get_size(*exp) + 2, sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	while ((*exp)[i] && strcmp((*exp)[i], s) < 0)
	{
		new[i] = (*exp)[i];
		i++;
	}
	new[i] = strdup(s);
	if (!new[i])
	{
		//ft_free(new);
		return (1);
	}
	while ((*exp)[i])
	{
		new[i + 1] = (*exp)[i];
		i++;
	}
	free(*exp);
	*exp = new;
	return (0);
}

static int	add_to_env(char ***env, char *s)
{
	char	**new;
	int		i;

	new = calloc(get_size(*env) + 2, sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	while ((*env)[i])
	{
		new[i] = (*env)[i];
		i++;
	}
	new[i] = strdup(s);
	if (!new[i])
	{
		//ft_free(new);
		return (1);
	}
	free(*env);
	*env = new;
	return (0);
}

static int	check_input(char *s)
{
	int	i;
	int	type;

	if (!s)
		return (0);
	if (!isalpha(s[0]) && s[0] != '_')
		return (-1);
	i = 0;
	type = 0;
	while (s[i])
	{
		if (s[i] == '=' && type != -1)
			type = 1;
		if (!isalnum(s[i]) && s[i] != '_' && s[i] != '=')
			type = -1;
		i++;
	}
	return (type);
}

int	ft_export(t_data *data, char **input)
{
	int	type;
	int	flag;

	flag = 0;
	input++;
	if (!input || !*input)
		return (print_exp(data->exp));
	else
	{
		while (*input)
		{
			type = check_input(*input);
			if (type == -1)
				flag = 1;
			else
			{
				if (type == 1)
					flag += add_to_env(&(data->env), *input);
				flag += add_to_exp(&(data->exp), *input);
			}
			input++;
		}
	}
	return (flag > 0);
}
