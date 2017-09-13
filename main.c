/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:18:05 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/13 15:20:55 by rfabre           ###   ########.fr       */
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


static void print_arg(t_select **lst)
{
    t_select *tmp;

    tmp = *lst;
    ft_resize();
    while (tmp)
    {
        if (tmp->is_print == 1)
        {
            how_print(&tmp);
            ft_putstr_fd(tmp->name, 0);
            ft_putstr_fd("\n", 0);
            ft_putstr_fd(tgetstr("me", NULL), 0);
        }
        tmp = tmp->next;
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
        print_arg(lst);
        buffer = 0;
        read(0, &buffer, 8);

        // ft_signal(&sz);
        tmp = handle_key(buffer, tmp, &ret);
        tputs(tgetstr("cl", NULL), 1, ft_pointchar);
        // ft_putnbr_fd(buffer, 0);
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
    int *len;
    tmp->name = ft_strdup(args);
    len = ft_strlen(args);
    if ((len >= g_data->max_name_len))
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

int              main(int ac, char **av)
{
    int i;
    t_select        *lst;

    i = 0;
    (void)ac;
    lst = NULL;
    get_arg(av + 1, &lst);
    set_termm();
    show_cursor(&lst);
    return (0);
}
