/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:54:17 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/29 14:06:09 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"

void	execute_command(t_cmd *command, t_data *data)
{
	if (command->failed || (command->connection_type != PIPE
			&& command->cmd_split && ft_isbuilting(command->cmd_split[0])))
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

void	execut_single_command(t_executor *exdt, t_cmd *command, t_data *data)
{
	int	pid;
	int	save_rd;
	int	save_wr;

	//printf("Execution Single Command\n");
	if (command->cmd_split && ft_isbuilting(command->cmd_split[0]))
	{
		//printf("BUILT Single Command\n");
		save_rd = open("/dev/stdin", O_RDONLY);
		if (save_rd == -1)
			return ;
		save_wr = open("/dev/stdout", O_WRONLY);
		if (save_wr == -1)
			return ;
		if (command->fd_write != -1)
			dup2(command->fd_write, STDOUT_FILENO);
		if (command->fd_read != -1)
			dup2(command->fd_read, STDIN_FILENO);
		command->failed = execbuilt(command->cmd_split, data);
		dup2(save_rd, STDIN_FILENO);
		dup2(save_wr, STDOUT_FILENO);
		close(save_wr);
		close(save_rd);
	}
	pid = fork();
	if (pid == 0)
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
		manage_files(command);
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
				break ;
			if (command->connection_type == OR && exdt.exit_status == 0)
				break ;
		}
		command = command->next;
	}
	data->exit_status = exdt.exit_status;
	//printf("exit status: %d\n", data->exit_status);
	return (exdt.exit_status);
}
