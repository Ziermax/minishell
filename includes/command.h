/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:12:27 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/12 17:57:46 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"

t_cmd	*add_command(t_cmd **cmd_lst);
t_cmd	*get_command(t_token *token, t_data *data);
char	*heredoc(char *word);
void	*heredoc_string(char *before, char *now, char *limiter);

#endif
