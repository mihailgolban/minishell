/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 12:33:13 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:39:56 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;
int		g_sigint;

int		main(int argc, char **argv, char **envp)
{
	g_env = envp;
	g_sigint = 1;
	if (argc && argv[0])
		;
	signal(SIGINT, ft_sigint);
	sh_loop();
	return (0);
}

void	sh_loop(void)
{
	char	*line;
	char	**args;
	char	*cmd;

	while (1)
	{
		if (g_sigint)
			ft_putstr("$> ");
		line = sh_read_line();
		cmd = line;
		g_sigint = 1;
		while (cmd && *cmd && g_sigint)
		{
			args = sh_split_line(&cmd);
			sh_execute(args);
			free(args);
		}
		free(line);
	}
}
