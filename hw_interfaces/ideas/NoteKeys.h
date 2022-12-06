// this is the base-class of note-keys (single-octave)

#ifndef NOTEKEYS_BASE_H
#define NOTEKEYS_BASE_H

#include <stdint.h> 

class NoteKeys_Base
{
  public:
    NoteKeys_Base();
    ~NoteKeys_Base();
    void update();

    uint32_t keyStates;
    uint32_t keyStatesLast;
    uint32_t keyFlag;
};

#endif


