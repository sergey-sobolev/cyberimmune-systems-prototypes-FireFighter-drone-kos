#include "gpio_connector.h"
#include <bsp/bsp.h>
#include <gpio/gpio.h>
#include <rtl/countof.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/cdefs.h>
#include <unistd.h>

bool
GPIOConnector::Init(void)
{
  std::cerr << "CCU GPIOConnector Init() start" << std::endl;

  rc = BspInit(NULL);
  if (rc != BSP_EOK) {
    std::cerr << "Failed to initialize BSP, error code: " << RC_GET_CODE(rc)
              << std::endl;
    return false;
  }

  if (rcOk == rc) {
    rc = BspSetConfig(HW_MODULE_NAME, HW_MODULE_CFG);
    if (rcOk != rc) {
      std::cerr << "Failed to set mux configuration for " << HW_MODULE_NAME
                << " module, error code: " << RC_GET_CODE(rc) << std::endl;
      return false;
    }
  }

  /* Initialize the GPIO. */
  if (rcOk == rc) {
    rc = GpioInit();
    if (rcOk != rc) {
      std::cerr << "GpioInit failed, error code: " << RC_GET_CODE(rc)
                << std::endl;
      return false;
    }
  }

  /* Initialize and setup HW_MODULE_NAME port. */
  if (rcOk == rc) {
    rc = GpioOpenPort(HW_MODULE_NAME, &handle);
    if (rcOk != rc) {
      std::cerr << "GpioOpenPort port " << HW_MODULE_NAME
                << " failed, error code: " << RC_GET_CODE(rc) << std::endl;
      return false;
    } else if (GPIO_INVALID_HANDLE == handle) {
      std::cerr << "GPIO module " << HW_MODULE_NAME << " handle is invalid."
                << std::endl;
      rc = rcFail;
      return false;
    }
  }

  if (rcOk == rc) {
    rtl_uint32_t pin16 = 16; // starts from zero
    rtl_uint32_t pin25 = 25;
    rc = GpioSetMode(handle, pin16, GPIO_DIR_OUT);
    if (rcOk != rc) {
      std::cerr << "GpioSetMode for module " << HW_MODULE_NAME << " pin "
                << pin16 << " failed, error code: " << RC_GET_CODE(rc)
                << std::endl;
      return false;
    }

    rc25 = GpioSetMode(handle, pin25, GPIO_DIR_OUT);
    if (rcOk != rc25) {
      std::cerr << "GpioSetMode for module " << HW_MODULE_NAME << " pin "
                << pin25 << " failed, error code: " << RC_GET_CODE(rc25)
                << std::endl;
      return false;
    }
  }

  if (rcOk == rc && rcOk == rc25) {
    return true;
  } else {
    return false;
  }
}

bool
GPIOConnector::Enable16(void)
{
  std::cerr << "CCU GPIOConnector::Enable16() start" << std::endl;

  rtl_uint32_t pin16 = 16;

  rc = GpioOut(handle, pin16, GPIO_HIGH_LEVEL);
  if (rcOk != rc) {
    std::cerr << "GpioOut 1 for module " << HW_MODULE_NAME << " pin " << pin16
              << " failed, error code: " << RC_GET_CODE(rc) << std::endl;
    return false;
  } else {
    std::cerr << "Module " << HW_MODULE_NAME << " pin " << pin16
              << " is set to 1." << std::endl;
    return true;
  }
}

bool
GPIOConnector::Enable25(void)
{
  std::cerr << "CCU GPIOConnector::Enable25() start" << std::endl;

  rtl_uint32_t pin25 = 25;
  rc25 = GpioOut(handle, pin25, GPIO_HIGH_LEVEL);
  if (rcOk != rc25) {
    std::cerr << "GpioOut 1 for module " << HW_MODULE_NAME << " pin " << pin25
              << " failed, error code: " << RC_GET_CODE(rc25) << std::endl;
    return false;
  } else {
    std::cerr << "Module " << HW_MODULE_NAME << " pin " << pin25
              << " is set to 1." << std::endl;
    return true;
  }
}

bool
GPIOConnector::Disable16(void)
{
  std::cerr << "CCU GPIOConnector::Disable16() start" << std::endl;

  rtl_uint32_t pin16 = 16;

  rc = GpioOut(handle, pin16, GPIO_LOW_LEVEL);
  if (rcOk != rc) {
    std::cerr << "GpioOut 1 for module " << HW_MODULE_NAME << " pin "
              << pin16 << " failed, error code: " << RC_GET_CODE(rc) << std::endl;
    return false;
  } else {
    std::cerr << "Module " << HW_MODULE_NAME << " pin " << pin16
              << " is set to 0." << std::endl;
    return true;
  }
}

bool
GPIOConnector::Disable25(void)
{
  std::cerr << "CCU GPIOConnector::Disable25() start" << std::endl;

  rtl_uint32_t pin25 = 25;

  rc25 = GpioOut(handle, pin25, GPIO_LOW_LEVEL);
  if (rcOk != rc25) {
    std::cerr << "GpioOut 0 for module " << HW_MODULE_NAME << " pin " << pin25
              << " failed, error code: " << RC_GET_CODE(rc) << std::endl;
    return false;
  } else {
    std::cerr << "Module " << HW_MODULE_NAME << " pin " << pin25
              << " is set to 0." << std::endl;
    return true;
  }
}

bool
GPIOConnector::Close(void)
{
  std::cerr << "CCU GPIOConnector::Close() start" << std::endl;

  /* Close GPIO port. */
  if (GPIO_INVALID_HANDLE != handle) {
    Retcode tempRc = GpioClosePort(handle);
    if (rcOk != tempRc) {
      std::cerr << "GpioClosePort for " << HW_MODULE_NAME
                << " port failed, error code: " << RC_GET_CODE(tempRc)
                << std::endl;
      return false;
    }
  }

  return true;
}
