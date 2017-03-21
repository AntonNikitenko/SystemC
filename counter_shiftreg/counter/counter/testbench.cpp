#include "systemc.h"
#include "counter.h"

int sc_main(int argc, char* argv[])
{
    sc_clock clock("clock", 5, SC_NS);
    sc_signal<bool> reset_n;
    sc_signal<bool> areset_n;
    sc_signal<bool> load;
    sc_signal<sc_uint<8>> data_in;
    sc_signal<sc_uint<8>> data_out;

    // Connect the DUT
    counter test_counter("test_counter");
    test_counter.clock(clock);
    test_counter.reset_n(reset_n);
    test_counter.areset_n(areset_n);
    test_counter.load(load);
    test_counter.data_in(data_in);
    test_counter.data_out(data_out);

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("counter_waveform");

    // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset_n, "reset_n");
    sc_trace(wf, areset_n, "areset_n");
    sc_trace(wf, load, "load");
    sc_trace(wf, data_in, "data_in");
    sc_trace(wf, data_out, "data_out");


    data_in = 0;
    load = 0;
    reset_n = 1;
    areset_n = 0;
    cout << "@" << sc_time_stamp() << " Asserting async reset_n\n" << endl;
    sc_start(5, SC_NS);
    areset_n = 1;


    for (int i=0; i<9; i++){
        sc_start(5, SC_NS);
        assert(data_out.read() == i+1);
    }


    sc_start(4, SC_NS);
    data_in = 3;
    load = 1;
    sc_start(2, SC_NS);
    load = 0;
    sc_start(2, SC_NS);
    assert(data_out.read() == 3);
    sc_start(2, SC_NS); 
    for (int i=0; i<13; i++){
        sc_start(5, SC_NS);
        assert(data_out.read() == i+4);
    }


    sc_start(2, SC_NS);
    int tmp = data_out.read();
    cout << endl << "tmp = " << tmp << endl;
    reset_n = 0;
    sc_start(5, SC_NS);
    assert(data_out.read() == 0);
    sc_start(5, SC_NS);
    reset_n = 1;

    for (int i=0; i<7; i++){
        sc_start(5, SC_NS);
    }
    sc_start(5, SC_NS);
    areset_n = 0;
    sc_start(1, SC_NS);
    assert(data_out.read() == 0);
    areset_n = 1;

    sc_start(10, SC_NS);
    cout << endl;


    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
return 0;
}