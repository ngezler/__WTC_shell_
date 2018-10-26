/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_terminal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:52:12 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:22:58 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			c_term_mv_back(t_shell *s)
{
	int		i;
	int		lcmd;

	i = 0;
	while (i != (s->c_line))
	{
		ft_putstr(tgetstr("up", NULL));
		i++;
	}
	ft_putstr(tgetstr("cr", NULL));
	i = 0;
	lcmd = s->prompt;
	s->rcmd ? lcmd += (int)ft_strlen(s->rcmd) : 0;
	while (i < lcmd)
	{
		ft_putstr(tgetstr("nd", NULL));
		i++;
	}
}

void			c_term_mv_down(t_shell *s)
{
	int		i;

	i = 0;
	while (i < s->c_line)
	{
		ft_putstr(tgetstr("do", NULL));
		i++;
	}
	i = 0;
	while (i != (s->c_line - 1))
	{
		ft_putstr(tgetstr("up", NULL));
		i++;
	}
}
