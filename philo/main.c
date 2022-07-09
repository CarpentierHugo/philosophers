/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarpent <hcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:37:21 by hcarpent          #+#    #+#             */
/*   Updated: 2022/06/14 19:52:46 by hcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_verif_nb(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9' || j > 9)
				return (1);
			j++;
		}
	}
	return (0);
}

int	ft_assign_args(t_glob *glob, char **argv, int argc)
{
	if (ft_verif_nb(argv))
		return (ft_error("Wrong arguments\n", glob, 0, 0));
	glob->nb_philos = ft_atoi(argv[1]);
	glob->time_die = ft_atoi(argv[2]);
	glob->time_eat = ft_atoi(argv[3]);
	glob->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		glob->nb_philos_eat = ft_atoi(argv[5]);
	else
		glob->nb_philos_eat = -1;
	if (!glob->nb_philos || !glob->time_die || !glob->time_eat
		|| !glob->time_sleep || !glob->nb_philos_eat)
		return (ft_error("Wrong arguments\n", glob, 0, 0));
	return (0);
}

int	main(int argc, char **argv)
{
	t_glob	glob;

	if (argc != 5 && argc != 6)
		return (ft_error("Wrong number of arguments\n", &glob, 0, 0));
	if (ft_assign_args(&glob, argv, argc))
		return (1);
	return (ft_philosophers(&glob));
}
