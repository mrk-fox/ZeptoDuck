# Day 1 - Planning the project, finding components and completing the first schematic. Spent hours: 6

First of all: What is this project? This project aims to create the smallest "Rubber Ducky" in the world. The current record consists of a small PCB which is insertable into a "normal" USB port.

We define a "Rubber Ducky" as a programmable HID being able to fire a sequence of keystrokes to controll the PCB the Rubber Ducky is connected to.

So, as seen in the currently smallest Rubber Ducky given, the constraint comes actually not from the electronics components size but rather from the ports size. Therefore, going down the line we may look at an even smaller and newer port - The USB-C standart. The main
problem with the USB-C port is, that it is very small when it comes to the plugs dimension. While the female sockets are rather easy to work around, the male ones do only have 2 diffrent geometrical mounting options when described relative to the PCB: Horizontal and vertical.
While the horizontal mount is easier on the PCB's size, it compomises with the length, as the part of the USB-C plug being actually inserted into the port needs to be freed of any PCB below or beside it. The vertical mounting on the other hand is handier when it comes to the 
USB-C sizes, but rather complicted when you want to keep the PCB small. 

After some long concidertations I came to the conclusion that a vertically mounted PCB is more beneficial aiming at the "worlds smallest" element of the project, and the PCB's size constraint should rather be a challenge for me. 

So, the male PCB plug measures around 8x2mm width and height, and this should be concidered our PCB size goal when it comes to the component selection. 

### What to look for
We will probably need the following components:
1. An MCU with integrated USB pinout to avoid any additional parts
2. An voltage regulator to translate from the VBUS to the VCC of the chip
3. All the other 0201 components like decoupling caps
4. 5.1kOhm resistors for the CC1 and CC2 pins of the USB port.

And looking for the components I remembred a whole amazing class of chips made for such small projects: WLCSP. These are raw silicon dices with chips inside. And after some time on the Microchip website... I found what i needed. An ATSAMD11D14A-UUT resembling a wonderfu Cortex-0 MCU with
the very needed USB D+ and D- pins. The MCU works on 3.3V, as expected, so a drop down converter was needed. TI had a wonderful line of capacitatorless buck downs, the TLV733. And my hit was the TLV73333PDQNR in the proprietary TI 1x1mm package. A delicatess of a buck down.

Oh, and I nearly forgor the USBC port itself. The GCT Company (Global Connector Technology) has wonderful connectors worldwide! Amazing for my case. The one I need is the USB4151-GF-C. I will probably cut off the side-holders as they are tooo big for this project. 

### Schematics time

I love datasheets. The more I see them, the more I start understanding why compactification matters... BUT NOT TO THAT EXTENT. The SAMD11 Microchip WLCSP package I need had its USB pinout buried in the depths of its datasheet and until i fially understood the table, a lot of time
has passed. But I studied all datasheets and assembled by heart the follwing schematic:

![ZeptoDuck Schematics](https://github.com/mrk-fox/ZeptoDuck/blob/main/img/Schematics%20v1.png)

Puhhh... Long day. I think tomorrow is fially PCB time! Yay! 

# Day 2 - Creating the PCB and breaking and arm trying to fit everything in. 10 hours.

So, not much to tell today actually. After getting the necessary footprints, the fiddeling around the assembly began and I really struggled to fit everything in, comply with the JLCPCB manufacturing guidelines and the aquisition possibilities I have. The biggest problem was... When I suddenly notices THAT NEARLY NO ONE HAD THE MICROCHIPS I NEEDED IN STOCK. Aside from one company - Worldway electronics... With a goddamn MOQ (Minimum Order Quantity) of 500 pcs... I wrote them an E-Mail asking for a MOQ relaxation for a poor student trying to break some world record. Lets see what they answer. The second problem is, that nearly no 0201 5.1kOhm resistors are anywhere in stock at an acceptable price-to-MOQ ratio. Well, i switches to 0402... and fitting them was.. phuh. The main problem was also in my head. I really didnt want to switch to a 4-Layer-PCB as this would just increase the VIA amount and placing a VIA anywhere is a huge compomise. I did it only when needed. I also sadly couldnt place any vias in between the MCU's pins due to the spacing colliding with JLCPCB's manufacturing constraints. BUT! Throgh herous effort I managed to route all that and pass ERC and DRC with flying colors... In nothing but 10 hours of pure swearing. One thing I learned today was, that JLCPCB is really lame. Their constraints are really constraint constrainting me in my concentration on size constraint compromized placement. Here, the finished PCB:
![ZeptoDuck PCB](https://github.com/mrk-fox/ZeptoDuck/blob/main/img/PCB%20v2.png)

# Day 3 - Finishing Panelization, Fimrware and moving files around for the ship. 5 hours.

Okay, as JLCPCB would struggle a lot manufacturing my 8x2mm PCB's, I'll help them a bit by creating a panel with 5 of them. This was very interesting as KiKit, the paneöization automator refused to ooperate on the behalf of such a small chip. I also wrote a lot of code. SAMD11 is a chip I know so it was faster than the first time, however, i needed a lot of time to even figure out HOW to make a HID device ot of a small and cute chip. I also learned a lot new about USB protocolls. Currently the firmware just configures itself as a keyboard on fireup and types Win+R and then notpad and stays idle until rebootet. Thats all currently. Here a pic of the finished panelization and the rendered ZeptoDuck.

![ZeptoDuck Panelized PCB](https://github.com/mrk-fox/ZeptoDuck/blob/main/img/Zeptoduck_panelized.png)

And also... WORLDWAY ELECTRONICS ANSWERED! They agreed to support me and agreed to give me all the things necessary for 65 incl. shipping! 
All this took 5 hours
