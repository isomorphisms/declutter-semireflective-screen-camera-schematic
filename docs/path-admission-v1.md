# Collision repair: complete admission and fresh outputs

The previously failing companion-output collision regression is fixed on the
qualified Linux/Chez host. The optical/geometry algorithms are unchanged. The
independent 24V marking-preservation failure remains open.

## Decision

Treat a processing run's entire read set and write set together. Refuse every
existing output, and require exclusive creation at the actual write boundary.
This removes implicit replacement from these scientific-data commands. Reruns
must use a fresh output stem or output directory; previous outputs are retained.
No automatic deletion or force option was added.

Simple filename inequality missed companion files and aliases. Canonical-name
checks alone would also miss hard links, and a preflight-only check leaves a
check/use window. Making existing outputs ineligible is smaller and stronger
than preserving implicit replacement through an increasingly complex inode
allowlist. Hard links need no special identity exemption: they already exist
and therefore cannot be outputs. No inode comparison is claimed or required.

## Implementation

| Boundary | Change |
| --- | --- |
| `RunPaths.admit_sources` | Physically resolve and require regular input files before reading plans/images; metadata checks never open FIFOs for reading |
| `RunPaths.admit_run` | Admit complete read/write sets, reject existing entries including dangling links, require existing directory parents and pairwise-distinct resolved prospective output names |
| `FreshFiles.write_new_buffer` | Check buffer extent, exclusively create with libc `fopen("wbx")`, write bytes, close on all ordinary error paths and report close/flush failure |
| `FreshFiles.write_new_text` | Same exclusive creation and checked close for provenance |
| `SchematicRaster.write_ppm` | Preserve P6 construction; replace truncating buffer-to-file open with the fresh binary writer |
| `Cleanup` | Admit input plus output/provenance; recheck the complete pair at save; provenance uses fresh text writer |
| `Aperture` | Admit window/image plus output/source map before processing; rendering checks the complete output pair |
| `Registration` | Admit plan before parsing, then plan/two images/two maps against all three outputs; provenance uses fresh writer |
| `Assemble` | Admit layout, then layout plus every resolved section input against the destination before allocation/copying |

The shared `System.File.exists` is deliberately not used for admission. In the
pinned base library it tries `openFile Read`, which misses dangling links and can
block on a FIFO. `test -f/-e/-L/-d` inspect metadata. GNU `realpath -P` resolves
symlinks before subsequent `..` components; prospective names use `-m`, while
all source/parent dependencies must resolve with `-e`. Exactly one terminal
newline is removed from utility output; meaningful leading/trailing spaces are
preserved. Empty, NUL-containing, line-delimited and excessive names fail closed.
Escaped argument arrays are used, not concatenated shell programs.

`fopen`'s `x` modifier maps to exclusive creation in glibc. Thus a file, symlink
or hard link inserted after preflight cannot be truncated by the new writer.
The tiny explicit FFI fills a real gap: the pinned inherited `Mode` enumeration
has no exclusive-create mode and its ordinary close discards close status.
It uses the same libc6/FILE-pointer boundary already used in that base library;
there is no added C implementation, compiled shim, Python/Node fallback or new
image-processing backend.

References: GNU libc, [Opening Streams](https://www.sourceware.org/glibc/manual/2.38/html_node/Opening-Streams.html),
and GNU coreutils, [realpath](https://www.gnu.org/software/coreutils/manual/html_node/realpath-invocation.html).
The installed implementation was also inspected and executed; online docs alone
are not the acceptance evidence.

## Executed qualification

Starting source: `dd3224a044d163c2b0f41d2ed6c4ee5d7f3176a1`, existing draft
isomorphisms/declutter-semireflective-screen-camera-schematic PR #1,
“Implement inspectable Idriç cleanup and provisional HMI registration”:
https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic/pull/1

Compiler: isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58,
existing maintained edric bootstrap, explicit Chez, Chez 10.4.1 / Debian 13.6
Linux x86-64, glibc and GNU coreutils 9.7. No compiler/backend fallback.

- The original 13 collision cases now reject before output creation and preserve
  every protected input digest.
- Expanded black-box suite: 24 rejected cases, four successful command invocations
  and their byte/input-preservation comparison. It adds second image/map roles,
  map/provenance hard links, Assemble image/layout aliases, dangling links,
  directory companions and FIFOs. No crash, missing executable or timeout is
  counted as successful rejection. Presence checking in the test itself was
  changed to metadata, so it cannot block while inspecting its FIFO fixtures.
- Direct path/write suite: 21 PASS records, including summary. It checks future
  output/output aliases through a symlink parent, missing parents, spaces,
  NUL/newline names, source FIFO/directory rejection, binary bounds, refusal to
  replace existing files, and deterministic symlink/hard-link insertion after
  admission. The underlying exclusive writer is tested directly, bypassing
  preflight, so the second layer cannot pass just because admission rejected.
- The expanded suite rejects the old production binaries: exit1, with real
  fixture corruption/partial writes detected. A blocked FIFO times out and is
  explicitly a failing test rather than a false positive.
- Existing RasterTests 34 and RegistrationTests 46 PASS records remain green.
- New private real-photo runs exercise Cleanup enhancement, Aperture,
  Registration and Assemble. Six corresponding P6 images/maps compare byte for
  byte with the baseline, including the whole 2448×3903 control reference.
  Original JPEG and baseline input/output hash checks remain unchanged.

One initial comparison paired the new masked 1718 reference with the package's
unmasked original observation. That comparison correctly differed at byte 18.
The package observation was independently confirmed byte-identical to the
unmasked original; comparison against the matching old masked reference then
passes. The mismatched-frame command/exit is retained in the receipts, not
described as a processing regression or silently hidden.

Initial test-source errors (a list-cons precedence expression and the reserved
word `partial` as a variable) were corrected. Their diagnostics are retained.
The preliminary standalone FreshFiles compile had no `main`; qualification is
its actual use through compiled producers and RunPathsTests, not that probe's
misleading zero shell status.

## Guarantee and limits

On the qualified host with stable parent directories, all **tested static**
unsafe collisions are rejected before creating any output. Every production
P6/provenance write independently refuses existing names. Originals and prior
outputs cannot be truncated by these writers even when a final-name alias is
inserted after admission. No implicit replacement remains.

This is not an atomic multi-file transaction, an exclusive file lock, an fsync
durability guarantee, or a defence against an adversary replacing parent
directories. Disk/I/O failure or a new namespace conflict after an earlier
output was created can leave a new incomplete bundle and returns failure.
Sources remain protected by exclusive creation; no rollback deletes files owned
by another process. Atomic bundle visibility would need a new directory or
manifest publication boundary and is outside this narrow repair.

Only the actual Linux/Chez/glibc/coreutils environment is qualified. Other
backends, case-folding filesystems and hosts need their own execution evidence.
Private photographs/crops and generated photographic outputs remain outside
GitHub and public CI artifacts. No CI run is claimed from these host checks.

This completes the existing `EARTH-RETECH-OUTPUT-ADMISSION-01` production owner
assignment; there is no competing repair. Future optical outputs must enumerate
all dependencies/destinations through `admit_run` and use the fresh writers.
The optical cleanup, all-section fidelity, overlap and topology jobs remain
separate. Keep PR draft while the known photographic requirement is failing.
