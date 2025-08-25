#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/gpio/consummer.h>


static int __init gpio_driver_init(){

}


module_init();
module_exit();
MODULE_AUTHOR("teiwiet");
MODULE_DESCRIPTOR("Simple LKM");
MODULE_LICENSE("GPL");

