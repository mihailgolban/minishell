/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 12:43:28 by mgolban           #+#    #+#             */
/*   Updated: 2017/02/27 12:41:07 by mgolban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include "libft.h"
# define LSH_RL_BUFSIZE 1024
# define LSH_TOK_BUFSIZE 64
# define LSH_TOK_DELIM " \t\r\a"

extern	char **g_env;
extern	int	g_sigint;
void	sh_loop(void);
char	*sh_read_line(void);
void	*ft_realloc(void *ptr, size_t size);
char	**sh_split_line(char **line);
int		sh_echo(char **args);
int		sh_cd(char **args);
int		sh_setenv(char **args);
int		sh_unsetenv(char **args);
int		sh_env();
int		sh_exit();
int		sh_help();
int		sh_num_builtins();
int		sh_execute(char **args);
char	*ft_getenv(const char *envname);
char	*ft_search_cmd(char *cmd);
int		ft_setenv(const char *name, const char *value, int overwrite);
int		ft_putenv(const char *str);
char	**ft_create_env(size_t env_len);
int		ft_is_executable(char *command);
char	*ft_check_cmd(char *cmd);
int		ft_is_exist(char *str);
char	*ft_check_dir(char *dir);
char	*ft_get_new_pwd(char *tofind, char *toreplace);
void	ft_changedir(char *newpwd);
void	ft_checkdollar(char **args);
void	ft_checkquote(char **buffer);
void	ft_waitquote(int quote, char **buffer, int position);
void	ft_buf_realloc(char **buffer, int bufsize);
void	ft_sigint();
int		ft_str_parser(char *line, char **end);
void	ft_split(char **line, char *end, char **tokens, int bufsize);
int		ft_quote(char **end, int *quote, int *dquote);
int		ft_is_semicolon(char **end, int *quote, int *dquote);
void	ft_get_last_cmd(char **buffer);
#endif
