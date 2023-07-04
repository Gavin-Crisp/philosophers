/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:34:49 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/15 15:10:34 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"

int	get_mil_diff(struct timeval a, struct timeval b)
{
	long	s;
	int		u;
	long	t;

	s = (a.tv_sec - b.tv_sec) * 1000;
	u = (a.tv_usec - b.tv_usec) / 1000;
	t = s + u;
	if (t < 0)
		return (-t);
	else
		return (t);
}

int	diff_from_now(struct timeval a)
{
	struct timeval	now;

	gettimeofday(&now, 0);
	return (get_mil_diff(now, a));
}
