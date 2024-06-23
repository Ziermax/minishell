/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 03:52:19 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 05:26:50 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

t_cmd	*get_command(t_token *token, char **path_split)
{
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
			aux = ft_calloc(sizeof(t_cmd), 1);
			if (!aux)
				return (lst_clear(&command, del_command), NULL);
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
			file->string = ft_strdup(token->string);
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
			//data.last_type = token->type;
			continue ;
		}
		data.last_type = token->type;
		token = token->next;
	}
	return (command);
}
