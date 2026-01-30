/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:57:46 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/29 23:09:16 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "time_utils.h"
#include "dongle_protocols.h"

static
void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->cooldown_end_ms = millis() + *dongle->cooldown;
	pthread_mutex_unlock(&dongle->mutex);
	dequeue(&dongle->queue);
}

void	release_two_dongles(t_coder *coder)
{
	t_coder	*left_neighboor;
	t_coder	*right_neighboor;

	release_dongle(coder->left_dongle);
	release_dongle(coder->right_dongle);

	left_neighboor = coder->left_neighboor;
	right_neighboor = coder->right_neighboor;

	pthread_mutex_lock(&left_neighboor->mutex);
	pthread_cond_broadcast(&left_neighboor->cond);
	pthread_mutex_unlock(&left_neighboor->mutex);

	pthread_mutex_lock(&right_neighboor->mutex);
	pthread_cond_broadcast(&right_neighboor->cond);
	pthread_mutex_unlock(&right_neighboor->mutex);
}
