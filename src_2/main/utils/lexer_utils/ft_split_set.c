/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:57:51 by mdiez-as          #+#    #+#             */
/*   Updated: 2024/01/06 17:05:25 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_2/minishell.h"
#include "../../../../include_2/main.h"
#include "../../../../include_2/lexer_utils.h"

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdlib.h>

/**************************************************/
static int	ft_isinstr(const char *s, const char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

static int	ft_getend(const char *s, const char *set, int end)
{
	while (ft_isinstr(set, s[end]) && end > 0)
		end--;
	return (end);
}

/* Trims the beginning and end of a string by characters included in the set */
char	*ft_strtrim(char const *s, char const *set)
{
	int		end;
	int		i;
	int		j;
	char	*trimmed;

	if (s == NULL || set == NULL)
		return (NULL);
	end = ft_getend(s, set, strlen(s) - 1);
	if (strlen(s) == 0 || end == 0)
		return (calloc(1, 1));
	i = 0;
	while (ft_isinstr(set, s[i]) && s[i])
		i++;
	trimmed = calloc(end - i + 2, sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	j = 0;
	while (i <= end && s[i])
	{
		trimmed[j] = s[i];
		i++;
		j++;
	}
	return (trimmed);
}
/**************************************************/
void	ft_free_str(char **str)
{
	free(*str);
	*str = NULL;
}


void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		ft_free_str(&split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static int	get_arr_len(char *str, char *set)
{
	char	*trimmed_str;
	int		arr_len;
	int		i;

	trimmed_str = ft_strtrim(str, set); //ft
	if (trimmed_str == NULL)
		return (-1);
	arr_len = 0;
	i = 0;
	if (strchr(set, trimmed_str[i]) == NULL) //ft
		arr_len++;
	while(trimmed_str[i])
	{
		if (strchr(set, trimmed_str[i]) != NULL) //ft
			arr_len++;
		i++;
	}
	free(trimmed_str);
	return (arr_len);
}

static size_t	get_element_size(char *str, char *set)
{
	size_t	size;

	size = 0;
	while (*str && strchr(set, *str) == NULL) //ft
	{
		size++;
		str++;
	}
	return (size);
}

char	**ft_split_set(char *str, char *set)
{
	char	**arr;
	int		arr_len;
	int		i;
	int		j;

	if (str == NULL || set == NULL)
		return (NULL);
	arr_len = get_arr_len(str, set);
	arr = calloc(arr_len + 1, sizeof(*arr)); //ft
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < arr_len && *str)
	{
		while (*str && strchr(set, *str) != NULL) //ft
			str++;
		arr[i] = calloc(get_element_size(str, set) + 1, sizeof(*arr[i])); //ft
		if (arr[i] == NULL)
			return (ft_free_split(arr));
		j = 0;
		while (*str && strchr(set, *str) == NULL) //ft
			arr[i][j++] = *str++;
		i++;
	}
	return (arr);
}


// int	main()
// {
// 	char	str[] = "Hoala Marta \n que yal";
// 	char	set[] = " \n";
// 	char	**split;

// 	split = ft_split_set(str, set);

// 	int	i = 0;
// 	int	j = 0;
// 	while (split[i][j] != '\0')
// 	{
// 		while (split[i][j] != '\0')
// 		{
// 			printf("%c", split[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		j = 0;
// 		i++;
// 	}
// }