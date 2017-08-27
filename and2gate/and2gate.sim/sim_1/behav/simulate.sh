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
ExecStep $xv_path/bin/xsim and2gate_tb_behav -key {Behavioral:sim_1:Functional:and2gate_tb} -tclbatch and2gate_tb.tcl -log simulate.log
