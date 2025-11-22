/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:49:58 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/22 22:52:35 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* bridge.c                                           :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: Fusion Team <42>                           +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/11/22 12:00:00 by Fusion Team       #+#    #+#             */
/* Updated: 2025/11/22 12:00:00 by Fusion Team      ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/**
 * @brief Configura los vectores de direccion (dir) y plano de camara (plane)
 * basandose en la orientación inicial del jugador (N, S, E, W).
 * * N (0) -> Dir (0, -1) | Plane (0.66, 0)
 * S (1) -> Dir (0, 1)  | Plane (-0.66, 0)
 * E (2) -> Dir (1, 0)  | Plane (0, 0.66)
 * W (3) -> Dir (-1, 0) | Plane (0, -0.66)
 */
static void	ft_set_orientation_vectors(t_grl *grl)
{
	if (grl->player_dir == 0) // N
	{
		grl->player.dir_x = 0.0;
		grl->player.dir_y = -1.0;
		grl->player.plane_x = 0.66;
		grl->player.plane_y = 0.0;
	}
	else if (grl->player_dir == 1) // S
	{
		grl->player.dir_x = 0.0;
		grl->player.dir_y = 1.0;
		grl->player.plane_x = -0.66;
		grl->player.plane_y = 0.0;
	}
	else if (grl->player_dir == 2) // E
	{
		grl->player.dir_x = 1.0;
		grl->player.dir_y = 0.0;
		grl->player.plane_x = 0.0;
		grl->player.plane_y = 0.66;
	}
	else if (grl->player_dir == 3) // W
	{
		grl->player.dir_x = -1.0;
		grl->player.dir_y = 0.0;
		grl->player.plane_x = 0.0;
		grl->player.plane_y = -0.66;
	}
}

/**
 * @brief Función Puente (Integration Layer).
 * Transfiere los datos parseados por Alex (Ints, Char*) a las estructuras
 * físicas y gráficas del motor de Rubén (Doubles, Vectores).
 */
void	ft_convert_data(t_grl *grl)
{
	// 1. Convertir Posición (De celda int a centro de celda double)
	// Sumamos 0.5 para que el jugador empiece EXACTAMENTE en el centro del cuadrado.
	grl->player.pos_x = (double)grl->player_col + 0.5;
	grl->player.pos_y = (double)grl->player_row + 0.5;

	// 2. Configurar Vectores de Mirada y Cámara
	ft_set_orientation_vectors(grl);

	// 3. (Opcional) Debug inicial
	printf("✅ BRIDGE: Datos convertidos.\n");
	printf("   -> Pos: [%f, %f]\n", grl->player.pos_x, grl->player.pos_y);
	printf("   -> Dir: [%f, %f]\n", grl->player.dir_x, grl->player.dir_y);
}