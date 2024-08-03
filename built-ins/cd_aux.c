/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:26:52 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/02 18:41:00 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include "../includes/built_utils.h"

void	delete_last_slash(char *str)
{
	int	i;

	if (!str)
		return ;
	i = ft_strlen(str) - 1;
	if (!i)
		return ;
	if (str[i] == '/')
		str[i] = '\0';
}

int	cd_old(t_data *data)
{
	int		idx;
	char	*path;

	idx = get_index_var(data->envp, "OLDPWD");
	if (idx == -1)
		return (1);
	path = get_value(data->envp[idx]);
	if (!path)
		return (1);
	ft_chdir(data, path);
	fd_printf(1, "%s\n", data->pwd);
	free(path);
	return (0);
}

int	cd_home_append(t_data *data, char *path)
{
	char	*cd;
	char	*home;

	home = getenv("HOME");
	if (!home && !path)
		return (fd_printf(2, "minishell: cd: HOME not set\n"), 1);
	if (!path || (path[0] == '~' && !path[1]))
	{
		ft_chdir(data, home);
		return (0);
	}
	path++;
	cd = ft_strjoin(data->home, path);
	if (!cd)
		return (1);
	ft_chdir(data, cd);
	free(cd);
	return (0);
}

int	cd_point(t_data *data)
{
	char	*cwd;
	char	*cd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		fd_printf(1, "cd: error retrieving current directory: getcwd: cannot");
		fd_printf(1, "access parent directories: No such file or directory\n");
		cd = ft_strjoin(data->pwd, "/.");
		if (!cd)
			return (1);
		free(data->pwd);
		data->pwd = cd;
		update_oldpwd(data->envp, 0);
		update_pwd(data->envp, cd);
		update_oldpwd(data->exp, 1);
		update_pwd(data->exp, cd);
		return (0);
	}
	ft_chdir(data, data->pwd);
	free(cwd);
	return (0);
}

int	cd_path(t_data *data, char *path)
{
	int		idx_pwd;
	int		idx_old;
	char	**new_pwd;
	char	**new_old;

	idx_pwd = get_index_var(data->envp, "PWD");
	if (idx_pwd == -1 && get_index_var(data->exp, "PWD") != -1)
	{
		new_pwd = add_created_data(data->envp, "PWD=");
		if (!new_pwd)
			return (1);
		data->envp = new_pwd;
	}
	idx_old = get_index_var(data->envp, "OLDPWD");
	if (idx_old == -1 && get_index_var(data->exp, "OLDPWD") != -1)
	{
		new_old = add_created_data(data->envp, "OLDPWD=");
		if (!new_old)
			return (1);
		data->envp = new_old;
	}
	ft_chdir(data, path);
	return (0);
}
