/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:18:51 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/14 20:45:44 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/built.h"
#include "../includes/executor.h"

int	ft_isbuilting(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "echo", 5))
		return (ECHO);
	if (!ft_strncmp(str, "unset", 6))
		return (UNSET);
	if (!ft_strncmp(str, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(str, "env", 4))
		return (ENV);
	if (!ft_strncmp(str, "cd", 3))
		return (CD);
	if (!ft_strncmp(str, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(str, "exit", 6))
		return (EXIT);
	return (0);
}

int	execbuilt(char	**cmd_argv, t_data *data)
{
	int	cmd_flag;
	int	ret;

	cmd_flag = ft_isbuilting(cmd_argv[0]);
	if (cmd_flag == ECHO)
		ret = ft_echo(cmd_argv, data);
	else if (cmd_flag == UNSET)
		ret = ft_unset(cmd_argv, data);
	else if (cmd_flag == EXPORT)
		ret = ft_export(cmd_argv, data);
	else if (cmd_flag == ENV)
		ret = ft_env(cmd_argv, data);
	else if (cmd_flag == CD)
		ret = ft_cd(cmd_argv, data);
	else if (cmd_flag == PWD)
		ret = ft_pwd(cmd_argv, data);
	else if (cmd_flag == EXIT)
		ret = ft_exit(cmd_argv, data);
	return (ret);
}

void	execut_single_built(t_executor *exdt, t_cmd *command, t_data *data)
{
	int	save_rd;
	int	save_wr;

	save_rd = dup(STDIN_FILENO);
	if (save_rd == -1)
		return ;
	save_wr = dup(STDOUT_FILENO);
	if (save_wr == -1)
		return ;
	if (command->fd_write != -1)
		dup2(command->fd_write, STDOUT_FILENO);
	if (command->fd_read != -1)
		dup2(command->fd_read, STDIN_FILENO);
	exdt->exit_status = execbuilt(command->cmd_split, data);
	dup2(save_rd, STDIN_FILENO);
	dup2(save_wr, STDOUT_FILENO);
	close(save_wr);
	close(save_rd);
	exdt->num_of_cmd = 0;
}
