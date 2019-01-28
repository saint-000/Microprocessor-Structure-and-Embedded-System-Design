
#include <linux/init.h> //包含对初始化函数和清除函数的定义
#include <linux/platform_device.h>
#include <linux/module.h>//包含可装载模块需要的大量符号和函数的定义
#include <linux/miscdevice.h>
#include <linux/ioport.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <asm/io.h>

#define DEVICE_NAME         "ees331_led_dev"


#define ees331_led_PHY_ADDR 0x41200000   


#define ees331_led_REG_WIDTH   32

static void __iomem *GPIO_Regs;

static int ees331_led_open(struct inode * inode , struct file * filp)//初始化LED亮这个函数，加载时被调用
{
  printk("ees331_led_dev open\n");
  iowrite32(16, GPIO_Regs);//led端口操作函数
  return 0;
}

static int ees331_led_release(struct inode * inode, struct file *filp)
{
  printk("ees331_led_dev close\n");
  iowrite32(0, GPIO_Regs);
  return 0;
}

static int ees331_led_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
  
  if (filp->f_flags & O_NONBLOCK)
    return -EAGAIN;

  *buffer=(char)ioread8(GPIO_Regs);
	
  return 0;
}
static int ees331_led_ioctl(struct file *filp, unsigned int reg_num, unsigned long arg)
{
	
	
/*------------Add your code here-----------------*/
//通过led地址给led寄存器赋值
iowrite32(arg, GPIO_Regs);


}

 
/*------------Add your code here-----------------*/
  
  return 0;
}
static const struct file_operations ees331_led_fops =
{

  .owner = THIS_MODULE,


/*------------Add your code here-----------------*/

  .open =ees331_led_open ,// 打开设备函数
  .release =ees331_led_release ,//关闭设备函数
  .read =ees331_led_read,     //读函数
  .unlocked_ioctl =  ees331_led_ioctl ,    // IO控制函数
  
  
/*------------Add your code here-----------------*/
};

static struct miscdevice ees331_led_dev =
{
  .minor = MISC_DYNAMIC_MINOR,
  .name = DEVICE_NAME,
  .fops = &ees331_led_fops,
};

int __init ees331_led_init(void)
{
  int ret;
  //Map device to the virtual address of kernel
  GPIO_Regs = ioremap(ees331_led_PHY_ADDR, 32); /* Verify it's non-null! */

  if(GPIO_Regs == NULL)
  {
    printk("ees331_led:[ERROR] Access address is NULL!\n");
    return -EIO;
  }  
 
  
  ret = misc_register(&ees331_led_dev);
  if (ret)
  {
    printk("ees331_led:[ERROR] Misc device register failed\n");
    return ret;
  }
  
  printk("ees331_led: success! Module init complete\n");

  iowrite32(255, GPIO_Regs);

  return 0; /* Success */
}

void __exit ees331_led_exit(void)
{
  iounmap(GPIO_Regs);
  misc_deregister(&ees331_led_dev);
  
  printk("ees331_led: Module exit\n");
}

module_init(ees331_led_init);
module_exit(ees331_led_exit);

MODULE_AUTHOR("B243");
MODULE_ALIAS("ees331_led");
MODULE_DESCRIPTION("zedboard ees331_led module");
MODULE_LICENSE("GPL");
