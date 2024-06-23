/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange_tokens2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:15:52 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 02:49:54 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

void	del_file(void *file)
{
	free(((t_file *)file)->string);
}

void	print_file(void *file)
{
	t_file	*aux;

	aux = file;
	printf("FILE [%p]:\n", aux);
	printf("| file: \"%s\"\n", aux->string);
	if (aux->open_mode)
		printf("| mode: '%c'\n", aux->open_mode);
	else
		printf("| mode: %d\n", aux->open_mode);
	printf("| next: [%p]\n", aux->next);
}

t_file	*get_files(t_token *token)
{
	t_type	last_type;
	t_file	*files;
	t_file	*aux;

	if (!token)
		return (NULL);
	last_type = 0;
	files = NULL;
	while (token && (token->type < AND || token->type > C_PAR))
	{
		if (last_type >= R_IN && last_type <= APP)
		{
			aux = ft_calloc(sizeof(t_file), 1);
			if (!aux)
				return (lst_clear(&files, del_file), NULL);
			lst_add_back(&files, aux);
			aux->string = ft_strdup(token->string);
			if (!aux->string)
				return (lst_clear(&files, del_file), NULL);
			aux->open_mode = last_type;
		}
		last_type = token->type;
		token = token->next;
	}
	if (!files)
		files = (void *)-1;
	return (files);
}

char	**get_cmd_split(t_token *token)
{
	char	**cmd_split;
	char	*tmp;

	if (!token)
		return (NULL);
	cmd_split = NULL;
	while (token && (token->type == CMD || token->type == ARG))
	{
		tmp = ft_strdup(token->string);
		if (!tmp)
			return (free_split(cmd_split), NULL);
		cmd_split = add_dir(cmd_split, tmp);
		if (!cmd_split)
			return (free(tmp), NULL);
		token = token->next;
	}
	return (cmd_split);
}

void	print_command(void *command)
{
	t_cmd	*aux;

	aux = command;
	printf("COMMAND [%p]:\n", aux);
	printf("| connection: '%c'\n", aux->connection_type);
	printf("| cmd_split+\n/\n");
	ft_print_split(aux->cmd_split);
	printf("\\\n| end_cmd_split-\n");
	printf("| files+\n/\n");
	lst_for_each(aux->files, print_file);
	printf("\\\n| end files-\n");
	printf("| path: \"%s\"\n", aux->path);
	printf("| next: [%p]\n", aux->next);
}

void	del_command(void *command)
{
	t_cmd	*aux;

	if (!command)
		return ;
	aux = command;
	free_split(aux->cmd_split);
	free(aux->path);
	lst_clear(&aux->files, del_file);
}

t_cmd	*get_command(t_token *token, char	**path_split)
{
	t_cmd	*commands;

	commands = NULL;
	commands = ft_calloc(sizeof(t_cmd), 1);
	if (!commands)
		return (NULL);
	commands->cmd_split = get_cmd_split(token);
	if (!commands->cmd_split)
		return (lst_clear(&commands, del_command), NULL);
	commands->files = get_files(token);
	if (!commands->files)
		return (lst_clear(&commands, del_command), NULL);
	if (commands->files == (void *)-1)
		commands->files = NULL;
	commands->path = find_exec_path(commands->cmd_split[0], path_split);
	if (!commands->path)
		return (lst_clear(&commands, del_command), NULL);
	return (commands);
}
