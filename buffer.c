/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchapka <tchapka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 23:45:43 by tchapka           #+#    #+#             */
/*   Updated: 2017/09/14 19:21:36 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int set_termm(void)
{
    char           *name_term;
    struct termios term;

    if ((name_term = getenv("TERM")) == NULL)
        return (-1);
    if (tgetent(NULL, name_term) == ERR)
        return (-1);
    if (tcgetattr(0, &term) == -1)
        return (-1);
    term.c_lflag &= ~(ICANON);
    term.c_lflag &= ~(ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSADRAIN, &term) == -1)
        return (-1);
    return (0);
}

void print_selected(t_select **lst)
{
    t_select *tmp;

    tmp = *lst;
    while (tmp)
    {
        if (tmp->is_selected)
        {
            ft_putstr(tmp->name);
            if (tmp->next)
                ft_putstr(" ");
        }
        (tmp) = tmp->next;
    }
    ft_putstr("\n");
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

t_select *move_cursor_up(t_select *tmp)
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

t_select *move_cursor_down(t_select *tmp)
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

t_select *select_it(t_select *tmp)
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

t_select *delete_it(t_select *tmp)
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
