#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>

#define GPIO_NUMBER 514 
static struct gpio_desc *gpio; 
static int __init gpio_driver_init(void)
{
    int ret;
    gpio = gpio_to_desc(GPIO_NUMBER);
    if (!gpio) {
        pr_err("Failed to get GPIO descriptor for GPIO %d\n", GPIO_NUMBER);
        return -EINVAL;
    }
    ret = gpiod_direction_output(gpio, 0);
    if (ret) {
        pr_err("Failed to set GPIO %d as output\n", GPIO_NUMBER);
        return ret;
    }

    gpiod_set_value(gpio, 1);
    pr_info("GPIO %d is set to HIGH\n", GPIO_NUMBER);

    return 0;
}

static void __exit gpio_driver_exit(void)
{
    if (gpio) {
        gpiod_set_value(gpio, 0);
        pr_info("GPIO %d is set to LOW\n", GPIO_NUMBER);
    }
    pr_info("GPIO driver unloaded\n");
}

module_init(gpio_driver_init);
module_exit(gpio_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple GPIO Driver using GPIO-514");
