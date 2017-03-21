#include "systemc.h"

#ifndef COUNTER_H
#define	COUNTER_H

SC_MODULE(counter) {
    sc_in_clk clock; // Clock input of the design
    sc_in<bool> reset_n; // negative high, synchronous Reset input
    sc_in<bool> areset_n; //asynchronous reser, negative high
    sc_in<bool> load;
    sc_in<sc_uint<8> > data_in; // 8 bit vector input
    sc_out<sc_uint<8> > data_out; // 8 bit vector output

    //------------Local Variables Here---------------------
    sc_uint<8> reg;

    //------------Code Starts Here-------------------------
    // Below function implements actual register logic

    void count();

    //Constructor
    SC_CTOR(counter) :
            clock("clock"),
            reset_n("reset_n"),
            areset_n("areset_n"),
            load("load"),
            data_in("data_in"),
            data_out("data_out") {
        cout << "Start Executing" << endl;
        SC_CTHREAD(count, clock.pos());
        reset_signal_is(reset_n, false);
        async_reset_signal_is(areset_n, false);
    } // End of Constructor

}; // End of Module

#endif