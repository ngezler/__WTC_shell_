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
	ft_printf("FIRST CSH  UNIX_SHELL AT WTC \n");
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

static void		w_logo(void)
{
	ft_printf("\e[1m\e[92m");
	ft_printf("/01     /10   /0101010  / 01  / 01  /  0101    / 101010101  / 01011101 /1010101  /1	 / 101010\n");
 	ft_printf("|101   /010  |10/    10 | 010 | 10 | 01     01|| 01______/ | ____  10 |_  101_/  0101  / 10__   01\n");
 	ft_printf("|10101/0101  |1|     101| 1011| 11 | 10     10|| 10             / 10    | 01      01/  | 10    __/\n");
 	ft_printf("|01 1/10 01  |0|     011| 11 01 00 | 01  _____ | 01010         / 01     | 11|             101010\n");
 	ft_printf("|10  010|10  |1|     100| 01  0101 | 10  10101|| 10___/       / 10      | 10		  ____  10\n");
 	ft_printf("|01   / |01  |1|     101| 01   010 | 01     10|| 01          / 01       | 00            /10      01\n");
 	ft_printf("|10  /  |10  |01 010/01 | 10    10 |  0101010 || 101010010  | 01010101  /110110|        | 1010101/\n");
 	ft_printf("/__/    |__/   ________/|__/   ___/  ________/ |_________/    ________/|_______/          ______/\n");
	ft_printf("\n");


	 ft_printf("/10      /10 /010101 /10   /10 /010011   /101010  /11   /11 /0101010 / 10      / 01\n");
	 ft_printf("| 101    /101|_  10_/| 101 | 01|_  10_/ /10__  01| 10  | 01| 01_____/| 00      | 11\n");
	 ft_printf("| 0011  /0101  | 01  | 1010| 11  | 11  | 10   __/| 11  | 10| 10      | 01      | 10\n");
	 ft_printf("| 11 10/10 00  | 00  | 10 01 01  | 01  |  010101 | 10101010| 01010   | 10      | 01\n");
	 ft_printf("| 10  101| 10  | 11  | 01  1010  | 10    ____  10| 01__  10| 10__/   | 00      | 11\n");
	 ft_printf("| 01   1 | 10  | 01  | 10   101  | 01   /10    01| 10  | 01| 01      | 01      | 10\n");
	 ft_printf("| 10  /  | 01 /101010| 01    10 /010011|  010101/| 01  | 10| 10101010| 01011001| 11101000\n");
	 ft_printf("|__/     |__/|______/|__/   __/|______/  ______/ |__/  |__/|________/|________/|________/\n");
	 ft_printf("\n");
	ft_printf("\e[39m");
}

int				welcome(t_shell *s)
{
	if (s->win_x <= 72 || !s->adv)
		return (1);
	TC_CLEAR_SCR;
	w_t_head();
	w_logo();
	w_footer();
	return (0);
}
