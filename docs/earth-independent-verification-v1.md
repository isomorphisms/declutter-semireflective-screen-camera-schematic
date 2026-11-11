# Earth follow-up jobs — independent ReTech fidelity verification

These assignments extend the executed first slice described in
`docs/independent-verification-v1.md`. They do not replace it with planning.
Keep PR draft. Sun's first-slice decision is complete; remaining bounded
implementation belongs to Earth. No Moon propagation is admitted yet.

## EARTH-RETECH-OUTPUT-ADMISSION-01 — existing sole production owner

```text
Model: Earth
Reasoning: High
Outcome: Reject every unsafe primary/companion write before writing anything,
with all read dependencies unchanged. This is the existing optical plan's job,
augmented with the independent verifier's executed red regression. Do not start
a competing repair if this job already has an owner; give that owner the fixtures.

Repository: https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic
Existing work: isomorphisms/declutter-semireflective-screen-camera-schematic PR #1,
“Implement inspectable Idriç cleanup and provisional HMI registration”:
https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic/pull/1
Branch: work/inspectable-cleanup. Original inspected baseline:
8145063ef13e3ddcda3284ed2ea7ccf6b6595b90.
First read docs/independent-verification-v1.md, evidence/coverage-v1, and the
current versions of CollisionTests.idric and the optical Sun output-admission
decision. Refresh live head/discussion/checks and reconcile any completed fix.
Verify source hashes against the receipt, preserve concurrent work, and use an
isolated worktree. Do not replace/reset/recreate the current implementation.

Compiler pin: isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58.
Maintained edric bootstrap, explicit Chez backend. Recorded host: Linux x86-64,
Chez 10.4.1; verify actual host/entrypoints. Read canonical STYLE.md and both
intent examples before source edits. No processing-language/backend fallback.

Authoritative decision and permitted files
Only this job changes production path admission in Cleanup.idric, Aperture.idric,
Registration.idric, Assemble.idric and a narrow shared RunPaths.idric. Preserve
optical, geometry, masking, output bytes and public CLI semantics for safe paths.
List the complete read set and write set after plans/layouts are admitted:
Cleanup input and every declared dependency vs output and provenance; Aperture
window/image vs output/source-map; Registration plan/two images/two maps vs
output/source-map/provenance; Assemble layout/all resolved sections vs output.
Check reads against every write and writes against one another before any write.
Use canonical/alias facilities supported by the runtime. String inequality does
not establish identity. If aliases cannot be resolved safely, fail closed or
use a demonstrably fresh disjoint output directory; state concurrency assumptions.

Independent evidence
CollisionTests.idric is compiled and executed against baseline production.
13 cases: 2 safe rejections, 11 invariant failures. It already demonstrates
overwritten window/image/plan bytes and symlink/hard-link source damage, entirely
on disposable fixtures. Cleanup's exact companion guard is already accepted;
extend it instead of rewriting it. Do not weaken the tests or bless successful
identity crops that happen to leave RGB unchanged while creating companions.

Run the existing compiled collision suite as:
collisiontests PRODUCTION_EXECUTABLE_DIRECTORY FRESH_DISPOSABLE_DIRECTORY
Resolve actual absolute paths; fixture directory must be fresh. Extend the matrix
to every input role (including second image/map), write/write admission, Assemble,
normalized relative paths and all supported symlink/hard-link aliases. Include
positive admitted writes and an intentionally broken guard. Require nonzero
rejection, identical before/after input digests, and no new partial output for
every negative case. Keep fixture construction and acceptance independent of
the production helper. Never run destructive collision cases on original files.

Execute existing raster/registration/aperture/landmark and source-replay checks
as relevant. Verify unchanged safe real outputs and PNG/P6 array equality using
private copies of the verified baseline packages. Private JPEGs, crops, reflections
and derivative images must remain outside GitHub/public CI artifacts.

Finish: all 13 existing and extended cases green, exact source/compiler/executable
hashes and commands/statuses recorded, all safe outputs unchanged. Supply the
exact passing head to the independent verification and optical owners. If the
runtime cannot establish path identity, report the first concrete gap; do not
claim alias safety. Keep PR draft; no merge/close/release/private publication.
```

