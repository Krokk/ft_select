/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:18:05 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/08 15:45:10 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void print_arg(t_select **lst/*, struct winsize sz*/)
{
    t_select *tmp;
    // t_padding pad;

    tmp = *lst;

    while (tmp)
    {
        ft_putendl(tmp->name);
        tmp = tmp->next;
    }
}

static int show_cursor(t_select **lst)
{
    char buffer[3];
    t_select *tmp;
    struct winsize sz;

    tmp = *lst;
    print_arg(&tmp);
    while (1)
     {
        read(0, buffer, 3);
        ioctl(0, TIOCGWINSZ, &sz);
        ft_putstr("\033[H\033[J");
        print_arg(&tmp);
        if (buffer[0] == 27)
         {

             printf("Screen width: %i  Screen height: %i\n", sz.ws_col, sz.ws_row);
            if (buffer[2] == 65)
                ft_putendl("fleche haut");
            if (buffer[2] == 66)
                ft_putendl("fleche bas");
            if (buffer[2] == 67)
                ft_putendl("fleche droit");
            if (buffer[2] == 68)
                ft_putendl("fleche gauche");
         }
        else if (buffer[0] == 4)
        {
            ft_putstr("\033[H\033[J");
          printf("Ctlr+d, on quitte !\n");
          return (0);
        }
        ft_putnbr(buffer[0]);
        ft_putchar('\n');
        ft_putnbr(buffer[1]);
        ft_putchar('\n');
        ft_putnbr(buffer[2]);
        ft_putchar('\n');
    }
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
    tmp->index = i;
    return (1);
}

static void add_t_select_list(t_select **alst, t_select *new)
{
    t_select	*lst;

	lst = *alst;
	if (lst == NULL)
	{
		*alst = new;
	}
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
}

static void get_arg(char **av, t_select **lst)
{
    t_select *tmp;
    int i;

    i = 0;
    while (av[i])
    {
        if (!(tmp = ft_memalloc(sizeof(t_select))) || !fillinfo(tmp, av[i], i))
            ft_error(1,"Malloc failed");
        else
            add_t_select_list(lst, tmp);
        i++;
    }
}

static int set_termin(void)
{
    char           *name_term;
    struct termios term;

    if ((name_term = getenv("TERM")) == NULL)
        return (-1);
    if (tgetent(NULL, name_term) == ERR)
        return (-1);
  // remplis la structure termios des possibilités du terminal.
    if (tcgetattr(0, &term) == -1)
        return (-1);
    term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
    term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    // On applique les changements :
    if (tcsetattr(0, TCSADRAIN, &term) == -1)
        return (-1);
}

int              main(int ac, char **av)
{
    int i;
    t_select        *lst;

    i = 0;
    (void)ac;
    lst = NULL;
    get_arg(av, &lst);
    set_termin();
    show_cursor(&lst);
    return (0);
}
