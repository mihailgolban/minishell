/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:43:05 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:43:30 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_read_line(void)
{
	int		bufsize;
	int		position;
	char	*buffer;
	int		c;

	bufsize = LSH_RL_BUFSIZE;
	position = 0;
	buffer = (char *)malloc(sizeof(char) * bufsize);
	while (1)
	{
		c = ft_getchar();
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			ft_checkquote(&buffer);
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;
		if (position >= bufsize - 1)
			ft_buf_realloc(&buffer, bufsize += LSH_RL_BUFSIZE);
	}
}

void	ft_buf_realloc(char **buffer, int bufsize)
{
	*buffer = (char *)ft_realloc(*buffer, bufsize * sizeof(char));
	if (!*buffer)
	{
		ft_putstr_fd("minishell: ft_realloc error", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_checkquote(char **buffer)
{
	int quote;
	int dquote;
	int position;
	int q;

	quote = 0;
	dquote = 0;
	q = 0;
	position = -1;
	while ((*buffer)[++position])
	{
		if (dquote == 0 && (*buffer)[position] == '\'')
			quote = (quote + 1) % 2;
		if (quote == 0 && (*buffer)[position] == '\"')
			dquote = (dquote + 1) % 2;
	}
	if (quote)
		q = '\'';
	if (dquote)
		q = '\"';
	if (q)
	{
		ft_waitquote(q, buffer, position);
		ft_checkquote(buffer);
	}
}

void	ft_waitquote(int quote, char **buffer, int position)
{
	int c;
	int bufsize;

	(*buffer)[position++] = '\\';
	(*buffer)[position++] = 'n';
	bufsize = position;
	(quote == '\'') ? ft_putstr("quote>") : ft_putstr("dquote>");
	while (1)
	{
		if (position >= bufsize)
			ft_buf_realloc(buffer, bufsize += LSH_RL_BUFSIZE);
		c = ft_getchar();
		if (c == '\n')
		{
			(*buffer)[position] = '\0';
			if (!g_sigint)
			{
				ft_get_last_cmd(buffer);
				g_sigint = 1;
			}
			return ;
		}
		(*buffer)[position] = c;
		position++;
	}
}

void	ft_get_last_cmd(char **buffer)
{
	char *tofree;

	tofree = *buffer;
	while (ft_strstr(*buffer, "\\n"))
		*buffer = ft_strstr(*buffer, "\\n") + 2;
	*buffer = ft_strdup(*buffer);
	free(tofree);
}
