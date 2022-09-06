/************************************************************
 * BlynkGO's HWButton
 *   Support For any MCU on Arduino IDE 
 ************************************************************/
#pragma once

#ifndef _HWBUTTON_H__
#define _HWBUTTON_H__

#define HWBUTTON_VERSION   "1.0.1"

/////////////////////////////////////////////////////////////////

#include "Arduino.h"

/////////////////////////////////////////////////////////////////

#define DEBOUNCE_MS      50
#define LONGCLICK_MS    250
#define DOUBLECLICK_MS  400
#define LONGPRESSED_MS  1500

#define SINGLE_CLICK      1
#define DOUBLE_CLICK      2
#define TRIPLE_CLICK      3
#define LONG_CLICK        4

#define HWButton  HWButton
/////////////////////////////////////////////////////////////////

class HWButton {
  private:
    byte pin;
    uint8_t _pinmode=INPUT_PULLUP;
    int prev_state;
    int state = HIGH;
    uint8_t STATE_PRESSED = LOW;
    uint8_t STATE_RELEASED = HIGH;
    bool first_input_mode;
    byte click_count = 0;
    unsigned int last_click_type = 0;
    unsigned long click_ms;
    unsigned long down_ms;
    unsigned long first_pressed_ms;     // BlynkGO
    unsigned int debounce_time_ms;
    unsigned int down_time_ms = 0;
    unsigned int longpressed_time_ms = LONGPRESSED_MS;  //BlynkGO
    bool pressed_triggered = false;
    bool longclick_detected = false;
        
    typedef void (*CallbackFunction) (HWButton* );

    CallbackFunction pressed_cb = NULL;
    CallbackFunction released_cb = NULL;
    CallbackFunction change_cb = NULL;
    CallbackFunction tap_cb = NULL;
    CallbackFunction click_cb = NULL;
    CallbackFunction long_cb = NULL;
    CallbackFunction double_cb = NULL;
    CallbackFunction triple_cb = NULL;
    CallbackFunction pressing_cb = NULL;
    CallbackFunction longpressed_cb = NULL;
    void* _user_data = NULL;
  public:
    HWButton(){pin = -1;}
    HWButton(byte attachTo);
    HWButton(byte attachTo, byte buttonMode, unsigned int debounceTimeout = DEBOUNCE_MS);
    void setDebounceTime(unsigned int ms);
    
    void setChangedHandler(CallbackFunction f);
    void setPressedHandler(CallbackFunction f);
    void setReleasedHandler(CallbackFunction f);
    void setClickHandler(CallbackFunction f);
    void setTapHandler(CallbackFunction f);
    void setLongClickHandler(CallbackFunction f);
    void setDoubleClickHandler(CallbackFunction f);
    void setTripleClickHandler(CallbackFunction f);
    void setPressingHandler(CallbackFunction f);  // BlynkGO
    void setLongPressed(CallbackFunction f);      // BlynkGO

    // BlynkGO
    void gpio(byte attachTo, byte buttonMode = INPUT_PULLUP, unsigned int debounceTimeout = DEBOUNCE_MS);
   
    inline uint8_t gpio()                                       { return pin;               }
    inline void onValueChanged(CallbackFunction f)              { setChangedHandler(f);     }
    inline void onPressed(CallbackFunction f)                   { setPressedHandler(f);     }
    inline void onReleased(CallbackFunction f)                  { setReleasedHandler(f);    }
    inline void onClicked(CallbackFunction f)                   { setClickHandler(f);       }
    inline void onShortClicked(CallbackFunction f)              { setTapHandler(f);         }
    inline void onLongClicked(CallbackFunction f)               { setLongClickHandler(f);   }
    inline void onDoubleClicked(CallbackFunction f)             { setDoubleClickHandler(f); }
    inline void onTripleClicked(CallbackFunction f)             { setTripleClickHandler(f); }
    inline void onPressing(CallbackFunction f)                  { setPressingHandler(f);    }
    inline void onLongPressed(CallbackFunction f)               { setLongPressed(f);        }
    inline void onLongPressed(unsigned int long_ms, CallbackFunction f)  { longpressed_time_ms = long_ms; setLongPressed(f);        }

    inline void reset(){
      onValueChanged(NULL);
      onPressed(NULL);
      onReleased(NULL);
      onClicked(NULL);
      onShortClicked(NULL);
      onLongClicked(NULL);
      onDoubleClicked(NULL);
      onTripleClicked(NULL);
      onPressing(NULL);
      onLongPressed(NULL);
    }

    inline void  user_data(void* user_data)                    { _user_data = user_data; }
    inline void* user_data()                                   { return _user_data;      }

    unsigned int wasPressedFor();
    boolean isPressed();
    inline bool isPressing()        { return isPressed(); }  // BlynkGO

    unsigned int getNumberOfClicks();
    unsigned int getClickType();
    uint8_t getAttachPin(){return pin;}
    bool operator==(HWButton &rhs);
    HWButton& operator =(uint8_t pin);

    void loop();
    inline void run()        { loop(); }
};

/////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////
