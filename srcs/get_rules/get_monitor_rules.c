/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_monitor_rules.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:26:20 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/06 21:31:22 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	get_monitor_rules(int *ncoders, int *cooldown, int *ncompiles_required)
{
	static int	already_initialized = FALSE;
	static int	number_of_coders;
	static int	dongle_cooldown;
	static int	number_of_compiles_required;

	if (already_initialized == FALSE)
	{
		already_initialized = TRUE;
		number_of_coders = *ncoders;
		dongle_cooldown = *cooldown;
		number_of_compiles_required = *ncompiles_required;
		return (FALSE);
	}
	*ncoders = number_of_coders;
	*cooldown = dongle_cooldown;
	*ncompiles_required = number_of_compiles_required;
	return (TRUE);
}
