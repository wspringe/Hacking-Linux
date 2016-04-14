
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/tty.h>
#include <linux/jiffies.h>
#include <linux/string.h>
#include <linux/slab.h>

asmlinkage long sys_my_syscall(int a, int b, char *c)
{
	char * kernel_buffer = (char *) kmalloc(5000, GFP_KERNEL);
	int len = 0, n = 0, temp_count = 0;
	struct task_struct *task;
	int time_in_sec, hr, rem, min, sec;
	char * tty_name = (char *) kmalloc(32, GFP_KERNEL);

	 //iterate through the tasks
	for_each_process(task) {
		
		//1) print the pid
		len += sprintf(kernel_buffer+len, "%5d ", (int) task->pid);

		//tty for (null) and replace with ?
			sprintf(tty_name, "%s", task->signal->tty->name);	
			if (tty_name[0] == '(' && tty_name[1] == 'n' && tty_name[2] == 'u' \
		    && tty_name[3] == 'l' && tty_name[4] == 'l' \
		    && tty_name[5] == ')' ) {
			tty_name[0] = '?';
			tty_name[1] = '\0';
		}
		
		//2) print the tty name
		len += sprintf(kernel_buffer+len, "%-8s ", tty_name);

		//3) print the cputime
		long userTime = task->utime / HZ; 
 		long execTime = task->stime / HZ; 
                time_in_sec = userTime + execTime; //correcting the cpu time

	    hr  = time_in_sec / 3600;
		rem = time_in_sec % 3600;
		min = rem / 60;
		sec = rem % 60; 

		len += sprintf(kernel_buffer+len, "%02d:%02d:%02d ", hr, min, sec);

		// 4)print the commands
		len += sprintf(kernel_buffer+len, "%s\n", task->comm);
		temp_count++;

		
	} 

	sprintf(kernel_buffer, "%d\n", temp_count);

	// limit size of amount copied to size of userspace buffer
	if (len > b)
		len = b;

	// copy the contents of kernel_buffer to userspace buffer c
	n = copy_to_user(c, kernel_buffer, len);

	// free the kernel buffer and tty_name allocated with kmalloc
	kfree(kernel_buffer);
	kfree(tty_name);

	// return the number of bytes NOT copied to userspace
	return n;
}
