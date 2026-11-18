# Retech / Pollard document archive

This folder preserves twelve distinct uploaded JPEGs supplied for reference on
2026-11-18. The user explicitly requested saving these documents in this
schematic-cleanup repository and recording supported inferences. The photographs
are unchanged: no crop, rotation, contrast adjustment, stitching or redraw is
part of the committed image set.

The records describe the photographed documents. They do not certify the
present machine's wiring or identify a fault. Earlier HMI photographs and other
private source collections are outside this upload.

## Find a document

| Original photograph | Document | Identity visible in the source |
| --- | --- | --- |
| [1000001994.jpg](originals/1000001994.jpg) | AES utility plan, first photograph | Same drawing as 2005; use both observations |
| [1000001995.jpg](originals/1000001995.jpg) | Labelled handwritten input/output sketch | Wire positions, colors and several “2 wires” annotations |
| [1000001996.jpg](originals/1000001996.jpg) | Rough handwritten sketch and transformer note | Approximately 0.250 kVA, 480/120; upside down as uploaded |
| [1000001997.jpg](originals/1000001997.jpg) | Vecoplan control panel schematic | E00102-3, rev A; job 03-V2354; Pollard Banknote #2; 2003-11-21 |
| [1000001998.jpg](originals/1000001998.jpg) | Compactor/discharge interlock detail | INSERT #1; rev A entry dated 2003-11-21; independent sheet number not visible |
| [1000001999.jpg](originals/1000001999.jpg) | Vecoplan control panel door layout | E00102-1, rev A; job 03-V2354; Pollard Banknote #2; 2003-11-21 |
| [1000002000.jpg](originals/1000002000.jpg) | Interior layout | Matching component tags support association with the Vecoplan set; title block not visible |
| [1000002001.jpg](originals/1000002001.jpg) | AES Low Elevation (Dust Sys. Install) | Pollard Banknote, Ypsilanti; 2004-01-30; drawing prefix 10430-, suffix unresolved |
| [1000002002.jpg](originals/1000002002.jpg) | Vecoplan control panel power wiring | E00102-2, rev A; job 03-V2354; Pollard Banknote #2; 2003-11-21 |
| [1000002003.jpg](originals/1000002003.jpg) | Retech Rotary Grinder Program Description | First photographed page; no page number or revision visible |
| [1000002004.jpg](originals/1000002004.jpg) | Program-description continuation | Completes the program-selection paragraph and explains the feed cycle |
| [1000002005.jpg](originals/1000002005.jpg) | AES utility plan, second photograph | 10430-K1, rev C; Pollard, Ypsilanti MI; 2004-01-29 |

The two AES utility photographs show the same identified drawing from different
views and remain separate sources. The clearer title in 2005 resolves the letter
in **10430-K1**. Photo 2005 is not a third program-description page.

The differently named uploads `image-1795013072185.jpg` and
`image-1795013078305.jpg` are byte-identical to 2003 and 2004 respectively. Repeated
uploads of 1997 through 2002 also compare equal. Each identical image is stored
once; [duplicate-aliases.tsv](duplicate-aliases.tsv) preserves these mappings.

## Reference notes

- [Document interpretation and corrections](interpretation.md) connects the
  sketches, electrical sheets, installation plan and program description.
- [Handwritten terminal positions](terminal-positions.tsv) preserves the clear
  sketch's literal labels and conductor-count annotations.
- [Electrical I/O](electrical-io.tsv) separates controller channels from circled
  wire numbers and drawing functions.
- [Source manifest](source-manifest.tsv) records each image's SHA-256, byte size,
  dimensions and document identity. Unknown fields remain explicit.
- [SHA256SUMS](SHA256SUMS) can be checked with `sha256sum -c SHA256SUMS` from this
  directory. The manifest describes the uploaded bytes, not an assumed
  higher-resolution camera original.

The most useful connections established during this review are the shared
wire-19 input commons, shared wire-3 output feeds, the hopper/screen-door series
path, the CR5 feed-pause cross-reference, and the agreement between the
handwritten 0.250 kVA note and the printed 250 VA transformer rating. The
handwritten output mark **9** and printed slow-output wire **6** remain distinct.

## Reading rules for subsequent work

Follow the original image links when a label matters. In the notes, **observed**
means visible on a supplied document; **inferred** means a stated comparison or
deduction; **unresolved** means the available pages do not establish the fact.
An observed design requirement is not an observation of the installed machine.

Keep wire identifiers, controller channels, field terminals, voltage ratings and
conductor sizes separate. Preserve uncertain handwriting and differences between
photographs. Do not turn the terminal sketches into a manufacturer pinout or
silently carry over the earlier proposed PLC identification.

This addition is an archive and document review. It does not claim execution of
the image-cleanup implementation, geometric reconstruction, electrical
continuity testing or physical-machine acceptance.
