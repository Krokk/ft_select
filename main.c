/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:18:05 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/12 16:09:56 by tchapka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int how_print(t_select **lst)
{
    if ((*lst)->is_print)
    {
        if ((*lst)->is_cursor)
            ft_putstr("\e[4m");
        if ((*lst)->is_selected)
            ft_putstr("\e[1m");
    }
    return (0);
}

static void print_arg(t_select **lst)
{
    t_select *tmp;

    tmp = *lst;
    while (tmp)
    {
        how_print(&tmp);
        ft_putendl(tmp->name);
        ft_putstr("\e[0m");
        tmp = tmp->next;
    }
}

static int show_cursor(t_select **lst)
{
    int buffer;
    t_select *tmp;
    struct winsize sz;
    int ret;

    tmp = *lst;
    ret = 0;
    ft_putstr("\033[H\033[J");
    print_arg(&tmp);
    while (ret != 1)
    {
        buffer = 0;
        read(0, &buffer, 8);
        ioctl(0, TIOCGWINSZ, &sz);
        tmp = handle_key(buffer, tmp, &ret);
        ft_putstr("\033[H\033[J");
        print_arg(lst);
    }
    if (ret)
        print_selected(lst);
    return (0);
}

static void ft_error(int erno, char *msg)
{
    if (erno == 1)
        ft_putendl_fd(msg, 2 );
}

static int fillinfo(t_select *tmp, char *args, int i)
{
    tmp->name = ft_strdup(args);
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
    while (av[++i])
    {
        if (!(tmp = ft_memalloc(sizeof(t_select))) || !fillinfo(tmp, av[i], i))
            ft_error(1,"Malloc failed");
        else
            add_t_select_list(lst, tmp);
    }
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
