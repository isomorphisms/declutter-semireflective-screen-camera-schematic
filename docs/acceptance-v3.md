# ReTech reconstruction acceptance — 11 November 2026

## Result

All twelve original photographs were decoded at 1152 × 1536, enhanced and masked
by the compiled Idriç programs. Two corroborated geometric pairs were executed
by Registration, then placed in control and power sheets. No original or
derivative photograph is included in this public repository.

| Acceptance | Result | Evidence |
| --- | --- | --- |
| Source | PASS on Linux x86-64, Chez | Pinned compiler, focused executed fixtures, source/executable digests |
| Registration | PARTIAL | 1716→1717 and 1720→1723 used; other joins remain separated |
| Photographic | PARTIAL | Reflection edges, dust, faint/clipped text and mask-boundary uncertainty remain |
| Output | PASS for delivered arrays | Six PNG/P6 pairs decode identically; every reference-sheet pixel independently replays |

The overall task remains **partial photographic reconstruction**, and the PR
remains draft. The inputs and required runtime were accessible. The remaining
blocker is photographic information and geometric evidence, not compiler access.

## Exact execution

Starting source: `28c8b7bc1b491be78962702dd9ddc15ec7af89bf`, on the existing
`work/inspectable-cleanup` branch.

Compiler: `isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58`;
version `0.8.0-2bce7677f`. The maintained `edric bootstrap` production route
completed, followed by explicit `--cg chez` compilation. Chez is 10.4.1.
Execution host: Debian 13 Linux x86-64. Bootstrap C support is the compiler's
foreign dependency boundary; no first-party C image processor was added.
No RefC execution, Java, Kotlin, Gradle, Python image pipeline or generative
redrawing was used.

[Exact commands and exit statuses](../evidence/host-v3/commands.tsv) are historical
absolute-path receipts from this run, rather than portable installation scripts.
[Source and executable hashes](../evidence/host-v3/source-and-executables.sha256)
bind the acceptance to the actual code and binaries.
[Compiler hashes](../evidence/host-v3/compiler.sha256) bind the production runtime.

Executed acceptance includes:

- RasterTests: 34 PASS records, including its summary.
- RegistrationTests: 46 PASS records, including its summary.
- CLI positive/negative registration plans: valid exit 0; impossible overlap and
  singular transformation exit 1 for their intended diagnostics.
- Aperture: exact known RGB/identity retained; transposed photo shape, crossed
  glass polygon and out-of-image control polygon exit 1.
- LandmarkAudit: independent exact quarter-turn fit; coincident landmark rejection;
  fixed-plan withheld terminals; deliberately incorrect terminal exits 1.
- VerifySource: every one of the 9,554,544 control and 5,522,304 power reference
  pixels equals its selected original RGB sample or explicit grey. A single
  mutated reference pixel is rejected at output coordinate 200,200.
- Six PNG/P6 decoded RGB arrays compare byte-for-byte equal.

The four additional native-atlas PNG/P6 pairs were also decoded and compared
byte-for-byte. Their hashes are in the native output receipt.

## Separation of responsibilities

| Boundary | Implementation |
| --- | --- |
| JPEG acquisition and decoding | External ImageMagick codec only; original JPEG hashes checked against source-manifest |
| Strict P6 byte and shape admission | SchematicRaster; header/payload errors remain distinct from geometric errors |
| Dimension-indexed raster operations | Raster/Position, checked row-major RGB and bounded copies |
| Geometry | Registration: admitted fixed-point similarities, inverse nearest-neighbour selection |
| Readability and glass occlusion | Cleanup: local contrast; Aperture: explicit convex glass/control polygons |
| Source composition | Assemble and explicit layout files; source-selection maps travel through the same geometry |
| Output and provenance | P6 writer, external PNG codec, byte-array comparison, independent VerifySource replay |

The requested PNM separation is implemented by composing these boundaries.
Parser acceptance is supporting evidence. It does not grant photographic acceptance.

## Registration evidence

[Integer audit](../evidence/host-v3/LandmarkAudit-run.tsv) independently recomputes
least-squares similarities and leave-one-out errors from the original landmark
table. It uses arbitrary-precision Integer arithmetic. Residuals in this audit
are squared pixel distances after rounding the predicted point to its nearest
integer pixel; they need not equal the older continuous residuals exactly.

| Pair | New maximum rounded held-out squared error | Decision |
| --- | ---: | --- |
| 1712→1713 | insufficient points | Reject |
| 1713→1718 | 340 | Reject |
| 1715→1716 | 337 | Reject |
| 1716→1717 | 34 | Use geometric fit with a visible 24-pixel seam gap |
| 1720→1723 | 58 | Use geometric fit with a visible 24-pixel seam gap |
| 1721→1722 | 64 | Keep provisional; unused in final sheet |

