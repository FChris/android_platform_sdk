#include <errno.h>

#define  LOG_TAG  "gen_gpio_odroidxu4"
#include <cutils/log.h>
#include <cutils/sockets.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <hardware/gen_gpio.h>

static const int MAX_BUF = 1024;

static int gpio_open(int gpio_pin) {
    //Nothing todo, this is only a mock
    return 0;
};

static int gpio_set_direction(int gpio_pin, char* direction) {
    //Nothing todo, this is only a mock
    return 0;
};

static int gpio_close(int gpio_pin) {
    //Nothing todo, this is only a mock
    return 0;
};

static int gpio_read_values(char* buffer, int length, int gpio_pin) {
    char buf[MAX_BUF];
    int count = 0;
    char value;
    while(count < length) {
        buffer[count] = 1; //Since this is a mock we always return 1
        count++;
    }
    return 0;
};

static int gpio_write_values(char* buffer, int length, int gpio_pin) {
    //Nothing todo, this is only a mock
    return 0;
};

static int gen_gpio_read (char* buffer, int length, int gpio_pin) {
    gpio_open(gpio_pin);
    gpio_set_direction(gpio_pin, "in");
    gpio_read_values(buffer, length, gpio_pin);
    gpio_close(gpio_pin);
    return 0;

};

static int gen_gpio_write (char* buffer, int length, int gpio_pin) {
    gpio_open(gpio_pin);
    gpio_set_direction(gpio_pin, "out");
    gpio_write_values(buffer, length, gpio_pin);
    gpio_close(gpio_pin);
    return 0;
};

static int open_gen_gpio(const struct hw_module_t* module, char const* name, struct hw_device_t** device) {
    struct gen_gpio_device_t *dev = malloc(sizeof(struct gen_gpio_device_t)); //Reserve memory for device struct
    memset(dev, 0, sizeof(*dev)); //Clear memory area

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*) module;
    dev->read = gen_gpio_read;
    dev->write = gen_gpio_write;

    *device = (struct hw_device_t*) dev;

    return 0;
};

static struct hw_module_methods_t gen_gpio_module_methods = {
    .open = open_gen_gpio
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = GEN_GPIO_HARDWARE_MODULE_ID,
    .name = "Generic GPIO HW Module",
    .author = "Christoph Fraedrich",
    .methods = &gen_gpio_module_methods,
};