## EARTH-RETECH-COVERAGE-COMPOSITION-02

```text
Model: Earth
Reasoning: High
Outcome: Extend qualified native coverage to independent geometry/alternate-source
consumption and mandatory observed coverage in every one of six control and four
power sections. Preserve existing positive slices and the required 24V-DC failure.

Repository: https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic
Existing work: isomorphisms/declutter-semireflective-screen-camera-schematic PR #1,
“Implement inspectable Idriç cleanup and provisional HMI registration”:
https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic/pull/1
Branch work/inspectable-cleanup; original baseline
8145063ef13e3ddcda3284ed2ea7ccf6b6595b90.
Refresh live state and read the exact first-slice head/receipt in
docs/independent-verification-v1.md, evidence/coverage-v1 and coverage-attempt.md.
Check source hashes and existing equivalent work. Isolate changes and preserve
concurrent edits. Pin isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58,
maintained edric bootstrap/explicit Chez, recorded Linux x86-64/Chez 10.4.1.
Read local instructions and canonical Idriç style/intent examples.

Sun decision
VerifyCoverage currently admits photograph→output native translations, full
witness-rectangle source/reference equality, sparse rendered contrast, explicit
evidence states, source digest/probe admission, and nonvacuity. It checks local
strokes, not whole symbols or topology. Keep this boundary honest. 1718 N and L
pass final control composition; an original 24V-DC probe at (590,1257) becomes
white and fails the broader ledger. Preserve that red result until a real later
candidate fixes it. Never remove/downgrade an observed witness because output fails.
1723's top rail passes its native aperture observation, while final composition
selects 1720 there. A legitimate alternate requires independently supported
feature correspondence; do not demand the wrong photograph or invent a match.

Permitted scope
Extend VerifyCoverage.idric, CoverageTests.idric, the witness schema/fixtures and
coverage docs/receipts. Add a small verifier-only geometric consumer if needed.
Do not edit Cleanup, Aperture, Registration algorithms, transforms, windows or
layouts; production source/map identity ownership belongs to the optical jobs.
Reuse P6 admission and existing VerifySource for pixel replay; do not reimplement
accepted tests or call production coordinate/selection functions as the oracle.

Consume qualified plan/layout/source/frame identities. Keep photograph, screen,
schematic, crop-local and output frames distinct, with checked origins/extents.
Use Integer for independent inverse/nearest-sample verification. Admit only the
current two supported pairs, and retain both grey seam gaps. Bind JPEG, decoded
RGB/P6, witness manifest, layout, plan, window/mask ownership, candidate and
verifier digests plus parameters and exact tested revisions. Equal dimensions
or a map's own claim cannot establish source ownership. Extend mandatory digest
admission beyond the current decoded-original check; reject missing, relabelled
or mismatched evidence bundles rather than guessing from filenames.

Inputs and witnesses
Recover verified retech-control-v3-private.zip and retech-power-v3-private.zip;
historical absolute workspace paths are receipts, not portable locations. Check
all 12 originals against source-manifest and both inventories. Use original-only
inspection to add fixed coverage in all 10 sections. Reuse current witnesses.
Prioritize upper-right glare 1712/1713, lower supply 1718, transformer/breaker1721,
X1/motor1723, and aperture fragments. For unreadable features retain UNRESOLVED;
do not fabricate text or choose background as the section's electrical witness.
For each newly admitted mark retain original/reference/baseline/candidate crops
at native density, source identity, evidence state, corroboration and outcome.
Agent annotations must never be called human-verified. If a required feature's
electrical identity is uncertain, stop that assertion at UNRESOLVED.

Tests
Keep the current real positive/mutation suites and actual moved-aperture/wrong-
photo/wrong-map CLI cases. Add registered-point, crop-origin, shifted-source,
relabeled-map, wrong-layout/plan/window, unsupported alternate, valid alternate,
missing-evidence and unrelated-dark-neighbour adversaries. Freeze requirements
outside candidate maps; empty, all-unresolved, all-unknown, missing-section or
all-grey output must fail even when VerifySource passes. A fallback cannot
change a terminal's identity or claim seam continuity.

Finish: the verifier checks every section nonvacuously and supports only genuine
declared correspondences, current good marks pass and all known corruptions fail
for specific causes, broader supply regression remains visible, current PNG/P6
and source replay are preserved. Record exact commands/exits/hashes and new
photographic observations. Stop on contradictory correspondence/identity evidence
or compiler/runtime gaps; return to Sun rather than redesigning optical behavior.
Keep PR draft; no merge/close/release/public image artifacts.
```

