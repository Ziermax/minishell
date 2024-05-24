/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:07:54 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/04/05 18:06:53 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int	fd_putchar(int fd, int c);
int	fd_putstr(int fd, char *str);
int	fd_printmem(int fd, unsigned long mem);
int	ft_lhexlen(unsigned long hex);
int	fd_printnbr(int fd, int nbr, int n);
int	fd_putnbr(int fd, int nbr);
int	ft_intlen(int nbr);
int	fd_putunbr(int fd, unsigned int nbr);
int	ft_untlen(unsigned int nbr);
int	fd_printhex(int fd, unsigned int hex, int x);
int	fd_puthex(int fd, unsigned int hex);
int	ft_hexlen(int hex);

#endif
