/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:57:46 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/05 17:38:26 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "time_utils.h"
#include "dongle_protocols.h"

static
void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_being_used = false;
	dongle->cooldown_end_ms = millis() + *dongle->cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}

void	release_two_dongles(t_coder *coder)
{
	t_coder	*left_neighbor;
	t_coder	*right_neighbor;

	release_dongle(coder->left_dongle);
	release_dongle(coder->right_dongle);

	left_neighbor = coder->left_neighbor;
	right_neighbor = coder->right_neighbor;

	pthread_mutex_lock(&left_neighbor->mutex);
	pthread_cond_broadcast(&left_neighbor->cond);
	pthread_mutex_unlock(&left_neighbor->mutex);

	pthread_mutex_lock(&right_neighbor->mutex);
	pthread_cond_broadcast(&right_neighbor->cond);
	pthread_mutex_unlock(&right_neighbor->mutex);
}
