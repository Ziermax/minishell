/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:49:04 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/09 16:35:09 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"

static int	update_data(char **data, const char *s, char *path, int idx)
{
	char	*new;

	new = ft_strjoin(s, path);
	if (!new)
		return (1);
	free(data[idx]);
	data[idx] = ft_strdup(new);
	free(new);
	if (!data[idx])
		return (1);
	return (0);
}

static int	pwd_quots(t_data *da, char **data, int idx_pwd)
{
	char	*tmp;

	tmp = put_quots(data[idx_pwd]);
	free(data[idx_pwd]);
	data[idx_pwd] = ft_strdup(tmp);
	free(tmp);
	if (!data[idx_pwd])
	{
		da->end = 1;
		return (1);
	}
	return (0);
}

static int	update_pwd(t_data *da, char **data, char *path, int quots)
{
	int		idx_pwd;
	int		idx_old;

	idx_pwd = get_index_var(data, "PWD=");
	idx_old = get_index_var(data, "OLDPWD=");
	if (pwd_idx == -1 || oldpwd_idx == -1)
		return (1);
	if (update_data(data, "OLD", data[idx_pwd], idx_old))
	{
		da->end = 1;
		return (1);
	}
	if (update_data(data, "PWD=", path, idx_pwd))
	{
		da->end = 1;
		return (1);
	}
	if (quots)
		return (pwd_quots(da, data, idx_pwd));
	return (0);
}

static int	make_cd(t_data *data, char *path)
{
	if (!ft_strncmp(path, ".", 2) && !getcwd(NULL, 0))
	{
		fd_printf(2, "cd: error retrieving current directory: getcwd: cannot");
		fd_printf(2, " access parent directories: %s\n", strerror(errno));
		return (1);
	}
	if (chdir(path) == -1)
	{
		fd_printf(2, "cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (update_pwd(data, data->envp, path, 0))
		return (1);
	if (update_pwd(data, data->exp, path, 1))
		return (1);
	return (0);
}

int	ft_cd(char **argv, t_data *data)
{
	int		size;
	char	*dir;

	argv++;
	size = ft_arraylen(argv);
	if (size > 1)
	{
		fd_printf(2, "minnishell: cd: too many arguments\n");
		return (1);
	}
	else if (size == 1)
	{
		dir = ft_strdup(getenv("HOME"));
		if (!dir)
		{
			data->end = 1;
			return (1);
		}
		size = make_cd(data, dir);
		free(dir);
		return (size);
	}
	else if (!size)
		return (make_cd(data, *argv));
}
