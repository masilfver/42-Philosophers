/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deaths.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:04:36 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/03 13:04:38 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	all_philosophers_ate_enough(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_mutex_lock(&info->philos[i].meal_mutex);
		if (info->philos[i].eat_count < info->has_to_eat)
		{
			pthread_mutex_unlock(&info->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&info->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

int	check_philo_death(t_philo *ph, t_info *info)
{
	long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&ph->meal_mutex);
	if (current_time - ph->last_meal > info->time_to_die)
	{
		pthread_mutex_unlock(&ph->meal_mutex);
		pthread_mutex_lock(&info->state_mutex);
		if (!info->dead_prt)
		{
			printf(CYAN "%ld %d died\n" RESET, get_time()
				- info->start_time, ph->id);
			info->dead_prt = true;
			info->dead = true;
		}
		pthread_mutex_unlock(&info->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->meal_mutex);
	return (0);
}

int	check_state(t_info *info)
{
	pthread_mutex_lock(&info->state_mutex);
	if (info->dead)
	{
		pthread_mutex_unlock(&info->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->state_mutex);
	return (0);
}

void	*check_deaths(void *void_info)
{
	int		i;
	t_info	*info;
	t_philo	*ph;

	info = (t_info *)void_info;
	while (1)
	{
		if (check_state(info))
			return (NULL);
		if (all_philosophers_ate_enough(info) && info->has_to_eat != -1)
		{
			pthread_mutex_lock(&info->state_mutex);
			info->dead = true;
			pthread_mutex_unlock(&info->state_mutex);
			return (NULL);
		}
		i = -1;
		while (++i < info->nbr_philo)
		{
			ph = &info->philos[i];
			if (check_philo_death(ph, info))
				return (NULL);
		}
	}
	return (NULL);
}
