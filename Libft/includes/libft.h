/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:01:12 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/21 13:51:34 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

# define STR_START 1
# define STR_ANY 2
# define STR_END 4

/*	string functions	*/
int		ft_strcmp(char *str1, char *str2);
int		ft_strlcat(char *dst, char *src, int dstsize);
int		ft_strfcat(char *dst, char *src, int dstsize, int from);
/*	length	functions	*/
int		ft_intlen(int nbr);
int		ft_splitlen(char **split);
int		ft_strlen(char *str);
/*	mallocers functions	*/
void	*ft_calloc(int count, int size);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *str1, char *str2);
char	*ft_threejoin(char *str1, char *str2, char *str3);
char	*ft_splitjoin(char **split);
/*	search functions	*/
char	*search_word_relative(char *word, char *str, int flag);
char	*search_word_in_str(char *word, char *str);
char	*search_word_in_split(char *word, char **split);
int		search_char(const char c, const char *set);
/*	is_identifiers functions	*/
int		ft_isdigit(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isspace(int c);
int		ft_isprint(int c);
int		ft_isacsii(int c);
/*	split functions	*/
void	free_split(char **split);
void	free_split_save(char **split, char *save);
char	*skip_spaces(char *str);
char	**ultra_split(char *str, char *(*skip)(char *), char *(*next)(char *));
char	**ft_split(char *str);
/*	extra functions	*/
int		fd_printf(int fd, const char *str, ...);
void	error_printf(int error, char *str, ...);
char	*get_next_line(int fd);

#endif
