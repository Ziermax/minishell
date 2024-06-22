/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:29:04 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/22 20:29:18 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/includes/libft.h"
# include "structs.h"
# include <stdio.h>

t_token	*tokeinator(char *line, char **envp);
void	del_token(void *token);
void	del_file(void *file);
void	del_command(void *command);
char	**get_cmd_split(t_token *token);
t_file	*get_files(t_token *token);
t_cmd	*get_command(t_token *token, char **path_split);
char	**split_path_env(char **envp);

#endif
