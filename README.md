# Hall sensor based Door Alarm

## Functionality of the system

A Hall sensor-based door alarm system is an electronic security device designed to monitor and detect the opening or closing of a door. It utilizes a Hall effect sensor, a specialized transducer that responds to changes in magnetic fields. In this context, the Hall sensor is strategically positioned in close proximity to a magnet that is affixed to either the door or the door frame. When the door is closed, the magnet aligns with the Hall sensor, creating a stable magnetic field. However, when the door is opened, the magnet moves away, causing a disruption in the magnetic field. This alteration triggers the Hall sensor to register a change in its output state. The system is programmed to recognize this transition and respond by activating an alarm, in the form of a buzzer alert. This setup serves as a simple yet effective means of enhancing security by providing an immediate alert in the event of unauthorized entry or tampering with the door. Hall-effect sensor gives output a low voltage when the magnet is near, and high voltage when the magnet is away.

**Note**: Hall effect sensor produces active low output which means that if magnetic field is detected then output is 0 and when magnetic field is not detected the output is 1.

## Working of Hall sensor 

A Hall sensor operates based on the Hall effect, where a voltage is generated across a conductor when subjected to a perpendicular magnetic field and an electric current. In a Hall sensor, a semiconductor chip responds to changes in a nearby magnetic field. When the magnetic field changes, it creates a voltage variation in the chip, which is then used to detect the presence, strength, and polarity of the magnetic field. This makes Hall sensors invaluable in various applications, from detecting door movement in security systems to precise control in motor applications.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/1af6ecc5-39c7-4b08-a334-40916aa5762d)

## Block Diagram

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/2db483ca-2c8e-4313-b2eb-daa7a3ec7052)

Here there are 2 inputs to the RISC-V processor,Power Supply switch which is the main control switch and Hall effect sensor. The two outputs are Buzzer and LED. 

## Schematic

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/408eeda4-4e64-4084-9224-1efe63478635)

## C Program

```
//#include <stdio.h>
//#include<stdlib.h>

int main() {

      //printf("entering main function\n");
      int control;
      int hall_sensor;
      int buzzer=0;
      int buzzer_reg = buzzer*4;
      int led=0;
      int led_reg = led*8;
      int mask = 0xFFFFFFF3;
      
      //int reg_check,control_check,sensor_check,test_reg;
   	    
 asm volatile(
	
	"and x30, x30, %2\n\t"	 
	"or x30, x30, %0\n\t" 
	"or x30, x30, %1\n\t"
	:
	:"r"(buzzer_reg), "r"(led_reg), "r"(mask)
	:"x30"
      );
	
		/* asm volatile(
		"addi x30, x30, 0\n\t"
		:"=r"(reg_check)
		:
		:"x30"
	);
	
 	//printf("reg_check is %d\n",reg_check);
        //printf("hall_sensor = %d, control=%d, buzzer = %d, led=%d\n", hall_sensor,control, buzzer_reg,led_reg);
       */ 
        		   	
//int k;
//for(k=0;k<1;k++)
   //printf("entering the while loop\n");
  while(1) 
  {
	  asm volatile(
        	"andi %0, x30, 1\n\t"
	        :"=r"(control)
		:
		:
 	);  
 	
/*
	asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(control_check)
    	:
    	:"x30"
    	);
    	//printf("control_check = %d\n",control_check);
    	//printf("control value = %d\n",control);
        */
	 	
	 	 
         //control = 0;
        //printf("control value is updated as  %d\n",control);
         
      if (control) {   

              //printf("control is 1 therefore inside if loop \n");            
              
		asm volatile(
        		"andi %0, x30, 2\n\t"
			:"=r"(hall_sensor)
        		:
        		:
	 	);  
   /*
 	        asm volatile(
    		  "addi %0, x30, 0\n\t"
    		  :"=r"(sensor_check)
    		  :
    		  :"x30"
    		);
	        //printf("sensor_check = %d\n",sensor_check);
	

 */
              
             // hall_sensor =0;
	        if(hall_sensor){
           //printf("hall sensor is 1 therefore inside if loop\n");
           //printf("Door Open!, Buzzer = ON, led =ON\n");
           
	
	            buzzer = 1;
	            led = 1;  	
	  } 
	  
	  else {
             //printf("hall sensor is 0 therefore else is executed\n");                          
             //printf("Door Closed, Buzzer = OFF , led = OFF\n ");

	    buzzer =0;
	    led=0;
	    
	    }
	    

//Updating registers for buzzer and led
    
	buzzer_reg = buzzer*4;
	led_reg = led*8;
	
	asm volatile(
	    "and x30, x30, %2\n\t"
	    "or x30, x30, %0 \n\t"
            "or x30, x30, %1 \n\t"
	    :
	    :"r"(buzzer_reg), "r"(led_reg), "r"(mask)
            :"x30"
          );	          
                   
  /*               
  asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(test_reg)
    	:
    	:"x30"
    	);
    	//printf("test_reg = %d\n",test_reg);
    //printf("hall_sensor = %d, control =%d, buzzer = %d,  led=%d\n",hall_sensor,control,buzzer_reg,led_reg);
*/

        }
 } 

 return 0;
}
```

