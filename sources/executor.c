/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:54:17 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/20 16:50:58 by mvelazqu         ###   ########.fr       */
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
	if (!path_split)
		return ;
	command->path = find_exec_path(command->cmd_split[0], path_split);
	free_split(path_split);
	if (!command->path)
		return ;
}

void	execut_single_command(t_executor *exdt, t_cmd *command, t_data *data)
{
	if (command->failed)
	{
		exdt->exit_status = command->failed;
		exdt->num_of_cmd = 0;
		return ;
	}
	if (command->cmd_split && ft_isbuilting(command->cmd_split[0]))
		return (execut_single_built(exdt, command, data));
	exdt->pid = fork();
	if (exdt->pid == -1)
	{
		data->end = 1;
		return ;
	}
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
	while (command && !data->end)
	{
		prepare_command(command, data);
		exdt.num_of_cmd += 1;
		if (command->connection_type == PIPE)
			pipetion(command);
		manage_files(command, data);
		if (command->connection_type == PIPE || exdt.num_of_cmd != 1)
			execut_piped_command(command, data, &exdt);
		else
			execut_single_command(&exdt, command, data);
		close(command->fd_read);
		close(command->fd_write);
		if (command->connection_type == AND || command->connection_type == OR
			|| command->connection_type == NO_TYPE)
			get_exit_status(&exdt, &command);
		data->exit_status = exdt.exit_status;
		if (command)
			command = command->next;
	}
	return (exdt.exit_status);
}
