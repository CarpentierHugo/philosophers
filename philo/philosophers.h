/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarpent <hcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:26:56 by hcarpent          #+#    #+#             */
/*   Updated: 2022/06/14 19:52:42 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_action;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*lfork_mutex;
	pthread_mutex_t	*rfork_mutex;
	int				*lfork;
	int				*rfork;
	long long		last_eat;
	int				nb_eat;
	struct s_glob	*glob;
}	t_philo;

typedef struct s_glob
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_philos_eat;
	int				dead;
	long long		start;
	pthread_t		*tid;
	t_philo			*philos;
	int				*forks;
	pthread_mutex_t	*forks_mutexes;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	die_mutex;
}	t_glob;

int			ft_atoi(const char *str);
void		ft_fill(int *tab, int nb, int size);
long long	timestamp(void);
long long	ft_get_time(t_philo *philo);
int			ft_take_forks(t_philo *philo, pthread_mutex_t *fork_mutex,
				int *fork, int i);
void		ft_msg(t_philo *philo, int action);
int			ft_die(t_philo *philo);
void		*ft_routine(void *arg);
int			ft_philosophers(t_glob *args);
int			ft_strlen(char *str);
int			ft_error(char *str, t_glob *glob, int to_free, int to_destroy);

#endif