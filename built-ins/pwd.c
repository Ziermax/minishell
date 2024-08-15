/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:35:11 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/15 13:07:46 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built.h"
#include "../includes/built_utils.h"
#include "../Libft/includes/libft.h"
#include <unistd.h>

int	check_oldpwd(t_data *data)
{
	int		idx;
	char	**new;

	if (get_index_var(data->envp, "OLDPWD") == -1)
	{
		idx = get_index_var(data->exp, "OLDPWD");
		if (idx == -1)
			return (0);
		new = add_created_data(data->envp, data->exp[idx]);
		if (!new)
			return (1);
		data->envp = new;
	}
	return (0);
}

static int	check_options(char *str)
{
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' && str[1])
	{
		fd_printf(2, "minishell: pwd: %s: invalid option\n", str);
		fd_printf(2, "pwd: no accept options\n", str);
		return (2);
	}
	return (0);
}

int	ft_pwd(char **argv, t_data *data)
{
	char	*cwd;

	if (argv)
	{
		argv++;
		if (check_options(*argv))
			return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (fd_printf(1, "%s\n", data->pwd), 0);
	fd_printf(1, "%s\n", cwd);
	free(cwd);
	return (0);
}
