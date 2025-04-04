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

int number_of_moves(struct game_state start) {
    
    
    return 0;
}
