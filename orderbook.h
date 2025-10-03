#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "types.h"

Order* generate_random_order(OrderBook* orderBook);
Order* split(Order* head);
Order* merge(Order* first, Order* second, int descending);
Order* merge_sort(Order* head, int descending);  // 1 or 0   1 for descending, 0 for ascending for sell side)
void match_orders(OrderBook* orderBook);
void display_order_book(const OrderBook* orderBook);
void free_order_book(OrderBook* orderBook);

#endif // ORDERBOOK_H