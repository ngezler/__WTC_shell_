/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 13:25:32 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:10:38 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trimmer(char *cmd)
{
	char	*rt;

	rt = NULL;
	if (cmd)
		rt = ft_strtrim(cmd);
	if (rt[0] == '\0')
		rt ? ft_memdel((void *)&rt) : (0);
	if (rt && rt[0] == '=')
		rt ? ft_memdel((void *)&rt) : (0);
	if (rt && (int)ft_strlen(rt) == ft_strxcchr(rt, '='))
		rt ? ft_memdel((void *)&rt) : (0);
	cmd ? ft_memdel((void *)&cmd) : (0);
	return (rt);
}

int				bi_setenv(t_shell *s, char *cmd)
{
	char	*t_name;
	char	*t_value;
	int		i;

	i = 0;
	t_name = NULL;
	t_value = NULL;
	cmd = trimmer(cmd);
	if (cmd && ft_strcchr(cmd, '='))
	{
		i = ft_strcchr(cmd, '=');
		(cmd[i] == '=') ? (i++) : (0);
		t_name = ft_strsub(cmd, 0, (i - 1));
		t_value = ft_strsub(cmd, i, ft_strlen(cmd) - i);
	}
	else if (cmd)
	{
		t_name = ft_strdup(cmd);
		t_value = ft_strnew(0);
	}
	cmd ? env_update(s, t_name, t_value) : (0);
	t_name ? ft_memdel((void *)&t_name) : (0);
	t_value ? ft_memdel((void *)&t_value) : (0);
	cmd ? ft_memdel((void *)&cmd) : (0);
	return (0);
}
