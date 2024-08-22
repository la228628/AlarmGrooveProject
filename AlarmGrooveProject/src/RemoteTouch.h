// The IR codes are used to control the display with a remote control
#ifndef REMOTETOUCH_H
#define REMOTETOUCH_H


extern uint64_t POWER;
extern uint64_t VOLUP;
extern uint64_t VOLDOWN;
extern uint64_t LEFT;
extern uint64_t RIGHT;
extern uint64_t PAUSE;
extern uint64_t DOWN;
extern uint64_t UP;
extern uint64_t ONE;

void setUpButton(uint64_t ircode);
void setDownButton(uint64_t ircode);
void setLeftButton(uint64_t ircode);
void setRightButton(uint64_t ircode);
void setSelectButton(uint64_t ircode);
void setPowerButton(uint64_t ircode);
void setVolumeUpButton(uint64_t ircode);
void setVolumeDownButton(uint64_t ircode);
void setOneButton(uint64_t ircode);


#endif // REMOTETOUCH_H