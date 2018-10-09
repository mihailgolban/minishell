/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:18:51 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:24:39 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sh_cd(char **args)
{
	char *newpwd;

	(*(args + 1) && ft_strcmp(*(args + 1), "--") == 0) ? args++ : 0;
	if (*(args + 1) == NULL)
		newpwd = ft_getenv("HOME");
	else if ((*(args + 1)[0] == '~') && *(args + 2) == NULL)
		newpwd = ft_strjoin(ft_getenv("HOME"), *(args + 1) + 1);
	else if (!ft_strcmp(*(args + 1), "-") && *(args + 2) == NULL)
		newpwd = ft_getenv("OLDPWD");
	else if (*(args + 3) != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	else if (*(args + 2) != NULL)
	{
		if ((newpwd = ft_get_new_pwd(*(args + 1),
						*(args + 2))) == NULL ||
				(ft_check_dir(newpwd)) == NULL)
			return (1);
	}
	else if ((newpwd = ft_check_dir(*(args + 1))) == NULL)
		return (1);
	ft_changedir(newpwd);
	return (1);
}

char	*ft_check_dir(char *dir)
{
	struct stat buf;

	if (access(dir, F_OK) == 0)
	{
		lstat(dir, &buf);
		if (!S_ISDIR(buf.st_mode))
		{
			ft_putstr_fd("cd: not a directory: ", 2);
			ft_putendl_fd(dir, 2);
		}
		else if (access(dir, X_OK) == 0)
			return (dir);
		else
		{
			ft_putstr_fd("cd: permission denied: ", 2);
			ft_putendl_fd(dir, 2);
		}
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(dir, 2);
	}
	return (NULL);
}

char	*ft_get_new_pwd(char *tofind, char *toreplace)
{
	char *pwd;
	char *p;
	char *tofree;

	pwd = getcwd(NULL, 0);
	if ((p = ft_strstr(pwd, tofind)) == NULL)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(tofind, 2);
		return (NULL);
	}
	else
	{
		*p = '\0';
		tofree = ft_strjoin(pwd, toreplace);
		pwd = ft_strjoin(tofree, p + ft_strlen(tofind));
		free(tofree);
		p = ft_getenv("HOME");
		if (p && ft_strstr(pwd, p))
		{
			ft_putchar('~');
			ft_putendl(pwd + ft_strlen(p));
		}
	}
	return (pwd);
}

void	ft_changedir(char *newpwd)
{
	chdir(newpwd);
	newpwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", ft_getenv("PWD"), 1);
	ft_setenv("PWD", newpwd, 1);
}
