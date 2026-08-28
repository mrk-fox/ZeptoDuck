

<div align="center">
<h1>ZeptoDuck</h1><br>
The smallest "Rubber Ducky" in the world.
<br>

![KiCad](https://img.shields.io/badge/kicad-%2300578F.svg?style=for-the-badge&logo=kicad&logoColor=white) 
[![License: CERN-OHL-S](https://img.shields.io/badge/License-CERN--OHL--S%20v2-red)](https://ohwr.org/cern_ohl_s_v2)
<br>

<img src="https://github.com/mrk-fox/ZeptoDuck/blob/main/img/Zeptoduck_v0.2_bg_rem.png" alt="Flowers" style="width:auto;">
</div>

# What is ZeptoDuck about?
In the world of rising digital vurneablility due to the effects of digitalization we are forced to develop tools to pentest the security structures we have developed and established over the years. One poular tool attackers use is the "Rubber Ducky". It is a broad term for a programmable HID execution device. The ZeptoDuck project, with the term "Zepto" coming from the greek word ζεπτο meaning one sextilionth. This, literally, small term was used to display the size of the ZeptoDuck only about 10x3x15mm. This is the world record for the smallest rubber ducky ever produced. 

# Features
ZeptoDuck covers a narrow spectre of features dur to its very specific usecase.

- ATSAMD11D14A-UUT as the main MCU
- Programmable via the SWD pads and the USB-C port with correct software.
- HID Input device capabilities.

# PCB and Schematics

The PCB itself is a minatuarized 2-Layer FR4 PCB with only a few components, most of them in very small formats.

<img src="https://github.com/mrk-fox/ZeptoDuck/blob/main/img/Schematics%20v1.png" alt="ZeptoDuck Schematics" style="width:auto;">
<img src="https://github.com/mrk-fox/ZeptoDuck/blob/main/img/PCB%20v2.png" alt="ZeptoDuck PCB" style="width:auto;">

<img src="https://github.com/mrk-fox/ZeptoDuck/blob/main/img/Zeptoduck_v0.2.png" alt="Zeptoduck Rendered" style="width:auto;">
<img src="https://github.com/mrk-fox/ZeptoDuck/blob/main/img/Zeptoduck_panelized.png" alt="Panelized ZeptoDuck Rendered" style="width:auto;">

# Assembly and Flashing

1. Apply solder paste through the soldermask on all necessary components footprints
2. Place the components on the PCB
3. Use a hotplate to solder the components to the PCB
4. Cut off the additional holders for the USB-C port
5. Flip the PCB and hand-solder the USB-C port (The hard part)
6. Flash the PCB using any pogo pin assembly while applying 5V voltage through the USB-C port
7. Youre ready to hack!

# BOM

| id | Name                          | Qty | Price |   |
|----|-------------------------------|-----|-------|---|
| 1  | PCB                           | 1   | 11.5$ |   |
| 2  | ATSAMD11D14A-UUT              | 10  | 16$   |   |
| 3  | TLV73333PDQNR                 | 10  | 5$    |   |
| 4  | WWE Shipping and Handling     | 4   | 39$   |   |
| x  | All other parts are in stock. | x   | x     |   |
| x  | TOTAL                         |     | 71.5$ |   |

# Information for reviewers
28.08.2026: The parts are avalible via a custom agreement between me and Worldway electronics. This project required 22 hours in total to finish. Thanks for reviewing.

# Thanks
I generously thank Worldway Electronics for kindy agreeing on an MOQ relaxation. <br>
<img src="https://s.worldwayelec.com/template/ic/images/logo.png" alt="WWE Logo" style="width:auto;">

Make sure to check out their website! 
worldwayelec.com
