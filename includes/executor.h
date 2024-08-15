/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:11:35 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/14 20:48:59 by mvelazqu         ###   ########.fr       */
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

void	pipetion(t_cmd *command);
int		error_command(char *command);
void	get_exit_status(t_executor *executor_data, t_cmd **cmd);
int		ft_isbuilting(char *str);
void	execute_command(t_cmd *command, t_data *data);
int		execbuilt(char	**cmd_argv, t_data *data);
void	execut_single_built(t_executor *exdt, t_cmd *command, t_data *data);
void	execut_piped_command(t_cmd *command, t_data *data, t_executor *exdt);
void	manage_files(t_cmd *command, t_data *data);
int		executor(t_cmd *command, t_data *data);
char	**split_path_env(char **envp);
char	*find_exec_path(char *command, char **path_split);
char	**expand_string(char *string, void *data);
char	**expand_split(char **split_string, t_data *data);

#endif
