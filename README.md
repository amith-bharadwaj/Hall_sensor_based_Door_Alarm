# Hall sensor based Door Alarm

## Functionality of the system

A Hall sensor-based door alarm system is an electronic security device designed to monitor and detect the opening or closing of a door. It utilizes a Hall effect sensor, a specialized transducer that responds to changes in magnetic fields. In this context, the Hall sensor is strategically positioned in close proximity to a magnet that is affixed to either the door or the door frame. When the door is closed, the magnet aligns with the Hall sensor, creating a stable magnetic field. However, when the door is opened, the magnet moves away, causing a disruption in the magnetic field. This alteration triggers the Hall sensor to register a change in its output state. The system is programmed to recognize this transition and respond by activating an alarm, in the form of a buzzer alert. This setup serves as a simple yet effective means of enhancing security by providing an immediate alert in the event of unauthorized entry or tampering with the door. Hall-effect sensor gives output a low voltage when the magnet is near, and high voltage when the magnet is away.

**Note**: Hall effect sensor produces active low output which means that if magnetic field is detected then output is 0 and when magnetic field is not detected the output is 1.

## Working of Hall sensor 

A Hall sensor operates based on the Hall effect, where a voltage is generated across a conductor when subjected to a perpendicular magnetic field and an electric current. In a Hall sensor, a semiconductor chip responds to changes in a nearby magnetic field. When the magnetic field changes, it creates a voltage variation in the chip, which is then used to detect the presence, strength, and polarity of the magnetic field. This makes Hall sensors invaluable in various applications, from detecting door movement in security systems to precise control in motor applications.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/1af6ecc5-39c7-4b08-a334-40916aa5762d)

## Block Diagram

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/2db483ca-2c8e-4313-b2eb-daa7a3ec7052)

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
In this case,the control value is updated as 1, therefore it enters the if loop and checks for the sensor value. As the hall sensor is 1, the second else statement is executed where it is notified that door is open so buzzer and led will be switched ON.

![Screenshot from 2023-10-25 14-12-31](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/8d55731f-b2b1-493b-9438-49d90e21477a)

### Case 2

In this case,the control value is updated as 1,therefore it enters the if loop and checks for the sensor value. As the hall sensor is 0, the second if loop is executed where it is notified that door is closed so buzzer and led will be switched OFF.

![Screenshot from 2023-10-25 14-14-13](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/1a7830e6-8af0-4556-9db9-ad3aa633c4a9)

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

In the image below,the operation performed is the first instruction ''' addi sp,sp,-48 ```.
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/ff2b9cbd-f7d0-4a6c-bdf9-8eab289ef58e)


## References

1. https://github.com/SakethGajawada/RISCV_GNU
2. https://github.com/bhargav-vlsi/RISCV-Display-controller
3. https://github.com/alwinshaju08/IIITB_Waterlevel_detector
4. https://circuitdigest.com/microcontroller-projects/interfacing-hall-effect-sensor-module-with-arduino
