#include<linux/module.h>
#include<linux/init.h>
#include<linux/kdev_t.h>
#include<linux/types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("teiwiet");
MODULE_DESCRIPTION("teiwiet's module");

static int driver_open(struct inode *device_file,struct file *instance)
{
	printk("open was called");
	return 0;
}

static int driver_close(struct inode *device_file,struct file *instance)
{
	printk("close was called");
	return 0;
}

static int hello_init(void){
	printk("Hello world");
	return 0;
}
static void hello_exit(void){
	printk("Goodbye world");
}

module_init(hello_init);
module_exit(hello_exit);
