/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarpent <hcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 02:57:57 by hcarpent          #+#    #+#             */
/*   Updated: 2022/06/14 19:52:44 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clear(t_glob *glob, int i)
{
	while (i < glob->nb_philos)
		pthread_mutex_destroy(&glob->forks_mutexes[i++]);
	pthread_mutex_destroy(&glob->write_mutex);
	pthread_mutex_destroy(&glob->die_mutex);
	free(glob->forks);
	free(glob->forks_mutexes);
	free(glob->philos);
	free(glob->tid);
}

int	ft_create_threads(t_glob *glob, int i)
{
	while (i < glob->nb_philos)
	{
		if (!i)
		{
			glob->philos[i].lfork_mutex
				= &glob->forks_mutexes[glob->nb_philos - 1];
			glob->philos[i].lfork = &glob->forks[glob->nb_philos - 1];
		}
		else
		{
			glob->philos[i].lfork_mutex = &glob->forks_mutexes[i - 1];
			glob->philos[i].lfork = &glob->forks[i - 1];
		}
		glob->philos[i].rfork_mutex = &glob->forks_mutexes[i];
		glob->philos[i].rfork = &glob->forks[i];
		glob->philos[i].id = i;
		glob->philos[i].last_eat = 0;
		glob->philos[i].nb_eat = 0;
		glob->philos[i].glob = glob;
		if (pthread_create(&glob->tid[i], NULL, ft_routine, &glob->philos[i]))
			return (ft_error("Thread creation failure\n", glob, 4, 3));
		i++;
	}
	return (0);
}

int	ft_init_mutexes(int i, t_glob *glob)
{
	glob->forks_mutexes = malloc(sizeof(pthread_mutex_t) * glob->nb_philos);
	if (!glob->forks_mutexes)
		return (ft_error("Memory allocation failure\n", glob, 1, 0));
	while (i < glob->nb_philos)
	{
		if (pthread_mutex_init(&glob->forks_mutexes[i++], NULL))
		{
			glob->nb_philos = i;
			return (ft_error("Mutex initialisation failure\n", glob, 2, 1));
		}
	}
	if (pthread_mutex_init(&glob->write_mutex, NULL))
		return (ft_error("Mutex initialisation failure\n", glob, 2, 1));
	if (pthread_mutex_init(&glob->die_mutex, NULL))
		return (ft_error("Mutex initialisation failure\n", glob, 2, 2));
	return (0);
}

int	ft_philosophers(t_glob *glob)
{
	int	i;

	glob->forks = malloc(sizeof(int) * glob->nb_philos);
	if (!glob->forks)
		return (ft_error("Memory allocation failure\n", glob, 0, 0));
	ft_fill(glob->forks, 1, glob->nb_philos);
	if (ft_init_mutexes(0, glob))
		return (1);
	glob->philos = malloc(sizeof(t_philo) * glob->nb_philos);
	if (!glob->philos)
		return (ft_error("Memory allocation failure\n", glob, 2, 3));
	glob->tid = malloc(sizeof(pthread_t) * glob->nb_philos);
	if (!glob->tid)
		return (ft_error("Memory allocation failure\n", glob, 3, 3));
	glob->dead = 0;
	glob->start = timestamp();
	if (ft_create_threads(glob, 0))
		return (1);
	i = 0;
	while (i < glob->nb_philos)
		pthread_join(glob->tid[i++], NULL);
	ft_clear(glob, 0);
	return (0);
}
