#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

// declarations

struct App
{
  uint8_t flags_u8;
};

extern volatile struct App app;


// defines
// ...

// functions 
void app_init (void);
void app_main (void);

#endif // APP_H_INCLUDED
