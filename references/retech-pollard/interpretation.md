# Interpretation of the Retech / Pollard documents

Reviewed 2026-11-18. All source links refer to the unaltered uploaded photographs
in this folder. Statements about a circuit describe what is drawn, unless an
inference or uncertainty is explicitly identified.

## Document families and machine identity

The Vecoplan electrical sheets identify **Pollard Banknote #2**, job
**03-V2354**, and the date **2003-11-21**. Their visible sheet numbers are
E00102-1 (door layout), E00102-2 (power wiring), and E00102-3 (control schematic).
The interlock insert carries the same release date. The interior layout has
matching component tags but no visible title block, so its association with the
set is inferred. [Sources: 1997](originals/1000001997.jpg),
[1998](originals/1000001998.jpg), [1999](originals/1000001999.jpg),
[2000](originals/1000002000.jpg), [2002](originals/1000002002.jpg).

AES supplied a separate **UTILITY DRAWING**, **10430-K1**, revision C, dated
**2004-01-29**, and a **Low Elevation (Dust Sys. Install)** drawing dated
**2004-01-30**. The utility drawing identifies Pollard in Ypsilanti, MI; the
elevation says Pollard Banknote, Ypsilanti. The drawing-number suffix on the
elevation is not secure enough to transcribe. The program-description pages
show neither a machine serial number nor a document date. These distinctions
prevent treating the entire upload as a single dated manual.
[Sources: 1994](originals/1000001994.jpg), [2001](originals/1000002001.jpg),
[2003](originals/1000002003.jpg), [2004](originals/1000002004.jpg),
[2005](originals/1000002005.jpg).

**Unresolved:** these photographs do not establish that every sheet describes
the current installed configuration, or map this set onto a different
controller discussed elsewhere. No controller manufacturer's name or catalog
number is legible here. The earlier identification of a MicroLogix 1200
1762-L24BWA and the proposed 1762-IF4 module remain unsupported identifications.
The visible I/O count and common groups may be used for comparison, with the
result labelled as an inference.

## The handwritten terminal sketches

The clearer sketch explicitly labels INPUTS and OUTPUTS. Each bank has two
staggered rows. The following positions are simply left-to-right positions in
each drawn row, not numbered terminals from a manufacturer.
[Source: 1995](originals/1000001995.jpg).

| Bank and row | Literal marks, left to right |
| --- | --- |
| Input upper | X, 20, 22, 19, 25, 27, X, X, X |
| Input lower | X, 19, 21, 23, 24, 26, 42, X, X |
| Output upper | 3, white, X, 4, 5, 3, 10, 11, X |
| Output lower | green, 3, 3, 3, 9, 8, 3, X, X |

Both input positions marked 19 have a “2 wires” annotation. On the output bank,
that annotation appears at upper positions 1, 2 and 6, and lower positions 1,
2, 3, 4 and 7. Its absence at another position does not prove a one-conductor
termination. An unlabelled curved mark below the input 21/23 area is retained
in the image; it is not transcribed as a confirmed jumper.

**Inferred:** repeated numbers and explicit multiple-conductor annotations make
this a wire-placement record. The labels are not a sequence of unique PLC
channel addresses. The meaning of X is not defined. The color green does not by
itself establish a protective-earth connection, nor does white establish a
neutral connection.

The rough sketch has the same broad arrangement after a 180-degree reading
rotation. Its unused-looking marks resemble `n/a`; two output marks are unclear
and occupy the positions labelled white and green in the clearer sketch. Those
uncertain marks should not be silently rewritten as colors. Its transformer
note reads approximately **KVA .250**, **480 / 120**, **X Former**.
[Source: 1996](originals/1000001996.jpg).

### Correspondence with the control schematic

The control schematic defines wire **18** as the positive side of its **24 V DC**
supply and wire **19** as the negative side. COM0 and COM1 connect to wire 19.
Wire **3** is the **120 V AC** feed after the E-stop chain and supplies output
L1 and VAC0 through VAC4. These are observed drawing connections. Their agreement
with repeated 19 and 3 marks is a cross-document inference supporting the
sketch's relationship to this drawing. It does not establish each physical
terminal's assignment. [Source: E00102-3 / 1997](originals/1000001997.jpg).

The input wire set 20–27 and 42 also matches the populated input conductors in
the schematic. There is an unresolved output difference: the sketch has a clear
**9**, whereas the schematic's slow-speed controller output leaves on wire
**6**, passes through an M2F interlock, and continues as wire **7** to M2S. In
the fast-speed circuit, wire **8** passes through an M2S interlock and becomes
wire **9** before M2F. A proposed alternating terminal-order interpretation
would put the handwritten 9 near the expected wire-6 position. That proposed
ordering is not a verified pinout. Preserve both readings; no correction to
the image or actual wiring follows from this comparison.

## Electrical I/O and numbering

Three numbering systems coexist on E00102-3: numbered controller channels,
circled wire identifiers, and field-terminal numbers beside connection points.
For example, input channel **4** receives circled wire **24** from the torque
switch, whose field terminals are **28** and **29**. Separately, circled wires
**28** and **29** connect the CT to the analog input. Equal numerals in those
different systems do not establish an electrical connection.
[Source: 1997](originals/1000001997.jpg).