## EARTH-RETECH-INDEPENDENT-ENHANCEMENT-03

```text
Model: Earth
Reasoning: High
Outcome: Complete independent arithmetic/dependency verification for legacy and
the declared masked signed-contrast candidate, while keeping useful-information
preservation a separate requirement.

Repository: https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic
Existing work: isomorphisms/declutter-semireflective-screen-camera-schematic PR #1,
“Implement inspectable Idriç cleanup and provisional HMI registration”:
https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic/pull/1
Branch work/inspectable-cleanup; baseline8145063ef13e3ddcda3284ed2ea7ccf6b6595b90.
Refresh head, discussions and checks. Read docs/independent-verification-v1.md,
evidence/coverage-v1, VerifyEnhancement.idric, VerifyCoverage.idric, current
OpticalContrast/Observation contracts if implemented, and the optical Sun plan.
Use source hashes and exact prerequisite receipts, not a remembered passing head.
Preserve concurrent work; isolated worktree. Compiler pin
isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58, maintained bootstrap,
explicit Chez, recorded Chez10.4.1/Linuxx86-64; verify actual execution target.

Existing qualified work
VerifyEnhancement directly enumerates clipped native neighbourhoods with Integer
sums, independently checks 28 RGB points, and rejects corruption/gain7. Its tiny
fixtures cover floor/clipping/non-square boundary and radius admission. It never
calls enhance/local_mean/normalize_sample or copies integral-image code. Correct
32/8/0 output still loses the 1718 local 24V-DC distinction. Preserve both facts.

Permitted scope
Extend VerifyEnhancement and independent focused fixtures/receipts. Add helpers
only below the verifier boundary. Do not edit production optical estimator,
renderer, masks, geometry or source selection; coordinate interfaces with the
existing EARTH-RETECH-MASKED-SIGNED-CONTRAST-02 owner. Implement legacy extension
now; masked-model execution depends on that owner's actual qualified artifact.
If absent, record candidate NOT_RUN rather than invent its output.

Independent masked oracle contract from the optical decision
For each clipped radius32 window, eligible original samples only: Integer sum S,
count N, geometric area A. Require N>=max(64,ceil(A/2)); unsupported estimates
retain original observed RGB with explicit unsupported status. Background Q8 is
floor(256*S/N), residual is backgroundQ8-256*sample, retained signed until final
rendering. Rendering floors signed Q8/256, noise0/gain8 then clips as declared.
Verify source/frame/mask ownership, support/count/status/rounding, every dependency,
numeric/allocation bounds and delayed rendering. If the implemented contract
differs, stop and report the contradiction instead of silently choosing a model.
Tiny fixtures must enumerate eligible samples directly; no production estimator
or integral algorithm may serve as the oracle. Share tested P6 admission only.
No Double, per-pixel lists, unchecked narrowing, source modification or language
fallback. Record replay-bundle digests and model/version/parameters.

Tests
Add faint wire, dark terminal dot, reflection edge crossing a wire, open gap,
mask-adjacent text, no/insufficient eligible samples, wrong source/frame/parameter
identity, support-mask corruption, signed fractional/negative values, clipping,
extreme bytes, accumulator/resource limits and delayed-vs-early clipping. Keep
independent whole-neighbourhood legacy checks and known-bad counterparts. Compare
all-eligible supported candidate neighborhoods to legacy; unsupported estimates
must preserve original samples/identity. Useful mark retention must still pass
VerifyCoverage and later VerifyTopology; arithmetic PASS alone cannot grant it.

Real acceptance
Use verified private original1718 supply and1723 boundary observations, whole-frame
estimation before crop, plus frozen1715 controls. Independently enumerate selected
real neighborhoods. Retain source/original/legacy/candidate/signed/status crops
privately at native density. Check bit-exact interior1718 negative control for
the exclusion-only method. Keep the observed24V loss red unless actually fixed.

Finish: legacy and available declared candidate arithmetic/dependency positives
pass; every known wrong arithmetic/bundle case fails; useful preservation is
reported separately and no optical improvement is asserted without photographs.
Record source/compiler/executable/output hashes, commands and exits. Stop at a
contract contradiction or missing candidate, preserve the executed work, and
name that specific blocker. Keep PR draft; no merge/close/release/private imagery
in GitHub/public CI artifacts. No Moon rollout of an unaccepted optical candidate.
```

