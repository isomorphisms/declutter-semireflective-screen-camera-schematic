# Program attempt: request better photographic evidence

## Purpose and intended behavior

Generate a private, offline review interface from source-bound uncertainty
regions. Show original pixels and the requested view, retain unresolved regions,
and accept additional photographs as pending evidence. A received photograph or
user deferral cannot assert that a marking or connection has been verified.
The existing coverage verifier supplies known processing-loss and ambiguous/
unobserved-witness findings; this is not a new automatic glare/OCR classifier.

## Type-system sketch (before implementation)

`PhotoRegion` associates an identifier, decoded-original filename and SHA-256,
native half-open rectangle, reason, and evidence description. Reasons distinguish
missing photographic evidence, unresolved alignment, unchecked regions,
processing damage, and preserved local appearance. No percentage is fabricated.

Central operations:

- `parse_regions : Text → Either Text (List PhotoRegion)`
- `guidance_for : review_reason → Text`
- `render_region : Text → PhotoRegion → IO (Either Text Text)`
- `render_review : Text → Text → List PhotoRegion → Text → IO (Either Text ())`

Pure parsing/guidance is separate from source admission, SHA-256 checking,
P6 decoding, image encoding, and exclusive report creation. Rectangle bounds
are admitted against the authenticated original. Original pixels are immutable.
The display overview may be sampled; the detail crop retains native RGB values.
Source coordinates remain authoritative independently of assembled-sheet layout.

## Effects and runtime boundary

Maintained Idriç/Chez compiler pin:
`isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58`.
Reuse `SchematicRaster`, `RunPaths`, `FreshFiles`, and `VerifyCoverage`.
The narrow browser boundary handles file selection, pending-photo preview,
deferral, and saving an offline HTML session; the Idriç program owns findings,
source authentication, crop admission, and report generation. Browser JavaScript
is necessary for those browser APIs; it is not an alternative image processor
or verifier. No server, account, external resource, or network request is needed.

BMP/base64 is a browser-format boundary only, with focused independent RGB
decoding acceptance. No contrast algorithm or guessed circuit content is added.

## Invariants and error states

- Processing loss requests software repair, not another photograph.
- New photographs remain pending verification; no client control grants PASS.
- Later/unavailable are workflow dispositions, not evidence states.
- Reject invalid/duplicate identifiers, malformed SHA-256, unsafe source names,
  unsupported reasons, empty/excessive manifests, out-of-frame rectangles,
  changed source bytes, excessive embedded pixels, and existing output names.
- Escape source-derived text in HTML; browser photo names are text, never markup.
- No automatic prompts for unchecked regions, and no whole-sheet PASS from a
  sparse set of witnesses. No inferred connection across an unresolved join.
- Originals, private crops and generated reports remain outside public GitHub.

## Result, commands, fallback, and language work

`PhotoReview` and `PhotoReviewTests` compile and execute through the pinned
compiler/Chez path. Focused checks and the independent ImageMagick decoder pass;
both a synthetic report and a three-region private original-photo report were
generated. Wrong-source, out-of-frame and alias CLI controls reject without
creating a report or changing protected inputs. Qualified material and executable
hashes are in `evidence/photo-review-v1/`.

Initial compilation caught an uppercase choice-type name and the inherited
nonempty-list return type of text splitting; the final source uses the actual
lowercase choice surface and explicit `List1.forget`. A later test indentation
error was corrected without changing acceptance. These were source mistakes,
not demonstrated compiler defects or permission to change implementation language.

Local browser startup requires sockets blocked by the host. Hosted browser
acceptance passed separately against generated synthetic imagery at
`0a22dedebc26750a2e700840bff05d1665cd0341`. This is not counted as Idriç compiler or
physical camera evidence. The first runner attempt exposed the pinned browser's
lack of Ubuntu 26.04 support; the workflow now names supported Ubuntu 24.04.

There is no fallback image processing. The inherited compiler's Unicode-minus
gap remains the existing documented notation exception; supported subtraction
is used at implementation boundaries. Camera overlays, automatic field-wide
confidence detection and assembled-sheet source-map transforms are not claimed
by this first source-coordinate review interface.
