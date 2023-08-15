Since C it's not a OOP language some design patterns have to be applied to use OOP concepts such as interfaces. There are no official standards so in this case the Linux Kernel's implementation on this aspect.

# Interfaces
This is an example of how the interfaces are applied in the Linux Kernel. (Including some kernel module's boilerplate).

```c
#include <linux/module.h>
#include <linux/kernel.h>

// Animal interface definition
struct animal_interface {
    void (*make_sound)(void);
};

// Dog implementation
static void dog_sound(void) {
    printk(KERN_INFO "Dog: Woof woof!\n");
}

// Cat implementation
static void cat_sound(void) {
    printk(KERN_INFO "Cat: Meow meow!\n");
}

static struct animal_interface dog_instance = {
    .make_sound = dog_sound,
};

static int __init my_module_init(void) {
    dog_instance.make_sound();
    printk(KERN_INFO "Module initialized\n");
    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Module exited\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Example of interface-like behavior using animal sounds");
```

*The example above it's inspired in the [fs kernel module](https://github.com/torvalds/linux/blob/master/include/linux/fs.h), specifically in the `file_operations` struct.*

