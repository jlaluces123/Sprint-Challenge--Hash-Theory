#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

/*
  We can hash each ticket such that the starting location is the key 
  and the destination is the value. 
  Then, when constructing the entire route, 
  the ith location in the route can be found by checking the 
  hash table for the i-1th location.
*/
char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));

  // 1. First we want to check if starting dest is NONE, so we can set first part of our route to the destination
  for (int i = 0; i < length; i++) {
    if ( strcmp(tickets[i]->source, "NONE") == 0 ) {
      route[0] = tickets[i]->destination; // --> EX: Since None: { PDX -> }
    } // 1a. As stated in hints: we can hash the ticket after
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination); // --> ht || NONE == Key || PDX == Value
  }

  // 2. We need to make the rest of the route (done by method given in hint)
  for (int i = 1; i < length; i++) { // --> We need to start at 1 here because there is no -1 pos in route
    if (hash_table_retrieve(ht, route[i - 1]) != NULL) { // --> Meaning we found a match in keys
      route[i] = hash_table_retrieve(ht, route[i - 1]); // --> retrieve will return the value at that key
    } else { // --> No matching Key
      route[i] = "NONE"; // --> end of trip
    }
  }

  // 3. Don't forget to free ht after
  destroy_hash_table(ht);
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%s\n", route[i]);
  }
}



#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
