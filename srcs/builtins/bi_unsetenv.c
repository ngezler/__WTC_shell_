/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 12:23:55 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:12:17 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		bi_unsetenv_err(char *cmd)
{
	cmd ? ft_memdel((void *)&cmd) : 0;
	ft_putendl(ERR_UNST);
	return (0);
}

int				bi_unsetenv(t_shell *s, char *cmd, int i, int j)
{
	char	*tmp;
	char	*clr;
	char	**dump;

	tmp = NULL;
	dump = NULL;
	if (cmd[0] == '\0')
		return (bi_unsetenv_err(cmd));
	dump = ft_sstrnew(ft_sstrlen(s->renv));
	clr = ft_strtrim(cmd);
	while (s->renv[i])
	{
		tmp = ft_strsub(s->renv[i], 0, (int)ft_strlen(clr));
		if (ft_strcchr(s->renv[i], '=') == (int)ft_strlen(clr))
			(!ft_strcmp(tmp, clr)) ? (0) : (dump[j++] = ft_strdup(s->renv[i]));
		else
			dump[j++] = ft_strdup(s->renv[i]);
		(tmp) ? ft_memdel((void *)&tmp) : 0;
		i++;
	}
	s->renv ? ft_sstrdel(s->renv) : (0);
	cmd ? ft_memdel((void *)&cmd) : (0);
	clr ? ft_memdel((void *)&clr) : (0);
	s->renv = dump;
	return (0);
}
