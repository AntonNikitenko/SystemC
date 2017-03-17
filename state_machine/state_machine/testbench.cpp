#include "systemc.h"
#include "state_machine.h"

#define soft_assert(signal, expected) \
      if (signal.read() != expected) { \
          cerr << "@" << sc_time_stamp() << " Check failed. Expected: " << expected << ". Actual: " << signal.read() << ".\n" << endl; \
      }

int sc_main(int argc, char* argv[]) {
    sc_clock clock("clock", 4, SC_NS);
    sc_signal<bool> reset;
    sc_signal<sc_uint<2> > x;
    sc_signal<sc_uint<2> > y;
	sc_signal<sc_uint<2> > st;
    int i = 0;
    // Connect the DUT
    state_machine test_state_machine("test_state_machine");
    test_state_machine.clock(clock);
    test_state_machine.reset(reset);
    test_state_machine.x(x);
    test_state_machine.y(y);
	test_state_machine.st(st);

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("st_machine_waveform");
    // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset, "reset");
    sc_trace(wf, x, "x");
    sc_trace(wf, y, "y");
	sc_trace(wf, st, "st");

    reset = 1; // Assert the reset
    cout << "@" << sc_time_stamp() << " Asserting reset\n" << endl;

    sc_start(6, SC_NS);

    reset = 0; // De-assert the reset
    cout << "@" << sc_time_stamp() << " De-Asserting reset\n" << endl;


    x = 1; 
    sc_start(4, SC_NS);
    assert(y.read() == 2);

    x = 3; 
    sc_start(4, SC_NS);
    assert(y.read() == 1);

    x = 0; 
    sc_start(4, SC_NS);
    assert(y.read() == 2);

    x = 0; 
    sc_start(4, SC_NS);
    assert(y.read() == 1);

    x = 0; 
    sc_start(4, SC_NS);
    assert(y.read() == 1);

    x = 1; 
    sc_start(4, SC_NS);
    assert(y.read() == 2);

    x = 3; 
    sc_start(4, SC_NS);
    assert(y.read() == 1);

    x = 3; 
    sc_start(4, SC_NS);
    assert(y.read() == 2);


    reset = 1; // Assert the reset
    cout << "@" << sc_time_stamp() << " Asserting reset\n" << endl;
    sc_start(1, SC_NS);
    assert(y.read() == 2);
    sc_start(5, SC_NS);

    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
    return 0; // Terminate simulation

}