### Digital inputs shown

| Channel | Circled wire | Drawing function / connection |
| --- | --- | --- |
| 0 | 20 | SCREEN DOOR caption; path includes hopper-door and screen-door contacts in series |
| 1 | 21 | ROTOR MOTOR TEMP; TR1 contact |
| 2 | 22 | OIL TEMP / LEVEL |
| 3 | 23 | PRESSURE SWITCH |
| 4 | 24 | TORQUE SWITCH |
| 5 | 25 | ROTOR O.L. TRIP; M1 overload-relay contact |
| 6 | 26 | HYD. O.L. TRIP; CB4 contact |
| 7 | 27 | DISCHARGE CONV. RUNNING / SMOKE DETECTOR INTERLOCK |
| 8 | 42 | DISCHARGE / RAM PAUSE; CR5 contact; caption partly across fold |
| 9 | No input conductor shown | OPTIONAL FRONT L.S. |
| 10 | No input conductor shown | OPTIONAL REAR L.S. |
| 11 | No input conductor shown | OPTIONAL START SW. |
| 12 | No input conductor shown | OPTIONAL STOP SW. |
| 13 | No input conductor shown | SPARE |

The first interlock path can be traced as wire 18 → field terminal 18 → hopper
door contacts → field terminal 19 → wire 41 → field terminal 20 → screen door
contacts → field terminal 21 → wire 20 → input 0. The earlier screen-door-only
summary omitted the upstream hopper-door chain. This is the depicted series
path, not an assertion that the present machine is wired identically.

For input 8, INSERT #1 identifies the CR5 coil as **COMPACTOR FEED PAUSE**. This
explains the relationship between the compactor interlock and the control
schematic's **DISCHARGE / RAM PAUSE** input without replacing one caption with
the other. [Sources: 1997](originals/1000001997.jpg),
[1998](originals/1000001998.jpg).

Temperature, level, pressure and torque reach the pictured controller as
switching/contact inputs. The rotor thermistor has its own TR1 interface before
the digital temperature-status input. Calling the controller input digital
does not imply that the underlying temperature sensor is itself a switch.

### Outputs shown

| Channel | Circled outgoing wire | Function and drawn destination |
| --- | --- | --- |
| 0 | None shown | OPTIONAL ET1 |
| 1 | 4 | ROTOR FORWARD → CR1 |
| 2 | 5 | ROTOR REVERSE → CR2 |
| 3 | 6 | RAM SLOW → M2F interlock → wire 7 → M2S |
| 4 | 8 | RAM FAST → M2S interlock → wire 9 → M2F |
| 5 | 10 | RAM FORWARD → CR3 |
| 6 | 11 | RAM REVERSE → CR4 |
| 7 | None shown | ROTOR BLOCK |
| 8 | None shown | SPARE |
| 9 | None shown | SPARE |

CR1 and CR2 operate the M1F/M1R rotor contactor circuits. CR3 and CR4 operate
the Y1/Y2 ram-solenoid circuits in the separate DC section. Optional or
unconnected positions are observations of this drawing, not confirmations of
unused positions on the installed equipment.
[Source: 1997](originals/1000001997.jpg).

### Analog path and transformer

E00102-3 draws a device tagged **CT**, with **LINE** and **LOAD** orientation
markings. Circled wire **28** connects to **IN0+**, and circled wire **29** to
**IN0−**, at a destination labelled **ANALOG INPUT**. E00102-2 places CT on the
rotor-motor power branch. The tag and connections are established. The CT's
manufacturer, ratio, output range and conditioning electronics are not specified;
the drawings do not establish whether the analog-facing device is a passive
transformer or a conditioned current transducer.
[Sources: 1997](originals/1000001997.jpg), [2002](originals/1000002002.jpg).

The power sheet labels the control transformer **250 VA**, and the control
sheet labels its secondary **120 V AC, 60 Hz**. The handwritten **0.250 kVA**
is arithmetically **250 VA**, so those two ratings agree. The handwritten 480/120
notation remains a transcription; it does not verify the installed primary tap.
The power sheet lists 230, 460 and 575 V supply options. The AES installation
plan specifies 460 V services. Preserve these literal specifications without
converting them into a measured supply voltage.
[Sources: 1996](originals/1000001996.jpg), [1997](originals/1000001997.jpg),
[2002](originals/1000002002.jpg), [2005](originals/1000002005.jpg).

## Motors and the wider installation

The power sheet identifies M1 as the rotor motor with M1F/M1R reversing
contactors, M2 as the hydraulic pump motor with six motor leads and M2S/M2F
switching, M3 as the **3/4 HP** discharge conveyor, and M4 as the **3 HP**
customer-supplied box dumper. The control sheet names the M2 commands slow and
fast. This pair of documents supports a slow/fast hydraulic-pump arrangement;
the six-lead count alone would not identify its winding or starting scheme.
[Sources: 1997](originals/1000001997.jpg), [2002](originals/1000002002.jpg).

