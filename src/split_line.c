/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 13:03:31 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:54:36 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sh_split_line(char **line)
{
	int		bufsize;
	char	**tokens;
	int		flag;
	char	*end;

	bufsize = LSH_TOK_BUFSIZE;
	flag = 0;
	tokens = (char **)malloc(bufsize * sizeof(char *));
	flag = ft_str_parser(*line, &end);
	ft_split(line, end, tokens, bufsize);
	if (flag == 1)
		(*line)++;
	return (tokens);
}

void	ft_split(char **line, char *end, char **tokens, int bufsize)
{
	int position;

	position = 0;
	while (*line < end)
	{
		if (**line != '\0')
		{
			tokens[position++] = *line;
			*line += ft_strcspn(*line, "\0");
		}
		else
			(*line)++;
		if (position >= bufsize)
		{
			bufsize += LSH_TOK_BUFSIZE;
			tokens = (char **)ft_realloc(tokens, bufsize * sizeof(char *));
		}
	}
	tokens[position] = NULL;
}

int		ft_str_parser(char *line, char **end)
{
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	*end = line;
	while (**end)
	{
		if (ft_quote(end, &quote, &dquote))
			continue;
		else if (ft_is_semicolon(end, &quote, &dquote))
			return (1);
		else if (ft_strchr(LSH_TOK_DELIM, **end) && !quote && !dquote)
		{
			**end = '\0';
			(*end)++;
		}
		else
			(*end)++;
	}
	return (0);
}

int		ft_quote(char **end, int *quote, int *dquote)
{
	if (**end == '\'' && !*dquote)
	{
		*quote = (*quote + 1) % 2;
		**end = '\0';
		ft_strcat(*end, *end + 1);
		return (1);
	}
	else if (**end == '\"' && !*quote)
	{
		*dquote = (*dquote + 1) % 2;
		**end = '\0';
		ft_strcat(*end, *end + 1);
		return (1);
	}
	return (0);
}

int		ft_is_semicolon(char **end, int *quote, int *dquote)
{
	if (**end == ';' && !*quote && !*dquote)
	{
		if (*(*end - 1) == '\\')
		{
			*(*end - 1) = '\0';
			ft_strcat(*end - 1, *end);
		}
		else
		{
			**end = '\0';
			return (1);
		}
	}
	return (0);
}
