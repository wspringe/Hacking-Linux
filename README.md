This repository holds the source code for the custom syscall and the userspace code to call that syscall.

I was messing around in Linux and seeing what I could do, so this is what I came up with. This syscall loops through each process
running on Linux currently and displays the pid, tty, tty name, and cputime and then sends them to a buffer that the userspace code picks
up and prints.

Once everything is all said and done, it should look exactly the same as using the command 'ps -e'.
