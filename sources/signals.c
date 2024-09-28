/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:59:16 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/09/28 14:02:05 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"
#include "../Libft/includes/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	normal_sig(int sig)
{
	if (sig == SIGINT)
	{
		fd_printf(1, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	cmd_sig(int sig)
{
	if (sig == SIGINT)
	{
		fd_printf(1, "\n");
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	doc_sig(int sig)
{
	if (sig == SIGINT)
	{
		fd_printf(1, "\n");
		g_exit_status = 130;
	}
}

void	quit_sig(int sig)
{
	if (sig == SIGQUIT)
	{
		fd_printf(2, "Quit (core dumped)\n");
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 131;
	}
}
