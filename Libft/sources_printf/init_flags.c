/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:07 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/27 15:29:17 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

t_flag	init_struct(void)
{
	t_flag	f;

	f.length = 0;
	f.error = 0;
	return (f);
}

void	reset_flags(t_flag *flag)
{
	flag->width = 0;
	flag->space = 0;
	flag->minus = 0;
	flag->alter = 0;
	flag->zero = 0;
	flag->aim = -1;
	flag->sign = '0';
	flag->type = '\0';
}
