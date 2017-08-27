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
ExecStep $xv_path/bin/xelab -wto f786e9ca3e33472d86a24b1310a94fb9 -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot hw_0_procedural_tb_behav xil_defaultlib.hw_0_procedural_tb xil_defaultlib.glbl -log elaborate.log
