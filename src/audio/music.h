// Background music: the embedded XM module played through MiniFMOD.
#pragma once

void musicStart();               // @ 0x407d1d
void musicStartDefault();        // @ 0x407d6b order 3
void musicPlay(int order);       // @ 0x407d7a restart the song at an order
void musicStop();                // @ 0x407da3
