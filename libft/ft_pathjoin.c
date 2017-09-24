/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchapka <tchapka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 02:00:19 by tchapka           #+#    #+#             */
/*   Updated: 2017/09/24 02:37:57 by tchapka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathjoin(char *folder, char *target)
{
	char	*tmp;
    char    *tmp2;

	if (!folder || !target)
		return (NULL);
	if ((folder[(ft_strlen(folder))] != '/'))
	{
		if (target[0] == '/')
			return (ft_strjoin(folder, ft_strchr(target, '/') + 1));
		else
		{
            tmp = ft_strjoin(folder, "/");
			tmp2 = ft_strjoin(tmp, ft_strchr(target, '/'));
            free (tmp);
			return (tmp2);
		}
	}
	else
	{
		if (target[0] == '/')
			return (ft_strjoin(folder, target + 1));
		else
			return (ft_strjoin(folder, target));
	}
}
