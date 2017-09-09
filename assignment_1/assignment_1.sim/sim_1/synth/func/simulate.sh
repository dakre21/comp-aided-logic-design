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
ExecStep $xv_path/bin/xsim reg_tb_func_synth -key {Post-Synthesis:sim_1:Functional:reg_tb} -tclbatch reg_tb.tcl -log simulate.log
