#include "counter.h"

void counter::count() {
    // We check if reset is active    
    reg = 0;
    data_out.write(reg);
    wait();
    while (true) {
        if(load) reg = data_in.read();
        else reg +=1;
        cout << "@" << sc_time_stamp() << " :: Have stored " << reg << endl;
        data_out.write(reg);
        wait();
    }
}