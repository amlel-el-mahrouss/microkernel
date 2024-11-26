/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 13/04/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/sys.h>

struct sys_host_ctrl_hid;
struct sys_host_ctrl_hub;
struct sys_host_ctrl_generic;

typedef enum
{
    USB_CODE_GET_STATUS = 0,
    USB_CODE_CLEAR_FEATURE = 1,
    USB_CODE_SET_FEATURE = 3,
    USB_CODE_SET_ADDRESS = 5,
    USB_CODE_GET_DESCRIPTOR = 6,
    USB_CODE_SET_DESCRIPTOR = 7,
    USB_CODE_GET_CONFIGURATION = 8,
    USB_CODE_SET_CONFIGURATION = 9,
    USB_CODE_GET_INTERFACE = 10,
    USB_CODE_SET_INTERFACE = 11,
    USB_CODE_SYNC_FRAME = 12
} USB_CODES;

typedef enum
{
    USB_FEAT_SEL_ENDPOINT_HALT = 0,
    USB_FEAT_SEL_DEVICE_REMOTE_WAKEUP = 1,
    USB_FEAT_SEL_TEST_MODE = 2,
} USB_FEAT_SEL;

enum
{
    AUDIO_DEVICE      = 0x01,
    COMM_DEVICE       = 0x02,
    HID_DEVICE        = 0x03,
    PHYSCIAL_DEVICE   = 0x05,
    IMAGING_DEVICE    = 0x06,
    PRINTER_DEVICE    = 0x07,
    MSC_DEVICE        = 0x08,
    HUB_DEVICE        = 0x09,
    CDC_DEVICE        = 0x0a,
    CCID_DEVICE       = 0x0b,
    SECURITY_DEVICE   = 0x0d,
    VIDEO_DEVICE      = 0x0e,
    HEALTHCARE_DEVICE = 0x0f,
    DIAGNOSTIC_DEVICE = 0xdc,
    WIRELESS_DEVICE   = 0xe0,
    MISC_DEVICE       = 0xef,
};

enum
{
    HID_SUBCLASS_NONE = 0,
    HID_SUBCLASS_BOOT = 1,
};

enum
{
    HID_BOOT_PROTO_NONE = 0,
    HID_BOOT_PROTO_KEYBOARD = 1,
    HID_BOOT_PROTO_MOUSE = 2,
};

typedef enum
{
    HC_HOST_OHCI = 0, // FireWire/FireHumanDevice
    HC_HOST_UHCI = 1, // USB 1.0
    HC_HOST_EHCI = 2, // USB 2.0
    HC_HOST_XHCI = 3, // USB 3.0
} HC_TYPE;
