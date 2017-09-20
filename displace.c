/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:29:13 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/20 15:55:14 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_select *move_cursor_up(t_select *tmp)
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

static t_select *move_cursor_down(t_select *tmp)
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

static t_select *select_it(t_select *tmp)
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

static t_select *delete_it(t_select *tmp, int *ret)
{
	t_select *save;

	save = NULL;
	tmp->is_selected = 0;
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
			tmp->prev->next = NULL;
			save = tmp->prev;
		}
	}
	else
	{
		if (tmp->next)
		{
			save = tmp->next;
			save->prev = NULL;
			g_select = g_select->next;
			return (save);
		}
		else
			*ret = 2;
	}
	save->is_cursor = 1;
	g_data->args_count -= 1;
	return (save);
}

static t_select *move_cursor_left(t_select *lst)
{
	t_select *tmp;
	int i;

	i = 0;
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

static t_select *move_cursor_right(t_select *lst)
{
	t_select *tmp;
	int i;

	i = 0;
	tmp = lst;

	tmp->is_cursor = 0;
	if ((tmp->line + g_data->win_line) <= g_data->args_count)
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

t_select *handle_key(int buffer, t_select *tmp, int *ret)
{
	if (buffer == PRESS_DOWN)
		return ((move_cursor_down(tmp)));
	else if (buffer == PRESS_UP)
		return ((move_cursor_up(tmp)));
	else if (buffer == PRESS_LEFT)
	    return((move_cursor_left(tmp)));
	else if (buffer == PRESS_RIGHT)
		return((move_cursor_right(tmp)));
	else if (buffer == PRESS_SPACE)
		return ((select_it(tmp)));
	else if (buffer == PRESS_ENTER)
		*ret = 1;
	else if (buffer == PRESS_DEL || buffer == PRESS_BACKSPACE)
		return ((delete_it(tmp, ret)));
	else if (buffer == PRESS_ESCAPE)
		set_termm_back(1);
	return (tmp);
}
