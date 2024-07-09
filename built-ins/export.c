/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:33:23 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 18:30:50 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../includes/built_utils.h"
#include "../Libft/includes/libft.h"
#include <limits.h>

static int	add_to_exp(t_data *data, char *var)
{
	char	**new;
	int		i;

	new = ft_calloc(ft_arraylen(data->exp) + 2, sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	while (data->exp[i] && ft_strncmp(data->exp[i], var, INT_MAX) < 0)
	{
		new[i] = data->exp[i];
		i++;
	}
	new[i] = put_quots(var);
	if (!new[i])
		return (free_split(new), 1);
	while (data->exp[i])
	{
		new[i + 1] = data->exp[i];
		i++;
	}
	free(data->exp);
	data->exp = new;
	return (0);
}

static int	add_to_env(t_data *data, char *var)
{
	char	**new;
	int		i;

	new = ft_calloc(ft_arraylen(data->envp) + 2, sizeof(char *));
	if (!new)
		return (1);
	i = 0;
	while (data->envp[i])
	{
		new[i] = data->envp[i];
		i++;
	}
	new[i] = var;
	free(data->envp);
	data->envp = new;
	return (0);
}

static int	check_input(char *var)
{
	int	type;
	int	i;

	if (var[0] == '-')
	{
		fd_printf(2, "minishell: export: options are not avaliable\n");
		return (-1);
	}
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (-1);
	i = 1;
	type = 0;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (-1);
		if (var[i] == '=')
			type = 1;
		i++;
	}
	return (type);
}

int	ft_export(char **argv, t_data *data)
{
	int	type;
	int	flag;

	argv++;
	if (!*argv)
		return (ft_split_message(data->exp, "declare -x ", NULL));
	flag = 0;
	while (*argv)
	{
		type = check_input(*argv);
		if (type == -1)
			flag = 1;
		else
		{
			if (type)
			{
				flag += ft_delete_var(data->envp, get_var(*argv));
				flag += ft_delete_var(data->exp, get_var(*argv));
				flag += add_to_env(data, *argv);
			}
			flag += add_to_exp(data, *argv);
		}
		argv++;	
	}
	return (flag > 0);
}
