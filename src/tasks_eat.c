/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:08:51 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/03 15:59:20 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->left_fork > philo->right_fork)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	grab_a_fork(philo);
	pthread_mutex_lock(second_fork);
	grab_a_fork(philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->info->state_mutex);
	if (!philo->info->dead)
	{
		printf(GREEN "%ld %d is eating\n" RESET, get_time()
			- philo->info->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->info->state_mutex);
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_usleep(philo, philo->info->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	grab_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->state_mutex);
	if (!philo->info->dead)
		printf(YELLOW "%ld %d has taken a fork\n" RESET, get_time()
			- philo->info->start_time, philo->id);
	pthread_mutex_unlock(&philo->info->state_mutex);
}
