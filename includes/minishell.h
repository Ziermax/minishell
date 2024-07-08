/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:29:04 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/08 17:21:54 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/errno.h>
# include "../Libft/includes/libft.h"
# include <signal.h>
# include <errno.h>
# include "structs.h"
# include "built.h"

void	minisheller(char *line);
t_token	*tokener(char *line);
int		init_data(t_data *data, char **envp);
int		ft_free(char ***s);
int		check_line(char *line);
/*	*
 *	Functions of Maxi
 */
t_token	*tokeinator(char *line, char **envp);
char	**get_cmd_split(t_token *token);
t_file	*get_files(t_token *token);
t_cmd	*get_command(t_token *token, t_data *data, char **path_split);
char	**split_path_env(char **envp);
int		executor(t_cmd *command, t_data	*data);
int		minishell(char *line, t_data *data);

#endif
