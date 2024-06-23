/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 03:09:53 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 05:21:49 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

static char	*get_type_str(t_type type)
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

	aux = file;
	printf("FILE [%p]:\n", aux);
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

	aux = command;
	printf("%d. COMMAND [%p]:\n", i++, aux);
	printf(" | cmd_split:\n /\n");
	ft_print_split(aux->cmd_split);
	printf(" \\ end_cmd_split-\n |\n");
	printf(" | files:\n /\n");
	lst_for_each(aux->files, print_file);
	printf(" \\ end files-\n |\n");
	printf(" | path: %s\n", aux->path);
	printf(" | subcommand: [%p]\n", aux->subcommand);
	printf(" | connection: '%s'\n", get_type_str(aux->connection_type));
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
