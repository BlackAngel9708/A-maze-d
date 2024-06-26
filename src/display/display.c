/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Display the moves of the robot
*/

#include "algorithme/bfs.h"
#include "amazed.h"
#include "my_macros.h"
#include "my.h"
#include <stddef.h>

static
void display_single_move(info_t *info,
    shortest_path_t *robot_rooms[info->nb_robots + 1],
    int *line_print, int current_robot)
{
    if (info == NULL || line_print == NULL || robot_rooms == NULL
        || robot_rooms[current_robot] == NULL)
        return;
    if (my_strcmp(robot_rooms[current_robot]->room->name,
            info->start_name) != 0) {
        if (*line_print == TRUE)
            my_putchar(' ');
        *line_print = TRUE;
        my_putstr("P");
        my_put_nbr(current_robot + 1);
        my_putstr("-");
        my_putstr(robot_rooms[current_robot]->room->name);
        robot_rooms[current_robot + 1] = robot_rooms[current_robot]->previous;
    }
}

static
int display_robots_move(info_t *info,
    shortest_path_t *robot_rooms[info->nb_robots + 1], int *line_print)
{
    int robot_finished = 0;

    for (int current_robot = 0; current_robot < info->nb_robots;
        current_robot += 1) {
        if (robot_rooms[current_robot] == NULL)
            continue;
        display_single_move(info, robot_rooms, line_print, current_robot);
        if (my_strcmp(robot_rooms[current_robot]->room->name, info->end_name)
            == 0) {
            robot_finished += 1;
        }
        robot_rooms[current_robot] = robot_rooms[current_robot]->next;
    }
    return robot_finished;
}

static
void display_space(int index)
{
    if (index > 0)
        my_putchar(' ');
}

static
int check_only_one_move(shortest_path_t *shortest_path, info_t *info)
{
    shortest_path_t *current_room = 0;

    if (shortest_path == NULL || shortest_path->room == NULL)
        return FALSE;
    if (shortest_path->next != NULL && shortest_path->next->room != NULL
        && shortest_path->next->room->next == NULL) {
        current_room = shortest_path->next;
        for (int i = 0; i < info->nb_robots; i += 1) {
            display_space(i);
            my_putstr("P");
            my_put_nbr(i + 1);
            my_putstr("-");
            my_putstr(current_room->room->name);
        }
        my_putchar('\n');
        return TRUE;
    }
    return FALSE;
}

int display_shortest_path(shortest_path_t *shortest_path, info_t *info)
{
    shortest_path_t *robot_rooms[info->nb_robots + 1];
    int robot_finished = 0;
    int line_print = 0;

    if (check_only_one_move(shortest_path, info) == TRUE)
        return SUCCESS;
    for (int i = 0; i <= info->nb_robots; i += 1)
        robot_rooms[i] = NULL;
    robot_rooms[0] = shortest_path;
    while (robot_finished < info->nb_robots) {
        robot_finished += display_robots_move(info, robot_rooms, &line_print);
        if (line_print == TRUE)
            my_putchar('\n');
        line_print = FALSE;
    }
    return SUCCESS;
}
