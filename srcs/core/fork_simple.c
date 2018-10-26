/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 14:28:06 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:30:32 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*search_path(char *path, char *chr)
{
	char			*tmp;
	char			*rt;
	DIR				*rep;
	struct dirent	*dirc;

	rt = NULL;
	if (!(rep = opendir(path)))
	{
		perror("minishell ");
		return (NULL);
	}
	while ((dirc = readdir(rep)) && !(rt))
	{
		tmp = ft_strdup(dirc->d_name);
		if (!(ft_strcmp(tmp, chr)))
			rt = ft_strdup(path);
		tmp ? ft_memdel((void *)&tmp) : (0);
	}
	(closedir(rep) == -1) ? (perror("minishell ")) : (0);
	return (rt);
}

static char		*get_path(t_shell *s, char *chr)
{
	char			*tmp;
	char			*rt;
	char			**path;
	int				i;

	i = 0;
	tmp = NULL;
	path = NULL;
	rt = NULL;
	if ((tmp = env_extract(s, "PATH")))
		path = ft_strsplit(tmp, ':');
	tmp ? ft_memdel((void *)&tmp) : (0);
	if (!(path))
		return (NULL);
	while (path[i] && !(tmp))
		tmp = search_path(path[i++], chr);
	if (tmp)
	{
		rt = ft_strjoin(tmp, "/");
		tmp ? ft_memdel((void *)&tmp) : (0);
		tmp = ft_strjoin(rt, chr);
		rt ? ft_memdel((void *)&rt) : (0);
	}
	path ? ft_sstrdel(path) : (0);
	return (tmp);
}

static t_shell	*forker(t_shell *s, char *exe, char **arg)
{
	pid_t			processus;
	int				status;

	if (!(access(exe, R_OK || X_OK)))
	{
		processus = fork();
		tc_close(s);
		if (processus == 0)
			execve(exe, arg, s->alt ? s->menv : s->renv);
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(-1, &status, 0);
		}
	}
	else
	{
		ft_pputstr(NO_RIGHTS, exe);
		ft_putendl_fd("", 2);
	}
	tc_refresh(s);
	return (s);
}

static char		**arg_builder(char *cmd, char **exe, int i, int k)
{
	char			**arg;
	char			*tmp;
	int				tag;

	arg = NULL;
	tmp = NULL;
	tag = 1;
	arg = ft_strsplit(cmd, ' ');
	while (arg[i])
	{
		if ((ft_strchr(arg[i], '/')) && tag && !*exe && !(tag = 0))
		{
			!*exe ? *exe = ft_strdup(arg[i]) : 0;
			k = ft_strcchr_rev(arg[i], '/') + 1;
			tmp = ft_strsub(arg[i], k, ft_strlen(arg[i]) - k);
			arg[i] ? ft_memdel((void *)&arg[i]) : (0);
			arg[i] = ft_strdup(tmp);
		}
		i++;
	}
	tmp ? ft_memdel((void *)&tmp) : 0;
	arg[i] && arg[i - 1][0] == '\0' ? ft_memdel((void *)&arg[i - 1]) : 0;
	return (arg);
}

t_shell			*process(t_shell *s, char *cmd, char *ex, char *tp)
{
	char			**arg;
	int				i;
	struct stat		st;

	i = ft_strcchr(cmd, ' ') ? ft_strcchr(cmd, ' ') : ft_strlen(cmd);
	tp = i < (int)ft_strlen(cmd) ? ft_strsub(cmd, 0, i) : ft_strdup(cmd);
	if (tp[0] == '.' || tp[0] == '/')
		ex = cd_path_solver(s, tp);
	else
		ex = get_path(s, tp);
	arg = arg_builder(cmd, &ex, 0, 0);
	if (!(access(ex, F_OK)) && stat(ex, &st) != -1)
	{
		if (S_ISREG(st.st_mode) && st.st_mode)
			forker(s, ex, arg);
		else
			ft_pputendl(NO_FOUND, cmd);
	}
	ex ? ft_memdel((void *)&ex) : (0);
	tp ? ft_memdel((void *)&tp) : (0);
	arg ? ft_sstrdel(arg) : (0);
	return (s);
}