## Commands to Convert C program to Assembly Code

Follow the below commands for code conversion.

```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o ./out hall_sensor.c 
riscv64-unknown-elf-objdump -d -r out > asm.txt

```
## Assembly Code

```
outfile:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fd010113          	addi	sp,sp,-48
   10058:	02812623          	sw	s0,44(sp)
   1005c:	03010413          	addi	s0,sp,48
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	fec42783          	lw	a5,-20(s0)
   10068:	00279793          	slli	a5,a5,0x2
   1006c:	fef42223          	sw	a5,-28(s0)
   10070:	fe042423          	sw	zero,-24(s0)
   10074:	fe842783          	lw	a5,-24(s0)
   10078:	00379793          	slli	a5,a5,0x3
   1007c:	fef42023          	sw	a5,-32(s0)
   10080:	ff300793          	li	a5,-13
   10084:	fcf42e23          	sw	a5,-36(s0)
   10088:	fe442783          	lw	a5,-28(s0)
   1008c:	fe042703          	lw	a4,-32(s0)
   10090:	fdc42683          	lw	a3,-36(s0)
   10094:	00df7f33          	and	t5,t5,a3
   10098:	00ff6f33          	or	t5,t5,a5
   1009c:	00ef6f33          	or	t5,t5,a4
   100a0:	001f7793          	andi	a5,t5,1
   100a4:	fcf42c23          	sw	a5,-40(s0)
   100a8:	fd842783          	lw	a5,-40(s0)
   100ac:	fe078ae3          	beqz	a5,100a0 <main+0x4c>
   100b0:	002f7793          	andi	a5,t5,2
   100b4:	fcf42a23          	sw	a5,-44(s0)
   100b8:	fd442783          	lw	a5,-44(s0)
   100bc:	00078c63          	beqz	a5,100d4 <main+0x80>
   100c0:	00100793          	li	a5,1
   100c4:	fef42623          	sw	a5,-20(s0)
   100c8:	00100793          	li	a5,1
   100cc:	fef42423          	sw	a5,-24(s0)
   100d0:	00c0006f          	j	100dc <main+0x88>
   100d4:	fe042623          	sw	zero,-20(s0)
   100d8:	fe042423          	sw	zero,-24(s0)
   100dc:	fec42783          	lw	a5,-20(s0)
   100e0:	00279793          	slli	a5,a5,0x2
   100e4:	fef42223          	sw	a5,-28(s0)
   100e8:	fe842783          	lw	a5,-24(s0)
   100ec:	00379793          	slli	a5,a5,0x3
   100f0:	fef42023          	sw	a5,-32(s0)
   100f4:	fe442783          	lw	a5,-28(s0)
   100f8:	fe042703          	lw	a4,-32(s0)
   100fc:	fdc42683          	lw	a3,-36(s0)
   10100:	00df7f33          	and	t5,t5,a3
   10104:	00ff6f33          	or	t5,t5,a5
   10108:	00ef6f33          	or	t5,t5,a4
   1010c:	f95ff06f          	j	100a0 <main+0x4c>
```


## Number of Unique Instructions

```
Number of different instructions: 10
List of unique instructions:
and
sw
andi
or
beqz
slli
j
addi
li
lw


```
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/fe6e1717-652d-423f-aa19-63be79b949fd)

## Spike Results

