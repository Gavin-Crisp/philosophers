/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:42:27 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/15 13:54:34 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	phil_eat(t_phil *data)
{
	printf("%d " YELLOW "%d" RESET " is " GREEN "eating\n" RESET,
		diff_from_now(data->start_time), data->number);
	gettimeofday(&data->last_ate, 0);
	usleep(data->args->time_eat * 1000);
	data->eat_times++;
	data->state = SLEEPING;
	if (data->number > 1)
		pthread_mutex_unlock(&data->forks[data->number - 2]);
	else
		pthread_mutex_unlock(&data->forks[data->args->phil_num - 1]);
	pthread_mutex_unlock(&data->forks[data->number - 1]);
}

void	grab_fork(t_phil *data, int left)
{
	if (left)
	{
		if (data->number > 1)
			pthread_mutex_lock(&data->forks[data->number - 2]);
		else
			pthread_mutex_lock(&data->forks[data->args->phil_num - 1]);
	}
	else
		pthread_mutex_lock(&data->forks[data->number - 1]);
	printf("%d " YELLOW "%d" RESET " has " MAGENTA "grabbed a fork\n" RESET,
		diff_from_now(data->start_time), data->number);
}

void	phil_think(t_phil *data)
{
	printf("%d " YELLOW "%d" RESET " is " BLUE "thinking\n" RESET,
		diff_from_now(data->start_time), data->number);
	grab_fork(data, 1);
	grab_fork(data, 0);
	data->state = EATING;
}

void	*philosopher(void *arg)
{
	t_phil	*data;

	data = arg;
	while (data->state != DEAD)
	{
		if (data->state == EATING)
			phil_eat(data);
		else if (data->state == SLEEPING)
		{
			printf("%d " YELLOW "%d" RESET" is " CYAN "sleeping\n" RESET,
				diff_from_now(data->start_time), data->number);
			usleep(data->args->time_sleep * 1000);
			data->state = THINKING;
		}
		else
			phil_think(data);
	}
	return (0);
}