The AES utility plan supplies the following installation specifications. The
table uses the clearer callouts in the second photograph, 2005; the first view
is preserved separately. These are documented requirements, not a new wiring
procedure or measured ratings.

| Equipment / connection | Specification on AES 10430-K1 |
| --- | --- |
| Rotor motor to control panel | 75 HP; 460 V, 3 phase, 60 Hz; 1/0 AWG; 3 current-carrying conductors plus 1 ground |
| Shredder hydraulic power unit to panel | 5 HP; 460 V, 3 phase, 60 Hz; #12 AWG; 6 current-carrying conductors plus 1 ground |
| Control wiring | 24 V; #18 AWG; **17** current-carrying conductors plus 1 ground |
| Conveyor to panel | 3/4 HP; 460 V, 3 phase, 60 Hz |
| Tipper controls to hydraulic power unit | 3 HP; 460 V, 3 phase, 60 Hz; #12 AWG; 3 current-carrying conductors plus 1 ground |
| Dust collector to start/stop station | 7.5 HP; 460 V, 3 phase, 60 Hz |
| Compactor service | 10 HP; 460 V, 3 phase, 60 Hz; existing-service compatibility to be checked |
| Hopper access-door interlock | 24 V; #18 AWG; 2 current-carrying conductors plus 1 ground |
| Conveyor E-stop to shredder panel | #18 AWG; 2 current-carrying conductors plus 1 ground |

The **17** conductor count is distinguishable in 2005; it must not be reduced
to 7. The drawing number is **10430-K1**, not the initially ambiguous 10430-X1.
The 5 HP hydraulic reading above is taken from 2005; faint text and markings in
the corresponding area of 1994 are not silently substituted for that reading.
Voltage **24 V**, wire identifier **24**, and size **#18 AWG** belong to different
fields. The rotor's **75 HP** installation specification should remain attached
to this source rather than being assigned to another machine by association.
[Sources: 1994](originals/1000001994.jpg), [2005](originals/1000002005.jpg).

The plan states that the dumper, shredder and conveyor are the only items
powered by the Vecoplan shredder control station. It gives the dust collector a
separate dedicated service/start-stop provision. Nevertheless, the conveyor
E-stop is specified to stop both conveyor and shredder, and the compactor hopper
door interlock is specified to stop shredder, conveyor, compactor, Kongskilde fan
and separator. Dry-contact links from the compactor cabinet coordinate these
controls. **Inference:** equipment with separate power services still
participates in shared interlocks. Power-source grouping and interlock grouping
must therefore remain separate in a reconstructed system diagram.
[Source: 2005](originals/1000002005.jpg).

The interior layout is a placement reference: it locates the PLC, DC supply,
TR1, transformer, CT, relays, breakers and starters. The door layout locates the
HMI, switches and disconnect handle. The AES elevation supplies a different
kind of evidence: equipment/ductwork geometry. Layout proximity does not create
electrical continuity. [Sources: 1999](originals/1000001999.jpg),
[2000](originals/1000002000.jpg), [2001](originals/1000002001.jpg).

## What the program pages establish

The main page presents machine identity and menu functions. Entering machine
operation first shows a daily-maintenance acknowledgement page. The operation
page is described as having eight buttons, a machine cutaway, digital and analog
amp-meter displays, and three status-text lines.
[Source: 2003](originals/1000002003.jpg).

| Function | Behavior described on the pages |
| --- | --- |
| Start / Stop | Start or stop the machine/system |
| Short stroke | Selectable partial ram retractions based on amp loading; one to five retractions, with determining factors unspecified |
| Auto stop | When enabled, shut down after 3 minutes running empty |
| Reset | Required following an alarm, according to the page |
| Ram reverse | Available with the machine running or stopped |
| Rotor reverse | Available when the machine is not running; 40-second delay after panel power is applied; hold to reverse; release to stop; another unspecified delay before Start becomes available |
| Programs | Three programs; A is described as most aggressive and C as most passive |

The continuation describes starting the rotor forward while retracting the ram
at fast speed. Once fully retracted, the ram advances. Programmed amp settings
can change its speed, stop it or reverse it, and the cycle continues until Stop
or the enabled auto-stop function shuts down the machine.
[Source: 2004](originals/1000002004.jpg).

**Corrections to earlier interpretation:** no numerical amp thresholds, settings
screen procedure or calibration method appear on these pages. Program B's
specific parameter differences are not given. A fixed progression of
normal-feed, slow-feed, stop and reverse at increasing thresholds is not
enumerated. “Digital and analog” describes displayed amp meters; it does not
prove two sensors or two analog input channels. The pages do not supply an
Alarm 10 trigger condition or establish its cause.

## Limits retained for later work

The archive supplies image evidence, cross-references and transcriptions. It
does not supply an installed-controller label, a machine serial-number match,
current-transducer specifications, editable PLC program, numerical amp settings
or physical continuity measurements. Missing labels and connections remain
unresolved. These limits should accompany any later reconstruction instead of
being filled from a generic controller or a different grinder's documentation.
