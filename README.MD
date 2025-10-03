# High Frequency Trading System Order Book Simulator

## Video Demo

*(link here when ready)*

## Project Description

The project I have chosen to create is a high frequency trading order book, written in C as a command line tool.

I decided on this project mainly due to personal interests and language comfort. Whilst doing CS50 I found C was the language I was most drawn to. I believe this is because of its subscript-like proponents of C++, a language I started to learn halfway through CS50, and am fond of.

When looking at the file structure of this project, you see four source files that contribute to the order book sim:

* `main.c` — the main program itself
* `types.h` — a design pattern I became        comfortable with working on a much larger C project
* `orderbook.h` + `orderbook.c` — imagine them as one file for visualisation’s sake

`orderbook.c` and `orderbook.h` combined are my attempt at replicating C++ classes within C. Combined with `types.h` you can mimic objects rather well in C, which surprised me and is definitely a learning I will carry with me to maybe even try and implement within other non-OOP languages.

---

## Main.c

* Contains a program loop, which runs for a defined number of *ticks*, `#defined` as `N`.
* This makes the number of ticks easily interchangeable with minimal effort.
* Calls functions located within the `orderbook.h` file (more on those soon).
* Finally (and importantly) calls a custom free function that frees all orders from the order book that have not been matched while the program was running.

---

## types.h

The types file is typically one of the first things I have found myself creating and using whenever writing a project in C. As mentioned before it allows object-like structures to be created when used in conjuncture with other named .c files.

In this instance, `types.h` is quite small, and only contains variable definitions for an `Order`, as well as linked list pointers to the order book and within the order book, with `order* next` allowing one to traverse within — necessary for sorting.

---

## orderbook.h / orderbook.c

This is the main bulk of the program.

### Random Order Generation

* We `malloc` size of `Order` struct.
* Fill the values using randomisation.
* Set `order->next` to `NULL`.
* Insert into the correct order book linked list.

  * If order type `B` (buy) → enter into buy order book.
  * Else → enter into sell order book.
* Finally return the order from the function.

This process takes place within the main loop, and therefore we end up with one new order per *tick*.

---

### Split()

Next we must split the order books into two halves within the `Split()` function.

To maintain performance I chose a 2-pointer approach I read about in a LeetCode comment section. Each order book is now in two halves.

---

### merge()

Next we must sort the order book using `merge()`.

On reflection, I am not sure why I chose this name — it made sense in the moment. If I was to expand this program its name would be one of my first changes.

Sorting is done by:

* Checking a flag in the function call for whether buy or sell side order book.

  * This affects whether sorting is descending or ascending.
* Doing a simple price comparison.
* Arranging values into sorted order.

I am quite proud of this implementation, using a clever OR condition to avoid repeating code for the ascending case.

---

### merge_sort()

Finally within sorting it all comes together with `merge_sort()`:

* Handle recursion base case of no sorting needed.
* Split the order book with a call to `split()`.
* Recursively sort each half of the order book with calls to `merge_sort()`.
* Merge the order books using `merge()`.

---

### Order Matching

The matching function checks that:

```c
buy.price >= sell.price
```

I chose this comparison for the sake of show and tell. In a real order book, only a decided range of prices will be matched together.

This can be easily changed by comparing the difference between the two prices and checking if it is less than a chosen variance.

A `printf` statement also notifies the user when an order has been matched.

---

### Display Order Book

This function is a set of print statements that display the `Order` struct values stored in the order book.

* Provides visual representation of FIFO linked list / queue.
* Shows order matching in action.
* Runs while both buy and sell contain values.

---

### Free Order Book

The `free_orderbook()` function frees all remaining orders located in the order book.

Although technically unnecessary due to modern OS auto freeing at the end of execution, it is still good practice.

It’s basically:

* Check if current order is NULL.
* If not, free it.

This is called right at the end of the program.

---

### Lessons Learned

Working on this project reinforced many of the core concepts I learned in CS50, while also pushing me to think about larger-scale program design. I gained practical experience with **dynamic memory management**, understanding how to allocate, update, and free linked list nodes safely, especially when dealing with partially filled orders. This helped me appreciate how careful one must be with pointers in C, and why memory leaks can easily occur if edge cases are overlooked.

I also learned the value of **code organization**. Splitting the program into `main.c`, `types.h`, and `orderbook.c`/`orderbook.h` made it easier to reason about each part independently. It forced me to design clear interfaces between components, which is a skill I know will transfer to future, larger projects. Writing a `Makefile` and structuring compilation into object files gave me a better understanding of how larger C programs are built and maintained professionally.

Implementing **merge sort on linked lists** was another major learning point. It required me to combine recursive thinking with pointer manipulation, and I developed strategies to avoid duplicating code for ascending and descending sorts. Similarly, building the **order matching engine** taught me how to handle conditional logic for partial and full fills, as well as how to traverse and update multiple linked lists simultaneously.

Finally, this project strengthened my **problem-solving and debugging skills**. Small errors with memory allocation, pointer assignments, or list traversal often caused crashes or incorrect matches, and tracking them down required careful reasoning. By systematically tracing through the program and testing different cases, I became more confident in diagnosing and fixing bugs in C.

Overall, this project was an excellent bridge between the basics learned in CS50 and more advanced, real-world programming concepts. It showed me how C can be used to implement complex systems, taught me the importance of clean, modular design, and gave me confidence to tackle future projects that combine algorithms, memory management, and system-level thinking.

