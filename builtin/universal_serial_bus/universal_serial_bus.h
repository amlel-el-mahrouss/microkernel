/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 10/11/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <hw/pci.h>
#include <hw/mmap.h>

typedef char usb_ctrl_name_t;
typedef int16_t usb_ctrl_kind_t;

struct usb_ctrl_device_info
{
    usb_ctrl_name_t name[64];
    usb_ctrl_kind_t kind;

    struct usb_ctrl_packet* incoming_port;
    struct usb_ctrl_packet* outgoing_port;

    union
    {
        bool ready_out : 1;
        bool ready_in : 1;
    };
};

enum
{
    USB_MASS_STORAGE = 0x08,
    USB_AUDIO_INTERFACE = 0x01,
    USB_PRINTING_DEVICE = 0x07,
    USB_HUB_DEVICE = 0x9,
    USB_VIDEO_INTERFACE = 0x0E,
    USB_WIRELESS_INTERFACE = 0xE0,
    USB_VENDOR = 0xFF,
};

/**
 * @brief Inits the USB devices from a device tree.
 * @return int32_t the number of usb devices discovered.
 */

int32_t usb_device_init(void);

/**
 * @brief Finis the USB devices found by the system.
 */

void usb_device_fini(void);

/**
 * @brief returns a string representation of the error.
 *
 * @param err error id.
 * @return const char* error as a string.
 */

const char* usb_err_to_str(long err);
