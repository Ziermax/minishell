/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:54:17 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/29 00:52:12 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"

void	execute_command(t_cmd *command, t_data *data)
{
	if (command->fd_write != -1)
		dup2(command->fd_write, STDOUT_FILENO);
	if (command->fd_read != -1)
		dup2(command->fd_read, STDIN_FILENO);
	close(command->fd_read);
	close(command->fd_write);
	close(command->fd_aux);
	if (command->failed)
		exit(1);
	if (command->subcommand)
		exit(executor(command->subcommand, data));
	if (!command->cmd_split)
		exit(0);
	if (ft_isbuilting(command->cmd_split[0]))
		execbuilt(command->cmd_split, data);
	execve(command->path, command->cmd_split, command->envp);
	error_command(command->cmd_split[0]);
	exit(0);
}

void	prepare_command(t_cmd *command, t_data *data)
{
	char	**path_split;

	command->envp = data->envp;
	if (!command->cmd_split)
		return ;
	path_split = split_path_env(data->envp);
	command->path = find_exec_path(command->cmd_split[0], path_split);
	free_split(path_split);
}

int	executor(t_cmd *command, t_data *data)
{
	t_executor	exdt;

	ft_bzero(&exdt, sizeof(t_executor));
	while (command)
	{
		prepare_command(command, data);
		exdt.num_of_cmd += 1;
		if (command->connection_type == PIPE)
		{
			pipe(exdt.pipe_end);
			command->fd_write = exdt.pipe_end[WR];
			command->fd_aux = exdt.pipe_end[RD];
			command->next->fd_read = exdt.pipe_end[RD];
		}
		manage_files(command);
		exdt.pid = fork();
		if (exdt.pid == -1)
			return (-1);
		if (!exdt.pid)
			execute_command(command, data);
		exdt.pids = add_integer(exdt.pids, exdt.num_of_cmd, exdt.pid);
		if (!exdt.pid)
			return (-1);
		close(command->fd_read);
		close(command->fd_write);
		if (command->connection_type == AND || command->connection_type == OR
			|| command->connection_type == NO_TYPE)
		{
			get_exit_status(&exdt);
			if (command->connection_type == AND && exdt.exit_status != 0)
				break ;
			if (command->connection_type == OR && exdt.exit_status == 0)
				break ;
		}
		command = command->next;
	}
	return (exdt.exit_status);
}
