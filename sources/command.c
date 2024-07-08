/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 03:52:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/08 22:24:17 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"
#include <unistd.h>

t_cmd	*new_command_node(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->connection_type = 0;
	new->cmd_split = NULL;
	new->path = NULL;
	new->files = NULL;
	new->subcommand = NULL;
	new->fd_read = -1;
	new->fd_write = -1;
	new->fd_aux = -1;
	new->envp = NULL;
	return (new);
}

char	*heredoc_read(char *word)
{
	char	*line;
	char	*text;
	char	*tmp;
	int		len;

	text = ft_strdup("");
	if (!text)
		return (NULL);
	len = ft_strlen(word);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || (!ft_strncmp(line, word, len)
				&& line[len] == '\n' && line[len] != '\0'))
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

t_cmd	*get_command(t_token *token, t_data *denv, char **path_split) {
	t_cmd	*command;
	t_cmd	*aux;
	t_anal	data;
	void	*tmp;
	t_file	*file;

	command = NULL;
	ft_bzero(&data, sizeof(t_anal));
	while (token)
	{
		if (token->type >= AND && token->type <= PIPE)
		{
			aux->connection_type = token->type;
			data.content = false;
		}
		if (!data.content)
		{
			aux = new_command_node();
			if (!aux)
				return (lst_clear(&command, del_command), NULL);
			aux->envp = denv->env;
			lst_add_back(&command, aux);
			data.content = true;
		}
		if (token->type == CMD || token->type == ARG)
		{
			tmp = ft_strdup(token->string);
			if (!tmp)
				return (lst_clear(&command, del_command), NULL);
			aux->cmd_split = add_dir(aux->cmd_split, tmp);
			if (!aux->cmd_split)
				return (lst_clear(&command, del_command), free(tmp), NULL);
			if (token->type == CMD)
			{
				aux->path = find_exec_path(aux->cmd_split[0], path_split);
				if (!aux->path)
					return (lst_clear(&command, del_command), NULL);
			}
		}
		else if (data.last_type >= R_IN && data.last_type <= APP)
		{
			file = ft_calloc(sizeof(t_file), 1);
			if (!file)
				return (lst_clear(&command, del_command), NULL);
			lst_add_back(&aux->files, file);
			if (data.last_type != HDOC)
				file->string = ft_strdup(token->string);
			else
				file->string = heredoc_read(token->string);
			if (!file->string)
				return (lst_clear(&command, del_command), NULL);
			file->open_mode = data.last_type;
		}
		else if (token->type == O_PAR)
		{
			data.parenthesis += 1;
			aux->subcommand = token;
			token = token->next;
			while (token && data.parenthesis != 0)
			{
				if (token->type == O_PAR)
					data.parenthesis += 1;
				else if (token->type == C_PAR)
					data.parenthesis -= 1;
				token = token->next;
			}
			continue ;
		}
		data.last_type = token->type;
		token = token->next;
	}
	return (command);
}
//			data.last_type = token->type;
