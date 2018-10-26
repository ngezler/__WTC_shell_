 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 12:53:26 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:46:09 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*get_shell_ptr(t_shell *s, int i)
{
	static t_shell	*shell;

	(i) ? (shell = s) : (0);
	return (shell);
}

static void	ft_sig_pause(t_shell *s)
{
	char			tmp[2];

	if (s->adv)
	{
		tmp[0] = s->term.c_cc[VSUSP];
		s->term.c_lflag |= (ICANON | ECHO);
		tcsetattr(0, 0, &(s->term));
	}
	else
		tmp[0] = 26;
	tmp[1] = '\0';
	ioctl(0, TIOCSTI, tmp);
	signal(SIGTSTP, SIG_DFL);
}

static void	ft_sig_resume(t_shell *s)
{
	if (s->adv)
	{
		s->term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(0, 0, &(s->term));
	}
	signal(SIGTSTP, signal_recon);
	minishell(s);
}

void		signal_recon(int sig)
{
	t_shell			*s;

	s = NULL;
	s = get_shell_ptr(s, 0);
	if (sig == SIGWINCH)
		tc_refresh(s);
	else if (sig == SIGTSTP)
		ft_sig_pause(s);
	else if (sig == SIGCONT)
		ft_sig_resume(s);
	else if (sig == SIGKILL)
		exit(0);
	else if (sig == SIGQUIT)
	{
		flush_minishell(s);
		exit(0);
	}
}

void		signal_handler(void)
{
	int				i;

	i = 0;
	while (i < 32)
		signal(i++, signal_recon);
}
