/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_fifo_turn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 00:03:14 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 00:25:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_control.h"

enum e_simulation_status	wait_fifo_turn(t_coder *coder)
{
	t_dongle	left_dongle;
	t_dongle	right_dongle;

	left_dongle = coder->left_dongle;
	right_dongle = coder->right_dongle;
	enqueue(left_dongle, coder);
	enqueue(right_dongle, coder);
	while (queue_top(left_dongle) != coder || queue_top(right_dongle) != coder)
		if (pthread_cond_timedwait())
			return (SIMULATION_STOPPED);
	return (SIMULATION_RUNNING);
}
