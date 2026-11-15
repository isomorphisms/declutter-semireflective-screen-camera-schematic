# Request better photographs where evidence is missing

The user directed that uncertainty should first produce a useful request for
more photographic evidence, instead of a guessed label, wire or connection.

## Implemented behavior

`PhotoRequests.idric` distinguishes glare, blur, missing coverage, disagreeing
views, uncertain alignment, processing loss, unchecked regions, and preserved
local appearance. These are evidence reasons, not calibrated probabilities.
Unchecked regions and sparse local PASS results cannot grant whole-sheet PASS.

`PhotoReview.idric` authenticates original P6 bytes by SHA-256 and checks each
native rectangle. It generates a standalone offline HTML review, embedding an
exact original detail crop and a sampled location overview. No neural redraw,
OCR correction or inferred circuit content is used. BMP/base64 is only the
browser encoding boundary. Source coordinates are authoritative; no mapping
into an assembled-sheet layout is invented.

Opening a region gives its original crop, evidence reason, source coordinates,
and a specific next view. Glare requests another camera side/height with the
same HMI diagram and scroll position. Missing coverage/alignment requests wider
or overlapping scrolled views with distinctive circuit landmarks. Processing
loss directs software repair. The frozen 1718 24V-DC contrast failure belongs
to that last category; another photograph is not demanded for it.

Each capture request supports Later and Cannot photograph. These choices are
independent of its evidence state. Additional selected/camera images appear as
**verification pending**. No client control resolves a region or asserts an
electrical connection. Save review and photographs downloads a new HTML copy
containing the original crop, disposition and new photographs. Reopening that
copy restores the state without a server, account, local storage or network.
The user must retain the downloaded copy; unsaved tab state is transient.

The browser code is narrowly scoped to browser APIs: selection, preview,
deferral and offline save. Idriç owns source authentication, image admission,
evidence classification, crop encoding and report generation.

## Inputs and integration

`photo-review regions` takes an explicit source-bound region manifest, original
directory, the repository `PhotoReviewView.html` template, and a fresh output
path. The version line is `version<TAB>photo-requests-v1`. Each subsequent row
has ten tab-separated fields:

| Field | Meaning |
| --- | --- |
| `region` | Row kind |
| identifier | Unique source-region name |
| original basename | Admitted decoded P6 file |
| SHA-256 | Exact decoded original identity |
| left, top, width, height | Native half-open original rectangle |
| reason | `glare`, `blur`, `missing-coverage`, `disagreement`, `alignment`, `processing-loss`, `unchecked`, `preserved` |
| evidence | Actual observation supporting the reason |

`photo-review coverage` reads an existing coverage manifest and the original,
reference, candidate and source-map images. It runs the existing independent
`verify_witness` checks. Observed local contrast/coverage failures become
processing repair; ambiguous or unobserved circuit witnesses become requests
for evidence; contamination does not become a circuit feature. Foreign source
identity and malformed frames are errors, not excuses to request another photo.
Successful checks retain their narrow local-appearance meaning.

Both entry points use complete read/write admission and exclusive output
creation. Existing files are not replaced. Failure before writing leaves no new
report. Crop size is bounded to 512×512, overview extent to 384 samples per side,
and the manifest to 24 regions. Photo attachments are limited to 12 images,
12 MiB each and 48 MiB total. Failed image decoding does not add evidence.

## Verification and remaining work

The maintained Idriç/Chez compiler pin is unchanged. Focused host checks cover
manifest rejection, source/rectangle admission, evidence classification,
contrast-loss versus retake behavior, identity failures, escaping, encoding and
original-pixel preservation. Independent ImageMagick decoding checks BMP RGB
channel order, orientation and row padding.

The browser acceptance suite exercises generated synthetic imagery only:
responsive layout, pending-image behavior, inert filenames, deferral, saved
session recovery, failed-image rejection and absence of remote requests. Hosted
browser checks bind the generated synthetic fixture to the qualified source
and template checksums. They do not rebuild the Idriç compiler or publish any
private image. Host compiler execution and browser CI are distinct evidence.

This first interface consumes explicit original-image observations and existing
coverage witnesses. It does not discover every uncertain area automatically.
New photographs still need decoding, source admission, alignment and the
relevant independent appearance/topology checks before a regenerated result can
resolve anything. Automatic camera aiming, electrical topology verification,
all-section uncertainty discovery and assembled-sheet source-map navigation
remain unfinished. The optical 24V regression remains open.
