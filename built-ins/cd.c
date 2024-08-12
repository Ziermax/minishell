/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:43:46 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/08/12 17:26:22 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include "../includes/built_utils.h"

int	update_oldpwd(char **data, int exp)
{
	int		idx_pwd;
	int		idx_old;
	char	*old;

	idx_pwd = get_index_var(data, "PWD");
	idx_old = get_index_var(data, "OLDPWD");
	if (idx_old == -1)
		return (1);
	else if (idx_pwd == -1 && !exp)
		old = ft_strdup("OLDPWD=");
	else if (idx_pwd == -1 && exp)
		old = ft_strdup("OLDPWD");
	else if (idx_pwd != -1)
		old = ft_strjoin("OLD", data[idx_pwd]);
	if (!old)
		return (1);
	free(data[idx_old]);
	data[idx_old] = old;
	return (0);
}

int	update_pwd(char **data, char *path)
{
	int		idx;
	char	*pwd;

	idx = get_index_var(data, "PWD");
	if (idx == -1)
		return (1);
	pwd = ft_strjoin("PWD=", path);
	if (!pwd)
		return (1);
	free(data[idx]);
	data[idx] = pwd;
	return (0);
}

int	ft_chdir(t_data *data, char *path)
{
	char	*pwd;
	int		error;

	if (chdir(path) == -1)
	{
		fd_printf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	delete_last_slash(pwd);
	free(data->pwd);
	data->pwd = pwd;
	error = 0;
	error += update_oldpwd(data->exp, 1);
	error += update_pwd(data->exp, pwd);
	error += update_oldpwd(data->envp, 0);
	error += update_pwd(data->envp, pwd);
	return (error);
}

static int	cd_action(char *str)
{
	if (!str)
		return (1);
	if (str[0] == '-' && !str[1])
		return (0);
	else if (str[0] == '-' && str[1])
	{
		fd_printf(2, "minishell: cd: %s: invalid option\n");
		fd_printf(2, "cd: options are not avaliable\n");
		return (-1);
	}
	else if (str[0] == '~')
		return (1);
	else if (str[0] == '.' && !str[1])
		return (2);
	return (3);
}

int	ft_cd(char **argv, t_data *data)
{
	int		action;

	argv++;
	if (ft_arraylen(argv) > 1)
		return (fd_printf(2, "minishell: cd: too many arguments\n"), 1);
	action = cd_action(*argv);
	if (action == -1)
		return (2);
	if (action == 0)
		return (cd_old(data));
	else if (action == 1)
		return (cd_home_append(data, *argv));
	else if (action == 2)
		return (cd_point(data));
	else if (action == 3)
		return (cd_path(data, *argv));
	return (1);
}