## EARTH-RETECH-INDEPENDENT-OVERLAP-04

```text
Model: Earth
Reasoning: High
Outcome: Implement VerifyOverlap.idric as a verifier of independently witnessed
circuit correspondences, with stroke/observation-relative residual limits.

Repository: https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic
Existing work: isomorphisms/declutter-semireflective-screen-camera-schematic PR #1,
“Implement inspectable Idriç cleanup and provisional HMI registration”:
https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic/pull/1
Branch work/inspectable-cleanup, baseline8145063ef13e3ddcda3284ed2ea7ccf6b6595b90.
Refresh mutable state, read local/canonical Idriç instructions and independent
first-slice source/hash receipts. Compiler pin
isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58; maintained bootstrap,
explicit Chez, recorded Linuxx86-64/Chez10.4.1. Preserve concurrent edits.

Sun decision/evidence
Only control1716→1717 and power1720→1723 have accepted geometric use, with24px grey
gaps and no electrical-continuity implication. Existing LandmarkAudit already
recomputes Integer fits/held-out diagnostics. Its unchanged published power fit
has original M2S middle-terminal held-outs L2 squared-error2 and T2 error5; a
wrong terminal fails. Reuse that evidence/implementation rather than rewriting
the accepted audit. It currently uses an unexplained universal squared limit25;
that does not establish the required stroke-relative rule or repeated-rung safety.
Pairs1712→1713,1713→1718,1715→1716 and1721→1722 stay unaccepted.

Permitted scope and contracts
Add VerifyOverlap.idric, original-derived held-out witness metadata, focused
false-match fixtures and scoped receipts. Do not refit production transforms,
move seams/windows, blend alternate images or change Cleanup. Independently
consume exact plan/source/frame/mask/layout identities and use Integer geometry.
Record each endpoint/symbol/terminal correspondence, original native crops,
which fitting data it was withheld from, observed stroke extent and coordinate
uncertainty. Freeze these before candidate evaluation. A residual limit must
follow measured stroke width and stated observation uncertainty in the same
frame; do not tune a universal number to produce green results.

Recover/hash both private original packages. Inspect1714,1718,1719 as separate
bottom-left observations; existence/appearance alone is not a fusion license.
For1716/1717 establish independently withheld distinguishable circuit features
from originals or leave new assertions UNRESOLVED. Repeated rungs, parallel
wires, dust, bezel and screen-stationary reflections do not establish identity.
Do not call agent observations human-verified. If no distinctive identity is
supported, return UNRESOLVED, preserving the old qualified geometry decision's
actual boundary rather than manufacturing a new photographic PASS.

Tests and finish
Check known accepted held-outs, deliberately wrong terminal/endpoint identity,
shifted observation, repeated-rung false match, same-sized wrong-source mask,
wrong frame/origin/plan and incompatible geometric support. Each known bad must
fail for a specific reason. Assert no promotion of the four unaccepted pairs.
Retain original/baseline/candidate crops at original density and exact hashes.
Finish when module compiles/runs through pinned Chez and admitted real held-outs
pass the justified tolerance while all false-match controls fail. Unsupported
correspondences remain UNRESOLVED. Stop at contradictory feature evidence rather
than redesigning registration. Record commands/statuses/source/compiler/output
hashes. Keep PR draft; no merge/close/release/public photographic artifacts.
```

