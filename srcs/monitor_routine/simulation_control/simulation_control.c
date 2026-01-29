/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:59:42 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 16:06:08 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>

bool	simulation_control(const bool *set_state)
{
	static bool				is_running = true;
	static pthread_mutex_t	simulation_ctl_mutex = PTHREAD_MUTEX_INITIALIZER;
	bool					current_state;

	pthread_mutex_lock(&simulation_ctl_mutex);
	if (set_state)
		is_running = *set_state;
	current_state = is_running;
	pthread_mutex_unlock(&simulation_ctl_mutex);
	return (current_state);
}

void	stop_simulation(void)
{
	const bool	running_state = false;

	simulation_control(&running_state);
}
