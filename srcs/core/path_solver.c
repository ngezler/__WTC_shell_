/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 11:21:56 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:49:24 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*cd_tilde(t_shell *s, char *cmd)
{
	char	*t_home;
	char	*t_sub;
	char	*rt;
	int		l_cmd;

	t_home = NULL;
	t_sub = NULL;
	rt = NULL;
	l_cmd = ft_strlen(cmd);
	if ((t_home = env_extract(s, "HOME")))
		if ((t_sub = ft_strsub(cmd, 1, (l_cmd - 1))))
			rt = ft_strjoin(t_home, t_sub);
	t_home ? ft_memdel((void *)&t_home) : (0);
	t_sub ? ft_memdel((void *)&t_sub) : (0);
	return (rt);
}

static char		*cd_dots_purge(char **scwd, char **scmd, int i)
{
	char	*tmp;
	char	*rt;
	int		j;

	tmp = NULL;
	rt = NULL;
	((j = ft_sstrlen(scwd)) > 0) ? (j--) : (0);
	(!(scwd[1])) ? (scwd[0] = ft_strdup("/")) : (0);
	while (scmd[i] && scwd[0])
	{
		if (!(ft_strcmp(scmd[i], ".")) || !(ft_strcmp(scmd[i], scwd[j])) ||
				!(ft_strcmp(scmd[i], "..")))
			(!(ft_strcmp(scmd[i], ".."))) ? (ft_memdel((void *)&scwd[j])) : (0);
		else if ((scwd[j + 1] = ft_strdup(scmd[i])))
			scwd[j + 2] = NULL;
		i++;
		((j = ft_sstrlen(scwd)) > 0) ? (j--) : (0);
		(!(scwd[0])) ? (scwd[0] = ft_strdup("/")) : (0);
	}
	rt = ft_sstrtostr(scwd, "/");
	tmp = ft_strjoin("/", rt);
	tmp ? ft_memdel((void *)&rt) : (0);
	rt = ft_strsub(tmp, 0, (ft_strlen(tmp) - 1));
	tmp ? ft_memdel((void *)&tmp) : (0);
	return (rt);
}

static char		*cd_dots(char *cmd, char *cwd, int i)
{
	char	*tmp;
	char	**scmd;
	char	**scwd;

	tmp = NULL;
	if (!(ft_strcmp(cmd, ".")) || !(ft_strcmp(cmd, "./")))
		return (ft_strdup(cwd));
	if (!ft_strcmp(cmd, "..") && cwd && (i = ft_strlen(cwd)))
	{
		while (cwd[i] != '/')
			i--;
		(i) ? (tmp = ft_strncpy(ft_strnew(i), cwd, i)) : (0);
	}
	if (!tmp && cwd && (i = ft_strlen(cwd)))
	{
		scmd = ft_strsplit(cmd, '/');
		scwd = ft_strsplit(cwd, '/');
		tmp = cd_dots_purge(scwd, scmd, 0);
		scmd ? ft_sstrdel(scmd) : (0);
		scwd ? ft_sstrdel(scwd) : (0);
	}
	if (!cwd)
		tmp = ft_strdup("/");
	return (tmp);
}

char			*cd_path_solver(t_shell *s, char *cmd)
{
	char	*dir;
	char	*tmp;
	char	*cwd;
	char	*ncmd;

	dir = NULL;
	tmp = NULL;
	cwd = NULL;
	ncmd = cmd ? ft_strtrim(cmd) : NULL;
	cwd = getcwd(cwd, 512);
	!cwd ? cwd = env_extract(s, "PWD") : (0);
	if (!ncmd || (*ncmd != '.' && *ncmd != '~' && *ncmd != '/'))
	{
		tmp = ft_strjoin(cwd, "/");
		dir = ncmd ? ft_strjoin(tmp, ncmd) : ft_strdup(cwd);
		tmp ? ft_memdel((void *)&tmp) : (0);
	}
	else
	{
		(*ncmd == '~') ? (dir = cd_tilde(s, ncmd)) : (0);
		(*ncmd == '.') ? (dir = cd_dots(ncmd, cwd, 0)) : (0);
		(*ncmd == '/') ? (dir = ft_strdup(ncmd)) : (0);
	}
	cwd ? ft_memdel((void *)&cwd) : (0);
	ncmd ? ft_memdel((void *)&ncmd) : (0);
	return (dir);
}
