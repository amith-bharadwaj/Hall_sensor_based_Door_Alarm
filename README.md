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
riscv32-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o ./amith_door_alarm.o amith_door_alarm.c
riscv32-unknown-elf-objdump -d -r amith_door_alarm.o > door_alarm_assembly.txt
```
## Assembly Code

```

amith_c.o:     file format elf32-littleriscv


Disassembly of section .text:

00010094 <alarm>:
   10094:	fe010113          	add	sp,sp,-32
   10098:	00812e23          	sw	s0,28(sp)
   1009c:	02010413          	add	s0,sp,32
   100a0:	000117b7          	lui	a5,0x11
   100a4:	00100713          	li	a4,1
   100a8:	18e7a423          	sw	a4,392(a5) # 11188 <__DATA_BEGIN__>
   100ac:	000117b7          	lui	a5,0x11
   100b0:	00100713          	li	a4,1
   100b4:	18e7a623          	sw	a4,396(a5) # 1118c <LED>
   100b8:	000117b7          	lui	a5,0x11
   100bc:	1887a783          	lw	a5,392(a5) # 11188 <__DATA_BEGIN__>
   100c0:	00179793          	sll	a5,a5,0x1
   100c4:	fef42623          	sw	a5,-20(s0)
   100c8:	fec42783          	lw	a5,-20(s0)
   100cc:	00ff6f33          	or	t5,t5,a5
   100d0:	000117b7          	lui	a5,0x11
   100d4:	18c7a783          	lw	a5,396(a5) # 1118c <LED>
   100d8:	00179793          	sll	a5,a5,0x1
   100dc:	fef42423          	sw	a5,-24(s0)
   100e0:	fe842783          	lw	a5,-24(s0)
   100e4:	00ff6f33          	or	t5,t5,a5
   100e8:	00000013          	nop
   100ec:	01c12403          	lw	s0,28(sp)
   100f0:	02010113          	add	sp,sp,32
   100f4:	00008067          	ret

000100f8 <turnOffAlarm>:
   100f8:	fe010113          	add	sp,sp,-32
   100fc:	00812e23          	sw	s0,28(sp)
   10100:	02010413          	add	s0,sp,32
   10104:	000117b7          	lui	a5,0x11
   10108:	1807a423          	sw	zero,392(a5) # 11188 <__DATA_BEGIN__>
   1010c:	000117b7          	lui	a5,0x11
   10110:	1807a623          	sw	zero,396(a5) # 1118c <LED>
   10114:	000117b7          	lui	a5,0x11
   10118:	1887a783          	lw	a5,392(a5) # 11188 <__DATA_BEGIN__>
   1011c:	00179793          	sll	a5,a5,0x1
   10120:	fef42623          	sw	a5,-20(s0)
   10124:	fec42783          	lw	a5,-20(s0)
   10128:	00ff6f33          	or	t5,t5,a5
   1012c:	000117b7          	lui	a5,0x11
   10130:	18c7a783          	lw	a5,396(a5) # 1118c <LED>
   10134:	00179793          	sll	a5,a5,0x1
   10138:	fef42423          	sw	a5,-24(s0)
   1013c:	fe842783          	lw	a5,-24(s0)
   10140:	00ff6f33          	or	t5,t5,a5
   10144:	00000013          	nop
   10148:	01c12403          	lw	s0,28(sp)
   1014c:	02010113          	add	sp,sp,32
   10150:	00008067          	ret

00010154 <main>:
   10154:	fe010113          	add	sp,sp,-32
   10158:	00112e23          	sw	ra,28(sp)
   1015c:	00812c23          	sw	s0,24(sp)
   10160:	02010413          	add	s0,sp,32
   10164:	fe042623          	sw	zero,-20(s0)
   10168:	001f7793          	and	a5,t5,1
   1016c:	fef42623          	sw	a5,-20(s0)
   10170:	fec42783          	lw	a5,-20(s0)
   10174:	00079663          	bnez	a5,10180 <main+0x2c>
   10178:	f1dff0ef          	jal	10094 <alarm>
   1017c:	fedff06f          	j	10168 <main+0x14>
   10180:	f79ff0ef          	jal	100f8 <turnOffAlarm>
   10184:	fe5ff06f          	j	10168 <main+0x14>

```

## Number of Unique Instructions

```
Number of different instructions: 12
List of unique instructions:
ret
lw
and
nop
jal
add
j
or
bne
li
sw
sll

```
![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/afa7b9a7-b7b0-4b5c-801d-e1a613337ef8)


## References

1. https://github.com/SakethGajawada/RISCV_GNU
2. https://github.com/bhargav-vlsi/RISCV-Display-controller
3. https://github.com/alwinshaju08/IIITB_Waterlevel_detector
4. https://circuitdigest.com/microcontroller-projects/interfacing-hall-effect-sensor-module-with-arduino
