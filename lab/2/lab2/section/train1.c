#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>

int simple_init(void) {
    printk(KERN_INFO "Loading Module training one\n");
    return 0;
}

void simple_exit(void) {
    printk(KERN_INFO "Removing Module training one\n");
}
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("train one module");
MODULE_AUTHOR("Farshid Nooshi");