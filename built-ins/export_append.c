/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:45:33 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/15 11:09:20 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"

static char	*get_append(char **data, char *var, int idx)
{
	char	*val;
	char	*new_var;

	val = get_value(var);
	new_var = ft_strjoin(data[idx], val);
	printf("VAR: %s\n", new_var);
	free(val);
	return (new_var);
}

static int	get_action(char *prev)
{
	int	i;

	i = 0;
	while (prev[i] && prev[i] != '=')
		i++;
	if (!prev[i])
		return (1);
	return (0);
}

static char	**make_append(char **data, char *var)
{
	int		idx;
	char	*name;
	char	*var_append;

	name = get_var(var);
	idx = get_index_var(data, name);
	free(name);
	if (idx == -1)
		return (add_created_data(data, var));
	if (get_action(data[idx]))
	{
		free(data[idx]);
		data[idx] = ft_strdup(var);
		if (!data[idx])
			return (NULL);
		return (data);
	}
	var_append = get_append(data, var, idx);
	if (!var_append)
		return (NULL);
	free(data[idx]);
	data[idx] = var_append;
	return (data);
}

int	isarray(t_data *data, char *var, int idx)
{
	int	i;

	if (idx == -1)
		return (0);
	i = 0;
	while (var[i] == '(')
	{
		if (var[i++] == '(')
		{
			fd_printf(2, "minishell: syntax error near unexpected token `('");
			return (-1);
		}
	}
	i = 0;
	while (data->exp[idx][i])
	{
		if (data->exp[idx][i++] == '(')
			return (1);
	}
	return (0);
}

int	ft_append(t_data *data, char *var)
{
	char	**new_env;
	char	**new_exp;
	char	*name;
	int		idx;
	int		isarr;

	if (!var)
		return (1);
	name = get_var(var);
	idx = get_index_var(data->exp, name);
	free(name);
	isarr = isarray(data, var, idx);
	if (isarr == -1)
		return (1);
	if (isarr)
		return (update_value(data, var, idx));
	new_env = make_append(data->envp, var);
	if (!new_env)
		return (1);
	data->envp = new_env;
	new_exp = make_append(data->exp, var);
	if (!new_exp)
		return (1);
	data->exp = new_exp;
	return (0);
}
