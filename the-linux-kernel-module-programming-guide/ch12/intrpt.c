
/*
 *  intrpt.c - An interrupt handler.
 *
 *  Copyright (C) 2001 by Peter Jay Salzman
 */

/*
 * The necessary header files
 */

/*
 * Standard in kernel modules
 */
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module */
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>	/* We want an interrupt */
#include <asm/io.h>

#define MY_WORK_QUEUE_NAME "WQsched.c"

static struct workqueue_struct *my_workqueue;

struct getchar_info {
        /* Other info ... */
    struct work_struct work;
    unsigned int scancode;
};

/*
 * This will get called by the kernel as soon as it's safe
 * to do everything normally allowed by kernel modules.
 */
static void got_char(struct work_struct *work)
{
    struct getchar_info *info = container_of(work, struct getchar_info, work);
    printk(KERN_INFO "Scan Code %x %s.\n",
            info->scancode & 0x7F,
            info->scancode & 0x80 ? "Released" : "Pressed");
}

/*
 * This function services keyboard interrupts. It reads the relevant
 * information from the keyboard and then puts the non time critical
 * part into the work queue. This will be run when the kernel considers it safe.
 */
irqreturn_t irq_handler(int irq, void *dev_id)
{
    /*
     * This variables are static because they need to be
     * accessible (through pointers) to the bottom half routine.
     */
    static int initialised = 0;
    static unsigned char scancode;
    static struct getchar_info task;
    unsigned char status;

    /*
     * Read keyboard status
     */
    status = inb(0x64);
    scancode = inb(0x60);

    if (initialised == 0) {
        INIT_WORK(&task.work, got_char);
        task.scancode = scancode;
        initialised = 1;
    } else {
        PREPARE_WORK(&task.work, got_char);
        task.scancode = scancode;
    }

    queue_work(my_workqueue, &task.work);

    return IRQ_HANDLED;
}

/*
 * Initialize the module - register the IRQ handler
 */
int init_module()
{
    my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);

    /*
     * Since the keyboard handler won't co-exist with another handler,
     * such as us, we have to disable it (free its IRQ) before we do
     * anything.  Since we don't know where it is, there's no way to
     * reinstate it later - so the computer will have to be rebooted
     * when we're done.
     */
    free_irq(1, NULL);

    /*
     * Request IRQ 1, the keyboard IRQ, to go to our irq_handler.
     * SA_SHIRQ means we're willing to have othe handlers on this IRQ.
     * SA_INTERRUPT can be used to make the handler into a fast interrupt.
     */
    return request_irq(1,	/* The number of the keyboard IRQ on PCs */
            irq_handler,	/* our handler */
            IRQF_SHARED, "test_keyboard_irq_handler",
            irq_handler);
}

/*
 *  * Cleanup
 *   */
void cleanup_module()
{
    /*
     * This is only here for completeness. It's totally irrelevant, since
     * we don't have a way to restore the normal keyboard interrupt so the
     * computer is completely useless and has to be rebooted.
     */
    free_irq(1, NULL);
}

/*
 * some work_queue related functions are just available to GPL licensed Modules
 */
MODULE_LICENSE("GPL");
/* vim: ts=4 sw=4 sts=4 et:
*/
