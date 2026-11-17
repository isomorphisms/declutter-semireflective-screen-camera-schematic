# Paper-photo mosaic reference (experimental)

This C11/POSIX reference covers the *source-mapping boundary* of issue #2. It
supports multiple manually aligned P6 photographs, canvas-to-native projective
warps, an optional continuous 3x3 bilinear residual mesh, explicit pairwise
cut lines with gutters, and unobserved pixels. It is not the Idric production
renderer and does **not** estimate camera poses or match features.

The private five-photo dust-system trial showed wrinkles at the image joins,
including dimension lines. The earlier pixel-provenance PASS is not geometric
acceptance. This reference cannot certify a drawing by merely using a mesh.

## Build and exercise

```sh
cc -std=c11 -O2 -Wall -Wextra -Wconversion -Werror paper_stitch.c -o paper-stitch
./check.sh
./paper-stitch plan.tsv output-stem
```

Decode each JPEG to **unenhanced 8-bit P6 PPM** separately, preserving an
original JPEG digest outside the repo. For example, use a local image decoder
as a format boundary; no JPEG data is included here. Inputs are supplied by
path relative to the current working directory, not the plan file. A plan is
one drawing view; **never combine the elevation and plan views**.

Plan directives (white-space separated):

```
canvas WIDTH HEIGHT
source ID FILE X0 Y0 X1 Y1 H11 H12 H13 H21 H22 H23 H31 H32
mesh ID dx00 dy00 dx10 dy10 dx20 dy20 dx01 dy01 dx11 dy11 dx21 dy21 dx02 dy02 dx12 dy12 dx22 dy22
join FIRST_ID SECOND_ID x|y CUT GAP
```

Each `source` rectangle is half-open in *output canvas* coordinates. An inverse
projective homography takes canvas `(x,y)` to native `(u,v)` with coefficients
in millionths:

```
d = 1000000 + H31*x + H32*y
u = (H11*x + H12*y + H13)/d
v = (H21*x + H22*y + H23)/d
```

The optional `mesh` adds a bilinearly interpolated native-pixel displacement,
in units of **1/256 pixel**, from nine shared grid nodes. Grid interpolation is
continuous across its internal cells. This is a *correction proposal*, not a
source of new drawing content. The guard rejects inconsistent cell orientation,
degenerate geometry and projective poles; it does not measure correspondence
quality or detect every possible fold. Only one mesh per source is allowed.

A `join` authorizes exactly two overlapping source observations. `x CUT` takes
FIRST_ID to the left, SECOND_ID to the right; `y CUT` selects above/below.
`GAP` is an explicitly unobserved strip in canvas pixels. Unqualified overlaps,
three-way overlap and joins that do not cross actual shared source coverage are
rejected. Sections visible in only one photograph retain that photograph.

Example with two synthetic horizontally overlapping 4x4 PPMs:

```
canvas 6 4
source 1 first.ppm 0 0 4 4 1000000 0 0 0 1000000 0 0 0
source 2 second.ppm 2 0 6 4 1000000 0 -2000000 0 1000000 0 0 0
join 1 2 x 3 1
```

## Evidence and outputs

Outputs are written only if absent (not as an atomic group):

- `output-stem.ppm`: observed P6 pixels, grey 232 only for unobserved points
- `output-stem.source-id.pgm`: 8-bit image, 0 means unknown, IDs 1-254
- `output-stem.source-x.pgm` and `.source-y.pgm`: 16-bit big-endian PGM native
  source coordinates, `65535` for unknown points

At each admitted mosaic pixel the program selects **exactly one original RGB
triplet** and records its source ID and native pixel coordinate. It checks
source replay before writing the results. The synthetic host tests include
corrupt replay, missing join, invalid denominator, folded-over mesh, refusal to
overwrite and actual input/output P6 operation. Replaying pixels establishes
provenance only, not that two dimension lines have been joined correctly.

### Not accepted / work still required

- Feature/landmark detection, correspondence filtering, independent withheld
  drawing-line residuals and section grouping
- Calibration of actual folds/curl beyond a simple 3x3 local correction mesh
- Real five-photo elevation/plan acceptance; private source photographs and
  corresponding mosaics must remain outside this public repository
- Port or integrate checked geometry into the Idric pipeline; verify at the
  pinned compiler and with physically photographed paper schematics
- Independent source digest authentication, output-set atomicity, seam review UI,
  geometry/topology acceptance and monitoring of irreversible fine-print loss

See [issue #2](https://github.com/the-twin-pines/declutter-semireflective-screen-camera-schematic/issues/2).
