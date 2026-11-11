# Independent photographic coverage — first executable slice

## Type sketch, before implementation

Photograph samples, photograph coordinates, output coordinates, evidence states,
feature kinds and rendered contrast are distinct. A frozen witness contains a
native rectangle, explicit `observed`/`ambiguous`/`unobserved` state, evidence and
corroboration descriptions, and bounded mark/background probes. A probe records
two original coordinates, their exact decoded RGB values, a channel, and a
minimum observed contrast. These are agent-inspected observations, never human
verification. Unreadable text has no asserted transcription.

`parse_manifest : Text → Either Text CoverageManifest`

`verify_coverage : CoverageManifest → Image → Image → Image → Image → IO (Either Text ())`

Inputs are the original decoded photograph, assembled unenhanced reference,
candidate readability sheet and assembled identity map. This first mapping is
an independently declared native translation for the selected 1718, 1715 and
1723 sections; arbitrary registration is deliberately unsupported. The manifest
binds the original JPEG SHA-256, decoded P6 SHA-256, layout SHA-256 and baseline
source revision. SHA admission is an external `sha256sum` boundary recorded in
the run receipt; the verifier independently checks source probe RGB, shapes,
full witnessed rectangle coverage/reference samples, and candidate probes.

Required electrical witnesses must have at least one probe. Their entire native
rectangles must survive with the right source ID and exact reference samples.
Every probe must remain darker than its adjacent background in its declared
channel by at least max(4, ceil(original_difference/2)). This is a bounded local
distinguishability condition, not OCR, general feature extraction, or proof of
whole-symbol/electrical identity. Candidate-dependent thresholds are forbidden.
The same contrast rule applies to a deliberate gap using the flank as mark and
the gap as background. Filled gaps therefore fail; this is not general topology.

Ambiguous/unobserved witnesses report UNRESOLVED and cannot supply acceptance.
Contamination is recorded separately and cannot grant electrical PASS. At least
one observed conductor and one observed marking, and every admitted witness,
must pass. Empty/all-unknown/all-unresolved inputs must fail. No confidence score.

Arrays remain the bounded contiguous raster representation. Only the small
witness list is linked; never a per-pixel list. Coordinates, extents and offsets
are admitted before addition. Limit manifest text to 64 KiB, 64 witnesses, 256
probes, 4096 pixels per witness. No host Double. No calls to production masking,
registration selection or optical estimation. Parsing shares tested P6 admission.

Effects: read five immutable files; print per-witness diagnostics; exit nonzero
on any required failure. No image output or production source modifications.
Focused mutation execution is separate, read-only for baseline files.

## Language/runtime

Idriç pin 2bce7677f513d711875e978bd6f5ad28b9e54d58, maintained edric bootstrap,
explicit Chez backend, Linux x86-64 / Chez 10.4.1. Existing SchematicRaster P6,
checked pixel access and bounded iteration are reused. Canonical STYLE.md and
both intent examples were read. Their intent notation is not assumed grammar.

## Results

VerifyCoverage, CoverageTests, VerifyEnhancement and CollisionTests compile and
execute through the pinned explicit Chez backend. No language/backend fallback
was used. Initial compilation exposed ordinary source errors: choice type names
require snake_case, an untyped numeric list needed an explicit List Int type,
`total` is reserved, and an effect bind needed explicit parentheses. They were
corrected in source; the first elaboration failure log is retained. Backend
errors printed after holes were emitted are not counted as executable acceptance.

Three real positive slices pass:1718 conductor/L marking in the final control
sheet,1715 node/gap/label stroke in that sheet, and1723 rail/terminal in its native
aperture output. All targeted erasure/mask/map/vacuity/gap mutation checks fail
for their intended causes. The broader1718 24V-DC requirement correctly FAILS:
one source stroke/background pair is rendered white at both positions. This
failure was retained alongside the narrower positive, never downgraded to
unknown. The native1723 boundary is selected from1720 in the final sheet; only
the observation-level1723 assertion is admitted in this version.

Independent direct32/8/0 arithmetic reproduces28 native RGB points; wrong gain
and corrupt output are rejected. Correct arithmetic and useful preservation
remain distinct. CollisionTests is intentionally red:11 of13 production
invocations violate pre-write rejection/preservation. Production repair belongs
only to the optical plan's Earth path-admission owner. Existing VerifySource and
LandmarkAudit are reused, not replaced. See docs/independent-verification-v1.md
and evidence/coverage-v1 for executed boundaries, exact commands and hashes.

## Language work

No new blocking Idriç capability was needed for the first slice. The next program
requirement is a checked, source/frame-bound verification bundle, with bounded
local trace/incidence arrays and independent Integer geometric consumption. Its
acceptance is a real alternate-source witness through composition plus wrong-
frame/digest/map controls. This is application verification work, not evidence
of a compiler gap or permission to substitute another language.
