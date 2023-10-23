# Hall sensor based Door Alarm

## Functionality of the system

A Hall sensor-based door alarm system is an electronic security device designed to monitor and detect the opening or closing of a door. It utilizes a Hall effect sensor, a specialized transducer that responds to changes in magnetic fields. In this context, the Hall sensor is strategically positioned in close proximity to a magnet that is affixed to either the door or the door frame. When the door is closed, the magnet aligns with the Hall sensor, creating a stable magnetic field. However, when the door is opened, the magnet moves away, causing a disruption in the magnetic field. This alteration triggers the Hall sensor to register a change in its output state. The system is programmed to recognize this transition and respond by activating an alarm, in the form of a buzzer alert. This setup serves as a simple yet effective means of enhancing security by providing an immediate alert in the event of unauthorized entry or tampering with the door. 

## Working of Hall sensor 

A Hall sensor operates based on the Hall effect, where a voltage is generated across a conductor when subjected to a perpendicular magnetic field and an electric current. In a Hall sensor, a semiconductor chip responds to changes in a nearby magnetic field. When the magnetic field changes, it creates a voltage variation in the chip, which is then used to detect the presence, strength, and polarity of the magnetic field. This makes Hall sensors invaluable in various applications, from detecting door movement in security systems to precise control in motor applications.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/1af6ecc5-39c7-4b08-a334-40916aa5762d)

## Block Diagram

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/2db483ca-2c8e-4313-b2eb-daa7a3ec7052)

## Schematic

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/408eeda4-4e64-4084-9224-1efe63478635)

## C Program

```
int main() {

   // Replace these variables with sensor pins and setup environment
      int control_switch;
      int hall_sensor;
      int buzzer=0; 
      int buzzer_reg = buzzer*4;
      int led=0; 
      int led_reg = led *8;

  
    	    
  asm volatile(
	"or x30, x30, %0\n\t" 
	"or x30, x30, %1\n\t"
	:
	:"r"(buzzer_reg), "r"(led_reg)
	:"x30"
	);


  while(1) {

	  asm volatile(
        	"andi %0, x30, 1\n\t"
	
        	:"=r"(control_switch)
		:
		:
 	);

          if (control_switch) {

		asm volatile(
        		"andi %0, x30, 2\n\t"
			:"=r"(hall_sensor)
        		:
        		:
	 	);

	if(hall_sensor){
	    // door closed
  
              // buzzer = digitalwrite(0);
              //printf("Buzzer is OFF");
	
	buzzer = 0;
  	
	led = 0;
  	
	  } 

	  
	  else {
          
              //hall_sensor = digital_read(0);         
              // DOOR OPEN
              // buzzer = digitalWrite(1)
              //printf("Buzzer is ON\n");

	buzzer = 1;
	led=1;	
	  }
    
	buzzer_reg = buzzer*4;
	led_reg = led*8;


	asm volatile(
	"or x30, x30, %0 \n\t"
        "or x30, x30, %1 \n\t"
	:
	:"r"(buzzer_reg), "r"(led_reg)
        :"x30"
        );

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

out:     file format elf32-littleriscv


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
   10080:	fe442783          	lw	a5,-28(s0)
   10084:	fe042703          	lw	a4,-32(s0)
   10088:	00ff6f33          	or	t5,t5,a5
   1008c:	00ef6f33          	or	t5,t5,a4
   10090:	001f7793          	andi	a5,t5,1
   10094:	fcf42e23          	sw	a5,-36(s0)
   10098:	fdc42783          	lw	a5,-36(s0)
   1009c:	fe078ae3          	beqz	a5,10090 <main+0x3c>
   100a0:	002f7793          	andi	a5,t5,2
   100a4:	fcf42c23          	sw	a5,-40(s0)
   100a8:	fd842783          	lw	a5,-40(s0)
   100ac:	00078863          	beqz	a5,100bc <main+0x68>
   100b0:	fe042623          	sw	zero,-20(s0)
   100b4:	fe042423          	sw	zero,-24(s0)
   100b8:	0140006f          	j	100cc <main+0x78>
   100bc:	00100793          	li	a5,1
   100c0:	fef42623          	sw	a5,-20(s0)
   100c4:	00100793          	li	a5,1
   100c8:	fef42423          	sw	a5,-24(s0)
   100cc:	fec42783          	lw	a5,-20(s0)
   100d0:	00279793          	slli	a5,a5,0x2
   100d4:	fef42223          	sw	a5,-28(s0)
   100d8:	fe842783          	lw	a5,-24(s0)
   100dc:	00379793          	slli	a5,a5,0x3
   100e0:	fef42023          	sw	a5,-32(s0)
   100e4:	fe442783          	lw	a5,-28(s0)
   100e8:	fe042703          	lw	a4,-32(s0)
   100ec:	00ff6f33          	or	t5,t5,a5
   100f0:	00ef6f33          	or	t5,t5,a4
   100f4:	f9dff06f          	j	10090 <main+0x3c>
```

## Number of Unique Instructions

```
Number of different instructions: 9
List of unique instructions:
or
andi
li
sw
j
lw
addi
slli
beqz


```
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/ccca128c-a8bd-4d2a-b4a0-74ced2411bd1)


## References

1. https://github.com/SakethGajawada/RISCV_GNU
2. https://github.com/bhargav-vlsi/RISCV-Display-controller
3. https://github.com/alwinshaju08/IIITB_Waterlevel_detector
4. https://circuitdigest.com/microcontroller-projects/interfacing-hall-effect-sensor-module-with-arduino
