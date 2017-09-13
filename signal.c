/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 07:58:46 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/13 15:12:31 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void    ft_signal(void)
{
    signal(SIGWINCH, ft_resize);
}

void ft_resize(void)
{
    struct winsize sz;
    int col_nbr;

    tputs(tgetstr("cl", NULL), 1, ft_pointchar);
    ioctl(0, TIOCGWINSZ, &sz);
    col_nbr = ((g_data->max_name_len + 4) / sz.ws_col);
    if ((col_nbr * sz.ws_row) < g_data->args_count)
        ft_putstr_fd("RESIZE THE SCREEN", 0);

}



// void set_termm_back(void)
// {
//
// }
