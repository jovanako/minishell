/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:58:42 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/04 22:33:14 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		free_ev_and_return(t_env_var *ev, int n)
{
	if (ev->key)
		free(ev->key);
	if (ev->value)
		free(ev->value);
	free(ev);
	return (n);
}