/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 07:58:46 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/14 19:38:21 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void   ft_resize(int i)
{

    (void)i;
    struct winsize sz;
    int col_nbr;

    tputs(tgetstr("cl", NULL), 1, ft_pointchar);
    // ft_putendl_fd("OUESH ELS GROS ON EST LA HEIN BANG BANG BANG BAM BOOM", 0);
    ioctl(0, TIOCGWINSZ, &sz);
    g_data->win_col = sz.ws_col;
    g_data->win_line = sz.ws_row;
    col_nbr = (sz.ws_col / (g_data->max_name_len + 4));
    if ((g_data->args_count / sz.ws_row) +1 >= col_nbr)
    {
        tputs(tgetstr("cl", NULL), 1, ft_pointchar);
        ft_putstr_fd("PLEASE RESIZE THE TERMINAL", 0);
    }
    else
        print_arg(g_select);
}


// void set_termm_back(void)
// {
//
// }
