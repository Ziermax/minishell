/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:29:04 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/29 03:22:53 by mvelazqu         ###   ########.fr       */
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

int		init_data(t_data *data, char **envp);
int		check_line(char *line);
/*	*
 *	Functions of Maxi
 */
t_token	*tokeinator(char *line, char **envp);
int		minishell(char *line, t_data *data);
t_cmd	*get_command(t_token *token, t_data *data);

#endif
