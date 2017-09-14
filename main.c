/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:18:05 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/14 19:57:45 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_select.h"

static int how_print(t_select **lst)
{
    if ((*lst)->is_print)
    {
        if ((*lst)->is_cursor)
            ft_putstr_fd(tgetstr("us", NULL), 0);
            // ft_putstr("\e[4m");
        if ((*lst)->is_selected)
            // ft_putstr("\e[1m");
            ft_putstr_fd(tgetstr("mr", NULL), 0);

    }
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
    char *str;
    // printf("\033[XA"); // Move up X lines;
    // printf("\033[XB"); // Move down X lines;
    // printf("\033[XC"); // Move right X column;
    // printf("\033[XD"); // Move left X column;
    // printf("\033[2J"); // Clear screen

    int x =0;
    int y = 0;
    col = 0;
    line = 0;
    tmp = lst;
        // ft_putnbr_fd(g_data->win_col, 0);
        // ft_putendl_fd("--------", 0);
        // ft_putnbr_fd(g_data->win_line, 0);
        // ft_putendl_fd("--------", 0);
        // ft_putnbr_fd(g_data->args_count, 0);
        // ft_putendl_fd("--------", 0);
    // tgoto(tgetstr("cm", NULL), 0);

    // str = tgoto(tgetstr("cm", NULL), 10, 10);
    tputs(tgetstr("cl", NULL), 1, ft_pointchar);
    while (col < g_data->win_col && tmp)
    {
        while (line + 1 < g_data->win_line && tmp)
        {
            tputs((tgoto(tgetstr("cm", NULL), x, y)), 1, ft_pointchar);
            how_print(&tmp);
            ft_putstr_fd(tmp->name, 0);
            ft_putstr_fd("\n", 0);
            ft_putstr_fd(tgetstr("me", NULL), 0);
            tmp = tmp->next;
            line++;
            y++;
        }
        x += g_data->max_name_len + 4;
        y = 0;
        col++;
        line = 0;
        // MANAGE PADDING
        // ft_putstr_fd("\033[20C", 0);
        // MOVE THE CURSOR UP
    }
}

static int show_cursor(t_select **lst)
{
    int buffer;
    t_select *tmp;

    int ret;

    tmp = *lst;
    ret = 0;
    tputs(tgetstr("cl", NULL), 1, ft_pointchar);
    while (ret != 1)
    {
        ft_signal();
        print_arg(*lst);
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

static void ft_error(int erno, char *msg)
{
    if (erno == 1)
        ft_putendl_fd(msg, 2 );
}

static int fillinfo(t_select *tmp, char *args, int i)
{
    int len;

    tmp->name = ft_strdup(args);
    len = ft_strlen(args);
    if ((len > g_data->max_name_len))
        g_data->max_name_len = len;
    tmp->is_print = 1;
    if (i == 0)
        tmp->is_cursor = 1;
    else
        tmp->is_cursor = 0;
    tmp->is_selected = 0;
    return (1);
}

static void add_t_select_list(t_select **alst, t_select *new)
{
    t_select	*lst;

	lst = *alst;
	if (lst == NULL)
	{
		*alst = new;
        new->next = NULL;
        new->prev = NULL;
	}
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
        new->prev = lst;
	}
}

static void get_arg(char **av, t_select **lst)
{
    t_select *tmp;
    int i;

    i =  - 1;
    g_data = ft_memalloc(sizeof(t_data));
    g_data->max_name_len = 0;
    while (av[++i])
    {
        if (!(tmp = ft_memalloc(sizeof(t_select))) || !fillinfo(tmp, av[i], i))
            ft_error(1,"Malloc failed");
        else
            add_t_select_list(lst, tmp);
    }
    g_data->args_count = i;
}

void    ft_signal(void)
{
    signal(SIGWINCH, ft_resize);
}

int              main(int ac, char **av)
{
    int i;
    t_select        *lst;

    i = 0;
    (void)ac;
    lst = NULL;
    get_arg(av + 1, &lst);
    set_termm();
    ft_resize(1);
    show_cursor(&lst);
    return (0);
}
