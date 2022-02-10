#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/slab.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};


LIST_HEAD(Head_Node);


int simple_init(void) {
    {
        int i =0;
        while(i < 5) {
            struct birthday *person;
            person = kmalloc(sizeof(person), GFP_KERNEL);
            person->day = i;
            person->month = 8;
            person->year = 1995;
            INIT_LIST_HEAD(&person->list);
            list_add_tail(&person->list, &Head_Node);
            i++;
        }
    }

        struct birthday *temp;
        int count = 0;
        printk(KERN_INFO "Reading list\n");

        list_for_each_entry(temp, &Head_Node, list) {
            printk(KERN_INFO "Node %d, data = {%d, %d, %d}\n", count++, temp->day, temp->month, temp->year);
        }

        printk(KERN_INFO "Total Nodes = %d\n", count);
    return 0;
}

void simple_exit(void) {
    {
        struct birthday *cursor, *temp;
        int count = 0;
        list_for_each_entry_safe(cursor, temp, &Head_Node, list) {
            printk(KERN_INFO "Node %d, data = {%d, %d, %d} is removing.\n", count++, temp->day, temp->month, temp->year);
            list_del(&cursor->list);
            kfree(cursor);
        }
    }
    {

        struct birthday *temp;
        int count = 0;
        printk(KERN_INFO "List Now Contains:\n");

        list_for_each_entry(temp, &Head_Node, list) {
            printk(KERN_INFO "Node %d, data = {%d, %d, %d}\n", count++, temp->day, temp->month, temp->year);
        }

        printk(KERN_INFO "Total Nodes = %d\n", count);
    }
}

module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("section one module");
MODULE_AUTHOR("Farshid Nooshi");