Native source inspection rechecked the rejected control overlaps. The common
rotor-reverse row is too obscured in 1712; the small spare/CR1 overlap in
1713→1718 remains unstable; and the overload row in 1715→1716 is close to the
bezel/dust boundary with no independently verified two-dimensional circuit
support. The repeated glare strip, hand/phone outline and glass dust do not
establish diagram correspondence.

Two newly inspected M2S middle terminals were withheld from the existing
seven-point 1720→1723 fit. Their observed coordinates are in
[held-out-landmarks.tsv](../registration/held-out-landmarks.tsv). Against the
**unchanged published plan**, L2 has squared error 2 and T2 squared error 5,
approximately 1.4 and 2.2 pixels. They add circuit-feature corroboration; they
do not verify any electrical connection. The older SIFT counts are historical
evidence from the prior continuation, not a newly executed SIFT run.

## Photographic processing

Readability parameters are radius 32, gain 8, noise subtraction 0. The earlier
24/8/3 candidate was inspected but could suppress faint marks. Zero noise
subtraction retains more faint contrast and also more dust/reflection texture.
The local mean suppresses smooth illumination variation. It cannot distinguish
all dark reflection contours from printed conductors or black terminal circles.

Aperture marks the outside of explicitly measured glass polygons and captured
navigation controls as grey. Control masks include triangles rather than broad
rectangular erasure around neighbouring wires. Conservative edge insets may
exclude clipped mark fragments near the bezel; these remain unresolved, and
the unmasked original JPEGs are included in the private packages.

Scrolling provides different observations of the same circuit row while glass
artifacts remain at screen coordinates. Registered overlap selection can use an
observed alternate where the preferred source is excluded. It does not remove
every reflection through temporal decomposition. No learned fill, dust
inpainting, OCR replacement, line repair, wire extension or cross-source
colour averaging was applied.

## Final sheets and exact sampling

| Sheet | Main PNG/P6 dimensions | Native one-source-pixel-per-output-pixel atlas |
| --- | --- | --- |
| Control | 2448 × 3903 | 2328 × 3903 |
| Power | 2336 × 2364 | 2328 × 2364 |

The control sheet contains all six distinct sections, using 1718 for the wider
bottom-left observation and the registered 1716/1717 lower right pair.
1714 and 1719 were processed and retained as private alternative observations.
The power sheet contains all four sections, using the supported left pair and
keeping 1721/1722 separated. Left/right circuit connectivity is unproven.

There is no download-size downscaling. Similarity registration necessarily
changes sampling relative to one photograph: each registered output pixel
selects exactly one nearest original sample. The additional native atlases
preserve direct one-to-one sampling without that geometric resampling.

Each main enhanced image has a same-layout unenhanced reference and a source
identity map. Their PNG and binary P6 arrays agree exactly.
[Output and decoded RGB hashes](../evidence/host-v3/output.sha256) identify them.

## Replay of source identity

Map samples have equal RGB channels. Values 12 through 23 identify photograph
1000001712 through 1000001723. Value 0 is excluded/unobserved; 232 is assembly
background. Both unknown kinds contain RGB(232,232,232) in the reference.

For a direct layout section, subtract the destination origin and add its source
origin. For a registered section, subtract its layout destination, add the
published plan origin, then use either the later point unchanged or the
nearest inverse point for the earlier source. The source ID selects which
formula applies. The retained plan, layout, window and source hashes make the
mapping reproducible for every selected output pixel.

For an enhanced sample, that mapping identifies the centre pixel and its
photograph; the recorded radius/gain/noise parameters also identify the local
background neighbourhood used to change its channels. Exact original-channel
preservation applies to the unenhanced reference and geometric selection.

VerifySource independently expresses these final layout mappings and recomputes
the inverses with arbitrary-precision Integer arithmetic. It shares the tested
P6 reader but does not call Registration's selection or transformation functions.
Its current mapping is specific to these final layout files; changing a layout
requires changing and rerunning this verifier.

## Remaining defects

The [compact defects ledger](remaining-defects-v3.tsv) records the unresolved
seams, approximate source-coordinate regions, excluded boundary fragments,
glare, dust, and faint text. No full-sheet electrical continuity or readable
recovery of every terminal number is claimed.

Private delivery contains the main PNG/P6 sheets, references and identity maps,
native atlases, all twelve original JPEGs grouped by circuit, enhanced
alternative observations, output hashes and replay plans. No public image
artifact or release is created.
