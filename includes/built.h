/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:48:29 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/07/08 19:18:24 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include "structs.h"

int	ft_echo(char **argv, t_data *data);
int	ft_cd(char **argv, t_data *data);
int	ft_pwd(char **argv, t_data *data);
int	ft_export(char **argv, t_data *data);
int	ft_unset(char **argv, t_data *data);
int	ft_env(char **argv, t_data *data);
int	ft_exit(char **argv, t_data *data);

#endif
