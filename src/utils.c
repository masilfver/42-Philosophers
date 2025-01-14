/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:48:16 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/04 10:34:37 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_usleep(t_philo *philo, int time_in_ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
	{
		if (check_if_died(philo->info))
			return (0);
		usleep(100);
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf(RED "%s\n" RESET, ERR_GTM);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	check_if_died(t_info *info)
{
	pthread_mutex_lock(&info->state_mutex);
	if (info->dead)
	{
		pthread_mutex_unlock(&info->state_mutex);
		return (true);
	}
	pthread_mutex_unlock(&info->state_mutex);
	return (false);
}
