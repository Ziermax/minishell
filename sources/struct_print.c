/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 03:09:53 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/07/31 18:44:47 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

char	*get_type_str(t_type type)
{
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == PIPE)
		return ("PIPE");
	if (type == O_PAR)
		return ("OPEN_PARANTHESIS");
	if (type == C_PAR)
		return ("CLOSE_PARANTHESIS");
	if (type == R_IN)
		return ("RED_INFILE");
	if (type == R_OUT)
		return ("RED_OUTFILE");
	if (type == HDOC)
		return ("HEREDOC");
	if (type == APP)
		return ("APPEND");
	if (type == CMD)
		return ("COMMAND");
	if (type == ARG)
		return ("ARGUMENT");
	if (type == FILES)
		return ("FILES");
	return ("NO_TYPE");
}

void	print_file(void *file)
{
	t_file	*aux;

	if (!file)
		return ;
	aux = file;
	printf("FILE [%p]:\n", aux);
	if (aux->open_mode != HDOC)
		printf("| file: \"%s\"\n", aux->string);
	printf("| mode: %s\n", get_type_str(aux->open_mode));
	printf("| next: [%p]\n", aux->next);
	if (aux->next)
		printf("|\n");
}

void	print_command(void *command)
{
	static int	i = 1;
	t_cmd		*aux;

	if (!command)
		return ;
	aux = command;
	printf("%d. COMMAND [%p]:\n", i++, aux);
	printf(" | path: %s\n", aux->path);
	printf(" | cmd_split:\n /\n");
	print_split(aux->cmd_split);
	printf(" \\ end_cmd_split-\n |\n");
	printf(" | files:\n /\n");
	lst_for_each(aux->files, print_file);
	printf(" \\ end files-\n |\n");
	printf(" | subcommand: [%p]\n", aux->subcommand);
	if (aux->subcommand)
	{
		printf(" | subcommand:\n /\n");
		//lst_for_each(aux->subcommand, print_command);
		printf(" \\ end subcommand-\n |\n");
	}
	printf(" | connection: '%s'\n", get_type_str(aux->connection_type));
	printf(" | read_from: %d\n | write_to %d\n", aux->fd_read, aux->fd_write);
	printf(" | next: [%p]\n", aux->next);
	if (aux->next)
		printf(" |-----------------------\n |-----------------------\n");
	else
	{
		printf("\n");
		i = 1;
	}
}

void	print_token(void *token)
{
	t_token	*aux;

	if (!token)
		return ;
	aux = token;
	printf("TOKEN [%p]:\n", aux);
	printf("| string: _%s_\n", aux->string);
	printf("| expanded: _%s_\n", aux->expanded);
	printf("| type: %s\n", get_type_str(aux->type));
	printf("| next: [%p]\n", aux->next);
	if (aux->next)
		printf("|\n");
	else
		printf("\n");
}
