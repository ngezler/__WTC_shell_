/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_clearing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakatsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 07:34:14 by mmakatsh          #+#    #+#             */
/*   Updated: 2018/10/25 08:16:55 by mmakatsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		c_prompt_update(t_shell *s, int *i)
{
	int			k;

	k = 0;
	TC_STR_LINE;
	while (k < s->prompt)
	{
		TC_MV_RIGHT;
		k++;
	}
	TC_DEL_LINE;
	*i = ft_strlen(s->rcmd);
	TC_STR_INSERT;
	ft_putstr(s->rcmd);
	TC_END_INSERT;
}

static void		c_rcmd_update(t_shell *s)
{
	t_comp		*tmp;
	char		*nrcmd;
	char		*srcmd;

	srcmd = NULL;
	nrcmd = NULL;
	tmp = c_seek_cursor(s);
	if (s->match)
	{
		nrcmd = ft_strsub(s->rcmd, 0, ft_strlen(s->rcmd) - ft_strlen(s->match));
		s->rcmd ? ft_memdel((void *)&s->rcmd) : 0;
		s->rcmd = ft_strjoin(nrcmd, tmp->name);
	}
	else
	{
		srcmd = ft_strsub(s->rcmd, 0, ft_strlen(s->rcmd));
		nrcmd = ft_strjoin(srcmd, tmp->name);
		s->rcmd ? ft_memdel((void *)&s->rcmd) : 0;
		s->rcmd = ft_strdup(nrcmd);
	}
	nrcmd ? ft_memdel((void *)&nrcmd) : 0;
	srcmd ? ft_memdel((void *)&srcmd) : 0;
}

static void		c_clearing_choice(t_shell *s)
{
	int			i;

	i = 0;
	while (i < s->c_line)
	{
		TC_MV_DOWN;
		TC_STR_LINE;
		TC_DEL_LINE;
		i++;
	}
	i = 0;
	while (i != (s->c_line))
	{
		TC_STR_LINE;
		TC_MV_UP;
		i++;
	}
	i = s->prompt;
	s->rcmd ? i = i + (int)ft_strlen(s->rcmd) : 0;
	while (i)
	{
		TC_MV_RIGHT;
		i--;
	}
}

void			c_clearing(t_shell *s, int *i, unsigned int key)
{
	if (s->comp && s->comp->name)
	{
		c_clearing_choice(s);
		if (key != K_RETURN && key != K_DEL)
		{
			c_rcmd_update(s);
			c_prompt_update(s, i);
		}
		flush_completion(s);
	}
}
