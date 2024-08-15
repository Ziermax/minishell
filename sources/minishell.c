/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:52:40 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/08/15 20:10:52 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/token.h"
#include "../includes/executor.h"
#include "../includes/signals.h"

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
	signal(SIGINT, cmd_sig);
	executor(commands, data);
	lst_clear(&commands, del_command);
	signal(SIGINT, normal_sig);
	return (0);
}
