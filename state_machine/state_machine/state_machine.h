#include "systemc.h"

#ifndef DESIGN_H
#define	DESIGN_H

SC_MODULE(state_machine) {
    sc_in_clk clock; // Clock input of the design
    sc_in<bool> reset; // active high, asynchronous Reset input
    sc_in<sc_uint<2> > x; //input
    sc_out<sc_uint<2> > y; //output
	sc_out<sc_uint<2> > st;

    //------------Local Variables Here---------------------
    sc_signal<sc_uint<2> > state;

    //------------Code Starts Here-------------------------
    // Below function implements actual register logic

    void change_st();

    void data_out();

    // Constructor
     SC_CTOR(state_machine) :
            clock("clock"),
            reset("reset"),
            x("x"),
            y("y"),
			st("st"){
        cout << "Executing new" << endl;
        SC_CTHREAD(change_st, clock.pos());
        async_reset_signal_is(reset, true);
        SC_METHOD(data_out);
        sensitive << state;
    } // End of Constructor

}; // End of Module

#endif	/* DESIGN_H */