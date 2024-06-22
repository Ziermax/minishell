/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:14:45 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/22 22:06:46 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/token.h"

static void	init_anal(t_anal *anal_data)
{
	anal_data->last_type = 0;
	anal_data->is_cmd_assign = 0;
	anal_data->is_cmd_syntax = 0;
	anal_data->content = 0;
	anal_data->parenthesis = 0;
}

static int	assing_type(char *string, t_anal *anal)
{
	if (!string)
		return (0);
	if (ft_istoken(string[0]) || (string[0] == '&' && string[1] == '&'))
	{
		if (string[0] == '(' || string[0] == ')'
			|| string[0] == '&' || string[0] == '|')
			anal->is_cmd_assign = false;
		return (string[0]);
	}
	if (anal->last_type == '>' || anal->last_type == '<')
		return ('f');
	if (!anal->is_cmd_assign)
	{
		anal->is_cmd_assign = 1;
		return ('c');
	}
	if (anal->is_cmd_assign)
		return ('a');
	return (0);
}

static bool	error_syntax(t_anal *anal, int current_type)
{
	if ((anal->is_cmd_syntax && (current_type == 'c' || current_type == '('))
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
			&& (anal->last_type == '<' || anal->last_type == '>')));
}

//t_token	*head;
//head = token;
//print_tokens(head);//Borrar printf
bool	analize_tokens(t_token *token)
{
	t_anal	anal_data;

	init_anal(&anal_data);
	while (token)
	{
		token->type = assing_type(token->string, &anal_data);
		if (error_syntax(&anal_data, token->type))
			break ;
		anal_data.last_type = token->type;
		token = token->next;
	}
	if (token || (anal_data.last_type != 'f' && anal_data.last_type != 'a'
			&& anal_data.last_type != 'c' && anal_data.last_type != ')'))
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
