/*
** EPITECH PROJECT, 2021
** rpg
** File description:
** fight_pathfinding
*/

#include "Rpg/Fight/fight.h"
#include "my_containers/my_vector.h"
#include "My/my_display.h"

int get_next_pos(fight_t *fight, int current, int dir);
int node_compare(node_t *na, node_t *nb);
void sort_nodes(node_t **nodes);
int get_heuristic_cost(fight_t *fight, int pos_a, int pos_b);

static node_t **init_nodes(fight_t *fight, int start, int end)
{
    node_t **nodes = malloc(sizeof(node_t *) * fight->size.x * fight->size.y);
    node_t *node;

    for (int x = 0; x < fight->size.x; x++) {
        for (int y = 0; y < fight->size.y; y++) {
            node = malloc(sizeof(node_t));
            node->g_cost = __SHRT_MAX__;
            node->l_cost = __SHRT_MAX__;
            node->parent = NULL;
            node->visited = 0;
            node->wall = !cell_is_empty(&fight->grid[x + y * fight->size.x]);
            node->pos = x + y * fight->size.x;
            nodes[x + y * fight->size.x] = node;
        }
    }
    nodes[start]->l_cost = 0;
    nodes[start]->g_cost = get_heuristic_cost(fight, 0, end);
    return nodes;
}

static int *resolve_path(fight_t *fight, node_t *end)
{
    int *path = NULL;
    int size = 0;
    int i;
    node_t *current = end;

    if (!current)
        return path;
    while (current) {
        size++;
        current = current->parent;
    }
    current = end;
    path = malloc(sizeof(int) * (size + 1));
    i = size - 1;
    while (current) {
        path[i--] = current->pos;
        current = current->parent;
    }
    path[size] = END_ARRAY;
    return path;
}

static void handle_dir(fight_t *fight, sfVector2i dir_cur, \
node_t **nodes, node_t ***opened, int end)
{
    node_t *current = nodes[dir_cur.y];
    node_t *neighbour;
    int cost;
    int next_pos = get_next_pos(fight, current->pos, dir_cur.x);

    if (next_pos == INEXISTING)
        return;
    neighbour = nodes[next_pos];
    if (!neighbour->visited && !neighbour->wall)
        my_vector_push((size_t **)opened, (size_t)neighbour);
    cost = current->l_cost + \
    get_heuristic_cost(fight, current->pos, neighbour->pos);
    if (cost < neighbour->l_cost) {
        neighbour->parent = current;
        neighbour->l_cost = cost;
        neighbour->g_cost = neighbour->l_cost + \
        get_heuristic_cost(fight, neighbour->pos, end);
    }
}

static int *end_algo(fight_t *fight, node_t **opened, \
node_t *current, node_t **nodes)
{
    int *path = NULL;

    my_vector_free((size_t **)&opened);
    if ((current != NULL))
        path = resolve_path(fight, current);
    for (int x = 0; x < fight->size.x; x++) {
        for (int y = 0; y < fight->size.y; y++) {
            free(nodes[x + y * fight->size.x]);
        }
    }
    free(nodes);
    return path;
}

int *fight_get_path(fight_t *fight, int from, int to)
{
    node_t **nodes = init_nodes(fight, from, to);
    my_vector(opened, node_t *, (fight->size.x * fight->size.y) / 2);
    node_t *current = nodes[from];

    my_vector_push((size_t **)&opened, (size_t)current);
    while (!my_vector_empty((size_t *)opened)) {
        sort_nodes(opened);
        while (!my_vector_empty((size_t *)opened) && \
            ((node_t *)my_vector_top((size_t *)opened))->visited)
            my_vector_pop((size_t **)&opened);
        if (my_vector_empty((size_t *)opened))
            break;
        current = (node_t *)my_vector_pop((size_t **)&opened);
        if (current->pos == to)
            return end_algo(fight, opened, current, nodes);
        current->visited = 1;
        for (int dir = 0; dir < 4; dir++)
            handle_dir(fight, \
            (sfVector2i){dir, current->pos}, nodes, &opened, to);
    }
    return end_algo(fight, opened, NULL, nodes);
}