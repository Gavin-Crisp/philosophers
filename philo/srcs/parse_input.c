/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:48:33 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/06 09:35:49 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input.h"

void	parse_arg(unsigned int *store, char *s)
{
	*store = ft_atoui(s);
	if (!*store)
		arg_error();
}

void	parse_input(int ac, char **av, t_args *store)
{
	if (ac < 5 || ac > 6)
		return (arg_error());
	parse_arg(&store->phil_num, av[1]);
	parse_arg(&store->time_die, av[2]);
	parse_arg(&store->time_eat, av[3]);
	parse_arg(&store->time_sleep, av[4]);
	if (ac == 6)
		parse_arg(&store->eat_times, av[5]);
	else
		store->eat_times = 0;
}
