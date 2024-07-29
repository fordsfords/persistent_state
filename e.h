/* e.h - Simple error handling. */
/*
# This code and its documentation is Copyright 2002-2021 Steven Ford
# and licensed "public domain" style under Creative Commons "CC0":
#   http://creativecommons.org/publicdomain/zero/1.0/
# To the extent possible under law, the contributors to this project have
# waived all copyright and related or neighboring rights to this work.
# In other words, you can use this code for any purpose without any
# restrictions.  This work is published from: United States.  The project home
# is https://github.com/fordsfords/E
*/
#ifndef E_H
#define E_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


/* Use when non-zero means error. */
#define EOK0(eok0_expr) do { \
  if ((eok0_expr) != 0) { \
    int eok0_errno = errno; \
    char eok0_errstr[1024]; \
    snprintf(eok0_errstr, sizeof(eok0_errstr), "Error %s:%d - '%s' is not 0", \
        __FILE__, __LINE__, #eok0_expr); \
    errno = eok0_errno; \
    perror(eok0_errstr); \
    exit(1); \
  } \
} while (0)


#define EOK1(eok1_expr) do { \
  if ((eok1_expr) != 1) { \
    int eok1_errno = errno; \
    char eok1_errstr[1024]; \
    snprintf(eok1_errstr, sizeof(eok1_errstr), "Error %s:%d - '%s' is not 1", \
        __FILE__, __LINE__, #eok1_expr); \
    errno = eok1_errno; \
    perror(eok1_errstr); \
    exit(1); \
  } \
} while (0)


/* Use when NULL means error. */
#define ENULL(enull_expr) do { \
  if ((enull_expr) == NULL) { \
    int enull_errno = errno; \
    char enull_errstr[1024]; \
    snprintf(enull_errstr, sizeof(enull_errstr), "Error %s:%d - '%s' is NULL", \
        __FILE__, __LINE__, #enull_expr); \
    errno = enull_errno; \
    perror(enull_errstr); \
    exit(1); \
  } \
} while (0)


/* Use when -1 means error. */
#define EM1(em1_expr) do { \
  if ((long)(em1_expr) == -1) { \
    int em1_errno = errno; \
    char em1_errstr[1024]; \
    snprintf(em1_errstr, sizeof(em1_errstr), "Error %s:%d - '%s' is -1", \
        __FILE__, __LINE__, #em1_expr); \
    errno = em1_errno; \
    perror(em1_errstr); \
    exit(1); \
  } \
} while (0)


#endif  /* E_H */
