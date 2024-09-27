# Amazon Sidewalk - SoC EM4 Sleep

The EM4 Sleep sample application demonstrates power optimization within the Sidewalk context. After a period of inactivity, the application automatically enters the deepest sleep mode (EM4). The device can be awakened or put to sleep using a timer or a button press. Additionally, it features a CLI and button commands for sending messages to the cloud.

> **Ⓘ INFO Ⓘ**: This application supports xG24 and xG28 radio boards on GSDK 4.4.0.

> **⚠ WARNING ⚠**: Sub-GHz communication occurs in the 900MHz band, a frequency open in the US but may be restricted in other regions.

## Prerequisites

To successfully interface with Amazon Sidewalk, this example application requires the preparation of cloud (AWS) resources and the addition of device credentials matched to those resources. To perform these tasks and procure access to a Sidewalk gateway, complete the initial software and hardware setup steps described in [Getting Started: Prerequisites](https://docs.silabs.com/amazon-sidewalk/latest/sidewalk-getting-started/prerequisites).

> **Ⓘ INFO Ⓘ**: Make note of the additional sub-GHz considerations discussed in the [Silicon Labs Wireless Development Kit](https://docs.silabs.com/amazon-sidewalk/latest/sidewalk-getting-started/prerequisites#silicon-labs-wireless-development-kit) section of the hardware prequisites.

## Build the Application

With prerequisites in place, generate the primary application image as described in [Getting Started: Create and Compile your Sidewalk Application](https://docs.silabs.com/amazon-sidewalk/latest/sidewalk-getting-started/create-and-compile-application).

## Prepare the Cloud and Endpoint

Create AWS resources to interface with your endpoint and couple the application image with device-specific credentials by following the steps in [Getting Started: Provision your Amazon Sidewalk Device](https://docs.silabs.com/amazon-sidewalk/latest/sidewalk-getting-started/provision-your-device).

## Modulation Control

By default, the application will only start on a default radio layer (BLE for xG24 and FSK for xG28). If you wish to change the default radio layer you can modify the `SL_SIDEWALK_COMMON_DEFAULT_LINK_TYPE` define value in the `config/sl_sidewalk_common_config.h` file. Possible values are:

| Value | Radio Layer | Comment |
|---|---|---|
| SL_SIDEWALK_LINK_BLE | BLE |  |
| SL_SIDEWALK_LINK_FSK | FSK |  |
| SL_SIDEWALK_LINK_CSS | CSS | Registration is not supported on CSS |

On the first boot with CSS modulation, the device will start on either FSK or BLE (depending on device support) to perform registration and switch back to CSS once registration is valid.

## Device sleep control

You can adjust the timeout duration for automated sleep, which is set to 30 seconds by default. To change this value, modify the `WAKEUP_INTERVAL_MS` define value in the `em4_mode.h` file. This definition controls both the inactivity timeout before the device enters sleep mode and the duration it remains in the sleep state.

```c
#define WAKEUP_INTERVAL_MS                30000 // 30 seconds
```

All functions and details regarding the sleep mechanism are available in the `em4_mode.c` and `em4_mode.h` files.

## Interacting with the Endpoint

Send commands to the endpoint using either the main board button presses or CLI commands. 

The J-Link RTT interface provides access to the CLI commands. The following table shows the available commands and their effect, with equivalent button presses where applicable. Some commands are dependent on the currently selected radio layer.

### All radio boards push-button actions:

| Command | Description | Example | Main Board Button |
|---|---|---|---|
| switch_link | Switch between BLE, FSK and CSS modulation (depending on supported radio, switch order is BLE->FSK->CSS) | > switch_link | N/A |
| N/A | Puts device into EM4 sleep mode |  | PB0/BTN0 |
| N/A | When device is in EM4 sleep mode, wakes-up the device |  | PB1/BTN1 |
| send | Connects to GW (BLE only) and sends an updated counter value to the cloud | > send | PB1/BTN1 |
| reset | Unregisters the Sidewalk Endpoint | > reset | N/A |

> **⚠ WARNING ⚠**: The `reset` command is used to unregister your device with the cloud. It can only be called on a registered AND time synced device.

## Interacting with the Cloud

Gain additional insight on the network activity from the cloud perspective by using the techniques described in [Getting Started: Interacting with the Cloud](https://docs.silabs.com/amazon-sidewalk/latest/interacting-with-the-cloud).

## Report Bugs & Get Support

You are always encouraged and welcome to ask any questions or report any issues you found to us via [Silicon Labs Community](https://community.silabs.com).
