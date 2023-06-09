File name readme-transport
Author sh
Date Oct.18.2004
Purpose: Describe Model simulation of Mining Transport System
*****************************************************************************************************************************
Atomic model: Gen
Purpose: Describe atomic model: Gen

Function:
Gen has no input port and one output port called out. Gen is used to generate trucks and assign unique TruckID to each truck.

Test strategy:
gen.ma includes configuration information and distribution information of Gen. Run the simulator and terminate in 00:30:00:000.

Result:
bat: gen.bat
input: no
output: gen.out
logfile: gen.log
*****************************************************************************************************************************
Atomic model: loadque
Purpose: Describe atomic model: loadqueue

Function:
loadqueue is an atomic model. It is used to store waiting list in front of loadserver.It has two input ports in & Done. "in" comes from gen and input TruckID, while "Done" comes from loadserver and input state of loadserver. It has one output port out.

Test strategy:
Loadqueue.ma includes configuration information and value of preparationTime.Loadqueue.ev includes input events series. Run the simulator.

Result:
bat: Loadqueue.bat
input: Loadqueue.ev
output: Loadqueue.out
logfile: Loadqueue.log
*****************************************************************************************************************************
Atomic model: loadserver
Purpose: Describe the atomic model: loadserver

Function:
loadserver is an atomic model. It is used to load trucks.It has one input port in and two output ports out and done. "in" comes from loadqueue. 

Test strategy:
case1:
loadserver.ma includes configuration information and distribution information of service time. Run the simulator.
Use the events input series in loadserver2.ev.
Result:
bat : loadserver2.bat
input: loadserver2.ev
output: loadserver2.out
logfile: loadserver2.log

case2:
loadserver.ma includes configuration information and distribution information of service time. loadserver.ev includes input events series. Run the simulator.

Result:
bat : loadserver.bat
input: loadserver.ev
output: loadserver.out
logfile: loadserver.log
*****************************************************************************************************************************
Atomic model: unloadque
Purpose: Describe the atomic model: unloadqueue

Function:
unloadqueue is an atomic model. It is used to store waiting list in front of unloadserver.It has two input ports in & Done. "in" comes from load and input TruckID, while "Done" comes from unloadserver and input state of unloadserver. It has one output port out.

Test strategy:
unloadqueue.ma includes configuration information and value of preparationTime.unLoadqueue.ev includes input events series. Run the simulator.

Result:
bat: unloadqueue.bat
input: unloadqueue.ev
output: unloadqueue.out
logfile: unloadqueue.log
*****************************************************************************************************************************
Atomic model: unloadserver
Purpose: Describe the atomic model: unloadserver

Function:
unloadserver is an atomic model. It is used to unload trucks.It has one input port in and two output ports out and done. "in" comes from unloadqueue. 

Test strategy:
unloadserver.ma includes configuration information and distribution information of service time. unloadserver.ev includes input events series. Run the simulator.

Result:
bat : unloadserver.bat
input: unloadserver.ev
output: unloadserver.out
logfile: unloadserver.log
*****************************************************************************************************************************
Coupled model: load
Purpose: Describe the coupled model: load

Function:
load is a coupled model including loadqueue and loadserver two atomic models. It has one input port arriveload and one output port exitload.

Test strategy:
load.ma includes configuration information and distribution information of load. load.ev includes input events series. Run the simulator.

Result:
bat: load.bat
input: load.ev
output: load.out
logfile: load.log
*****************************************************************************************************************************
Coupled model: unload
Purpose: Describe the coupled model: unload

Function:
load is a coupled model including unloadqueue and unloadserver two atomic models. It has one input port arriveunload and one output port exitunload.

Test strategy:
unload.ma includes configuration information and distribution information of unload. unload.ev includes input events series. Run the simulator.

Result:
bat : unload.bat
input: unload.ev
output: unload.out
logfile: unload.log
*****************************************************************************************************************************
Top-level model: transport
Function:
Transport is a model including gen, load and unload three torp-level models and totally five atomic models. It has no input port and one output port exitunload.Transport system is build to simulate the mining transport system with load and unload services.

Test strategy:
Transport.ma includes configuration information and distribution information of gen,load and unload. Run the simulator and set the stop time as 40 minutes.

Result:
Bat: transport.bat
output: transport.out
logfile: transport.log

Transportadv.ma includes the same configuration information with transport.ma. But compare with transport.ma, normal mean of loadserver is shortened and normal mean of unloadserver becomes longer. Run the simulator and set the stop time as 40 minutes

Result:
Bat: transportadv.bat
output: transportadv.out
logfile: transportadv.log

Transportgen.ma includes the same configuration information with transportadv.ma. But compare with transportadv.ma, distribution parameters of loadserver and unloadserver are the same, distribution parameters of gen is prolonged. Run the simulator and set the stop time as 40 minutes.

Result:
Bat: transportgen.bat
output: transportgen.out
logfile: transportgen.log

