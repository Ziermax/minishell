/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:28:05 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 03:03:09 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"
#include <stdio.h>

t_type	ft_istoken(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "&&", 2))
		return (AND);
	if (!ft_strncmp(str, "||", 2))
		return (OR);
	if (!ft_strncmp(str, "<<", 2))
		return (HDOC);
	if (!ft_strncmp(str, ">>", 2))
		return (APP);
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	if (!ft_strncmp(str, "(", 1))
		return (O_PAR);
	if (!ft_strncmp(str, ")", 1))
		return (C_PAR);
	if (!ft_strncmp(str, "<", 1))
		return (R_IN);
	if (!ft_strncmp(str, ">", 1))
		return (R_OUT);
	return (0);
}

void	del_token(void *token)
{
	t_token	*aux;

	aux = token;
	free(aux->string);
	free(aux->expanded);
}

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
}
