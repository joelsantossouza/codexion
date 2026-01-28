/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_fifo_turn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:03:14 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 11:51:25 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_control.h"

enum e_simulation_status	wait_fifo_turn(t_coder *coder)
{
	t_dongle_queue	*left_queue;
	t_dongle_queue	*right_queue;

	left_queue = &coder->left_dongle->queue;
	right_queue = &coder->right_dongle->queue;
	pthread_mutex_lock();
	enqueue(left_queue, coder);
	enqueue(right_queue, coder);
	while (queue_top(left_queue) != coder || queue_top(right_queue) != coder)
	{
		if (is_simulation_running() == false)
		{
			pthread_mutex_unlock();
			return (SIMULATION_STOPPED);
		}
		if (pthread_cond_timedwait())
		{
			pthread_mutex_unlock();
			return (SIMULATION_STOPPED);
		}
	}
	pthread_mutex_unlock();
	return (SIMULATION_RUNNING);
}
