#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    uint64_t val = serialize(state);
    insert_at_head(&(q->data), val);

}

struct game_state dequeue(struct queue *q) {
    
    uint64_t val = remove_from_tail(&(q->data));
    struct game_state game1 = deserialize(val);

    return game1;
}

static int finalCheck (struct game_state start) {
    uint8_t tiles[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!(tiles[i][j] == start.tiles[i][j])) {
                return 0;
            }
        }
    }
    return 1;
}

static int searchList (struct linked_list list, uint64_t serial) {
    struct list_node *current = list.head;

while (current != NULL)
{
  if (serial == current->value) {
    return 1;
  }
  current = current->next;
}
    return 0;
}

int number_of_moves(struct game_state start) {
    struct queue q = {.data = {.head = NULL}};
    struct game_state current = start;
    enqueue(&q, start);
    while (q.data.head != NULL) {
        current  = dequeue(&q);
        if (finalCheck(current)) {
            free_list(q.data);
            return current.num_steps;
        }
        // printf("hello\n");
        struct game_state next = current;
        if (next.empty_row == 3) {
            // printf("up should not move\n");
            // printf("next.empty_row = %d, current.empty_row = %d\n", next.empty_row, current.empty_row);
        }
        move_up(&next);
        if (!searchList(q.data, serialize(next)) && next.empty_row != current.empty_row) {
            // printf("up\n");
            enqueue(&q, next);
        }
        next = current;
        move_down(&next);
        if (!searchList(q.data, serialize(next)) && next.empty_row != current.empty_row) {
            // printf("down\n");
            enqueue(&q, next);
        }
        next = current;
        move_right(&next);
        if (!searchList(q.data, serialize(next)) && next.empty_col != current.empty_col) {
            // printf("right\n");
            enqueue(&q, next);
        }
        next = current;
        move_left(&next);
        if (!searchList(q.data, serialize(next)) && next.empty_col != current.empty_col) {
            // printf("left\n");
            enqueue(&q, next);
        }
    }

    return 1;
}
