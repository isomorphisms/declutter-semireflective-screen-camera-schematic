# Program attempt: schematic-cleanup

Status: `PARTIAL` for the full photographic reconstruction; `PASS` for the implemented raster program's compile and focused runtime acceptance.

## Purpose

Produce inspectable pixel transformations of the user's photographs of a schematic displayed on a reflective HMI. The photographs are the evidence. The program must not invent wires, characters, component symbols, or obscured content.

## Intended behavior

Read a strictly validated binary RGB P6 PNM, retain its dimensions, and make a conservative local-contrast enhancement. Optional bounded crops preserve exact source coordinates. Write P6 so a separate image codec can encode PNG without supplying any cleanup algorithm. An assembly consumer may copy pixels from admitted input images into a declared canvas.

The enhancement is explicitly lossy. Local brightness normalization suppresses broad illumination and reflection gradients but cannot prove that a retained or removed detail belongs to the schematic. Original photographs and unenhanced source-coordinate assemblies remain the comparison authority.

## Type-system sketch

### Values and domains

- Image width and height are positive whole-number counts.
- A channel is one unsigned eight-bit sample; a pixel has red, green, and blue channels.
- A pixel position belongs to the rectangle determined by its image dimensions.
- A raster carries its width and height as type indices and retains its admitted payload offset and buffer extent.
- A crop has an origin and positive extent contained in the source rectangle.
- Enhancement parameters are a bounded local-background radius, contrast gain, and noise subtraction in sample units.

### Types and signatures

`Raster width height` stores admitted pixels for those exact dimensions. `Position width height` stores coordinates and erased `So` evidence of the rectangle bounds. `Image` packages runtime dimensions with the matching raster. Public operations admit a position before reading or writing the raw buffer.

`read_ppm : Text → IO (Either Text Image)`

`write_ppm : Text → Image → IO (Either Text ())`

`pixel_at : Image → Int → Int → IO (Maybe Pixel)`

`put_pixel : Image → Int → Int → Pixel → IO Bool`

`enhance : Image → Parameters → IO (Either Text Image)`

### Actions and effects

Pure functions validate dimensions, coordinates, header numbers, and enhancement arithmetic. IO actions open and validate P6 files, allocate bounded buffers, construct channel integral sums, transform pixels, and save results. The input image buffer is read-only during enhancement.

### Laws, invariants, and errors

- Every admitted file has exactly the declared RGB payload length, with no truncated or trailing payload.
- The scalar pixel-read/write API admits each coordinate through `Position width height`. Bulk rectangle copies instead use checked rectangle extents and explicit row-address arithmetic. Integral-sum storage uses checked allocation extents and implementation arithmetic; it is not covered by the pixel-position proof.
- Read and write channel order is RGB, contiguous rows, three bytes per pixel.
- The enhancement preserves dimensions and spatial identity: output at `(x,y)` derives from the source pixel at `(x,y)` and the explicitly bounded local-background rectangle.
- Constant-color regions become white under normalization; an input darker than its local mean remains darker as gain increases.
- A crop copies pixels without interpolation or content generation.
- Bounds, resource limits, unsupported PNM variants, detected allocation mismatches, and file errors are explicit failures. Foreign allocation exceptions remain a host-runtime boundary. CLI input/output paths with identical spelling are rejected; this is not a proof against filesystem aliases.
- The type guarantees do not establish optical reflection separation, text correctness, or electrical continuity.

### Runtime and backend boundary

Canonical Idriç revision: `2bce7677f513d711875e978bd6f5ad28b9e54d58`.

The host execution target is the maintained Chez backend. `Data.Buffer` and `System.File.Buffer` are inherited foreign-runtime boundaries. Their buffer allocation, byte access, and file writes are trusted primitives; the semantic layer checks lengths and coordinates before invoking them. No RefC, generated-C cleanup, Python image implementation, or neural image generation is used.

## Idriç attempt