## EARTH-RETECH-LOCAL-TOPOLOGY-05

```text
Model: Earth
Reasoning: High
Outcome: Implement VerifyTopology.idric for small, original-witnessed incidence
assertions. A complete netlist/extractor is explicitly outside scope.

Repository: https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic
Existing work: isomorphisms/declutter-semireflective-screen-camera-schematic PR #1,
“Implement inspectable Idriç cleanup and provisional HMI registration”:
https://github.com/isomorphisms/declutter-semireflective-screen-camera-schematic/pull/1
Branch work/inspectable-cleanup; baseline8145063ef13e3ddcda3284ed2ea7ccf6b6595b90.
Refresh live state and first-slice hashes/receipts; preserve concurrent work and
use an isolated worktree. Compiler pin
isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58, maintained edric bootstrap,
explicit Chez, recorded Linuxx86-64/Chez10.4.1. Read local/canonical instructions.

Authoritative bounded assertions
The original1715 filled COM0 node around[705,737)×[677,707) visibly meets a left
horizontal arm and vertical bus. Inspect native original with a small halo and
freeze west/north/south local trace ports and their incidence at this node.
The original TR1 region[350,390)×[850,885) contains distinct contact bars, with
the tested open space near(370,867), flanked near(362,867)/(378,867). Freeze two
locally separate arms and the forbidden bridge region. Source SHA is in
coverage-1715.tsv. Current appearance tests reject dot erasure and gap filling,
but do not prove arm connectivity or port incidence. Preserve that distinction.
Original1723[525,625)×[700,850) is the optical plan's separate-conductor control;
inspect it before admitting ports. Do not infer a crossing/junction merely from
a dark contour. Add a crossing-without-connection assertion only if original
photographic support establishes it; otherwise report UNRESOLVED.

Permitted source and interfaces
Add VerifyTopology.idric and a small typed local-assertion/witness format plus
focused tests/docs. Consume qualified source/frame, original-dependent traces,
explicit terminal identities, ports, nodes, required separations and gaps. Reuse
VerifyCoverage/P6 identity admission, not production cleanup's segmentation or
coordinate transforms as an oracle. Trace storage must be bounded arrays or
small feature paths; no per-pixel linked lists/Double. Keep coordinate uncertainty
and observed/ambiguous/unobserved states explicit. Any extraction/threshold
decision must preserve feature identity and be checked against original trace
witnesses; a reflection-derived path cannot become an electrical conductor.
Do not add a general OCR, complete netlist, automatic line repair, redraw or
optical algorithm. No production Cleanup/Aperture/Registration changes.

Positive and adversarial acceptance
At native density verify one continuous witnessed trace, the COM0 three-arm
supported junction, distinct parallel traces if admitted, and the intentional
open TR1 gap. Reject deleted arm/connection, erased node, added branch/bridge,
filled gap, merged parallel wires and unsupported terminal identity. Include
glare-hidden connections as UNRESOLVED, an unrelated nearby dark contour, and
seam/left-right boundary cases. No plausible extension across a24px grey seam
counts as evidence. Do not infer global terminal equivalence from a local port.
Run synthetic graph adversaries AND actual original/baseline/candidate regions;
freeze original-derived expected incidence before examining candidate traces.
Agent annotations are not human verification. Retain all native evidence privately.

Finish: compiled/executed pinned-Chez VerifyTopology passes supported original
local assertions, rejects each fabricated/deleted connection for its actual
cause, and preserves unresolved connections. Broader electrical acceptance
remains partial. Record exact source/compiler/executable/output/witness hashes,
commands, exits and private crop identities. If the photographs contradict the
node/gap/port interpretation, stop that assertion and report the contradiction;
do not change semantics to pass. Keep PR draft; no merge/close/release/private
imagery in GitHub or public CI artifacts. No Moon job until semantic and real-
photograph acceptance is settled at an exact passing head.
```
