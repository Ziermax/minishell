/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:14:45 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/14 21:26:17 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	assing_type(char *string, int last_type)
{
	static bool	is_cmd;

	if (!string)
		return (0);
	if (ft_istoken(string[0]) || (string[0] == '&' && string[1] == '&'))
	{
		if (string[0] == '(' || string[0] == ')'
			|| string[0] == '&' || string[0] == '|')
			is_cmd = false;
		return (string[0]);
	}
	if (last_type == '>' || last_type == '<')
		return ('f');
	if (!is_cmd)
	{
		is_cmd = 1;
		return ('c');
	}
	if (is_cmd)
		return ('a');
	return (0);
}

static bool	error_syntax(int last_type, int current_type)
{
	static bool	is_cmd;
	static bool	content;
	static int	parenthesis;

	if ((is_cmd && (current_type == 'c' || current_type == '('))
		|| (!content && (current_type == '&' || current_type == '|'
				|| current_type == ')'))
		|| ((last_type == '<' || last_type == '>') && current_type != 'f'))
		return (true);
	if (current_type == '(')
		parenthesis += 1;
	else if (current_type == ')')
		parenthesis -= 1;
	if (current_type == 'c' || current_type == ')')
		is_cmd = true;
	else if (current_type == '&' || current_type == '|')
	{
		is_cmd = false;
		content = false;
	}
	if (current_type == '>' || current_type == 'c')
		content = true;
	return (parenthesis < 0
		|| ((last_type == '<' || last_type == '>') && current_type != 'f'));
}

bool	analize_tokens(t_token *token)
{
	int	last_type;

	last_type = 0;
	while (token)
	{
		token->type = assing_type(token->string, last_type);
		if (error_syntax(last_type, token->type))
			break ;
		last_type = token->type;
		token = token->next;
	}
	if (token || (last_type != 'f' && last_type != 'a'
			&& last_type != 'c' && last_type != ')'))
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
