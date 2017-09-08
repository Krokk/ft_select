/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:17:43 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/08 15:29:47 by rfabre           ###   ########.fr       */
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

typedef struct s_select
{
    char    *name;
    int     is_print;
    int     is_cursor;
    int     is_selected;
    int     index;
    struct s_select *next;
}               t_select;

int		ft_ini(void);
int		ft_exit(void);

#endif
