/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarpent <hcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:22:26 by hcarpent          #+#    #+#             */
/*   Updated: 2022/06/14 19:59:24 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_msg(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->glob->write_mutex);
	if (action == TAKING_FORK)
		printf("%lld %d has taken a fork\n", ft_get_time(philo), philo->id + 1);
	else if (action == EATING)
		printf("%lld %d is eating\n", ft_get_time(philo), philo->id + 1);
	else if (action == SLEEPING)
		printf("%lld %d is sleeping\n", ft_get_time(philo), philo->id + 1);
	else if (action == THINKING)
		printf("%lld %d is thinking\n", ft_get_time(philo), philo->id + 1);
	else if (action == DIED)
		printf("%lld %d died\n", ft_get_time(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->glob->write_mutex);
}

int	ft_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->glob->die_mutex);
	if (philo->glob->dead)
	{
		pthread_mutex_unlock(&philo->glob->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->glob->die_mutex);
	if (ft_get_time(philo) - philo->last_eat >= philo->glob->time_die)
	{
		pthread_mutex_lock(&philo->glob->die_mutex);
		if (philo->glob->dead)
		{
			pthread_mutex_unlock(&philo->glob->die_mutex);
			return (1);
		}
		ft_msg(philo, DIED);
		philo->glob->dead = 1;
		pthread_mutex_unlock(&philo->glob->die_mutex);
		return (1);
	}
	return (0);
}

int	ft_wait(t_philo *philo, int time_wait)
{
	long long	start;

	start = ft_get_time(philo);
	while (ft_get_time(philo) - start < time_wait)
	{
		usleep(100);
		if (ft_die(philo))
			return (1);
	}
	return (0);
}

int	ft_take_forks(t_philo *philo, pthread_mutex_t *fork_mutex, int *fork, int i)
{
	if (philo->id % 2 && !philo->nb_eat && !i)
		usleep(10000);
	pthread_mutex_lock(fork_mutex);
	while (!*fork)
	{
		pthread_mutex_unlock(fork_mutex);
		usleep(100);
		if (ft_die(philo))
			return (1);
		pthread_mutex_lock(fork_mutex);
	}
	*fork = 0;
	pthread_mutex_unlock(fork_mutex);
	ft_msg(philo, TAKING_FORK);
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_take_forks(philo, philo->lfork_mutex, philo->lfork, 0)
			|| ft_take_forks(philo, philo->rfork_mutex, philo->rfork, 1))
			return (NULL);
		ft_msg(philo, EATING);
		philo->last_eat = ft_get_time(philo);
		if (ft_wait(philo, philo->glob->time_eat))
			return (NULL);
		pthread_mutex_lock(philo->lfork_mutex);
		*philo->lfork = 1;
		pthread_mutex_unlock(philo->lfork_mutex);
		pthread_mutex_lock(philo->rfork_mutex);
		*philo->rfork = 1;
		pthread_mutex_unlock(philo->rfork_mutex);
		if (++philo->nb_eat == philo->glob->nb_philos_eat)
			return (NULL);
		ft_msg(philo, SLEEPING);
		if (ft_wait(philo, philo->glob->time_sleep))
			return (NULL);
		ft_msg(philo, THINKING);
	}
}
