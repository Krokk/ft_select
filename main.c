/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:18:05 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/20 16:00:38 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int ft_quit(void)
{
    exit(0);
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
	if (i == 0)
		tmp->is_cursor = 1;
	else
		tmp->is_cursor = 0;
	tmp->is_selected = 0;
	return (1);
}

void add_t_select_list(t_select **alst, t_select *new)
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

int              main(int ac, char **av)
{
	int i;
	t_select        *lst;

	i = 0;
    lst = NULL;
	if (ac < 2)
        ft_putendl_fd("usage : ./ft_select <arguments>", 2);
    else
    {
        get_arg(av + 1, &lst);
        set_termm();
        tputs(tgetstr("vi", NULL), 1, ft_pointchar);
        ft_signal();
        show_cursor(&lst);
        return (0);
    }
}
