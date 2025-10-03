#ifndef TYPES_H
#define TYPES_H

typedef struct Order {
    int id;
    char type; // B for buy, S for sell
    int quantity;
    double price;
    struct Order* next;
} Order;

typedef struct OrderBook {
    Order* buyOrders; // linked list of buy orders (head of linked list sorted in descending order by price)
    Order* sellOrders; // linked list of sell orders (head of linked list sorted in ascending order by price)
    int nextOrderId; // to assign unique IDs to orders
} OrderBook;

#endif // TYPES_H
