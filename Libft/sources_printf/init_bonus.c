/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:42:25 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/25 17:42:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

t_flag	init_struct(void)
{
	t_flag	f;

	f.length = 0;
	f.error = 0;
	return (f);
}

void	reset_flags(t_flag *f)
{
	f->width = 0;
	f->space = 0;
	f->minus= 0;
	f->alter = 0;
	f->zero = 0;
	f->aim = -1;
	f->sign = '0';
	f->type = '\0';
}
