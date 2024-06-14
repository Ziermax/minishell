/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:52:40 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/06/14 21:13:34 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*	line: ">hola cat|ls -l>out&&$USER'<NOTOKEN$NOUSERninada'"
 *	sep: "> hola cat | ls -l > out && $USER '<NOTOKEN$NOUSERninada' "	*/
t_token	*minisheller(char *line, char **envp)
{
	t_token	*tokens;

	tokens = tokener(line);
	if (!tokens)
		return (NULL);
	printf("####TOKENS DONE#####\n");
	print_tokens(tokens);
	if (!analize_tokens(tokens))
		return (free_tokens(&tokens), NULL);
	printf("\n###AnalizeDone###\n");
	print_tokens(tokens);
	clean_tokens(&tokens, envp);
	printf("\n###CLEANING DONE###\n");
	print_tokens(tokens);
	free_tokens(&tokens);
	printf("OKKKEY\n");
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token	*tokens;

	argc = argc;
	argv = argv;
	str = "h>>out<<in||hola&&hola&&&hola&& hola((hola))";
	printf("str:\n%s\n\n", str);
	if (argc == 1)
		tokens = minisheller(str, envp);
	else
		tokens = minisheller(argv[1], envp);
	print_tokens(tokens);
	free_tokens(&tokens);
}
	//str = "\"$TEST\"'$PATH' $USER$TEST $USER\"hola\"";
	//str = "    $HOLS";
