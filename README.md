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
void Read_Hall_Sensor();
void Alarm_control();

int main() {
    while (1) {
        Read_Hall_Sensor();
    }
    return 0;
}

// Fuction for controlling Alarm
void Alarm_control() {

    int HallSensorState; 
    int buzzer=0; 
    int buzzer_reg;
    int led=0;
    int led_reg;
    
    buzzer_reg = buzzer*2;
     asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(buzzer_reg)
	:"x30"
	);
    
    led_reg = led*2;
     asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(led_reg)
	:"x30"
	);

    
    asm volatile(
	"andi %0, x30, 1\n\t"
	:"=r"(HallSensorState)
	:
	:
	);

        if (HallSensorState==1) {
            // magnetic field detected means door locked no alarm
            //printf("Door Locked No buzzer,No led");
            buzzer=0;
            led=0;
            
            buzzer_reg = buzzer*2;
            
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(buzzer_reg)
		:"x30"
		);
		
	    led_reg = led*2;
	    
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(led_reg)
		:"x30"
		);	
        } 
        
        
        else {
                    // magnetic field not detected means door unlocked switch on alarm
            //printf("Door unlocked ON buzzer,ON led");
            buzzer=1;
            led=1;
            
            buzzer_reg = buzzer*2;
            
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(buzzer_reg)
		:"x30"
		);
		
	    led_reg = led*2;
	    
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(led_reg)
		:"x30"
		);	
        }
    }


void Read_Hall_Sensor() {
    Alarm_control();
    }

```
## Commands to Convert C program to Assembly Code

Follow the below commands for code conversion.

```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o hall_sensor.out hall_sensor.c 
riscv64-unknown-elf-objdump -d -r hall_sensor.out > asm.txt

10:44

```
## Assembly Code
```

hall_sensor.out:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	ff010113          	add	sp,sp,-16
   10078:	00112623          	sw	ra,12(sp)
   1007c:	00812423          	sw	s0,8(sp)
   10080:	01010413          	add	s0,sp,16
   10084:	0d4000ef          	jal	10158 <Read_Hall_Sensor>
   10088:	ffdff06f          	j	10084 <main+0x10>

0001008c <Alarm_control>:
   1008c:	fd010113          	add	sp,sp,-48
   10090:	02812623          	sw	s0,44(sp)
   10094:	03010413          	add	s0,sp,48
   10098:	fe042623          	sw	zero,-20(s0)
   1009c:	fe042423          	sw	zero,-24(s0)
   100a0:	fec42783          	lw	a5,-20(s0)
   100a4:	00179793          	sll	a5,a5,0x1
   100a8:	fef42223          	sw	a5,-28(s0)
   100ac:	fe442783          	lw	a5,-28(s0)
   100b0:	00ff6f33          	or	t5,t5,a5
   100b4:	fe842783          	lw	a5,-24(s0)
   100b8:	00179793          	sll	a5,a5,0x1
   100bc:	fef42023          	sw	a5,-32(s0)
   100c0:	fe042783          	lw	a5,-32(s0)
   100c4:	00ff6f33          	or	t5,t5,a5
   100c8:	001f7793          	and	a5,t5,1
   100cc:	fcf42e23          	sw	a5,-36(s0)
   100d0:	fdc42703          	lw	a4,-36(s0)
   100d4:	00100793          	li	a5,1
   100d8:	02f71c63          	bne	a4,a5,10110 <Alarm_control+0x84>
   100dc:	fe042623          	sw	zero,-20(s0)
   100e0:	fe042423          	sw	zero,-24(s0)
   100e4:	fec42783          	lw	a5,-20(s0)
   100e8:	00179793          	sll	a5,a5,0x1
   100ec:	fef42223          	sw	a5,-28(s0)
   100f0:	fe442783          	lw	a5,-28(s0)
   100f4:	00ff6f33          	or	t5,t5,a5
   100f8:	fe842783          	lw	a5,-24(s0)
   100fc:	00179793          	sll	a5,a5,0x1
   10100:	fef42023          	sw	a5,-32(s0)
   10104:	fe042783          	lw	a5,-32(s0)
   10108:	00ff6f33          	or	t5,t5,a5
   1010c:	03c0006f          	j	10148 <Alarm_control+0xbc>
   10110:	00100793          	li	a5,1
   10114:	fef42623          	sw	a5,-20(s0)
   10118:	00100793          	li	a5,1
   1011c:	fef42423          	sw	a5,-24(s0)
   10120:	fec42783          	lw	a5,-20(s0)
   10124:	00179793          	sll	a5,a5,0x1
   10128:	fef42223          	sw	a5,-28(s0)
   1012c:	fe442783          	lw	a5,-28(s0)
   10130:	00ff6f33          	or	t5,t5,a5
   10134:	fe842783          	lw	a5,-24(s0)
   10138:	00179793          	sll	a5,a5,0x1
   1013c:	fef42023          	sw	a5,-32(s0)
   10140:	fe042783          	lw	a5,-32(s0)
   10144:	00ff6f33          	or	t5,t5,a5
   10148:	00000013          	nop
   1014c:	02c12403          	lw	s0,44(sp)
   10150:	03010113          	add	sp,sp,48
   10154:	00008067          	ret

00010158 <Read_Hall_Sensor>:
   10158:	ff010113          	add	sp,sp,-16
   1015c:	00112623          	sw	ra,12(sp)
   10160:	00812423          	sw	s0,8(sp)
   10164:	01010413          	add	s0,sp,16
   10168:	f25ff0ef          	jal	1008c <Alarm_control>
   1016c:	00000013          	nop
   10170:	00c12083          	lw	ra,12(sp)
   10174:	00812403          	lw	s0,8(sp)
   10178:	01010113          	add	sp,sp,16
   1017c:	00008067          	ret
```

## Number of Unique Instructions

```
Number of different instructions: 12
List of unique instructions:
add
nop
sw
and
jal
sll
bne
or
li
ret
j
lw

```
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/f0029fa4-0457-409a-b3c9-fcb5bcba82a0)



## References

1. https://github.com/SakethGajawada/RISCV_GNU
2. https://github.com/bhargav-vlsi/RISCV-Display-controller
3. https://github.com/alwinshaju08/IIITB_Waterlevel_detector
4. https://circuitdigest.com/microcontroller-projects/interfacing-hall-effect-sensor-module-with-arduino
