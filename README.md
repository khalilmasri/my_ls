# my_ls

**SPECIFICATIONS**

Write a programm called my_ls. Following the specifications of this man page.

**NAME**

my_ls -- list directory contents

**SYNOPSIS**

my_ls [-at] [file ...]

**DESCRIPTION**

For each operand that names a file of a type other than directory, my_ls displays its name as well as any requested, associated information. For each operand that names a file of type directory, my_ls displays the names of files contained within that directory, as well as any requested, associated information.

If no operands are given, the contents of the current directory are displayed. If more than one operand is given, non-directory operands are displayed first; directory and non-directory operands are sorted separately and in lexicographical order.

The following options are available:

-a Include directory entries whose names begin with a dot (.).

-t Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

**Requirements**

The code must be compiled with the flags -Wall -Wextra -Werror.

**Hint(s)**

Global variables are strictly FORBIDDEN

tv_sec AND tv_nsec are used for the -t options

use st_mtim

**Authorized functions**

malloc(3)

free(3)

printf(3)

write(2)

stat(2)

lstat(2)

opendir(2)

closedir(2)

readdir(2)