### Case 1
In this case,the control value is updated as 1, therefore it enters the if loop and checks for the sensor value. As the hall sensor is 1, the if loop is executed where it is notified that door is open so buzzer and led will be switched ON.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/24dbfcab-e0a2-4e3d-a04d-c39bc44a4efd)


### Case 2

In this case,the control value is updated as 1,therefore it enters the if loop and checks for the sensor value. As the hall sensor is 0, the second else statement is executed where it is notified that door is closed so buzzer and led will be switched OFF.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/9b9f7efc-df48-4a4e-9bb7-753c51dcd2c0)


### Case 3
In this case,the control switch is OFF, here control value is given as 0. Therefore it does not proceed further in detecting the sensor value.

![Screenshot from 2023-10-25 14-19-56](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/b602925e-d822-4330-8d91-cd9b8db283b3)

## Functional Simulation

To verify the functionality of the Verilog code generated for the processor chip, we will conduct a functional simulation. This involves testing the processor with a range of input combinations and then comparing the resulting output with the expected values to ensure proper operation.

### Case 1

Here in this example, the inputs are control_switch = 1, Hall_sensor_value = 0. As the control switch is ON the system will start working now, as the hall sensor value is 0 ,since hall sensor value is a active low signal, it means that the magnetic field is detected , hence the door is Closed. So the Buzzer and LED should be in OFF state. (Buzzer=0 , LED =0 ). The same is observed as a 2 bit output variable in the waveform.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/8e7008c0-ec41-4aa5-855f-2331e0eca4e4)


### Case 2
Here in this example, the inputs are control_switch = 1, Hall_sensor_value = 1. As the control switch is ON the system will start working now, as the hall sensor value is 1 , it means that the magnetic field is not detected , hence the door is open. So the Buzzer and LED should be in ON state. (Buzzer=1 , LED =1 ). The same is observed as a 2 bit output variable in the waveform.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/1a64f64d-bee2-4f70-8396-50ec87eac172)


### Case 3

In this case, the inputs are control_switch = 0, Hall_sensor_value = 0. As the control switch is OFF , the system will not work, the hall sensor would not proceed to sense the magnetic field therefore output is 0. Buzzer and LED are OFF.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/20ccecfe-36a8-4c8b-b714-42a0e5467f75)

## Instruction Verification

Here, Signal43, Signal45, and Signal58 serve as registers with specific functionalities.Signal43 contains the hardwired wire zero register, referred to as x0.Signal45 is designated as the register for the stack pointer, denoted as x2.Signal58 is associated with the a5 register.

In the image below,the operation performed is the first instruction "addi sp,sp,-48". 

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/ff2b9cbd-f7d0-4a6c-bdf9-8eab289ef58e)

### Verification of input Instruction and output Instruction 

 In this instruction,fec42783 lw a5,-20(s0), the value from memory at an offset of -20 bytes from the address in s0 is loaded into register a5. This is where the program is retrieving some data from memory, which is the input data.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/21455fac-e431-4e22-a12c-0434328c99a4)

 In this instruction,00ef6f33  or t5,t5,a4 ,The  bitwise OR operation between the values in t5 and a4, is performed and stores the result in t5.This is where the output is being dumped.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/7087b9de-1e60-4565-b333-6bf9d42e11f4)

## Yosys Synthesis

Yosys is an open-source synthesis tool widely used in the field of digital design and electronic engineering. It plays a crucial role in the process of converting a high-level hardware description (usually written in a language like Verilog or VHDL) into a gate-level netlist, which can be further used for logic optimization and implementation on a target FPGA or ASIC platform. Yosys employs a series of algorithms and techniques, including technology mapping, optimization, and various heuristics, to efficiently translate and optimize the input design. It supports a range of synthesis targets, making it versatile and adaptable to different hardware platforms. Additionally, Yosys offers features for formal verification and other advanced analyses, making it a valuable tool for both initial synthesis and subsequent refinement of digital designs.



## Gate Level Simulation

Gate-level simulation is a crucial step in the verification process of digital electronic designs. In gate-level simulation, the design is represented in terms of individual logic gates and their interconnections, rather than in a higher-level hardware description language (HDL) like Verilog or VHDL. This simulation approach provides a more detailed and accurate representation of how the actual hardware will behave. The simulator models the propagation delays of logic gates and simulates the switching behavior of signals. By applying test vectors to the inputs of the gates, designers can observe how the circuit responds, allowing them to detect and debug potential issues such as timing violations, race conditions, and logic errors. Gate-level simulation is particularly important for verifying the correctness and performance of a design before it is synthesized and implemented on hardware.
Follow these below commands to convert RTL code into netlist by yosys.

