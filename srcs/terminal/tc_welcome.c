/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_welcome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 08:10:52 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/26 11:57:01 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		w_t_head(void)
{
	ft_printf("\e[1m\e[93m");
	ft_printf("FIRST SH  UNIX_SHELL AT WTC \n");
	ft_printf("\n");
	ft_printf("\e[39m");
}


static void		w_footer(void)
{
	ft_printf("\e[1m\e[93m");
	ft_printf("BY: MONGEZI MAKATSHU\n");
	ft_printf("\n");
	ft_printf("\e[39m");
}

int				welcome(t_shell *s)
{
	if (s->win_x <= 72 || !s->adv)
		return (1);
	TC_CLEAR_SCR;
	w_t_head();
	w_footer();
	return (0);
}
