/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:40:43 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 20:44:21 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "time_manipulation.h"

uint64_t	timestamp(const uint64_t *new_start)
{
	static uint64_t	start_saved;

	if (new_start)
		start_saved = *new_start;
	return (millis() - start_saved);
}