```
yosys
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v 
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog synth_processor_test.v
```

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/364c6b37-dba6-4d91-8e00-3b594e093cae)
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/a3e2e339-2df9-4b91-b70e-480b14e3742c)


In the image below, we can see the synthesized circuit for wrapper module in processor.
```
show wrapper
```

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/37f7c3a9-be67-404d-958b-1abd98846db8)


Follow the below command to run GLS simulation.

```
iverilog -o test synth_processor_test.v testbench.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v
```
The output waveform generated is given below.

**Case1:** In this case the inputs provided is ```11``` , the control switch is 1 and the hall sensor is 1 which means the magnetic field is not detected, therefore the buzzer and led should be ON.The same can be verified in the GLS Simulation waveform given below. It matches with the functional verification done in the previous steps.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/4f29ce0c-95d6-4f26-81b3-4543dc5d32f0)

**Case2:** In this case the inputs provided is ```01``` , the control switch is 0 and the hall sensor is 1 which means the control switch is OFF, therefore the system does not function and outputs are 0.The same can be verified in the GLS Simulation waveform given below. It matches with the functional verification done in the previous steps.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/948b39c4-b4c2-4322-9e09-6f3f284e7024)

## Physical Design

Physical design in VLSI (Very Large Scale Integration) refers to the process of transforming a logical circuit representation of an integrated circuit (IC) into a physical layout that can be manufactured. This process involves translating the logical design into a geometric representation that can be fabricated on a semiconductor substrate. The physical design process is critical for achieving the desired performance, power efficiency, and manufacturability of the integrated circuit.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/6245bcca-69d0-4228-9ada-1993239a0480)

Here is a brief overview of the key steps in the physical design:

**Floorplanning:** Involves allocating space for various functional blocks of the design on the chip.Determines the overall chip size, the placement of major components, and the interconnections between them.

**Placement:**
        Decides the exact locations of individual standard cells or other functional elements on the chip.
        Aims to minimize the total wire length and optimize for performance and area.

**Global Routing:**
Establishes the high-level connections between different blocks on the chip.
        Defines the general paths that the interconnecting wires will follow.

**Detailed Routing:**
        Focuses on the detailed paths of interconnections between individual transistors and gates.
        Involves metal layer routing to connect various components while adhering to design rules and constraints.

**Clock Tree Synthesis:**
        Designs a network of clock distribution lines to ensure synchronized operation of all components.
        Aims to minimize clock skew and maintain signal integrity.

**Power Planning:**
        Manages the distribution of power throughout the chip to ensure that each component receives the necessary power supply.
        Addresses issues related to power consumption and dissipation.

**Physical Verification:**
        Involves checking the layout against design rules and constraints to ensure manufacturability.
        Includes tasks such as design rule checking (DRC) and layout versus schematic (LVS) verification.

**Extraction:**
        Extracts parasitic information from the layout, such as resistance and capacitance, for use in subsequent simulations.

**Timing Closure:**
        Focuses on meeting the specified timing requirements by adjusting the placement and sizing of components.
        Involves multiple iterations to achieve optimal performance.

**Signoff:**
        The final step involves obtaining approval from various design tools and signoff criteria.
        Once signoff is achieved, the design is considered ready for fabrication.

##  Preparing the Design

Include the files in the working directory, and perform the following commands.
```
make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design project_riscv
```
![Screenshot from 2023-11-14 11-38-34](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/7a9fde6b-4e8f-41f0-b87e-610e17023110)

## Synthesis

Synthesis is the process of converting a high-level hardware description, typically in a hardware description language (HDL) like Verilog or VHDL, into a netlist of logical gates and flip-flops. This netlist represents the functionality of the circuit without specifying the physical layout. Synthesis tools optimize the design for area, power, and timing, generating a register transfer level (RTL) description that serves as the input for subsequent stages of the VLSI Physical design flow.

Follow the below command to run synthesis.
```
%run_synthesis
```
![Screenshot from 2023-11-14 11-40-38](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/616fcb75-3d9d-4681-8e92-bca06cb20059)

