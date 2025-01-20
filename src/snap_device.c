#include "includes.h"
#include "snap_device.h"
#include "module_control.h"
#include "tracer.h"
#include "logging.h"
#include "tracer_helper.h"

static struct snap_device** snap_devices;
static spinlock_t snap_device_lock;
// static unsigned long snap_device_lock_flags;

int init_snap_device_array(void){
    LOG_DEBUG("allocate global device array");
    snap_devices =
            kzalloc(dattobd_max_snap_devices * sizeof(struct snap_device *),
                    GFP_KERNEL);
    if (!snap_devices) {
            return -ENOMEM;
    }
    spin_lock_init(&snap_device_lock);
    return 0;
}

void cleanup_snap_device_array(void){
    LOG_DEBUG("destroying snap devices");
    if (snap_devices) {
            int i;
            struct snap_device *dev;

            snap_device_array_mut snap_devices_wrp = get_snap_device_array_mut();

            tracer_for_each(dev, i)
            {
                    if (dev) {
                            LOG_DEBUG("destroying minor - %d", i);
                            tracer_destroy(dev, snap_devices_wrp);
                    }
            }
        
            put_snap_device_array_mut(snap_devices_wrp);
            kfree(snap_devices);
            snap_devices = NULL;
    }
}

snap_device_array get_snap_device_array(void){
    spin_lock(&snap_device_lock);
    return snap_devices;
}

snap_device_array_mut get_snap_device_array_mut(void){
    spin_lock(&snap_device_lock);
    return snap_devices;
}

snap_device_array get_snap_device_array_nolock(void){
    return snap_devices;
}

void put_snap_device_array(snap_device_array _){
    spin_unlock(&snap_device_lock);
    return;
}

void put_snap_device_array_mut(snap_device_array_mut _){
    spin_unlock(&snap_device_lock);
    return;
}

void put_snap_device_array_nolock(snap_device_array _){
    return;
}