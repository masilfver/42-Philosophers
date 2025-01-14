/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:06:34 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/03 13:13:07 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	prep_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philos = malloc(sizeof(t_philo) * info->nbr_philo);
	if (!info->philos)
	{
		while (i < info->nbr_philo)
		{
			pthread_mutex_destroy(&info->forks[i]);
			i++;
		}
		free(info->forks);
		free(info->thread);
		printf(RED "%s\n" RESET, ERR_MAL);
		return (1);
	}
	return (0);
}

void	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		info->philos[i].eat_count = 0;
		info->philos[i].last_meal = -1;
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].right_fork = &info->forks[(i + 1) % info->nbr_philo];
		if (pthread_mutex_init(&info->philos[i].meal_mutex, NULL) != 0)
			printf(RED "%s %d\n" RESET, ERR_MMX, i + 1);
	}
}
