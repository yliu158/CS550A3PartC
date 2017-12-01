#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <asm/uaccess.h>


MODULE_LICENSE("GPL");            ///< The license type -- this affects available functionality
MODULE_AUTHOR("Yang Liu");  

static int buffer[100];

static int __init pip_init(void);
static void __exit pip_exit(void);


static int __init pip_init(void) {
  kprint("Namepipe module say hello.\n");
  return 0;
}

static void __exit pip_exit(void) {
  kprint("Namepipe module say goodbye.\n");
}

module_init(init);
module_exit(exit);
