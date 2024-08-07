/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 03:23:48 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/31 18:44:42 by mvelazqu         ###   ########.fr       */
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
