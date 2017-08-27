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
ExecStep $xv_path/bin/xsim hw_0_procedural_tb_behav -key {Behavioral:sim_1:Functional:hw_0_procedural_tb} -tclbatch hw_0_procedural_tb.tcl -log simulate.log
