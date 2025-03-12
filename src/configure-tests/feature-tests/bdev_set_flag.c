// SPDX-License-Identifier: GPL-2.0-only

/*
 * Copyright (C) 2025 Datto Inc.
 */

#include "includes.h"

MODULE_LICENSE("GPL");

static inline void dummy(void){
    struct block_device *bdev = NULL;
    unsigned flag;

    bdev_set_flag(bdev, flag);
}
 