The statistics after synthesis can be seen below:

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/e47dd13a-94e4-4a05-b54a-3911709acfab)

## FloorPlanning

Floor planning involves the strategic allocation of space on a semiconductor chip for different functional blocks. This process determines the overall chip size, the placement of major components, and the interconnections between them. Efficient floor planning is crucial for optimizing chip performance, minimizing signal delays, and managing power distribution. It considers factors such as the physical proximity of critical components, interconnect lengths, and the overall layout's impact on manufacturability. 

Follow the below command to run Floorplan.

```
%run_floorplan
```
![Screenshot from 2023-11-14 11-41-10](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/938649a3-e553-4ffa-aa5e-803f269eabe3)


To view the floorplan on Magic, follow the below command in floorplan directory.

```
magic -T /home/amith/.volare/volare/sky130/versions/1341f54f5ce0c4955326297f235e4ace1eb6d419/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/355057ab-1438-4bd1-82dc-c710135d6f78)

### Die Area And Core Area after floorplan

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/73c97294-b646-42f0-930b-658656a1f73e)

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/50ac5be5-8f98-4c3e-8550-391ae9348f66)

## Placement

In Placement, the individual functional elements, such as standard cells or IP blocks, are strategically positioned on the semiconductor chip. The goal is to optimize the arrangement to minimize the overall interconnect wirelength, which directly impacts performance and power consumption. The placement process involves algorithms that consider factors like signal delays, congestion, and the physical proximity of components to enhance the chip's overall efficiency. Effective placement sets the foundation for subsequent steps in the design flow, influencing the circuit's area utilization, timing closure, and manufacturability.

command to run placement is given below.
```
%run_placement
```
![Screenshot from 2023-11-14 11-51-34](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/77508fbd-47ec-4afc-90c9-e27e0b9d78af)

Follow the below command to view the layout after placement in magic software in the placement directory.
```
magic -T /home/amith/.volare/volare/sky130/versions/1341f54f5ce0c4955326297f235e4ace1eb6d419/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/bc42e177-a828-4878-b553-3d9c149ac381)

## CTS

The goal is to ensure uniform and low-skew distribution of clock signals to all components, facilitating synchronous and reliable operation of the entire integrated circuit. Clock tree analysis involves designing a hierarchical tree-like structure of clock distribution lines, buffers, and clock gating cells. This process aims to minimize clock skew, reduce power consumption, and meet stringent timing requirements. By carefully managing clock signals, designers can enhance the overall performance and reliability of the chip. The clock tree analysis phase is essential for achieving timing closure and ensuring that all sequential elements in the design are synchronized.

command to run cts:
```
%run_cts
```
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/bee3bdf5-7b59-4c3d-a1f0-42de42d7a784)

## Routing

Routing is a crucial phase in VLSI physical design that involves the detailed planning and implementation of interconnections between different components on a semiconductor chip. After placement, where the positions of individual elements are determined, the routing process establishes the paths for wires or metal tracks to connect these elements. Global routing defines the high-level connections, while detailed routing specifies the exact paths, adhering to design rules and constraints. Efficient routing aims to minimize signal delays, optimize for performance and area, and meet specified design objectives. Advanced algorithms and optimization techniques are employed to navigate the complex task of interconnecting thousands or millions of components while considering factors like congestion, wirelength, and signal integrity. Successful routing is crucial for achieving the desired functionality, performance, and manufacturability of the integrated circuit.

command to run routing is:
```
%run_routing
```
![Screenshot from 2023-11-14 12-25-32](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/a4a186cd-0816-429c-a6d5-d2b8b6a6db3e)


## Acknowledgement
1. Mr Kunal Ghosh, Co-Founder VLSI SYSTEM DESIGN 
2. Mayank Kabra,Founder,Chipcron Pvt.Ltd.
3. Alwin Shaju IIITB
4. Bhargav DV IIITB

## References

1. https://github.com/SakethGajawada/RISCV_GNU
2. https://github.com/bhargav-vlsi/RISCV-Display-controller
3. https://github.com/alwinshaju08/IIITB_Waterlevel_detector
4. https://circuitdigest.com/microcontroller-projects/interfacing-hall-effect-sensor-module-with-arduino
