/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 13:43:23 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 09:02:00 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tc_refresh(t_shell *s)
{
	struct winsize	win;

	if (s->adv)
	{
		s->term.c_lflag &= ~(ICANON | ECHO);
		if (tcsetattr(0, 0, &(s->term)) == -1)
			return (1);
		ioctl(0, TIOCGWINSZ, &win);
		s->win_x = win.ws_col;
		s->win_y = win.ws_row;
	}
	return (0);
}

int		tc_init(t_shell *s)
{
	struct winsize	window;
	char			*tty_test;

	tty_test = ttyname(0);
	if (tty_test == NULL)
	{
		ft_putendl_fd("Don't try to fool me...", 2);
		exit(1);
	}
	if ((tgetent(NULL, getenv("TERM")) < 1) || (tcgetattr(0, &(s->term)) == -1))
		return (1);
	s->term.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, 0, &(s->term)) == -1)
		return (1);
	ioctl(0, TIOCGWINSZ, &window);
	s->win_x = window.ws_col;
	s->win_y = window.ws_row;
	s->adv = 1;
	tty_test ? ft_memdel((void *)&tty_test) : 0;
	return (0);
}

int		tc_close(t_shell *s)
{
	if (s->adv)
	{
		s->term.c_lflag |= (ICANON | ECHO);
		if (tcsetattr(0, 0, &(s->term)) == -1)
			return (1);
	}
	return (0);
}
