/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:17:43 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/13 15:21:00 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <stdio.h>
# include "./libft/libft.h"


// typedef strct  t_padding
// {
//     int      max_name_len;
//     int      rows;
//     int      col;
//     int      file_count;
//     /*
//
//     */
//
// }

typedef struct s_data
{
            int win_col;
            int win_line;
            int max_name_len;
            int args_count;
}              t_data;

t_data                  *g_data;

typedef struct s_select
{
    char    *name;
    int     is_print;
    int     is_cursor;
    int     is_selected;
    struct s_select *next;
    struct s_select *prev;
}               t_select;

int                 ft_ini(void);
int                 ft_exit(void);
int                 set_termm(void);
t_select            *handle_key(int buffer, t_select *tmp, int *ret);
t_select            *move_cursor_down(t_select *tmp);
t_select *move_cursor_up(t_select *tmp);
t_select *select_it(t_select *tmp);
void print_selected(t_select **lst);
t_select *delete_it(t_select *tmp);
t_select *delete_it_norme(t_select **tmp);
int						ft_pointchar(int c);
void ft_resize(void);
void    ft_signal(void);
#endif
