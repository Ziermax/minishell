/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:12:27 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/30 20:39:02 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"

t_cmd	*add_command(t_cmd **cmd_lst);
char	*heredoc_read(char *word);
t_cmd	*get_command(t_token *token, t_data *data);
void	*heredoc_string(char *before, char *now, char *limiter);

#endif
