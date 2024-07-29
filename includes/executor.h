/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:11:35 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/29 04:38:26 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>
# include "structs.h"

# define RD 0
# define WR 1

void	error_command(char *command);
void	get_exit_status(t_executor *executor_data);
int		ft_isbuilting(char *str);
int		execbuilt(char	**cmd_argv, t_data *data);
void	manage_files(t_cmd *command);
int		executor(t_cmd *command, t_data *data);
char	**split_path_env(char **envp);
char	*find_exec_path(char *command, char **path_split);

#endif
