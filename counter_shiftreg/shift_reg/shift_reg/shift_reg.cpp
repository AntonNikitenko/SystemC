#include "shift_reg.h"

void shift_reg::shift() {
    // We check if reset is active
    data = 0;
    data_out = 0;
    out = 0;
    wait();
    while (true) {
        if(dir==false){
            data.write((data.read().range(6, 0), in.read()));
			data_out.write(data.read());
			out = (bool)data.read().bit(7);
        }
		else {
            data.write((in.read(),data.read().range(7, 1)));
			data_out.write(data.read());
			out = (bool)data.read().bit(0);
		}
        cout << "@" << sc_time_stamp() << " :: Have stored " << data_out.read() << endl;
        wait();
    }
}
