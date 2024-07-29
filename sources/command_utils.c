/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:02:47 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/26 21:17:09 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/structs.h"
#include <unistd.h>

t_cmd	*add_command(t_cmd **cmd_lst)
{
	t_cmd	*command;

	command = ft_calloc(sizeof(t_cmd), 1);
	if (!command)
		return (NULL);
	lst_add_back(cmd_lst, command);
	command->fd_write = -1;
	command->fd_read = -1;
	command->fd_aux = -1;
	return (command);
}

char	*heredoc_read(char *word)
{
	char	*line;
	char	*text;
	char	*tmp;
	int		len;

	text = NULL;
	len = ft_strlen(word);
	while (1) {
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || (!ft_strncmp(line, word, len)
				&& line[len] == '\n' && line[len + 1] == '\0'))
			break ;
		tmp = ft_strjoin(text, line);
		free(text);
		free(line);
		if (!tmp)
			return (NULL);
		text = tmp;
	}
	free(line);
	return (text);
}
