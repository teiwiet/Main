#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define LED_GPIO_PIN 514// Thay đổi cho phù hợp với thiết bị của bạn
#define DEVICE_NAME "led_char_dev"

static int led_gpio = LED_GPIO_PIN;
static dev_t dev_num;
static struct cdev led_cdev;
static struct class *led_class;

// Hàm bật/tắt LED
static void set_led_state(int state)
{
    gpio_set_value(led_gpio, state);
}

// Hàm open (mở thiết bị)
static int led_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "LED Driver: Thiết bị được mở\n");
    return 0;
}

// Hàm release (đóng thiết bị)
static int led_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "LED Driver: Thiết bị được đóng\n");
    return 0;
}

// Hàm write (ghi dữ liệu vào thiết bị)
static ssize_t led_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
    char buffer[4]; // Chỉ cần một chuỗi nhỏ để đọc trạng thái
    int state;

    if (len > 4)
        len = 4;

    if (copy_from_user(buffer, buf, len)) {
        printk(KERN_ERR "LED Driver: Không thể sao chép dữ liệu từ user\n");
        return -EFAULT;
    }

    buffer[len] = '\0'; // Đảm bảo chuỗi kết thúc bằng NULL

    if (kstrtoint(buffer, 10, &state)) {
        printk(KERN_ERR "LED Driver: Dữ liệu không hợp lệ\n");
        return -EINVAL;
    }

    if (state == 1) {
        set_led_state(1); // Bật LED
        printk(KERN_INFO "LED Driver: LED bật\n");
    } else if (state == 0) {
        set_led_state(0); // Tắt LED
        printk(KERN_INFO "LED Driver: LED tắt\n");
    } else {
        printk(KERN_ERR "LED Driver: Chỉ chấp nhận 0 hoặc 1\n");
        return -EINVAL;
    }

    return len;
}

// Cấu trúc file_operations
static const struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_release,
    .write = led_write,
};

// Hàm khởi tạo module
static int __init led_init(void)
{
    int ret;

    printk(KERN_INFO "LED Driver: Đang khởi tạo\n");

    // Cấp phát GPIO
    ret = gpio_request(led_gpio, "LED_GPIO");
    if (ret) {
        printk(KERN_ERR "LED Driver: Không thể yêu cầu GPIO %d\n", led_gpio);
        return ret;
    }

    // Đặt GPIO là output
    ret = gpio_direction_output(led_gpio, 0);
    if (ret) {
        printk(KERN_ERR "LED Driver: Không thể thiết lập hướng GPIO\n");
        gpio_free(led_gpio);
        return ret;
    }

    // Cấp phát số major/minor
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret) {
        printk(KERN_ERR "LED Driver: Không thể cấp phát số thiết bị\n");
        gpio_free(led_gpio);
        return ret;
    }

    // Khởi tạo cdev
    cdev_init(&led_cdev, &led_fops);
    ret = cdev_add(&led_cdev, dev_num, 1);
    if (ret) {
        printk(KERN_ERR "LED Driver: Không thể thêm cdev\n");
        unregister_chrdev_region(dev_num, 1);
        gpio_free(led_gpio);
        return ret;
    }

    // Tạo class và device trong /dev
    led_class = class_create(DEVICE_NAME);
    if (IS_ERR(led_class)) {
        printk(KERN_ERR "LED Driver: Không thể tạo class\n");
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        gpio_free(led_gpio);
        return PTR_ERR(led_class);
    }

    if (!device_create(led_class, NULL, dev_num, NULL, DEVICE_NAME)) {
        printk(KERN_ERR "LED Driver: Không thể tạo thiết bị\n");
        class_destroy(led_class);
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        gpio_free(led_gpio);
        return -ENOMEM;
    }

    printk(KERN_INFO "LED Driver: Đã khởi tạo thành công\n");
    return 0;
}

// Hàm dọn dẹp module
static void __exit led_exit(void)
{
    printk(KERN_INFO "LED Driver: Đang dọn dẹp\n");

    // Xóa thiết bị và class
    device_destroy(led_class, dev_num);
    class_destroy(led_class);

    // Xóa cdev và giải phóng số thiết bị
    cdev_del(&led_cdev);
    unregister_chrdev_region(dev_num, 1);

    // Tắt LED và giải phóng GPIO
    set_led_state(0);
    gpio_free(led_gpio);

    printk(KERN_INFO "LED Driver: Đã dọn dẹp xong\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YourName");
MODULE_DESCRIPTION("Character Driver để điều khiển LED");
MODULE_VERSION("1.0");
