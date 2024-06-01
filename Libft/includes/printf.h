/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:23:46 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/06/01 13:06:22 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# define NUMBR "0123456789abcdef"

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_flag
{
	int		fd;
	int		length;
	int		error;
	int		space;
	int		minus;
	int		alter;
	int		zero;
	int		width;
	int		aim;
	char	sign;
	char	type;
}	t_flag;

int		fd_printf(int fd, char const *s, ...);
void	ft_di(int n, t_flag *flag);
void	ft_u(unsigned int n, t_flag *flag);
void	ft_dir(unsigned long p, t_flag *flag);
void	ft_xx(unsigned int n, t_flag *flag);

void	ft_putnbr(unsigned long n, unsigned long base, t_flag *flag);
void	ft_putchar(char c, t_flag *flag);
void	ft_putchar_flag(char c, t_flag *flag);
void	ft_putstr(char *s, t_flag *flag);
void	ft_putstr_flag(char *s, t_flag *flag);

t_flag	init_struct(void);
void	reset_flags(t_flag *flag);
void	get_flags(char **s, t_flag *flag);

void	ft_add_width(t_flag *flag, int len, char c);
char	*ft_put_flags(char *s, t_flag *flag);

#endif
