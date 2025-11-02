# persistent_state

Example of a program that uses a POSIX shared memory segment to save state
that is persisted across program restarts.


<!-- mdtoc-start -->
&bull; [persistent_state](#persistent_state)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Introduction](#introduction)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Misc details](#misc-details)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [License](#license)  
<!-- TOC created by '../mdtoc/mdtoc.pl README.md' (see https://github.com/fordsfords/mdtoc) -->
<!-- mdtoc-end -->


## Introduction

Example of a program that uses a POSIX shared memory segment to save state
that is persisted across program restarts.
Note that it does not persist across system reboots (i.e. there is no file
backing the shared segment).

This test program has a required command-line parameter: either the word
'attach' or 'unlink'.
If 'attach' is supplied, it will first try to attach to an existing
shared memory segment.
If non exists, it will create one.
It will also tell whether it was attached or created.

If 'unlink' is supplied, an existing one will be deleted.


## Misc details

When you create a POSIX shared memory segment, it can be seen using the `ls`
command:
````
$ ls -l /dev/shm/
total 4
-rw-r--r-- 1 sford sford 8 Aug  6 16:56 persistent_state
````

It can be deleted by removing that file using the `rm` command, or by using
the `shm_unlink()` API, as demonstrated in this test program.

The file 'e.h' contains a set of macros for simple error handling.
See https://github.com/fordsfords/E for details.


## License

I want there to be NO barriers to using this code, so I am releasing it to the public domain.  But "public domain" does not have an internationally agreed upon definition, so I use CC0:

This work is dedicated to the public domain under CC0 1.0 Universal:
http://creativecommons.org/publicdomain/zero/1.0/

To the extent possible under law, Steven Ford has waived all copyright
and related or neighboring rights to this work. In other words, you can 
use this code for any purpose without any restrictions.
This work is published from: United States.
Project home: https://github.com/fordsfords/persistent_state
