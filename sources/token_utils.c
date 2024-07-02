/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:28:05 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/23 03:20:19 by mvelazqu         ###   ########.fr       */
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
