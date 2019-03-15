#ifndef SYS_H_INCLUDED
#define SYS_H_INCLUDED


// declarations

struct Sys
{
  uint8_t  flags_u8;
};

extern volatile struct Sys sys;


// defines
// ...


// functions
void sys_init (void);
void sys_main (void);

#endif // SYS_H_INCLUDED
