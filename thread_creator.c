// thread_creator takes the responsibility of creating a
// new thread and assigning it the function it must run.

#include "types.h"
#include "stat.h"
#include "user.h"

#define PAGESIZE 4096

int thread_creator(void fn(void*), void *arg) {
  // Initialising and allocating space for thread's stack.
  void *w = malloc(2 * PAGESIZE);
  if (w == 0)
    return -1;
  
  // The stack itself is here.
  // We attempt to page-align it.
  void *stack;
  int rem = (uint) w % PAGESIZE;
  if (rem == 0)
    stack = w;
  else
    stack = w + (PAGESIZE - rem);

  // Creating the thread.
  int thread_id = thread_create(stack);
  
  // If the system fails to create the new thread, display proper
  // message and jump out.
  if (thread_id == -1)
    printf(1, "Failed to create thread.\n");

  // If the system creates the thread successfully, the thread runs the passed
  // function address, frees the first stack space and exits.
  else if (thread_id == 0) {
    fn(arg);
    free(w);
    exit();
  }

  return thread_id;
}