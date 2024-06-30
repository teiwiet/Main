#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#define DEV_MEM_SIZE 512

char device_buff[DEV_MEM_SIZE];

loff_t pcd_llseek(struct file* filp,loff_t off,int whence){
	return 0;
}

ssize_t pcd_read(struct file *filp,char* __user buff,size_t count,loff_t* f_pos){
	return 0;
}

ssize_t pcd_write(struct file* filp,const char* __user buff,size_t count,loff_t* f_pos){
	return 0;
}

int pcd_open(struct inode* inode,struct file* filp){
	return 0;
}

int pcd_release(struct inode* inode,struct file* filp){
	return 0;
}


int ret;
dev_t device_number;
struct cdev pcd_cdev;
struct file_operations pcd_fops={
	.llseek = pcd_llseek,
	.open = pcd_open,
	.write = pcd_write,
	.release = pcd_release,
	.read = pcd_read
};

struct class* pcd_class;
struct device* pcd_device;
static int __init pcd_driver_init(void){
	// dynamically create a device number
	ret = alloc_chrdev_region(&device_number,0,1,"pcd");
	printk("Device create with %d:%d",MAJOR(device_number),MINOR(device_number));
	cdev_init(&pcd_cdev,&pcd_fops);
	pcd_cdev.owner = THIS_MODULE;
	cdev_add(&pcd_cdev,device_number,1);
	pcd_class = class_create("pcd_class");
	pcd_device = device_create(pcd_class,NULL,device_number,NULL,"pcd");
	return 0;
}
static void __exit pcd_driver_exit(void){
	printk("Goodbye World");
}

module_init(pcd_driver_init);
module_exit(pcd_driver_exit);
MODULE_AUTHOR("teiwiet");
MODULE_DESCRIPTION("My simple LKM");
MODULE_LICENSE("GPL");
