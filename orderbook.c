#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "orderbook.h"

Order* generate_random_order(OrderBook* orderBook) {
    Order* newOrder = malloc(sizeof(Order));
    if (!newOrder) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newOrder->id = orderBook->nextOrderId++;
    newOrder->type = (rand() % 2) ? 'B' : 'S'; // Randomly choose buy or sell
    newOrder->quantity = (rand() % 100) + 1; // Random quant between 1 - 100
    newOrder->price = ((rand() % 1000) / 10.0) + 1.0; // Random price between 1.0 - 100.0
    newOrder->next = NULL;

    if (newOrder->type == 'B') {
        // insert into buy linked list in descending order
        newOrder->next = orderBook->buyOrders;
        orderBook->buyOrders = newOrder;
    } else {
        // insert into sell linked list in ascending order
        newOrder->next = orderBook->sellOrders;
        orderBook->sellOrders = newOrder;
    }
    return newOrder;
}

Order* split(Order* head) {
    Order* fast = head;
    Order* slow = head;

    // move fast pointer 2 steps and slow pointer one until fast reaches End
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        if (fast != NULL) {
            slow = slow->next;
        }
    }

    // split orderbooks into two halves
    Order* temp = slow->next;
    slow->next = NULL;
    return temp;
}

Order* merge(Order* first, Order* second, int descending) {

    // if either list is empty, returnt eh other list
    if (first == NULL) {return second;}
    if (second == NULL) {return first;}

    // pick smaller value
    if ((descending && first->price > second->price) ||
        (!descending && first->price < second->price) ||
        (first->price == second->price)) {
        first->next = merge(first->next, second, descending);
        return first;
    } else {
        second->next = merge(first, second->next, descending);
        return second;
    }
}



Order* merge_sort(Order* head, int descending) {

    // handle base case (if list contains < 1 order it doesnt need sorting
    if (head == NULL || head->next == NULL) {return head;}

    // split orderbook into halves
    Order* second = split(head);

    // recursivelty sort each half
    head = merge_sort(head, descending);
    second = merge_sort(second, descending);

    // merge two sorted halves
    return merge(head, second, descending);
}

void match_orders(OrderBook* orderBook) {
    // Implementation of order matching
    Order* buy = orderBook->buyOrders;
    Order* sell = orderBook->sellOrders;
    Order* prevBuy = NULL;
    Order* prevSell = NULL;

    while (buy && sell && buy->price >= sell->price) {
        int tradeQuantity = (buy->quantity < sell->quantity) ? buy->quantity : sell->quantity;

        printf("Trade executed: Buy Order ID %d and Sell Order ID %d for Quantity %d at Price %.2f\n",
               buy->id, sell->id, tradeQuantity, sell->price);

        buy->quantity -= tradeQuantity;
        sell->quantity -= tradeQuantity;

        if (buy->quantity == 0) {
            Order* temp = buy;
            if (prevBuy) {prevBuy->next = buy->next;}
            else {orderBook->buyOrders = buy->next;}
            buy = buy->next;
            free(temp);
        } else {
            prevBuy = buy;
            buy = buy->next;
        }

        if (sell->quantity == 0) {
            Order* temp = sell;
            if (prevSell) {prevSell->next = sell->next;}
            else {orderBook->sellOrders = sell->next;}
            sell = sell->next;
            free(temp);
        } else {
            prevSell = sell;
            sell = sell->next;
        }
    }
}


void display_order_book(const OrderBook* orderBook) {

    printf("\n=== ORDER BOOK ===\n");

    printf("BUY ORDERS (bids):\n");
    Order* buy = orderBook->buyOrders;
    if (!buy) {
        printf("  [empty]\n");
    }
    while (buy) {
        printf("  ID:%d  Price:%.2f  Qty:%d\n", buy->id, buy->price, buy->quantity);
        buy = buy->next;
    }

    printf("SELL ORDERS (asks):\n");
    Order* sell = orderBook->sellOrders;
    if (!sell) {
        printf("  [empty]\n");
    }
    while (sell) {
        printf("  ID:%d  Price:%.2f  Qty:%d\n", sell->id, sell->price, sell->quantity);
        sell = sell->next;
    }
    printf("==================\n\n");
}

void free_order_book(OrderBook* orderBook) {
    Order* current;
    Order* next;

    // free buy orders
    current = orderBook->buyOrders;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    orderBook->buyOrders = NULL;

    // free sell orders
    current = orderBook->sellOrders;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    orderBook->sellOrders = NULL;
}

