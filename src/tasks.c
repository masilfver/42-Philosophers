/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:48:12 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/03 15:58:56 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->state_mutex);
	if (!philo->info->dead)
		printf(MAGENTA "%ld %d is thinking\n" RESET, get_time()
			- philo->info->start_time, philo->id);
	pthread_mutex_unlock(&philo->info->state_mutex);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->state_mutex);
	if (!philo->info->dead)
	{	
		printf(BLUE "%ld %d is sleeping\n" RESET, get_time()
			- philo->info->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->info->state_mutex);
	philo_usleep(philo, philo->info->time_to_sleep);
}
