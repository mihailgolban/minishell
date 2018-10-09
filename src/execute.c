/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:41:40 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 13:07:10 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_builtin_str[] = {"echo", "cd", "setenv", "unsetenv",
	"env", "exit", "help"};
int		(*g_builtin_func[])(char **) = {&sh_echo, &sh_cd, &sh_setenv,
	&sh_unsetenv, &sh_env, &sh_exit, &sh_help};

int		sh_num_builtins(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
}

int		sh_launch(char **args)
{
	pid_t	pid;
	char	*cmd;

	if ((pid = fork()) == -1)
		ft_putstr_fd("minishell: fork error\n", 2);
	else if (pid == 0)
	{
		if ((cmd = ft_check_cmd(args[0])) != 0)
		{
			if (execve(cmd, args, g_env) == -1)
				ft_putstr_fd("minishell: execve error\n", 2);
		}
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	return (1);
}

int		sh_execute(char **args)
{
	int i;

	i = -1;
	ft_checkdollar(args);
	if ((args[0] == NULL) || (ft_strchr(args[0], '/')
				&& (!ft_is_exist(args[0]) || !ft_is_executable(args[0]))))
		return (1);
	if (ft_strcmp(args[0], ".") == 0)
	{
		ft_putendl_fd("minishell: command not found: .", 2);
		return (1);
	}
	while (++i < sh_num_builtins())
	{
		if (ft_strcmp(args[0], g_builtin_str[i]) == 0)
			return ((*g_builtin_func[i])(args));
	}
	return (sh_launch(args));
}

char	*ft_check_cmd(char *cmd)
{
	char *command;

	if ((command = ft_search_cmd(cmd)) == 0)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		return (0);
	}
	if (ft_is_executable(command) == 0)
		return (0);
	return (command);
}

char	*ft_search_cmd(char *cmd)
{
	char *searchpath;
	char *sp;
	char command[256];

	if (ft_strchr(cmd, '/'))
		return (cmd);
	searchpath = ft_strdup(ft_getenv("PATH"));
	while (searchpath)
	{
		if ((sp = ft_strchr(searchpath, ':')))
			*sp++ = '\0';
		ft_strcat(ft_strcat(ft_strcpy(command, searchpath), "/"), cmd);
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		searchpath = sp;
	}
	return (0);
}
