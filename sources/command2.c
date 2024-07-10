/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:39:43 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/09 11:07:43 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"
#include <unistd.h>

t_cmd	*get_command2(t_token *token, t_data *data, char **path_split);

t_cmd	*add_command(t_cmd **cmd_lst, char **envp)
{
	t_cmd	*command;

	command = ft_calloc(sizeof(t_cmd), 1);
	if (!command)
		return (NULL);
	command->envp = envp;
	lst_add_back(cmd_lst, command);
	command->fd_write = -1;
	command->fd_read = -1;
	command->fd_aux = -1;
	return (command);
}

char	*heredoc_read2(char *word)
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

void	set_conection(t_cmd **cmd_lst, t_anal *info, t_token *token)
{
	if (info->aux)
		info->aux->connection_type = token->type;
	info->aux = NULL;
	cmd_lst = cmd_lst;
}

void	set_command(t_cmd **cmd_lst, t_anal *info, t_token *token, t_data *data)
{
	char	*tmp;

	if (!info->aux)
		info->aux = add_command(cmd_lst, data->env);
	if (!info->aux)
		return (lst_clear(cmd_lst, del_command));
	tmp = ft_strdup(token->string);
	if (!tmp)
		return (lst_clear(cmd_lst, del_command));
	info->aux->cmd_split = add_dir(info->aux->cmd_split, tmp);
	if (!info->aux->cmd_split)
		return (lst_clear(cmd_lst, del_command), free(tmp));
	if (token->type == CMD)
		info->aux->path = find_exec_path(info->aux->cmd_split[0],
				info->path_split);
	if (!info->aux->path)
		return (lst_clear(cmd_lst, del_command));
}

void	set_file(t_cmd **cmd_lst, t_anal *info, t_token **tkn_p, t_data *data)
{
	t_file	*file;

	if (!info->aux)
		info->aux = add_command(cmd_lst, data->env);
	if (!info->aux)
		return (lst_clear(cmd_lst, del_command));
	file = ft_calloc(sizeof(t_file), 1);
	if (!file)
		return (lst_clear(cmd_lst, del_command));
	file->open_mode = (*tkn_p)->type;
	lst_add_back(&(info->aux->files), file);
	if ((*tkn_p)->type != HDOC)
		file->string = ft_strdup((*tkn_p)->next->string);
	else
	{
		file->string = heredoc_read2((*tkn_p)->next->string);
	}
	if (!file->string)
		return (lst_clear(cmd_lst, del_command));
	if ((*tkn_p)->type == HDOC)
		swap_strings(&data->heredoc, ft_strjoin(data->heredoc, file->string));
	*tkn_p = (*tkn_p)->next;
}

void	set_subcommand(t_cmd **cmd_lst, t_anal *info,
	t_token **tkn_p, t_data *data)
{
	t_token	*token;

	if (!info->aux)
		info->aux = add_command(cmd_lst, data->env);
	if (!info->aux)
		return (lst_clear(cmd_lst, del_command));
	token = *tkn_p;
	info->aux->subcommand = get_command2(token->next, data, info->path_split);
	if (!info->aux->subcommand)
		return (lst_clear(cmd_lst, del_command));
	info->parenthesis = 1;
	while (token && info->parenthesis)
	{
		token = token->next;
		if (!token)
			break ;
		if (token->type == O_PAR)
			info->parenthesis += 1;
		else if (token->type == C_PAR)
			info->parenthesis -= 1;
	}
	*tkn_p = token;
}

t_cmd	*get_command2(t_token *token, t_data *data, char **path_split)
{
	t_cmd	*command;
	t_anal	info;

	command = NULL;
	ft_bzero(&info, sizeof(t_anal));
	info.path_split = path_split;
	while (token)
	{
		if (token->type >= AND && token->type <= PIPE)
			set_conection(&command, &info, token);
		else if (token->type == CMD || token->type == ARG)
			set_command(&command, &info, token, data);
		else if (token->type >= R_IN && token->type <= APP)
			set_file(&command, &info, &token, data);
		else if (token->type == O_PAR)
			set_subcommand(&command, &info, &token, data);
		if (token)
			token = token->next;
		if (!command || (token && token->type == C_PAR))
			break;
	}
	return (command);
}
