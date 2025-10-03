#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "orderbook.h"

#define N 10 // Number of ticks


int main() {

    OrderBook orderBook = {NULL, NULL, 1}; // Initialize empty order book

    for (int tick = 0; tick < N; tick++) {

        generate_random_order(&orderBook);

        // sort both sides
        orderBook.buyOrders = merge_sort(orderBook.buyOrders, 1);
        orderBook.sellOrders = merge_sort(orderBook.sellOrders, 0);
        
        display_order_book(&orderBook);
        match_orders(&orderBook);
        
        printf("----- End of Tick %d -----\n", tick);
    }
    free_order_book(&orderBook);
    return 0;
}
