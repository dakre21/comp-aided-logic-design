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
ExecStep $xv_path/bin/xelab -wto c2599be8df034c588ebf73eb8d01459a -m64 --debug typical --relax --mt 8 --maxdelay -L xil_defaultlib -L simprims_ver -L secureip --snapshot reg_tb_time_synth -transport_int_delays -pulse_r 0 -pulse_int_r 0 -pulse_e 0 -pulse_int_e 0 xil_defaultlib.reg_tb xil_defaultlib.glbl -log elaborate.log
