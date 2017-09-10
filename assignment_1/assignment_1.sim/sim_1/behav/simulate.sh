#!/bin/bash -f
xv_path="/opt/Xilinx/Vivado/2017.2"
ExecStep()
{
"$@"
RETVAL=$?
if [ $RETVAL -ne 0 ]
then
exit $RETVAL
fi
}
ExecStep $xv_path/bin/xsim mux_tb_behav -key {Behavioral:sim_1:Functional:mux_tb} -tclbatch mux_tb.tcl -log simulate.log
