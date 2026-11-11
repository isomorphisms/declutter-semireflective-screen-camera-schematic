# Program attempt: output path admission

Status: PASS on the qualified Linux/Chez host; broader photographic fidelity PARTIAL

## Purpose

Repair the executed companion-output/input collisions without changing optical
or geometric processing. This session now owns the existing Earth path-admission
repair at the user's request. No equivalent open repair/PR was found; isolated
worktree starts at dd3224a044d163c2b0f41d2ed6c4ee5d7f3176a1.

## Intended behavior

Each command lists every read dependency and every primary/companion output.
Before image processing/writing, admit regular source files and physically
resolved, pairwise-distinct prospective destinations. Every destination must
be new. Existing regular files, hard links, symlinks (including dangling ones),
directories and special nodes are rejected without opening them for reading.
The actual writer must exclusively create a new file, never truncate one.

Fresh-only output is deliberate. Retaining implicit replacement would require
mutable inode identity checks and still leave a check/use overwrite race. With
new outputs, any pre-existing inode is ineligible, so hard-link comparisons are
unnecessary. Reruns use fresh stems/directories. No automatic deletion/force flag.

## Type-system sketch

### Values and domains

Raw path text, regular source paths, prospective output names, physically
resolved filesystem names, ordered complete read/write sets, bounded byte
buffers, and exclusive FILE handles. Input identity is not string identity.

### Types and signatures

`admit_sources : List Text → IO (Either Text ())`

`admit_run : List Text → List Text → IO (Either Text ())`

`write_new_buffer : Text → Buffer → Int → IO (Either Text ())`

`write_new_text : Text → Text → IO (Either Text ())`

Pure path-string admission rejects empty/NUL/newline/tab and unbounded names.
Pure duplicate checks apply to resolved output names. Effects inspect metadata,
resolve links, exclusively create, write and close. No image algorithm in helpers.

### Actions and effects

RunPaths uses escaped argument lists for the qualified host's GNU realpath,
dirname and test metadata operations. No composed shell programs. `test -f`,
`-e`, and `-L` inspect metadata; inherited System.File.exists is unsuitable
because it opens Read and can miss dangling links/block on FIFOs. Unavailable
metadata services or unresolved parents fail closed.

FreshFiles uses the maintained Chez/C FILE-handle boundary, libc fopen mode wbx
and fclose. The inherited Mode type lacks exclusive create. The new narrow FFI
uses the same libc6 naming already present in the pinned base library; no C
image processor, extra compiled shim, or backend substitution is introduced.
Buffer extents are checked, handles closed on errors, and fclose errors reported.

### Laws, invariants, and errors

Static unsafe read/write or write/write aliases are rejected before any output
creation. Each writer independently refuses an existing final name. Even a name
inserted after preflight cannot cause truncation or following of an existing
symlink. Sources and prior outputs are immutable under these writers.

This is not a multi-file transaction: I/O failure or external namespace mutation
after an earlier output was created can leave a new incomplete bundle. It must
report failure, never PASS; originals remain safe. Atomic all-or-none bundle
publication would require a directory/manifest commit boundary and is a separate
interface change. Tests must distinguish this limitation from static-collision
rejection. Do not claim protection against an adversary replacing parent
directories or against deliberate writes through external code.

### Runtime and backend boundary

Qualified Linux x86-64 / Chez10.4.1 / glibc / GNU coreutils9.7. Compiler pin
isomorphisms/Idric@2bce7677f513d711875e978bd6f5ad28b9e54d58, existing maintained
edric bootstrap, explicit Chez. Other hosts/backends are unqualified, not assumed.

## Idriç attempt

Sources: RunPaths.idric, FreshFiles.idric, command admission and P6 writer changes.
Preserve existing CollisionTests and extend its adversaries rather than weakening
its expected rejection/no-new-output/input-digest conditions.

## Result or failure

All producers and suites compile and execute through the pinned Chez route.
The original13 rejected-collision cases pass; the expanded suite has24 passing
rejections, four positive commands and their byte/input comparison. Direct path
tests have21 PASS records including summary. Existing raster34/registration46
records pass. Six real-photo output/map byte comparisons pass against the matching
baseline pipeline stages; original and baseline hash checks remain unchanged.

First source-test failures were a list-cons precedence expression and using
reserved `partial` as a variable; diagnostics retained and corrected. A preliminary
standalone FreshFiles probe lacked main; its shell exit0 is not acceptance.
The old production binaries fail the extended suite as expected. The initial
unmasked-vs-masked photo comparison fails as expected; frame identity was then
confirmed and the matching masked comparison passes. See docs/path-admission-v1.md
and evidence/path-admission-v1 for exact commands, exits and digests.

## Fallback

None.

## Idriç language work exposed

Inherited file Mode lacks exclusive create and close-status reporting. A future
maintained file API should expose a new-file capability and checked close.
Acceptance: existing file/symlink/hard-link/dangling-link refuse without truncation;
late-creation race refuses; regular fresh binary/text output closes successfully.

## Evidence boundary

No photographic cleanup improvement is implied. Existing label loss remains a
separate red requirement. Only file admission/input preservation is this repair.
