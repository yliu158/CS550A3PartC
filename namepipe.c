#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <asm/uaccess.h>

#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <sys/sem.h>

static int buffer_size;
module_param(buffer_size, int, 0000);
int queue* = NULL;


MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_AUTHOR("Yang Liu");    ///< The author -- visible when you use modinfo

static struct miscdevice pipe;
static int open_count;
static int buffer_size;

static struct semaphore full;
static struct semaphore empty;
static struct semaphore mutex;
static int read_index;
static int write_index;

static int pipe_open(struct inode*, struct file*);
static ssize_t pipe_read(struct file*, char*, size_t, loff_t*);
static ssize_t pipe_write(struct file*, const char*, size_t, loff_t*);
static int pipe_close(struct inode*, struct file*);

static ssize_t pipe_read(struct file *file, char __user * out, size_t size, loff_t * off) {
	/**
	while (True) {
		item = remove item();
		index --;
		down(sem full);
		buffer[index++] = item;
		up(sem empty);
	}
	*/
	return 0;
}

static ssize_t pipe_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
	/**
	while (True) {
		item = copy form user();
		down(sem empty);
		buffer[index++] = item;
		up(sem full);
	}
	*/
	return 0;
}

static int pipe_open (struct inode * id, struct file * filep){
  printk(KERN_ALERT "Pipe has been opened.\n");
  return 0;
}

static int pipe_close(struct inode * id, struct file * filep) {
  printk(KERN_ALERT "Pipe successfully closed.\n");
  return 0;
}

static struct file_operations pipe_fops = {
  .owner = THIS_MODULE,
  .open = pipe_open,
  .release = my_close,
  .read = pipe_read,
};

static struct miscdevice pipe = {
  .minor = MISC_DYNAMIC_MINOR,
  .name = "namedpipe",
  .fops = &pipe_fops
};


static int __init pipe_init(void) {

	int register_return_value;
	if((register_return_value = misc_register(&my_device))){
		/*misc_register() returns
		0: success
		-ve: failure*/
		printk(KERN_ERR "Could not register the device\n");
		return register_return_value;
	}

	sema_init(full, buffer_size);
	sema_init(empty, buffer_size);
	sema_init(mutex, 1);

	int _allocated = 0;
	buffer = (char**)kmalloc(buffer_size*sizeof(char*), GFP_KERNEL);

  printk(KERN_ALERT "Init namedpipe sucessfully.\n");
  misc_register(&pipe);
  return 0;
}

static void __exit pipe_exit(void) {
  misc_deregister(&pipe);
  printk(KERN_ALERT "Exit namedpipe.\n");
}

module_init(pipe_init);
module_exit(pipe_exit);
