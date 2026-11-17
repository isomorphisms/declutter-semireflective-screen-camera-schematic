#!/bin/sh
# No private photo input or network access. Requires a C11 compiler.
set -eu
here=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT HUP INT TERM
"${CC:-cc}" -std=c11 -O2 -Wall -Wextra -Wconversion -Werror "$here/paper_stitch.c" -o "$work/paper-stitch"
"$work/paper-stitch" --self-test
printf 'P6\n4 4\n255\nABCDEFGHIJKLMNOPQRSTUVWXabcdefghijklmnopqrstuvwx' > "$work/first.ppm"
printf 'P6\n4 4\n255\n0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL' > "$work/second.ppm"
cat > "$work/good.tsv" <<PLAN
canvas 6 4
source 1 $work/first.ppm 0 0 4 4 1000000 0 0 0 1000000 0 0 0
source 2 $work/second.ppm 2 0 6 4 1000000 0 -2000000 0 1000000 0 0 0
join 1 2 x 3 1
PLAN
"$work/paper-stitch" "$work/good.tsv" "$work/result"
for file in .ppm .source-id.pgm .source-x.pgm .source-y.pgm; do test -s "$work/result$file"; done
if "$work/paper-stitch" "$work/good.tsv" "$work/result" >/dev/null 2>&1; then echo 'FAIL: overwritten output'; exit 1; fi
sed '/^join /d' "$work/good.tsv" > "$work/nojoin.tsv"
if "$work/paper-stitch" "$work/nojoin.tsv" "$work/nojoin" >/dev/null 2>&1; then echo 'FAIL: missing join admitted'; exit 1; fi
if test -e "$work/nojoin.ppm"; then echo 'FAIL: invalid plan wrote output'; exit 1; fi
# A huge central offset would fold a synthetic sheet over itself and must be rejected.
cat >> "$work/good.tsv" <<'MESH'
mesh 1 0 0 0 0 0 0 0 0 32768 0 0 0 0 0 0 0 0 0
MESH
if "$work/paper-stitch" "$work/good.tsv" "$work/fold" >/dev/null 2>&1; then echo 'FAIL: folded-over mesh admitted'; exit 1; fi
if test -e "$work/fold.ppm"; then echo 'FAIL: invalid mesh wrote output'; exit 1; fi
# Three-photo layout: two distinct qualified overlaps, no triple pixel ownership.
cp "$work/first.ppm" "$work/third.ppm"
cat > "$work/three.tsv" <<PLAN
canvas 8 4
source 1 $work/first.ppm 0 0 4 4 1000000 0 0 0 1000000 0 0 0
source 2 $work/second.ppm 2 0 6 4 1000000 0 -2000000 0 1000000 0 0 0
source 3 $work/third.ppm 4 0 8 4 1000000 0 -4000000 0 1000000 0 0 0
join 1 2 x 3 1
join 2 3 x 5 1
PLAN
"$work/paper-stitch" "$work/three.tsv" "$work/three" >/dev/null
test -s "$work/three.source-id.pgm"
# An extra overlapping 4x4 exposure would create an ambiguous triple owner.
sed "s@source 3 $work/third.ppm 4 0 8 4 1000000 0 -4000000@source 3 $work/third.ppm 2 0 6 4 1000000 0 -2000000@" \
  "$work/three.tsv" > "$work/triple.tsv"
if "$work/paper-stitch" "$work/triple.tsv" "$work/triple" >/dev/null 2>&1; then echo 'FAIL: triple-overlap accepted'; exit 1; fi
if test -e "$work/triple.ppm"; then echo 'FAIL: triple-overlap wrote output'; exit 1; fi
printf '%s\n' 'PASS: C11 compile, 2-/3-photo synthetic P6 output, provenance, overwrite, missing/triple joins, foldover rejection'
