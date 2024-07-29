#!/bin/sh
# bld.sh

# Update TOC in doc
for F in *.md; do :
  if egrep "<!-- mdtoc-start -->" $F >/dev/null; then :
    # Update doc table of contents (see https://github.com/fordsfords/mdtoc).
    if which mdtoc.pl >/dev/null; then mdtoc.pl -b "" $F;
    elif [ -x ../mdtoc/mdtoc.pl ]; then ../mdtoc/mdtoc.pl -b "" $F;
    else echo "FYI: mdtoc.pl not found; Skipping doc build"; echo ""; fi
  fi
done

# Allow C99 features, disallow C11 features. The "-D_XOPEN_SOURCE=500" defines ftruncate().
CC_OPTS="-std=c99 -pedantic-errors -Wall -Wextra -D_XOPEN_SOURCE=500"

gcc $CC_OPTS -o persistent_state persistent_state.c; if [ $? -ne 0 ]; then exit 1; fi
