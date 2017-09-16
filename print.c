/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:40:24 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/16 18:02:44 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void print_selected(t_select **lst)
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
    tputs(tgetstr("ve", NULL), 1, ft_pointchar);
}

static int how_print(t_select **lst)
{
    if ((*lst)->is_cursor)
        ft_putstr_fd(tgetstr("us", NULL), 0);
    if ((*lst)->is_selected)
        ft_putstr_fd(tgetstr("mr", NULL), 0);
    return (0);
}

int						ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}


void print_arg(t_select *lst)
{
    t_select *tmp;
    int col;
    int line;
    int x;

    x = 0;
    col = 0;
    line = -1;
    tmp = lst;
    tputs(tgetstr("cl", NULL), 1, ft_pointchar);
    while (col < g_data->win_col && tmp)
    {
        while (++line + 1 < g_data->win_line && tmp)
        {
            tputs((tgoto(tgetstr("cm", NULL), x, line)), 1, ft_pointchar);
            // METTRE LE PRINT DANS UNE SOUS FONCTION
            //
            how_print(&tmp);
            ft_putstr_fd(tmp->name, 0);
            ft_putstr_fd("\n", 0);
            ft_putstr_fd(tgetstr("me", NULL), 0);
            tmp = tmp->next;
        }
        x += g_data->max_name_len + 4;
        col++;
        line =  - 1;
    }
}


int show_cursor(t_select **lst)
{
    int buffer;
    t_select *tmp;
    int ret;

    tmp = *lst;
    ret = 0;
    g_select = tmp;
    tputs(tgetstr("cl", NULL), 1, ft_pointchar);
    while (ret != 1)
    {
        ft_resize(1);
        buffer = 0;
        read(0, &buffer, 8);
        tmp = handle_key(buffer, tmp, &ret);
        tputs(tgetstr("cl", NULL), 1, ft_pointchar);
    }
    if (ret == 1)
        print_selected(lst);
    // if (ret == 2)
    //     quit_select()
    return (0);
}
