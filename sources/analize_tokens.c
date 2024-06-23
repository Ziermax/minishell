/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:14:45 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 03:02:30 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

/*static t_type	select_type(char *type)
{
	if (!ft_strncmp(type, "&&", 2))
		return (AND);
	if (!ft_strncmp(type, "||", 2))
		return (OR);
	if (!ft_strncmp(type, "|", 1))
		return (PIPE);
	if (!ft_strncmp(type, "<", 1))
		return (R_IN);
	if (!ft_strncmp(type, ">", 1))
		return (R_OUT);
	if (!ft_strncmp(type, "<<", 2))
		return (HDOC);
	if (!ft_strncmp(type, ">>", 2))
		return (APP);
	return (0);
}*/

static t_type	assing_type(char *string, t_anal *anal)
{
	t_type	type;

	if (!string)
		return (0);
	type = ft_istoken(string);
	if (type)
	{
		if (type >= AND && type <= C_PAR)
			anal->is_cmd_assign = false;
		return (type);
	}
	if (anal->last_type >= R_IN && anal->last_type <= APP)
		return (FILES);
	if (anal->is_cmd_assign)
		return (ARG);
	else
	{
		anal->is_cmd_assign = true;
		return (CMD);
	}
}

static bool	error_syntax(t_anal *anal, t_type current_type)
{
	if ((anal->is_cmd_syntax && (current_type == CMD || current_type == O_PAR))
		|| (!anal->content && ((current_type >= AND && current_type <= PIPE)
				|| current_type == C_PAR))
		|| ((anal->last_type >= R_IN && anal->last_type <= APP)
			&& current_type != FILES))
		return (true);
	if (current_type == O_PAR)
		anal->parenthesis += 1;
	else if (current_type == C_PAR)
		anal->parenthesis -= 1;
	if (current_type == CMD || current_type == C_PAR)
		anal->is_cmd_syntax = true;
	else if (current_type >= AND && current_type <= PIPE)
	{
		anal->is_cmd_syntax = false;
		anal->content = false;
	}
	if (current_type == R_OUT || current_type == CMD)
		anal->content = true;
	return (anal->parenthesis < 0);
}
/*	if ((anal->is_cmd_syntax && (current_type == 'c' || current_type == '('))
		|| (!anal->content && (current_type == '&' || current_type == '|'
				|| current_type == ')'))
		|| ((anal->last_type == '<' || anal->last_type == '>')
			&& current_type != 'f'))
		return (true);
	if (current_type == '(')
		anal->parenthesis += 1;
	else if (current_type == ')')
		anal->parenthesis -= 1;
	if (current_type == 'c' || current_type == ')')
		anal->is_cmd_syntax = 1;
	else if (current_type == '&' || current_type == '|')
	{
		anal->is_cmd_syntax = false;
		anal->content = false;
	}
	if (current_type == '>' || current_type == 'c')
		anal->content = 1;
	return (anal->parenthesis < 0 || (current_type != 'f'
			&& (anal->last_type == '<' || anal->last_type == '>')));*/

bool	analize_tokens(t_token *token)
{
	t_anal	anal_data;

	ft_bzero(&anal_data, sizeof(t_anal));
	while (token)
	{
		token->type = assing_type(token->string, &anal_data);
		if (error_syntax(&anal_data, token->type))
			break ;
		anal_data.last_type = token->type;
		token = token->next;
	}
	if (token || ((anal_data.last_type < CMD || anal_data.last_type > FILES)
			&& anal_data.last_type != C_PAR))
	{
		if (token)
			fd_printf(2, "minichel: syntax error near unexpected token '%s'\n",
				token->string);
		else
			fd_printf(2,
				"minichel: syntax error near unexpected token 'new line'\n");
		return (false);
	}
	return (true);
}
//	void	*head;
//	head = token;
//	lst_for_each(head, print_token);
