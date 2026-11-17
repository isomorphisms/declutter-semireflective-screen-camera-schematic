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
printf '%s\n' 'PASS: C11 compile, synthetic P6 input/output, no overwrite, missing join, foldover rejection'
