#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_threejoin(char *str1, char *str2, char *str3)
{
	char	*join;
	int		len1;
	int		len2;
	int		len3;
	int		i;

	len1 = strlen(str1);
	len2 = strlen(str2);
	len3 = strlen(str3);
	if (!len1 && !len2 && !len3)
		return (NULL);
	join = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (++i < len1)
		join[i] = str1[i];
	i -= 1;
	while (++i < len1 + len2)
		join[i] = str2[i - len1];
	i -= 1;
	while (++i < len1 + len2 + len3)
		join[i] = str3[i - len1 - len2];
	join[i] = '\0';
	return (join);
}

static int	ft_length_num(int n)
{
	long int	l;

	l = 1;
	while (n >= 10)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*num;
	
	len = ft_length_num(n);
	num = calloc(len + 3, sizeof(char));
	if (!num)
		return (NULL);
	num[0] = '[';
	while (len > 0)
	{
		num[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	num[len + 2] = ']';
	return (num);
}

char *make_array(char **content, int size)
{
	char	*var;
	char 	*val;
	char	*value;
	char	*index;
	int		i;

	i = 0;
	size = 3;
	var = strdup("");
	while (i < size)
	{
		index = ft_itoa(i);
		value = ft_threejoin("\"", content[i], "\"");
		free(content[i]);
		val = ft_threejoin(index, "=", value);
		free(index);
		free(value);
		if (i)
			var = ft_threejoin(var, " ", val);
		else
			var = ft_threejoin(var, "", val);
		free(val);
		i++;
	}
	free(content);
	return (var);
}

char *get_content(char *var, int *idx)
{
	int		i;
	int		size;
	char	*value;
	
	i = *idx;
	size = 0;
	while (var[i] != ' ' && var[i] != ')')
	{
		i++;
		size++;
	}
	value = calloc(size + 1, sizeof(char));
	if (!value)
		return (NULL);
	i = 0;
	while (var[*idx] != ' ' && var[*idx] != ')')
	{
		value[i++] = var[*idx];
		(*idx)++;
	}
	return (value);
}

char *get_array(char *input, int size)
{
	char	**array;
	int		i;
	int		idx_arr;

	array = calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (input[i] != '(')
		i++;
	i++;
	idx_arr = 0;
	while (input[i] && input[i] != ')')
	{
		if (input[i] != ' ' && input[i] != '\t')
			array[idx_arr++] = get_content(input, &i);
		i++;
	}
	return (make_array(array, size));
}

int export_array(char *var)
{
	char	*var_array;
	char	*array;

	var_array = get_array(var, 3);
	array = ft_threejoin("x=(", var_array, ")");
	free(var_array);
	return (0);
}

int	main(int ac, char **av)
{
	char *array;
	
	array = strdup(av[1]);
	export_array(array);
	free(array);
}