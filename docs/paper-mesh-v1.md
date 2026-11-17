# Source-preserving paper mesh: bounded first implementation

Issue #2 needs a different capture geometry from scrolled HMI viewports. This
slice accepts **explicitly grouped, manually measured triangular patches** of
one paper sheet. Adjacent triangles can describe locally different affine
maps, including folds. This is a piecewise-affine approximation, not a fitted
projective camera model, automatic feature matching or automatic dewarping.

`PaperMesh.idric` parses a bounded manifest, authenticates decoded originals by
SHA-256, rejects degenerate/reflected panels and conflicting output claims,
and selects exactly one nearest original RGB sample per covered output pixel.
There is no blending, OCR substitution, synthesized line, contrast enhancement
or inferred document connection. Coordinate arithmetic is integer/rational.

One manifest is one page. Plan and elevation must be separate manifests. The
version line is `paper-mesh-v1 WIDTH HEIGHT`. Other lines are:

```
source ID BASENAME WIDTH HEIGHT DECODED_P6_SHA256
triangle ID DX0 DY0 SX0 SY0 DX1 DY1 SX1 SY1 DX2 DY2 SX2 SY2
gap LEFT TOP WIDTH HEIGHT
```

Triangle vertices are counterclockwise in image coordinates (positive signed
area). The destination and original triangles must have the same orientation.
Coordinates refer to sample centers; a boundary may lie one past the raster
extent. Top/left half-open edge ownership prevents duplicate shared-edge
claims. Nearest-neighbour ties round upward for nonnegative source coordinates.
A rounded sample outside an original remains unobserved; it is never clamped.
Declared gap rectangles remain grey and carry no original-pixel identity.

Run `PaperMesh PLAN.tsv ORIGINAL_P6_DIRECTORY NEW_OUTPUT.pnm`. The output is an
unenhanced P6 raster, `.x.pnm`, `.y.pnm`, and an exact `.plan.tsv` copy. Each
coordinate map stores RGB=(source ID, low coordinate byte, high coordinate
byte); both maps must name the same original. All-zero map values mean an
unobserved grey output pixel. Originals and outputs have separate path admission;
existing destinations are never replaced. Multi-file output is not transactional.

`PaperReplay PLAN.tsv ORIGINAL_P6_DIRECTORY OUTPUT.pnm` authenticates the
originals again and independently reads the coordinate maps to compare every
covered RGB sample against the selected original. It also checks map shapes,
source identities, coordinate bounds, explicit gaps and unknown-pixel encoding.
It does **not** certify completeness, feature identity, correct geometry or an
optically correct join. A wrong mesh can still have perfect pixel provenance.

The dedicated workflow compiles the first-party Idric sources using the
canonical compiler pin `2bce7677f513d711875e978bd6f5ad28b9e54d58` and its
maintained `edric bootstrap` / Chez route. It runs synthetic arithmetic, parser,
image and replay controls, plus the existing RasterTests and RegistrationTests.
Qualification status must be read from the actual exact-head run, not this file.
Only public code, synthetic fixture logs and runtime files enter its artifacts.

## Remaining work

Automatic landmark proposals, independent held-out landmark checks, robust
homography fitting, mesh-fold/curvature discovery, a mesh-editing interface and
whole-sheet optical acceptance remain unfinished. The supplied five private
photographs must be executed and inspected separately; synthetic PASS cannot
establish photographic acceptance. Do not publish those photographs, manifests
containing their identifiers, or rendered derivatives in this public repository.
