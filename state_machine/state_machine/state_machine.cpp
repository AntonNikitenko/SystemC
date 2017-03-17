#include "state_machine.h"

void state_machine::change_st() {
    state = 0;
    wait();
    while (true) {
        switch(state.read()){
            case 0:
                if (x.read() == 0) state = 2;
                else if (x.read() == 1) state = 1;
                else if (x.read() == 3) state = 3;
                else state = 0;
                break;
            case 1:
                if (x.read() == 0) state = 2;
                else if (x.read() == 3) state = 3;
                else state = 0;
                break;
            case 2:
                if (x.read() == 0) state = 2;
                else if (x.read() == 1) state = 1;
                else state = 0;
                break;
            case 3:
                if (x.read() == 0) state = 1;
                else if (x.read() == 3) state = 0;
                else state = 0;
                break;
            default:
                state = 0;
        }
        wait();
    }
}

void state_machine::data_out() {
    switch(state.read()){
        case 0: st=0; y = 2; break;
        case 1: st=1; y = 2; break;
        case 2: st=2; y = 1; break;
        default: st=3; y = 1;
    }
}