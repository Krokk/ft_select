/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:13:28 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/25 15:27:42 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_select	*detele_it_norme(t_select *lst, int *ret)
{
	t_select	*tmp;

	tmp = NULL;
	if (lst->next)
	{
		tmp = lst->next;
		tmp->prev = NULL;
		g_select = g_select->next;
		g_data->args_count -= 1;
		tmp->is_cursor = 1;
		return (tmp);
	}
	else
	{
		*ret = 2;
		return (lst);
	}
}

t_select		*delete_it(t_select *tmp, int *ret)
{
	t_select	*save;

	save = NULL;
	if (tmp->prev)
	{
		if (tmp->next)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			save = tmp->next;
		}
		else
		{
			(tmp->prev)->next = NULL;
			save = tmp->prev;
		}
		ft_strdel(&tmp->name);
		free(tmp);
	}
	else
		save = detele_it_norme(tmp, ret);
	save->is_cursor = 1;
	if ((g_data->args_count -= 1) <= 0)
		*ret = 2;
	return (save);
}

t_select		*move_cursor_up(t_select *tmp)
{
	tmp->is_cursor = 0;
	if (tmp->prev)
		tmp = tmp->prev;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	tmp->is_cursor = 1;
	return (tmp);
}

t_select		*move_cursor_down(t_select *tmp)
{
	tmp->is_cursor = 0;
	if (tmp->next)
		tmp = tmp->next;
	else
	{
		while (tmp->prev)
			tmp = tmp->prev;
	}
	tmp->is_cursor = 1;
	return (tmp);
}

t_select		*select_it(t_select *tmp)
{
	if (tmp->is_selected)
		tmp->is_selected = 0;
	else
		tmp->is_selected = 1;
	tmp->is_cursor = 0;
	if (tmp->next)
		tmp = tmp->next;
	else
	{
		while (tmp->prev)
			tmp = tmp->prev;
	}
	tmp->is_cursor = 1;
	return (tmp);
}
