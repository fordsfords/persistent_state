#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "e.h"  /* Simple error handling. */

#define PSTATE_NAME "/persistent_state"
#define PSTATE_SIZE (sizeof(persistent_state_t))
#define PSTATE_MAGIC 0x8ac1d648  // From random.org

typedef volatile struct persistent_state_s {
  uint32_t magic;  // Flag to check if the memory has been initialized
  uint32_t state;
} persistent_state_t;

typedef struct runtime_state_s {
  persistent_state_t *pstate_ptr;
  int pstate_fd;
  char *pstate_name;
} runtime_state_t;


void pstate_unlink(runtime_state_t *my_rstate) {
  EM1(shm_unlink(my_rstate->pstate_name));
}  /* pstate_unlink */


int pstate_attach(runtime_state_t *my_rstate) {
  int pstate_fd;
  persistent_state_t *pstate_ptr;
  int created = 0;

  /* Try to create new shared memory segment. */
  pstate_fd = shm_open(my_rstate->pstate_name, O_CREAT | O_EXCL | O_RDWR, 0666);
  if (pstate_fd != -1) {
    created = 1;
    /* Set the size of the shared memory segment. */
    EM1(ftruncate(pstate_fd, PSTATE_SIZE));
  }
  else {
    /* Bad status, but maybe its because it already exists. */
    if (errno == EEXIST) {
      /* Shared memory already exists, just open it. */
      EM1(pstate_fd = shm_open(PSTATE_NAME, O_RDWR, 0666));
    }
    else { EM1(pstate_fd); }
  }
  my_rstate->pstate_fd = pstate_fd;

  /* Map the shared memory segment. */
  ENULL(pstate_ptr = mmap(NULL, PSTATE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, pstate_fd, 0));
  my_rstate->pstate_ptr = pstate_ptr;

  /* Initialize if we created the segment. */
  if (created) {
    pstate_ptr->state = 0;
    pstate_ptr->magic = PSTATE_MAGIC;
  } else {
    if (pstate_ptr->magic != PSTATE_MAGIC) { printf("Error, shared mem mapped but not initialized.\n"); exit(1); }
  }

  return created;
}  /* pstate_attach */


void pstate_detach(runtime_state_t *my_rstate) {
  if (my_rstate->pstate_ptr != NULL) {
    munmap((void *)my_rstate->pstate_ptr, PSTATE_SIZE);
    my_rstate->pstate_ptr = NULL;
  }
  if (my_rstate->pstate_fd != -1) {
    close(my_rstate->pstate_fd);
    my_rstate->pstate_fd = -1;
  }
}  /* pstate_detach */


void usage(void)
{
  printf("Usage: persistent_state { attach | unlink }\n");
}  /* usage */


void do_work(runtime_state_t *my_rstate, int created) {
  my_rstate->pstate_ptr->state++;
  printf("do_work created=%d, state=%d\n", created, my_rstate->pstate_ptr->state);
}  /* do_work */


int main(int argc, char **argv) {
  runtime_state_t my_rstate = { .pstate_ptr=NULL, .pstate_fd=-1, .pstate_name=PSTATE_NAME };

  if (argc != 2) { usage(); return 1; }

  if (strcmp(argv[1], "attach") == 0) {
    int created = pstate_attach(&my_rstate);
    do_work(&my_rstate, created);
    pstate_detach(&my_rstate);
  }
  else if (strcmp(argv[1], "unlink") == 0) {
    pstate_unlink(&my_rstate);
  }
  else { printf("Bad cmd: '%s'\n", argv[1]); usage(); return 1; }

  return 0;
}  /* main */
