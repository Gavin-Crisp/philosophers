/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:13:52 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/14 13:38:09 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include "structs.h"
# include "enums.h"
# include "colours.h"
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_phil
{
	t_phil_state	state;
	unsigned int	number;
	unsigned int	eat_times;
	t_args			*args;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
	struct timeval	last_ate;
}	t_phil;

void	*philosopher(void *arg);
#endif
