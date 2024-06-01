/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:24:51 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/01 18:43:59 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static char	*add_quotes(const char *s)
{
	char	*result;
	size_t	len;
	int		i;

	len = strlen(s);
	result = calloc(len + 3, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		result[i] = *s;
		if (result[i] == '=' && len != -1)
		{
			i++;
			result[i] = '\"';
			len = -1;
		}
		i++;
		s++;
	}
	result[i] = '\"';
	return (result);
}

static int	sort_one(t_data *data, char *s)
{
	char	**new;
	int		i;

	i = 0;
	while (data->exp[i])
		i++;
	new = calloc(i + 2, sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	while (data->exp[i] && strcmp(s, data->exp[i]) > 0)
	{
		new[i] = strdup(data->exp[i]);
		i++;
	}
	new[i++] = strdup(s);
	while (data->exp[i - 1])
	{
		new[i] = strdup(data->exp[i - 1]);
		i++;
	}
	ft_freeze(data->exp);
	data->exp = new;
	return (0);
}

static int	put_var(t_data *data, char *s, int equal)
{
	char	*new_var;

	if (equal == 1)
		new_var = add_quotes(s);
	else
		new_var = s;
	if (!new_var)
		return (1);
	return (sort_one(data, new_var));
}

static int	check_export(char *s)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	if (s[0] == '=')
		return (-1);
	while (s[i])
	{
		if (s[i] == '=')
			type = 1;
		i++;
	}
	return (type);
}

static void	add_env(t_data *data, char *var)
{
	int	i;

	i = 0;
	while (data->envp[i])
		i++;
	data->envp[i] = var;
	data->envp[i + 1] = NULL;
}

static int	print_exp(char **s)
{
	int	error;

	while (*s)
	{
		error = printf("declare -x %s\n", *s);
		if (error == -1)
			return (1);
		s++;
	}
	return (0);
}

static int	check_num(char *s)
{
	if (s[0] > '0' && s[0] < '9')
		return (1);
	else
		return (0);
}

int	ft_export(char **s, t_data *data)
{
	int	type;
	int	error;

	error = 0;
	if (!s || !(*s))
		return (print_exp(data->exp));
	else
	{
		while (*s)	
		{
			type = check_export(*s);
			if (type == -1)
				error = 1;
			else if (type == 1)
				add_env(data, *s);
			if (type != -1 && !check_num(*s))
				error += put_var(data, *s, type);
			else
				error = 1;
			s++;
		}
	}
	print_exp(data->exp);
	if (error > 0)
		error = 1;
	return (error);
}
