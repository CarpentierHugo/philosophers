/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarpent <hcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 05:56:48 by hcarpent          #+#    #+#             */
/*   Updated: 2022/06/14 19:52:49 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error(char *str, t_glob *glob, int to_free, int to_destroy)
{
	int	i;

	if (to_free)
		free(glob->forks);
	if (to_free > 1)
		free(glob->forks_mutexes);
	if (to_free > 2)
		free(glob->philos);
	if (to_free == 4)
		free(glob->tid);
	i = 0;
	if (to_destroy)
	{
		while (i < glob->nb_philos)
			pthread_mutex_destroy(&glob->forks_mutexes[i++]);
	}
	if (to_destroy > 1)
		pthread_mutex_destroy(&glob->write_mutex);
	if (to_destroy == 3)
		pthread_mutex_destroy(&glob->die_mutex);
	write(2, str, ft_strlen(str));
	return (1);
}
