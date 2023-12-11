/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:20:54 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/11 18:01:49 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_2/minishell.h"
#include "../../../../include_2/main.h"
#include "../../../../include_2/lexer_utils.h"


int	exit_on_syntax_error(void)
{
	ft_fprintf(2, "minishell: Invalid Syntax at token\n");
	set_err_code(EXIT_SYNTAX_ERROR);
	ft_free_split(get_lex_toks());
	return (EXIT_SYNTAX_ERROR);
}

static bool	is_correct_subshell(char *line, int i)
{
	while (i > 0 && line[i] && ft_isspace(line[i]))
		i--;
	if (i >= 0 && (line[i] != '&' && line[i] != '|'))
		return (false);
	return (true);
}

static bool	has_opening_bracket(char *line, int i)
{
	while (i > 0 && line[i] && line[i] != '(')
		i--;
	if (i >= 0 && line[i] != '(')
		return (false);
	return (true);
}

static int	count_subshell_chars(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			while (line[++i] && line[i] != '\'')
				;
		if (line[i] == '\"')
			while (line[++i] && line[i] != '\"')
				;
		if (line[i] == c)
			count++;
		if (line[i])
			i++;
	}
	return (count);
}

bool	is_valid_line_syntax(char *line)
{
	int	i;

	i = 0;
	if (count_subshell_chars(line, '(') != count_subshell_chars(line, ')'))
		return (false);
	
	while (line[i])
	{
		if (line[i] == '\'')
			while (line[++i] && line[i] != '\'')
				;
		if (line[i] == '\"')
			while (line[++i] && line[i] != '\"')
				;
		if (line[i] == '(')
			if (!is_correct_subshell(line, i - 1))
				return (false);
		if (line[i] == ')')
			if (!has_opening_bracket(line, i - 1))
				return (false);
		if (line[i] == ';' || line[i] == '\\')
			return (false);
		if (line[i])
			i++;
	}
	return (true);
}

int	main()
{
	char	line[] = "echo Hello";
	char	c = 'l';
	int		i = 5;
	int		count;
	bool	res;

	count = count_subshell_chars(line, c);
	//res = has_opening_bracket(line, i);

	res = is_correct_subshell(line, c);
	printf("res = %d\n", res);
}

