/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:29:13 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/25 15:28:48 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_select	*move_cursor_left(t_select *lst)
{
	t_select	*tmp;
	int			i;

	i = -1;
	tmp = lst;
	tmp->is_cursor = 0;
	if ((tmp->line - g_data->win_line) >= -1)
	{
		while (++i < g_data->win_line)
			tmp = tmp->prev;
		tmp->is_cursor = 1;
	}
	else
	{
		while (tmp->prev)
			tmp = tmp->prev;
		tmp->is_cursor = 1;
	}
	return (tmp);
}

static t_select	*move_cursor_right(t_select *lst)
{
	t_select	*tmp;
	int			i;

	i = -1;
	tmp = lst;
	tmp->is_cursor = 0;
	if ((tmp->line + g_data->win_line) < g_data->args_count)
	{
		while (++i < g_data->win_line)
			tmp = tmp->next;
		tmp->is_cursor = 1;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->is_cursor = 1;
	}
	return (tmp);
}

static t_select	*select_all(t_select *lst)
{
	t_select	*tmp;

	tmp = g_select;
	if (lst->is_selected == 0)
	{
		while (tmp)
		{
			tmp->is_selected = 1;
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			tmp->is_selected = 0;
			tmp = tmp->next;
		}
	}
	return (lst);
}

static t_select	*select_from(t_select *lst)
{
	t_select	*tmp;

	tmp = lst;
	if (lst->is_selected == 0)
	{
		while (tmp)
		{
			tmp->is_selected = 1;
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			tmp->is_selected = 0;
			tmp = tmp->next;
		}
	}
	return (lst);
}

t_select		*handle_key(int buffer, t_select *tmp, int *ret)
{
	if (buffer == PRESS_DOWN)
		return ((move_cursor_down(tmp)));
	else if (buffer == PRESS_UP)
		return ((move_cursor_up(tmp)));
	else if (buffer == PRESS_LEFT)
		return ((move_cursor_left(tmp)));
	else if (buffer == PRESS_RIGHT)
		return ((move_cursor_right(tmp)));
	else if (buffer == PRESS_SPACE)
		return ((select_it(tmp)));
	else if (buffer == PRESS_STARS)
		return ((select_all(tmp)));
	else if (buffer == PRESS_BACKSLASH)
		return ((select_from(tmp)));
	else if (buffer == PRESS_ENTER)
		*ret = 1;
	else if (buffer == PRESS_BACKSPACE || buffer == PRESS_DEL)
	{
		tmp->is_selected = 0;
		return ((delete_it(tmp, ret)));
	}
	if (buffer == PRESS_ESCAPE || *ret == 2)
		*ret = 2;
	return (tmp);
}
