/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:53:01 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/08 13:20:17 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	add_to_exp(char ***str, char *var)
{
	char	**new;
	int		i;

	new = calloc(get_size(*str) + 2, sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	while ((*str)[i] && strcmp((*str)[i], var) < 0)
	{
		new[i] = strdup((*str)[i]);
		i++;
	}
	new[i] = put_quots(var);
	if (!new[i])
		return (ft_free(&new));
	while ((*str)[i])
	{
		new[i + 1] = strdup((*str)[i]);
		i++;
	}
	new[i + 1] = NULL;
	free(*str);
	*str = new;
	return (0);
}

static int	add_to_env(char ***str, char *var)
{
	char	**new;
	int		i;

	new = calloc(get_size(*str) + 2, sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	while ((*str)[i])
	{
		new[i] = strdup((*str)[i]);
		if (!new[i])
			return (ft_free(&new));
		i++;
	}
	new[i] = strdup(var);
	new[i + 1] = NULL;
	free(*str);
	*str = new;
	return (0);
}

static int	check_exp(char *var)
{
	int	type;
	int	i;

	if (!isalpha(var[0]) && var[0] != '_')
		return (-1);
	i = 1;
	type = 0;
	while (var[i])
	{
		if (!isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (-1);
		if (var[i] == '=')
			type = 1;
		i++;
	}
	return (type);
}

static int	print_exp(char **s)
{
	while (*s)
	{
		if (printf("declare -x %s\n", *s) == -1)
			return (1);
		s++;
	}
	return (0);
}

int	ft_export(t_data *data, char **input)
{
	int	flag;
	int	type;

	input++;
	if (!input)
		return (print_exp(data->exp));
	flag = 0;
	while (*input)
	{
		type = check_exp(*input);
		if (type == -1)
			flag = 1;
		else
		{
			if (type)
			{
				flag += ft_delete_var(&(data->env), get_var(*input));
				flag += ft_delete_var(&(data->exp), get_var(*input));
				flag += add_to_env(&(data->env), *input);
			}
			flag += add_to_exp(&(data->exp), *input);
		}
		input++;
	}
	return (flag);
}
