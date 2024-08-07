/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:20:23 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/31 19:21:25 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/executor.h"

int	heredoc_case(char *content)
{
	int		pipe_doc[2];

	if (pipe(pipe_doc) == -1)
		return (-1);
	write(pipe_doc[1], content, ft_strlen(content));
	close(pipe_doc[1]);
	return (pipe_doc[0]);
}

int	open_file(char *file, t_type open_mode, int last_fd)
{
	int	o_flag;
	int	fd;

	close(last_fd);
	if (open_mode == R_OUT)
		o_flag = O_WRONLY | O_TRUNC | O_CREAT;
	else if (open_mode == APP)
		o_flag = O_WRONLY | O_APPEND | O_CREAT;
	else if (open_mode == R_IN)
		o_flag = O_RDONLY;
	if (open_mode != HDOC)
		fd = open(file, o_flag, 420);
	else
		fd = heredoc_case(file);
	if (fd == -1)
		return (-1);
	return (fd);
}
//	fd_printf(2, "opening: \"%s\" in %d ass: %s\n",
//		file, fd, get_type_str(open_mode));

void	manage_files(t_cmd *command)
{
	t_file	*file;

	file = command->files;
	while (file)
	{
		if (file->open_mode == R_OUT || file->open_mode == APP)
			command->fd_write = open_file(file->string, file->open_mode,
					command->fd_write);
		else if (file->open_mode == R_IN || file->open_mode == HDOC)
			command->fd_read = open_file(file->string, file->open_mode,
					command->fd_read);
		if (((file->open_mode == R_IN || file->open_mode == HDOC)
				&& command->fd_read == -1) || ((file->open_mode == R_OUT
					|| file->open_mode == APP) && command->fd_write == -1))
		{
			fd_printf(2, "minichell: %s: %s\n", file->string, strerror(errno));
			command->failed = 1;
			break ;
		}
		file = file->next;
	}
//	if (file)
//		file = file->next;
//	while (file)
//	{
//		if (file->open_mode == HDOC)
//			close(heredoc_case(file->string));
//		file = file->next;
//	}
}
