/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_printer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 14:09:12 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:21:46 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	c_printer_node(t_comp *lst)
{
	lst->cursor ? ft_putstr(tgetstr("us", NULL)) : (0);
	lst->cursor ? (ft_putstr_fd("\033[31m", 2)) : (0);
	ft_putstr_fd(lst->name, 2);
	ft_putstr_fd("\033[00m", 2);
	lst->cursor ? ft_putstr(tgetstr("ue", NULL)) : (0);
}

static int	c_printer_line(t_shell *s, t_comp *lst, int loop, int i)
{
	t_comp	*tmp;

	tmp = lst->next;
	c_printer_node(lst);
	while (loop)
	{
		i = 1;
		while (i++ < (s->c_line))
		{
			if (tmp == s->comp)
				return (0);
			tmp = tmp->next;
		}
		if (tmp != s->comp)
		{
			i = lst->len;
			while (i++ < (s->c_sx + 1))
				ft_putstr(" ");
			c_printer_node(tmp);
			lst = tmp;
			tmp = tmp->next;
		}
		loop--;
	}
	return (0);
}

void		c_printer(t_shell *s)
{
	t_comp	*tmp;
	int		loop;

	tmp = s->comp;
	loop = s->c_line;
	while (loop)
	{
		c_printer_line(s, tmp, s->c_pline, 1);
		loop > 1 ? ft_putstr(tgetstr("do", NULL)) : (0);
		tmp = tmp->next;
		loop--;
	}
}
