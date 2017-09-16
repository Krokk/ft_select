/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 15:29:13 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/16 15:30:21 by rfabre           ###   ########.fr       */
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

static t_select *delete_it(t_select *tmp)
{
    t_select *save;

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
    /* not working with the first elem  NEED FIX*/
    {
        if (tmp->next)
        {
            tmp->next->prev = NULL;
            save = tmp->next;
        }
        else
        {
            ft_putendl_fd("ya plus rien mamen", 0);
            exit (0);
        }
    }
    ft_strdel(&tmp->name);
    free(tmp);
    save->is_cursor = 1;
    g_data->args_count -= 1;
    return (save);
}

t_select *handle_key(int buffer, t_select *tmp, int *ret)
{
    if (buffer == PRESS_DOWN)
        return ((move_cursor_down(tmp)));
    else if (buffer == PRESS_UP)
        return ((move_cursor_up(tmp)));
    // if (buffer == PRES_LEFT)
    //     move_cursor_left(lst, data);
    // if (buffer == PRES_RIGHT)
    else if (buffer == PRESS_SPACE)
        return ((select_it(tmp)));
    else if (buffer == PRESS_ENTER)
        *ret = 1;
    else if (buffer == PRESS_DEL || buffer == PRESS_BACKSPACE)
        return ((delete_it(tmp)));
    else if (buffer == PRESS_ESCAPE)
        *ret = 2;
    return (tmp);
}
