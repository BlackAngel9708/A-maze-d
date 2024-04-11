/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Display the moves of the robot
*/

#include "algorithme/bfs.h"
#include "my_macros.h"
#include "my.h"

int display_shortest_path(shortest_path_t *shortest_path, int nb_robots,
    int start_room)
{
    if (shortest_path == NULL || shortest_path->room == NULL)
        return FAILURE;
    if (shortest_path->next == NULL)
        return FAILURE;
    display_shortest_path(shortest_path->next, nb_robots, start_room);
    for (int i = start_room; i <= nb_robots; i += 1) {
        if (i > 1)
            shortest_path = shortest_path->next;
        if (shortest_path == NULL || shortest_path->next == NULL)
            break;
        if (i > 1)
            my_putchar(' ');
        my_putstr("P");
        my_put_nbr(i);
        my_putstr("-");
        my_putstr(shortest_path->room->name);
    }
    my_putchar('\n');
    return SUCCESS;
}
