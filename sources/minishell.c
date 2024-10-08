/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:52:40 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/09/28 13:51:23 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/executor.h"

/*	line: ">hola cat|ls -l>out&&$USER'<NOTOKEN$NOUSERninada'"
 *	sep: "> hola cat | ls -l > out && $USER '<NOTOKEN$NOUSERninada' "	*/
int	minishell(char *line, t_data *data)
{
	t_token	*tokens;
	t_cmd	*commands;

	tokens = tokeinator(line, data->envp);
	if (!tokens)
	{
		data->exit_status = 2;
		return (-1);
	}
	commands = get_command(tokens, data);
	lst_clear(&tokens, del_token);
	if (!commands)
		return (-1);
	executor(commands, data);
	lst_clear(&commands, del_command);
	return (0);
}
