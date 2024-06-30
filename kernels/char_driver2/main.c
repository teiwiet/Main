#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kernel.h> 
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#define DEV_MEM_SIZE 512 
#undef pr_fmt 
#define pr_fmt(fmt) "%s:" fmt,__func__  
char device_buffer[DEV_MEM_SIZE];


loff_t pcd_lseek(struct file *filp,loff_t off,int whence){
	pr_info("lseek requested");
	return 0;
};
ssize_t pcd_read(struct file* filp,char* __user buff,size_t count,loff_t* f_pos){
	pr_info("read requested %zu bytes\n",count);
	return 0;
};
ssize_t pcd_write(struct file* filp,const char* __user buff,size_t count,loff_t* f_pos){
	pr_info("read requested %zu bytes\n",count);
	return 0;
};
int pcd_open(struct inode* inode,struct file* filp){
	pr_info("Open successfully");
	return 0;
};
int pcd_release(struct inode* inode,struct file* filp){
	pr_info("Release successfully");
	return 0;
};
// file operations of the pcd_driver 
struct file_operations pcd_fops = {
	.open = pcd_open,
	.write = pcd_write,
	.read = pcd_read,
	.llseek = pcd_lseek,
	.release = pcd_release,
	.owner = THIS_MODULE
};
int ret;

// this hold the device number 
dev_t device_number;
// cdev variable
struct cdev pcd_cdev;

struct class *class_pcd;
struct device *device_pcd;
static int __init pcd_driver_init(void){
	// 1.dynamic alloc device number 
	ret = alloc_chrdev_region(&device_number,0,1,"pcd_divices");
	printk("Device number <major>:<minor> = %d:%d",MAJOR(device_number),MINOR(device_number));
	// 2. initalize the cdev structure with fops
	cdev_init(&pcd_cdev,&pcd_fops);
	pcd_cdev.owner = THIS_MODULE;
	// 3. register a device with VFS
	cdev_add(&pcd_cdev,device_number,1);

	/* create device class under /sys/class */
	class_pcd = class_create("pcd_class");

	// populate the sysfs with the device information 
	device_pcd = device_create(class_pcd,NULL,device_number,NULL,"pcd");
	pr_info("Module init was successfully \n");
	return 0;
}

static void __exit pcd_driver_exit(void){
	device_destroy(class_pcd,device_number);
	class_destroy(class_pcd);
	cdev_del(&pcd_cdev);
	unregister_chrdev_region(device_number,1);
	pr_info("module unloaded successfully");
}

module_init(pcd_driver_init);
module_exit(pcd_driver_exit);


MODULE_AUTHOR("teiwiet");
MODULE_DESCRIPTION("teiwiet");
MODULE_LICENSE("GPL");
