/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:04:12 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/15 20:06:31 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/command.h"

static void	set_subcommand(t_cmd **cmd_lst, t_anal *info,
	t_token **tkn_p, t_data *data)
{
	t_token	*token;

	if (!info->aux)
		info->aux = add_command(cmd_lst);
	if (!info->aux)
		return (lst_clear(cmd_lst, del_command));
	token = *tkn_p;
	info->aux->subcommand = get_command(token->next, data);
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

static void	set_file(t_cmd **cmd_lst, t_anal *info,
	t_token **tkn_p, t_data *data)
{
	t_file	*file;

	if (!info->aux)
		info->aux = add_command(cmd_lst);
	if (!info->aux)
		return (lst_clear(cmd_lst, del_command));
	file = ft_calloc(sizeof(t_file), 1);
	if (!file)
		return (lst_clear(cmd_lst, del_command));
	file->open_mode = (*tkn_p)->type;
	lst_add_back(&(info->aux->files), file);
	if (file->open_mode != HDOC)
		file->string = ft_strdup((*tkn_p)->next->string);
	else
		file->string = heredoc((*tkn_p)->next->string);
	if (!file->string)
		return (lst_clear(cmd_lst, del_command));
	*tkn_p = (*tkn_p)->next;
	if (file->open_mode != HDOC)
		return ;
	file = heredoc_string(data->heredoc, file->string, (*tkn_p)->string);
	if (!file)
		return (lst_clear(cmd_lst, del_command));
	free(data->heredoc);
	data->heredoc = (char *)file;
}

static void	set_command(t_cmd **cmd_lst, t_anal *info, t_token *token)
{
	char	*tmp;

	if (!info->aux)
		info->aux = add_command(cmd_lst);
	if (!info->aux)
		return (lst_clear(cmd_lst, del_command));
	tmp = ft_strdup(token->string);
	if (!tmp)
		return (lst_clear(cmd_lst, del_command));
	info->aux->cmd_split = add_dir(info->aux->cmd_split, tmp);
	if (!info->aux->cmd_split)
		return (lst_clear(cmd_lst, del_command), free(tmp));
}

static void	set_conection(t_anal *info, t_token *token)
{
	if (info->aux)
		info->aux->connection_type = token->type;
	info->aux = NULL;
}

t_cmd	*get_command(t_token *token, t_data *data)
{
	t_cmd	*command;
	t_anal	info;

	command = NULL;
	ft_bzero(&info, sizeof(t_anal));
	while (token)
	{
		if (token->type == AND || token->type == OR || token->type == PIPE)
			set_conection(&info, token);
		else if (token->type == CMD || token->type == ARG)
			set_command(&command, &info, token);
		else if (token->type >= R_IN && token->type <= APP)
			set_file(&command, &info, &token, data);
		else if (token->type == O_PAR)
			set_subcommand(&command, &info, &token, data);
		if (token)
			token = token->next;
		if (!command || (token && token->type == C_PAR))
			break ;
	}
	return (command);
}
