#include "systemc.h"
#include "shift_reg.h"

int sc_main(int argc, char* argv[])
{
    sc_clock clock("clock", 5, SC_NS);
    sc_signal<bool> reset_n;
    sc_signal<bool> areset_n;
    sc_signal<bool> dir;
    sc_signal<sc_uint<8>> data;
    sc_signal<bool> in;
    sc_signal<sc_uint<8>> data_out;
    sc_signal<bool> out;

    // Connect the DUT
    shift_reg shift_reg_test("shift_reg");
    shift_reg_test.clock(clock);
    shift_reg_test.reset_n(reset_n);
    shift_reg_test.areset_n(areset_n);
    shift_reg_test.dir(dir);
    shift_reg_test.in(in);
    shift_reg_test.data_out(data_out);
    shift_reg_test.out(out);

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("shift_reg_waveform");

    // Dump the desired signals
    sc_trace(wf, clock, "clock");
    sc_trace(wf, reset_n, "reset_n");
    sc_trace(wf, areset_n, "areset_n");
    sc_trace(wf, dir, "dir");
    sc_trace(wf, in, "in");
    sc_trace(wf, data_out, "data_out");
    sc_trace(wf, out, "out");


    dir = 0;
    in = 0;
    reset_n = 1;
    areset_n = 0;
    cout << "@" << sc_time_stamp() << " Asserting async reset_n\n" << endl;
    sc_start(5, SC_NS);
    areset_n = 1;
    sc_start(4, SC_NS);


    in = 1;
    sc_start(1, SC_NS);
    sc_start(5, SC_NS);
    assert(data_out.read() == 0);
    sc_start(5, SC_NS);
    assert(data_out.read() == 1);
    sc_start(2, SC_NS);
    in = 0;
    sc_start(3, SC_NS);
    assert(data_out.read() == 3);
    sc_start(5, SC_NS);
    assert(data_out.read() == 7);

    sc_start(5, SC_NS);
    assert(data_out.read() == 0x0e);
    sc_start(5, SC_NS);
    assert(data_out.read() == 0x1c);
    sc_start(5, SC_NS);
    assert(data_out.read() == 0x38);


    sc_start(2, SC_NS);
    int tmp = data_out.read(); 
    cout << endl << "tmp = " << tmp << endl;
    reset_n = 0;
    sc_start(1, SC_NS);
    assert(data_out.read() == tmp);
    sc_start(4, SC_NS);
    assert(data_out.read() == 0);
    sc_start(3, SC_NS);
    reset_n = 1;
	sc_start(5,SC_NS);


	dir=1;
	in=1;
	sc_start(5,SC_NS);
	assert(data_out.read()==0x00);
	sc_start(5,SC_NS);
	assert(data_out.read()==0x80);
	sc_start(5,SC_NS);
	assert(data_out.read()==0xc0);
	in=0;
	sc_start(5,SC_NS);
	
	assert(data_out.read()==0xe0);
	sc_start(5,SC_NS);
	assert(data_out.read()==0x70);


    for(int i = 0; i<15; i++) sc_start(5, SC_NS);
    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
return 0;
}