/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:42:27 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/28 13:24:13 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*death_check(void *arg)
{
	t_phil	*data;

	data = arg;
	while (1)
	{
		if ((unsigned int)diff_from_now(data->last_ate) >= data->args->time_die)
		{
			data->state = DEAD;
			printf(RESET "%d " YELLOW "%d" RED " died\n" RESET,
				diff_from_now(data->start_time), data->number);
			kill(data->killswitch, SIGKILL);
			break ;
		}
	}
	return (0);
}

void	setup_thread(t_phil *data)
{
	int			ret;
	pthread_t	thread;

	ret = pthread_create(&thread, 0, death_check, data);
	if (!ret)
		return ;
	init_error();
	kill(data->killswitch, SIGKILL);
}

void	phil_eat(t_phil *data)
{
	printf(RESET "%d " YELLOW "%d" RESET " is " GREEN "eating\n" RESET,
		diff_from_now(data->start_time), data->number);
	gettimeofday(&data->last_ate, 0);
	usleep(data->args->time_eat * 1000);
	data->eat_times++;
	if (data->eat_times == data->args->eat_times)
		sem_post(data->fed);
	data->state = SLEEPING;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	phil_think(t_phil *data)
{
	printf(RESET "%d " YELLOW "%d" RESET " is " BLUE "thinking\n" RESET,
		diff_from_now(data->start_time), data->number);
	sem_wait(data->forks);
	printf(RESET "%d " YELLOW "%d" RESET " has " MAGENTA "grabbed a fork\n"
		RESET, diff_from_now(data->start_time), data->number);
	sem_wait(data->forks);
	printf(RESET "%d " YELLOW "%d" RESET " has " MAGENTA "grabbed a fork\n"
		RESET, diff_from_now(data->start_time), data->number);
	data->state = EATING;
}

void	*philosopher(t_phil *data)
{
	setup_thread(data);
	while (data->state != DEAD)
	{
		if (data->state == EATING)
			phil_eat(data);
		else if (data->state == SLEEPING)
		{
			printf(RESET "%d " YELLOW "%d" RESET" is " CYAN "sleeping\n" RESET,
				diff_from_now(data->start_time), data->number);
			usleep(data->args->time_sleep * 1000);
			data->state = THINKING;
		}
		else
			phil_think(data);
	}
	return (0);
}
