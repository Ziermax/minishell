/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:45:33 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/15 11:43:42 by adrmarqu         ###   ########.fr       */
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

int	ft_append(t_data *data, char *var)
{
	char	**new_env;
	char	**new_exp;

	if (!var)
		return (1);
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
