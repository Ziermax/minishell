/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:49:04 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/15 13:54:49 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include "../includes/built_utils.h"

static int	update_new(char **data, char *var)
{
	int	idx;

	idx = get_index_var(data, "PWD");
	if (idx == -1)
		return (1);
	free(data[idx]);
	data[idx] = var;
	return (0);
}

static int	update_old(char **data)
{
	int		idx;
	int		old_idx;
	char	*new;

	idx = get_index_var(data, "PWD=");
	old_idx = get_index_var(data, "OLDPWD=");
	if (idx == -1)
		return (1);
	new = ft_strjoin("OLD", data[idx]);
	if (!new)
		return (1);
	free(data[old_idx]);
	data[old_idx] = new;
	return (0);
}

int	update_pwd(t_data *data, char *path)
{
	char	*var;
	char	*var_quots;

	var = get_pwd(data->envp, path);
	if (!var)
		return (1);
	update_old(data->envp);
	update_new(data->envp, var);
	var_quots = put_quots(var);
	if (!var_quots)
		return (1);
	update_old(data->exp);
	update_new(data->exp, var_quots);
	return (0);
}

int	make_cd(t_data *data, char *path)
{
	if (!path || !*path)
		return (0);
	if (!ft_strncmp(path, ".", 2) && !getcwd(NULL, 0))
	{
		fd_printf(2, "cd: error retrieving current directory: getcwd: can");
		fd_printf(2, "not access parent directories: %s\n", strerror(errno));
		return (update_pwd(data, path));
	}
	if (chdir(path) == -1)
	{
		fd_printf(2, "cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (update_pwd(data, path));
}

int	ft_cd(char **argv, t_data *data)
{
	unsigned int	size;
	char			*dir;

	argv++;
	size = ft_arraylen(argv);
	if (!size)
	{
		dir = ft_strdup(getenv("HOME"));
		if (!dir)
			return (fd_printf(2, "cd: %s\n", strerror(errno)), 1);
		size = make_cd(data, dir);
		free(dir);
		return ((int)size);
	}
	else if (size == 1)
		return (make_cd(data, *argv));
	else if (size > 1)
		return (fd_printf(2, "minishell: cd: too many arguments\n"), 1);
	return (0);
}
