/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:54:17 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/12 17:35:23 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"

void	execute_command(t_cmd *command, t_data *data)
{
	if (command->failed)
		exit(command->failed);
	if (command->fd_write != -1)
		dup2(command->fd_write, STDOUT_FILENO);
	if (command->fd_read != -1)
		dup2(command->fd_read, STDIN_FILENO);
	close(command->fd_read);
	close(command->fd_write);
	close(command->fd_aux);
	if (command->subcommand)
		exit(executor(command->subcommand, data));
	if (!command->cmd_split)
		exit(0);
	if (ft_isbuilting(command->cmd_split[0]))
		exit(execbuilt(command->cmd_split, data));
	execve(command->path, command->cmd_split, command->envp);
	exit(error_command(command->cmd_split[0]));
}
/* || (command->connection_type != PIPE
			&& command->cmd_split && ft_isbuilting(command->cmd_split[0]))*/

void	prepare_command(t_cmd *command, t_data *data)
{
	char	**path_split;

	command->envp = data->envp;
	if (!command->cmd_split)
		return ;
	command->cmd_split = expand_split(command->cmd_split, data);
	if (!command->cmd_split || !command->cmd_split[0])
	{
		free_split(command->cmd_split);
		command->cmd_split = NULL;
		return ;
	}
	path_split = split_path_env(data->envp);
	command->path = find_exec_path(command->cmd_split[0], path_split);
	free_split(path_split);
	if (!command->path)
		return ;
}

void	execut_single_command(t_executor *exdt, t_cmd *command, t_data *data)
{
	int	save_rd;
	int	save_wr;

	if (command->cmd_split && ft_isbuilting(command->cmd_split[0]))
	{
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
		return ;
	}
	exdt->pid = fork();
	if (exdt->pid == 0)
		execute_command(command, data);
	exdt->pids = add_integer(exdt->pids, exdt->num_of_cmd, exdt->pid);
	if (!exdt->pids)
		return ;
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
		manage_files(command, data);
		if (command->connection_type == PIPE || exdt.num_of_cmd != 1)
		{
			exdt.pid = fork();
			if (exdt.pid == -1)
				return (-1);
			if (!exdt.pid)
				execute_command(command, data);
			exdt.pids = add_integer(exdt.pids, exdt.num_of_cmd, exdt.pid);
			if (!exdt.pids)
				return (-1);
		}
		else
			execut_single_command(&exdt, command, data);
		close(command->fd_read);
		close(command->fd_write);
		if (command->connection_type == AND || command->connection_type == OR
			|| command->connection_type == NO_TYPE)
		{
			get_exit_status(&exdt);
			if (command->connection_type == AND && exdt.exit_status != 0)
				command = command->next;
			if (command->connection_type == OR && exdt.exit_status == 0)
				command = command->next;
		}
		command = command->next;
	}
	data->exit_status = exdt.exit_status;
	return (exdt.exit_status);
}
	//printf("exit status: %d\n", data->exit_status);
