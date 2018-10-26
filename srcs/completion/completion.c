/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 12:39:29 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:26:39 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_comp		*c_seek_cursor(t_shell *s)
{
	t_comp			*ptr;

	if (s->comp->cursor)
		ptr = s->comp;
	else
	{
		ptr = s->comp->next;
		while (ptr->next != s->comp && !(ptr->cursor))
			ptr = ptr->next;
	}
	return (ptr);
}

void		c_next_item(t_shell *s)
{
	t_comp			*ptr;

	ptr = s->comp;
	while (!ptr->cursor)
		ptr = ptr->next;
	ptr->cursor = 0;
	ptr->next->cursor = 1;
}

int			completion(t_shell *s, int *i)
{
	!(s->comp) ? c_match(s, NULL, NULL, i) : c_next_item(s);
	if (s->comp && s->comp != s->comp->next)
	{
		c_term_mv_down(s);
		c_printer(s);
		c_term_mv_back(s);
	}
	else if (s->comp && s->comp->name)
		c_clearing(s, i, 0);
	return (0);
}
