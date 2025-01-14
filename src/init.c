/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:00:41 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/03 17:08:09 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	mutex_init(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			printf(RED "%s\n" RESET, ERR_FORK);
			while (--i >= 0)
				pthread_mutex_destroy(&info->forks[i]);
			free(info->forks);
			free(info->thread);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_thp(t_info *info)
{
	info->thread = malloc(sizeof(pthread_t) * info->nbr_philo);
	if (!info->thread)
	{
		printf(RED "%s\n" RESET, ERR_MAL);
		return (1);
	}
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nbr_philo);
	if (!info->forks)
	{
		printf(RED "%s\n" RESET, ERR_MAL);
		return (1);
	}
	if (mutex_init(info) == 1)
		return (1);
	if (prep_philo(info) == 1)
		return (1);
	return (0);
}

int	init_more_info(int argc, char **argv, t_info *info)
{
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->dead_prt = false;
	if (argc == 6)
	{
		info->has_to_eat = ft_atoi(argv[5]);
		if (info->has_to_eat < 1)
		{
			printf(RED "%s\n" RESET, ERR_EAT);
			return (1);
		}
	}
	else
		info->has_to_eat = -1;
	info->dead = false;
	return (0);
}

int	init_info(int argc, char **argv, t_info *info)
{
	info->nbr_philo = ft_atoi(argv[1]);
	if (info->nbr_philo < 1 || info->nbr_philo > 200)
	{
		printf(RED "%s\n" RESET, ERR_PHI);
		return (1);
	}
	if (pthread_mutex_init(&info->state_mutex, NULL) != 0)
	{
		printf(RED "%s\n" RESET, ERR_STA);
		return (1);
	}
	if (init_more_info(argc, argv, info) == 1)
		return (1);
	return (0);
}
