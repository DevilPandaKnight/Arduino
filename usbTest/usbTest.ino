#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "usbconfig.h"
#include "usbdrv.h"

struct keyboard_report_t{
  uint8_t a;
  uint8_t b;
};

static keyboard_report_t keyboard_report;

PROGMEM const char usbHidReportDescriptor[23] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x02,                    //   REPORT_COUNT (2)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xc0                           // END_COLLECTION
};

static unsigned char idle_rate; // ignored
static unsigned char protocol_version = 0; // ignored


unsigned char usbFunctionSetup(unsigned char data[8])
{
  usbRequest_t *rq ;
  memcpy(&rq,&data,8);
  if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) /* class request type */{
    if (rq->bRequest == USBRQ_HID_GET_REPORT) /* wValue: ReportType (highbyte), ReportID (lowbyte) */{
      long s = sizeof(keyboard_report);
      memcpy(&usbMsgPtr,&keyboard_report,s);
      return s;
    }
     else if (rq->bRequest == USBRQ_HID_GET_IDLE)
    {
      memcpy(&usbMsgPtr,&idle_rate,sizeof(idle_rate));
      return 1;
    }
    else if (rq->bRequest == USBRQ_HID_SET_IDLE)
    {
      idle_rate = rq->wValue.bytes[1];
    }
    else if (rq->bRequest == USBRQ_HID_GET_PROTOCOL)
    {
      memcpy(&usbMsgPtr,&protocol_version,sizeof(protocol_version));
      return 1;
    }
    else if (rq->bRequest == USBRQ_HID_SET_PROTOCOL)
    {
      protocol_version = rq->wValue.bytes[1];
    }
    else if (rq->bRequest == USBRQ_HID_SET_REPORT)
    {
      if (rq->wLength.word == 1) // check data is available
      {
        return USB_NO_MSG; // send nothing but call usbFunctionWrite
      }
    }
  }
  return 0;
}

void setup() {

}

void loop() {
  sei();
  usbInit(); // start v-usb
  usbDeviceDisconnect(); // enforce USB re-enumeration, do this while interrupts are disabled!
  _delay_ms(250);
  usbDeviceConnect();
  
  sei(); // enable interrupts

  keyboard_report.a = 'a';
  keyboard_report.b = 'b';
  
  for(;;){
    usbPoll();

    
  }
}
