/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_config_control.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:26:20 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/30 18:34:59 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

const t_codexion_config	*codexion_config_control(const t_codexion_config *set_config)
{
	static t_codexion_config	codexion_config;

	if (set_config)
		codexion_config = *set_config;
	return ((const t_codexion_config *)&codexion_config);
}
