/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 03:23:48 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/26 19:01:24 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"
#include "../Libft/includes/libft.h"

void	del_file(void *file)
{
	free(((t_file *)file)->string);
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
	lst_clear(&aux->subcommand, del_command);
}

void	del_token(void *token)
{
	t_token	*aux;

	aux = token;
	free(aux->string);
	free(aux->expanded);
}

void	del_data(t_data *data)
{
	if (data->envp)
		free_split(data->envp);
	if (data->exp)
		free_split(data->exp);
	if (data->pwd)
		free(data->pwd);
	if (data->home)
		free(data->home);
	if (data->heredoc)
		free(data->heredoc);
}
