#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("proc write and read");
MODULE_AUTHOR("lchj");
#define PROC_TEST_FILE_NAME "proc_test_file"
#define PROC_TEST_PARENT_FILE_NAME NULL
static int proc_test_read(struct file *flip,char *buf,size_t count,loff_t *f_ops);
static int proc_test_write(struct file *flip,char *buf,size_t count,loff_t *f_ops);
static struct proc_dir_entry *proc_entry;

int len,temp;
static char *str;
static char test[100];
struct file_operations hello_proc_fops = {
	read :proc_test_read,
	.write = proc_test_write
};
int init_proc_module(void){
	printk("proc_test_modlue_init\n");
	proc_entry = proc_create( PROC_TEST_FILE_NAME, 0466, PROC_TEST_PARENT_FILE_NAME ,&hello_proc_fops);
	str ="hello proc test";
	len = strlen(str);
	temp = len;
	printk("%d",len);
	return 0;
}

void exit_proc_module(void){
	printk("proc_test module exit\n");
	remove_proc_entry(PROC_TEST_FILE_NAME,PROC_TEST_PARENT_FILE_NAME);
}

static int proc_test_read(struct file *flip,char *buf,size_t count,loff_t *f_ops){
	printk("test\n");
	printk("%d\n",count);
	if(count>temp){
		count=temp;
	}
	printk("%d\n",count);
	temp=temp-count;
	copy_to_user(buf,str, count);
	if(count==0){
		temp=len;
	}
	printk("%d\n",count);
	return count;
}
static int proc_test_write(struct file *flip,char *buf,size_t count,loff_t *f_ops){
	printk("write  count%zu",count);
	str = kmalloc(100,GFP_KERNEL);
	copy_from_user(str,buf,count);
	len = strlen(str);
	temp = len;
	return count;
}

module_init(init_proc_module);
module_exit(exit_proc_module);