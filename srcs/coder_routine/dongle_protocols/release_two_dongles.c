/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:57:46 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 11:46:27 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline
void	release_dongle(t_dongle *dongle)
{
	t_dongle_queue	*dongle_queue;

	pthread_mutex_lock();
	dongle->last_release_ms = millis();
	dongle_queue = dongle->queue;
	if (dongle_queue->first != dongle_queue->last)
		dongle_queue->first = (dongle_queue->first + 1) % QUEUE_SIZE;
	pthread_mutex_unlock();
}

void	release_two_dongles(t_coder *coder)
{
	t_dongle	left_dongle;
	t_dongle	right_dongle;

	left_dongle = coder->left_dongle;
	right_dongle = coder->right_dongle;
	release_dongle(left_dongle);
	release_dongle(right_dongle);
	pthread_cond_broadcast();
	pthread_cond_broadcast();
}
