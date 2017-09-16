/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 07:58:46 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/16 17:32:20 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void    ft_signal(void)
{
    signal(SIGWINCH, ft_resize);
    // signal(SIGQUIT, set_termm_back);
}

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

void   ft_resize(int i)
{

    (void)i;
    struct winsize sz;
    int col_nbr;

    tputs(tgetstr("cl", NULL), 1, ft_pointchar);
    ioctl(0, TIOCGWINSZ, &sz);
    g_data->win_col = sz.ws_col;
    g_data->win_line = sz.ws_row;
    col_nbr = (sz.ws_col / (g_data->max_name_len + 4));
    if ((g_data->args_count / sz.ws_row) +1 >= col_nbr)
    {
        tputs(tgetstr("cl", NULL), 1, ft_pointchar);
        ft_putstr_fd("PLEASE RESIZE THE TERMINAL", 0);
        g_data->is_print = 0;
    }
    else
    {
        g_data->is_print = 1;
        print_arg(g_select);
    }
}


// void set_termm_back(int i)
// {
//     (void)i;
//
//
// }
