/*
** EPITECH PROJECT, 2021
** My world
** File description:
** center mouse
*/

#include <SFML/Graphics/RenderWindow.h>

#include "functions.h"

void center_mouse(sfRenderWindow *wind)
{
    sfVector2u size = sfRenderWindow_getSize(wind);

    sfMouse_setPositionRenderWindow(
        (sfVector2i){size.x / 2, size.y / 2}, wind);
}
