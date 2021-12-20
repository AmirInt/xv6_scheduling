#include "types.h"
#include "stat.h"
#include "user.h"

#define PAGESIZE 4096

int thread_creator(void fn(void*), void *arg) {
  void *w = malloc(2 * PAGESIZE);
  if (w == 0)
    return -1;
  
  void *stack;

  int rem = (uint) w % PAGESIZE;

  if (rem == 0)
    stack = w;
  else
    stack = w + (PAGESIZE - rem);

  int thread_id = thread_create(stack);
  
  if (thread_id == -1)
    printf(1, "Failed to create thread.\n");

  else if (thread_id == 0) {
    fn(arg);
    free(w);
    exit();
  }

  return thread_id;
}