Sources: `SchematicRaster.idric`, `Cleanup.idric`, `RasterTests.idric`, and `language-probes/UnicodeMinus.idric`.

Compiler: the canonical revision above was bootstrapped locally with its maintained Chez route. Its version output is `0.8.0-2bce7677f`. Execution host: Linux x86-64. The raster core retained the `.idric` total default; it contains no totality bypass, unchecked proof cast, or postulate. CLI process-exit actions and acceptance actions are explicitly `covering`.

The exact executed build, check, and runtime commands are preserved in [`qualification-commands.txt`](qualification-commands.txt). They are historical command receipts with absolute paths from the observed host, not a portable installation procedure. Runtime logs are in `_/build/checks/` during this working run; the source record below distinguishes their outcomes from photo quality.

## Result or failure

The type-system sketch above was written before source implementation.

- `Cleanup.idric`: compiled through current Idriç to Chez, exit status 0.
- `RasterTests.idric`: compiled through current Idriç to Chez, exit status 0.
- `RasterTests` execution: exit status 0. Passing cases include non-square row-major RGB indexing, exact P6 roundtrip, a whitespace-valued first binary pixel, rejection of truncated/trailing payload, rejection of zero dimensions and unsupported sample format, header limits, rejected out-of-bounds reads/writes, overlapping copy staging, exact crop, maximum-integer origins, deterministic local-mean arithmetic, clipped corner windows, preserved dimensions, and an unchanged source buffer.
- The separate `Assemble.idric` consumer also compiled through the same compiler; its scene/layout acceptance is recorded separately by that consumer.
- `language-probes/UnicodeMinus.idric`: actual `--check` exit status 1 with `Undefined name −`. This is a source-notation capability gap, not a failure of the compiled raster implementation.

Focused logs: `cleanup-build.log`, `raster-tests-build.log`, `raster-tests-run.log`, `assemble-build.log`, and `unicode-minus.log` under `_/build/checks/`.

Photo cleanup remains a visual trial. The available assembly uses cropped sections with visible gutters; it is not seamless geometric registration. Per-channel local-mean contrast is lossy and can retain reflection/dust edges or suppress faint true ink. Passing the raster checks does not change those limitations.

The real first photograph was processed successfully with radius `24`, gain `8`, and noise subtraction `3`. Visual review selected that setting as the first-trial compromise: broad reflection and background texture are reduced, but some faint marks are lost and reflection contours remain. The original reference is retained. No smoothing was added after qualification. The full selected-photo batch, source digests, and output digests are recorded separately by the surrounding task.

## Fallback

None.

## Idriç language work exposed

First observed Idriç capability gap: the canonical source guide requests mathematical Unicode minus, but this exact compiler rejects `left − right`. The accepted program therefore retains the currently supported ASCII subtraction token and uses accepted Unicode multiplication and arrows. This notation exception is explicit; the source remains Idriç and executes through the same compiler.

Smallest plausible language change: recognize Unicode minus in `.idric` mathematical expressions and lower it consistently to the existing subtraction operation, preserving `.idr` compatibility tokenization. This repository records the consumer-shaped probe; compiler ownership remains in `isomorphisms/Idric`.

Acceptance test for the notation change: the existing `UnicodeMinus.idric` probe must typecheck and execute subtraction with positive, negative, and zero results on the revised compiler; an `.idr` compatibility case must retain its existing meaning. No such compiler change is claimed here.

## Evidence boundary

The implemented raster program has exact-compiler compilation and focused host-execution evidence. Its dependent types associate positions with raster dimensions and record coordinate admission. Bulk row copies and integral sums use checked extents and implementation arithmetic, not a whole-memory formal proof. Reflection separation, character identity, recovered electrical connectivity, seamless registration, and physical/user acceptance are not proved. Full photographic reconstruction remains `PARTIAL`, independently of the passing implementation checks. Publication and full-photo outputs have separate receipts owned by the surrounding task.
