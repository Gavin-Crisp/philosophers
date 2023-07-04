/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:20:42 by gcrisp            #+#    #+#             */
/*   Updated: 2023/06/16 09:41:32 by gcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input.h"
#include "structs.h"
#include "philosopher.h"
#include <pthread.h>
#include <sys/time.h>

void	cleanup(pthread_mutex_t *forks, t_phil *phil_data, pthread_t *threads,
		unsigned int n)
{
	unsigned int	i;

	if (forks)
	{
		i = 0;
		while (i < n)
			pthread_mutex_destroy(&forks[i++]);
		free(forks);
	}
	free(phil_data);
	if (!threads)
		return ;
	i = 0;
	while (i < n)
		pthread_detach(threads[i++]);
	free(threads);
}

t_phil	*get_phil_data(t_args *args, pthread_mutex_t *forks)
{
	t_phil			*out;
	struct timeval	now;
	unsigned int	i;

	out = malloc(sizeof(t_phil) * args->phil_num);
	if (!out)
		return (0);
	gettimeofday(&now, 0);
	i = args->phil_num;
	while (i--)
	{
		out[i] = (t_phil){THINKING, i + 1, 0, args, forks, now, now};
		if (i % 2)
			out[i].state = SLEEPING;
	}
	return (out);
}

int	init(pthread_mutex_t **forks, t_phil **phil_data, pthread_t **threads,
		t_args *args)
{
	unsigned int	i;
	int				ret;

	*forks = malloc(sizeof(pthread_mutex_t) * args->phil_num);
	*phil_data = get_phil_data(args, *forks);
	*threads = malloc(sizeof(pthread_t) * args->phil_num);
	if (!*forks || !*phil_data || !*threads)
		return (1);
	ret = 0;
	i = 0;
	while (i < args->phil_num && !ret)
		ret = pthread_mutex_init(&(*forks)[i++], 0);
	if (ret)
		return (1);
	while (i-- && !ret)
		ret = pthread_create(&(*threads)[i], 0, philosopher, &(*phil_data)[i]);
	return (ret);
}

void	loop(t_phil *phil_data, t_args *args)
{
	unsigned int	i;
	unsigned int	full;

	while (1)
	{
		i = args->phil_num;
		full = 0;
		while (i--)
		{
			if ((unsigned int)diff_from_now(phil_data[i].last_ate)
				>= args->time_die)
			{
				printf("%d " YELLOW "%d" RED " died\n" RESET,
					diff_from_now(phil_data[i].start_time),
					phil_data[i].number);
				phil_data[i].state = DEAD;
				return ;
			}
			if (phil_data[i].eat_times >= args->eat_times && args->eat_times)
				full++;
		}
		if (full == args->phil_num)
			return ;
	}
}

int	main(int ac, char **av)
{
	t_args			args;
	pthread_mutex_t	*forks;
	t_phil			*phil_data;
	pthread_t		*phils;

	parse_input(ac, av, &args);
	if (init(&forks, &phil_data, &phils, &args))
	{
		cleanup(forks, phil_data, phils, args.phil_num);
		init_error();
	}
	loop(phil_data, &args);
	cleanup(forks, phil_data, phils, args.phil_num);
}
