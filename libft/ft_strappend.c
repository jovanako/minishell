/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:43:09 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/28 20:43:09 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strappend(char *s1, const char *s2)
{
    char    *tmp;

    if (!(tmp = ft_strjoin(s1, s2)))
        return (NULL);
    free(s1);
    return (tmp);
}