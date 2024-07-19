/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:40:36 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/19 11:37:13 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built_utils.h"

char	**add_created_data(char **data, char *var)
{
	int		i;
	char	**new;

	i = 0;
	new = ft_calloc(ft_arraylen(data) + 2, sizeof(char *));
	if (!new)
		return (data);
	while (data[i])
	{
		new[i] = data[i];
		i++;
	}
	new[i] = ft_strdup(var);
	if (!new[i])
	{
		free_split(new);
		return (NULL);
	}
	free(data);
	return (new);
}

static char	**make_export(char **data, char *var)
{
	int		idx;

	idx = check_mode(data, var);
	if (idx != -1)
	{
		free(data[idx]);
		data[idx] = ft_strdup(var);
		if (!data[idx])
			return (NULL);
		return (data);
	}
	return (add_created_data(data, var));
}

static int	export_var(t_data *data, char *var, int type)
{
	char	**new_env;
	char	**new_exp;

	if (!var)
		return (1);
	if (type)
	{
		new_env = make_export(data->envp, var);
		if (!new_env)
			return (1);
		data->envp = new_env;
	}
	new_exp = make_export(data->exp, var);
	if (!new_exp)
		return (1);
	data->exp = new_exp;
	return (0);
}

static int	select_export(t_data *data, char *var)
{
	int		type;

	type = get_type(var);
	if (type == -1)
		return (1);
	if (type == 2)
	{
		var = delete_plus(var);
		return (ft_append(data, var));
	}
	else if (type == 3)
		return (export_array_append(data, var));
	else if (type == 4)
		return (export_array(data, var));
	else
		return (export_var(data, var, type));
	return (0);
}

int	ft_export(char **argv, t_data *data)
{
	int	flag;

	argv++;
	if (!*argv || !argv[0][0])
		return (print_export(data->exp));
	if (argv[0][0] == '-')
	{
		fd_printf(2, "minishell: export: -%c: invalid option\n", argv[0][1]);
		fd_printf(2, "minishell: export is not accepting options today\n");
		return (2);
	}
	flag = 0;
	while (*argv)
	{
		if (select_export(data, *argv))
			flag = 1;
		argv++;
	}
	return (flag);
}
