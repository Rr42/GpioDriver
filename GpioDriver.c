/* 
* File name: GpioDriver.c
* Code author: Ramana R (github@Rr42)
* Code version: v1.0
* Application: GPIO test driver
* Description:
*     Sample code to demonstrate a linux character driver for Raspberry Pi 3B.
* Note: 
*  Kernel space stack is small so DO NOT make too many varibles inside functions 
* it can cause the driver to crash, this is not a problem in user space since user 
* space stacks are huge comparatively. Use global space instead.
*/

/* Includes */
#include <linux/module.h>
#include <linux/kernel.h>
/* File operations structure, allows to open/close, read/write to the device */
#include <linux/fs.h> 
/* Char driver for character device drivers */
#include <linux/cdev.h>
/* Allows access to semaphores for sychronization, helps privent corruption due to multiple threads accessing the same data */
#include <linux/semaphore.h>
/* Access and map data from user space to kernel space; copy_to_user,copy_from_user */
#include <linux/uaccess.h>
/* Include GPIO functionality */
#include "gpioCore.h"
/* Include for handling character data */
#include <linux/string.h>

/* Data structure for virtual device */
struct fake_device 
{
    char command[1];
    char result[5];

    /* Privent data corruption */
    struct semaphore sem;
} virtual_device;

/* myCDEV */
struct cdev *mcdev;
/* holes major number */
int major_number;
/* holds return value */
int ret;
/* holds major number that kernel gives as a structure*/
dev_t dev_num;

/* Max minor number */
#define MX_MINOR 1

/* define the device name */
#define DEVICE_NAME "GpioDriver"

/* Error codes */
const char ECODE_OK[2] = "0\0";
const char ECODE_FAIL[3] = "-1\0";

/* Device open function */
int gpiodriver_open(struct inode *inode, struct file *filp)
{
    /* Lock the device using semiphore to privent other modules from using the device at the same time */
    if(down_interruptible(&virtual_device.sem) != 0)
    {
        printk(KERN_ALERT "GpioDriver: could not lock device\n");
        return -1;
    }

    printk(KERN_INFO "GpioDriver: Device opened\n");
    return 0;
}

/* Device read function */
ssize_t gpiodriver_read(struct file *filp, char *bufStoreData, size_t bufCount, loff_t *curoffset)
{
    /* Take data from kernel space (device) to user space (process) */
    printk(KERN_INFO "GpioDriver: Reading from device\n");

    /* (<destination>, <source>, <sizeToTransfer>) */
    ret = copy_to_user(bufStoreData, virtual_device.command, bufCount);
    return ret;
}

/* Device write function */
ssize_t gpiodriver_write(struct file *filp, const char *bufStoreData, size_t bufCount, loff_t *curoffset)
{
    /* Take data from user space (process) to kernel space (device)*/
    printk(KERN_INFO "GpioDriver: Writing to device\n");

    /* (<destination>, <source>, <sizeToTransfer>) */
    ret = copy_from_user(virtual_device.command, bufStoreData, bufCount);

    switch(virtual_device.command[0])
    {
        case '0': 

            strcpy(virtual_device.result, (const char*)&ECODE_OK);
        break;
        case '1':

            strcpy(virtual_device.result, (const char*)&ECODE_OK);
        break;
        default:
            strcpy(virtual_device.result, (const char*)&ECODE_FAIL);
        break;
    }

    return ret;
}

/* Device close function */
int gpiodriver_close(struct inode *inode, struct file *filp)
{
    /* remove lock on device */
    up(&virtual_device.sem);
    printk(KERN_INFO "GpioDriver: Device closed\n");
    return 0;
}

/* File opperations structure */
struct file_operations fops = {
    /* Privents unloading of module when operations are running */
    .owner = THIS_MODULE,
    .open = gpiodriver_open,
    .release = gpiodriver_close,
    .write = gpiodriver_write,
    .read = gpiodriver_read
};


/* Init function */
static int gpiodriver_init(void)
{
    /* Registering device */
    /* Step 1 */
    /* Get major number and allocate char device region */
    ret = alloc_chrdev_region(&dev_num, 0, MX_MINOR, DEVICE_NAME);
    /* alloc_cdev_region(<device structure>, <startime major number>, <maximum minor number>, <device name>)*/

    if(ret < 0)
    {
        /* exit on error */
        printk(KERN_ALERT "GpioDriver: failed to allocate major number\n");
        return ret;
    }

    /* Extract the major number */
    major_number = MAJOR(dev_num);
    printk(KERN_INFO "GpioDriver: major number is %d\n", major_number);
    printk(KERN_INFO "GpioDriver: use \"mknod /dev/%s c %d 0\" for device file\n", DEVICE_NAME, major_number);

    /* Step 2 */
    /* Allocate char device structure */
    mcdev = cdev_alloc();
    /* Structure for file opperations */
    mcdev->ops = &fops;
    mcdev->owner = THIS_MODULE;
    /* Add cdev to kernel */
    ret = cdev_add(mcdev, dev_num, MX_MINOR);
    if(ret < 0)
    {
        printk(KERN_ALERT "GpioDriver: Failed to add cdev to kernel\n");
    }

    /* Init the semaphore with initial value of 1 */
    sema_init(&virtual_device.sem, 1);

    printk(KERN_INFO "GpioDriver: Module loaded\n");
    return 0;
}

/* Exit function */
static void gpiodriver_exit(void)
{
    /* unregister everything in reverse order */
    cdev_del(mcdev);

    unregister_chrdev_region(dev_num, MX_MINOR);
    printk(KERN_ALERT "GpioDriver: unloaded module\n");
}

module_init(gpiodriver_init);
module_exit(gpiodriver_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Rr42");
MODULE_DESCRIPTION("Sample GPIO driver");
MODULE_VERSION("1.0");
