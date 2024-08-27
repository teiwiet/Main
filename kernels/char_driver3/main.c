#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#define DEV_MEM_SIZE 512

char buff[DEV_MEM_SIZE];
int ret;
dev_t device_number;
struct cdev pcd_cdev;

loff_t pcd_llseek(struct file* filp,loff_t f_pos,int whence){
	return 0;
}
ssize_t pcd_write(struct file* filp,const char* __user buff,size_t count,loff_t* fpos){
	return 0;
}

ssize_t pcd_read(struct file* filp,char* __user buff,ssize_t count,loff_t* fpos){}

int pcd_open(struct inode* inode,struct file* filp){
	return 0;
};
int pcd_release(struct inode* inode,struct file* filp){
	return 0;
};


struct file_operations pcd_fops = {
	.owner = THIS_MODULE,
	.llseek = pcd_llseek,
	.write = pcd_write,
	.read = pcd_read,
	.open = pcd_open,
	.release = pcd_release
};
static int __init pcd_init(void){
	printk(KERN_INFO "This is a very simple LKM by me :smiley face:");
	ret = alloc_chrdev_region(&device_number,0,1,"pcd");
	printk(KERN_INFO "the device successfully register with %d:%d",MAJOR(device_number),MINOR(device_number));
	cdev_init(&pcd_cdev,&fops);
	pcd_cdev.owner = THIS_MODULE;
	cdev_add(&pcd_cdev,device_number,1);
	return 0;
}

static void __exit pcd_exit(void){
	printk(KERN_INFO "Goodbyte world");
}

module_init(pcd_init);
module_exit(pcd_exit);
MODULE_AUTHOR("teiwiet");
MODULE_DESCRIPTION("Simple LKM by teiwiet");
MODULE_LICENSE("GPL");
