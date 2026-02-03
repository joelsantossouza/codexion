/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_edf_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:52:40 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/03 17:13:20 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "coder.h"

static
bool	is_my_turn(t_coder *me)
{
	t_coder			*left_neighbor;
	t_coder			*right_neighbor;
	bool			have_left_priority;
	bool			have_right_priority;

	left_neighbor = me->left_neighbor;
	right_neighbor = me->right_neighbor;

	pthread_mutex_lock(&left_neighbor->mutex);
	pthread_mutex_lock(&right_neighbor->mutex);

	if (me->deadline_ms < left_neighbor->deadline_ms)
		have_left_priority = true;
	else if (me->deadline_ms == left_neighbor->deadline_ms)
		have_left_priority = me->compilations_done < left_neighbor->compilations_done;

	if (me->deadline_ms < right_neighbor->deadline_ms)
		have_right_priority = true;
	else if (me->deadline_ms == right_neighbor->deadline_ms)
		have_right_priority = me->compilations_done < right_neighbor->compilations_done;

	pthread_mutex_unlock(&right_neighbor->mutex);
	pthread_mutex_unlock(&left_neighbor->mutex);

	return (have_left_priority && have_right_priority);
}

enum e_simulation_status	wait_edf_turn(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	while (is_my_turn(coder) == false)
	{
		if (is_simulation_running() == false)
		{
			pthread_mutex_unlock(&coder->mutex);
			return (SIMULATION_STOPPED);
		}
		if (pthread_cond_timedwait(&coder->cond, &coder->mutex, &coder->deadline_ts) == ETIMEDOUT)
		{
			pthread_mutex_unlock(&coder->mutex);
			return (SIMULATION_STOPPED);
		}
	}
	pthread_mutex_unlock(&coder->mutex);
	return (SIMULATION_RUNNING);
}
