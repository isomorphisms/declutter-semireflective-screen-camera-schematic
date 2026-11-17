/* Paper schematic mosaic reference, C11/POSIX; no optical claims.
 * Input: P6 photographs converted without enhancement. Output: single observed
 * nearest-neighbour source pixel or grey missing-data marker, plus source maps.
 */
#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PHOTOS 8
#define MAX_JOINS 16
#define MAX_SIDE 32768
#define MAX_PIXELS 12000000
#define UNIT 1000000LL
#define MESH_UNIT 256LL

typedef struct { int width, height; uint8_t *rgb; } Image;
typedef struct {
    int id, x0, y0, x1, y1, mesh_enabled;
    char path[512];
    int64_t h[8]; /* canvas -> native: numerator first six, denominator last two + UNIT */
    int64_t mesh[3][3][2]; /* 1/256 native pixel: (row,column,axis) */
    Image image;
} Photo;
typedef struct { int first, second, axis, cut, gap, hits; } Join;
typedef struct {
    int width, height, count, join_count;
    Photo photos[MAX_PHOTOS]; Join joins[MAX_JOINS];
} Plan;
typedef struct {
    int width, height;
    uint8_t *rgb, *ids, *xs, *ys; /* x and y big-endian 16-bit */
} Mosaic;

static void image_free(Image *im) { free(im->rgb); im->rgb = NULL; }
static void mosaic_free(Mosaic *m) {
    free(m->rgb); free(m->ids); free(m->xs); free(m->ys);
    memset(m, 0, sizeof *m);
}
static void plan_free(Plan *p) {
    for (int i = 0; i < p->count; ++i) image_free(&p->photos[i].image);
}
static int64_t rounded_div(int64_t n, int64_t d) { /* d > 0, bounded inputs */
    return n < 0 ? -((-n + d / 2) / d) : (n + d / 2) / d;
}
static int number(const char *s, int64_t lo, int64_t hi, int64_t *out) {
    if (!s || !*s) return 0;
    char *end = NULL;
    errno = 0;
    intmax_t n = strtoimax(s, &end, 10);
    if (errno || !end || *end || n < lo || n > hi) return 0;
    *out = (int64_t)n;
    return 1;
}
static int tokenize(char *line, char *items[], int maximum) {
    int count = 0;
    char *save = NULL;
    for (char *s = strtok_r(line, " \t\r\n", &save); s; s = strtok_r(NULL, " \t\r\n", &save)) {
        if (*s == '#') break;
        if (count == maximum) return -1;
        items[count++] = s;
    }
    return count;
}
static int read_plan(const char *filename, Plan *p) {
    FILE *f = fopen(filename, "r");
    if (!f) return fprintf(stderr, "cannot open plan: %s\n", filename), 0;
    char *line = NULL; size_t cap = 0; int line_no = 0, canvas_seen = 0, ok = 1;
    while (getline(&line, &cap, f) >= 0) {
        ++line_no;
        char *t[32]; int n = tokenize(line, t, 32); int64_t v[19];
        if (n == 0) continue;
        if (n < 0) { ok = 0; break; }
        if (!strcmp(t[0], "canvas") && n == 3 && !canvas_seen) {
            ok = number(t[1], 1, MAX_SIDE, &v[0]) && number(t[2], 1, MAX_SIDE, &v[1]);
            if (ok && v[0] * v[1] <= MAX_PIXELS) {
                p->width = (int)v[0]; p->height = (int)v[1]; canvas_seen = 1;
            } else ok = 0;
        } else if (!strcmp(t[0], "source") && n == 15 && canvas_seen && p->count < MAX_PHOTOS) {
            Photo *s = &p->photos[p->count];
            ok = strlen(t[2]) < sizeof s->path && number(t[1], 1, 254, &v[0]);
            for (int i = 0; ok && i < p->count; ++i) if (p->photos[i].id == v[0]) ok = 0;
            for (int i = 0; ok && i < 4; ++i) ok = number(t[3 + i], 0, MAX_SIDE, &v[i + 1]);
            for (int i = 0; ok && i < 8; ++i)
                ok = number(t[7 + i], -2000000000, 2000000000, &v[i + 5]);
            if (ok) {
                s->id = (int)v[0]; strcpy(s->path, t[2]);
                s->x0 = (int)v[1]; s->y0 = (int)v[2];
                s->x1 = (int)v[3]; s->y1 = (int)v[4];
                for (int i = 0; i < 8; ++i) s->h[i] = v[i + 5];
                ok = s->x0 < s->x1 && s->y0 < s->y1 &&
                     s->x1 <= p->width && s->y1 <= p->height;
                const int linear[] = {0, 1, 3, 4};
                for (int i = 0; ok && i < 4; ++i)
                    if (s->h[linear[i]] > 4000000 || s->h[linear[i]] < -4000000) ok = 0;
                if (s->h[6] < -10000 || s->h[6] > 10000 ||
                    s->h[7] < -10000 || s->h[7] > 10000) ok = 0;
                /* A projective pole in the covered rectangle must be rejected. */
                for (int j = 0; ok && j < 4; ++j) {
                    int x = j & 1 ? s->x1 - 1 : s->x0;
                    int y = j & 2 ? s->y1 - 1 : s->y0;
                    int64_t den = UNIT + s->h[6] * x + s->h[7] * y;
                    if (den < UNIT / 8 || den > UNIT * 8) ok = 0;
                }
                if (ok) ++p->count;
            }
        } else if (!strcmp(t[0], "mesh") && n == 20 && canvas_seen) {
            ok = number(t[1], 1, 254, &v[0]);
            for (int i = 0; ok && i < 18; ++i) ok = number(t[i + 2], -32768, 32768, &v[i + 1]);
            Photo *s = NULL;
            for (int i = 0; i < p->count; ++i) if (p->photos[i].id == v[0]) s = &p->photos[i];
            if (!s || s->mesh_enabled) ok = 0;
            if (ok) {
                for (int row = 0; row < 3; ++row)
                    for (int col = 0; col < 3; ++col)
                        for (int axis = 0; axis < 2; ++axis)
                            s->mesh[row][col][axis] = v[1 + row * 6 + col * 2 + axis];
                s->mesh_enabled = 1;
            }
        } else if (!strcmp(t[0], "join") && n == 6 && p->join_count < MAX_JOINS) {
            Join *j = &p->joins[p->join_count];
            ok = number(t[1], 1, 254, &v[0]) && number(t[2], 1, 254, &v[1]) &&
                 number(t[4], 0, MAX_SIDE, &v[2]) && number(t[5], 0, 256, &v[3]);
            if (ok && (!strcmp(t[3], "x") || !strcmp(t[3], "y")) && v[0] != v[1]) {
                j->first = (int)v[0]; j->second = (int)v[1];
                j->axis = !strcmp(t[3], "y"); j->cut = (int)v[2]; j->gap = (int)v[3];
                for (int i = 0; i < p->join_count; ++i)
                    if ((p->joins[i].first == j->first && p->joins[i].second == j->second) ||
                        (p->joins[i].first == j->second && p->joins[i].second == j->first)) ok = 0;
                if (ok) ++p->join_count;
            } else ok = 0;
        } else ok = 0;
        if (!ok) break;
    }
    if (ferror(f)) ok = 0;
    fclose(f); free(line);
    if (!canvas_seen || !p->count) ok = 0;
    if (!ok) fprintf(stderr, "invalid plan (near line %d)\n", line_no);
    return ok;
}
static int ppm_token(FILE *f, char *buffer, size_t size) {
    int c;
    do {
        c = fgetc(f);
        if (c == '#') { while ((c = fgetc(f)) != '\n' && c != EOF) {} }
    } while (c == '#' || c == '\n' || c == '\r' || c == ' ' || c == '\t');
    if (c == EOF) return 0;
    size_t i = 0;
    while (c != EOF && c != '\n' && c != '\r' && c != ' ' && c != '\t') {
        if (i + 1 >= size) return 0;
        buffer[i++] = (char)c;
        c = fgetc(f);
    }
    buffer[i] = '\0';
    return i != 0;
}
static int read_ppm(const char *name, Image *im) {
    FILE *f = fopen(name, "rb"); if (!f) return 0;
    char tok[64]; int64_t w, h, max;
    int ok = ppm_token(f, tok, sizeof tok) && !strcmp(tok, "P6") &&
             ppm_token(f, tok, sizeof tok) && number(tok, 1, MAX_SIDE, &w) &&
             ppm_token(f, tok, sizeof tok) && number(tok, 1, MAX_SIDE, &h) &&
             ppm_token(f, tok, sizeof tok) && number(tok, 255, 255, &max) &&
             w * h <= MAX_PIXELS;
    if (ok) {
        size_t sz = (size_t)(w * h * 3);
        im->rgb = malloc(sz); ok = im->rgb && fread(im->rgb, 1, sz, f) == sz && fgetc(f) == EOF;
        if (ok) { im->width = (int)w; im->height = (int)h; }
    }
    fclose(f); if (!ok) image_free(im);
    return ok;
}
static int64_t mesh_axis(const Photo *s, int x, int y, int axis) {
    if (!s->mesh_enabled) return 0;
    int width = s->x1 - s->x0 - 1, height = s->y1 - s->y0 - 1;
    if (width <= 0 || height <= 0) return s->mesh[0][0][axis];
    int64_t px = (int64_t)(x - s->x0) * 2 * UNIT / width;
    int64_t py = (int64_t)(y - s->y0) * 2 * UNIT / height;
    int cx = px >= UNIT ? 1 : 0, cy = py >= UNIT ? 1 : 0;
    int64_t u = px - cx * UNIT, v = py - cy * UNIT;
    int64_t a = (s->mesh[cy][cx][axis] * (UNIT-u) + s->mesh[cy][cx+1][axis] * u) / UNIT;
    int64_t b = (s->mesh[cy+1][cx][axis] * (UNIT-u) + s->mesh[cy+1][cx+1][axis] * u) / UNIT;
    return (a * (UNIT-v) + b * v) / UNIT;
}
/* Continuous native coordinate in 1/256 pixel; integer rounding happens once. */
static int project_256(const Photo *s, int x, int y, int64_t *xx, int64_t *yy) {
    int64_t den = UNIT + s->h[6] * x + s->h[7] * y;
    if (den < UNIT / 8 || den > UNIT * 8) return 0;
    int64_t nx = s->h[0] * x + s->h[1] * y + s->h[2];
    int64_t ny = s->h[3] * x + s->h[4] * y + s->h[5];
    *xx = rounded_div(nx * MESH_UNIT, den) + mesh_axis(s, x, y, 0);
    *yy = rounded_div(ny * MESH_UNIT, den) + mesh_axis(s, x, y, 1);
    return 1;
}
/* Reject orientation reversal/crease foldover inside the 3x3 correction mesh.
 * This is NOT a line-continuity or registration accuracy acceptance test. */
static int warp_admitted(const Photo *s) {
    if (s->x1 - s->x0 < 3 || s->y1 - s->y0 < 3) return !s->mesh_enabled;
    int xs[3] = {s->x0, (s->x0 + s->x1 - 1)/2, s->x1 - 1};
    int ys[3] = {s->y0, (s->y0 + s->y1 - 1)/2, s->y1 - 1};
    int64_t gx[3][3], gy[3][3];
    for (int y = 0; y < 3; ++y) for (int x = 0; x < 3; ++x)
        if (!project_256(s, xs[x], ys[y], &gx[y][x], &gy[y][x])) return 0;
    int orientation = 0;
    for (int y = 0; y < 2; ++y) for (int x = 0; x < 2; ++x) {
        for (int corner = 0; corner < 2; ++corner) {
            int ax = x + corner, ay = y + corner;
            int bx = x + 1 - corner, by = y + corner;
            int cx = x + corner, cy = y + 1 - corner;
            int64_t rx = gx[by][bx] - gx[ay][ax];
            int64_t ry = gy[by][bx] - gy[ay][ax];
            int64_t dx = gx[cy][cx] - gx[ay][ax];
            int64_t dy = gy[cy][cx] - gy[ay][ax];
            int64_t det = rx*dy - ry*dx;
            int sign = det > 0 ? 1 : det < 0 ? -1 : 0;
            if (!sign || (orientation && sign != orientation)) return 0;
            orientation = sign;
        }
    }
    return 1;
}
static int source_sample(const Photo *s, int x, int y, int *sx, int *sy) {
    if (x < s->x0 || x >= s->x1 || y < s->y0 || y >= s->y1) return 0;
    int64_t xx, yy;
    if (!project_256(s, x, y, &xx, &yy)) return -1;
    xx = rounded_div(xx, MESH_UNIT); yy = rounded_div(yy, MESH_UNIT);
    if (xx < 0 || yy < 0 || xx >= s->image.width || yy >= s->image.height) return 0;
    *sx = (int)xx; *sy = (int)yy; return 1;
}
static int allocate_mosaic(Mosaic *m, int width, int height) {
    size_t count = (size_t)width * (size_t)height;
    m->width = width; m->height = height;
    m->rgb = malloc(3 * count); m->ids = calloc(count, 1);
    m->xs = malloc(2 * count); m->ys = malloc(2 * count);
    if (!m->rgb || !m->ids || !m->xs || !m->ys) return 0;
    memset(m->rgb, 232, 3 * count); memset(m->xs, 255, 2 * count); memset(m->ys, 255, 2 * count);
    return 1;
}
static int render(Plan *p, Mosaic *m) {
    for (int i = 0; i < p->count; ++i)
        if (!warp_admitted(&p->photos[i]))
            return fprintf(stderr, "projective/mesh warp folds over or has invalid geometry\n"), 0;
    if (!allocate_mosaic(m, p->width, p->height)) return 0;
    for (int y = 0; y < p->height; ++y) for (int x = 0; x < p->width; ++x) {
        const Photo *candidate[3]; int native_x[3], native_y[3], count = 0;
        for (int k = 0; k < p->count; ++k) {
            int a, b, hit = source_sample(&p->photos[k], x, y, &a, &b);
            if (hit < 0) return fprintf(stderr,"invalid projective denominator\n"), 0;
            if (hit > 0) {
                if (count == 2) return fprintf(stderr,"triple overlap: explicit grouping required\n"), 0;
                candidate[count] = &p->photos[k]; native_x[count] = a; native_y[count] = b;
                ++count;
            }
        }
        int select = count ? 0 : -1;
        if (count == 2) {
            Join *join = NULL;
            for (int k = 0; k < p->join_count; ++k) {
                Join *j = &p->joins[k];
                if ((j->first == candidate[0]->id && j->second == candidate[1]->id) ||
                    (j->first == candidate[1]->id && j->second == candidate[0]->id)) { join = j; break; }
            }
            if (!join) return fprintf(stderr,"unqualified photo overlap\n"), 0;
            int axis_value = join->axis ? y : x;
            if (axis_value == join->cut) join->hits++;
            int lower = join->cut - join->gap / 2;
            int upper = join->cut + (join->gap + 1) / 2;
            if (axis_value >= lower && axis_value < upper) select = -1;
            else {
                int preferred = axis_value < lower ? join->first : join->second;
                select = candidate[0]->id == preferred ? 0 : 1;
            }
        }
        if (select >= 0) {
            size_t index = (size_t)y * (size_t)p->width + (size_t)x;
            const Photo *s = candidate[select];
            int sx = native_x[select], sy = native_y[select];
            size_t src = ((size_t)sy * (size_t)s->image.width + (size_t)sx) * 3;
            memcpy(m->rgb + index * 3, s->image.rgb + src, 3);
            m->ids[index] = (uint8_t)s->id;
            m->xs[2 * index] = (uint8_t)(sx >> 8); m->xs[2 * index + 1] = (uint8_t)sx;
            m->ys[2 * index] = (uint8_t)(sy >> 8); m->ys[2 * index + 1] = (uint8_t)sy;
        }
    }
    for (int k = 0; k < p->join_count; ++k)
        if (!p->joins[k].hits) return fprintf(stderr,"join does not cross a shared observation\n"), 0;
    return 1;
}
static int write_exclusive(const char *path, const char *magic, int width, int height,
                           int max_value, const uint8_t *bytes, size_t count) {
    int fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd < 0) return 0;
    FILE *f = fdopen(fd, "wb");
    if (!f) { close(fd); unlink(path); return 0; }
    int ok = fprintf(f, "%s\n%d %d\n%d\n", magic, width, height, max_value) > 0 &&
             fwrite(bytes, 1, count, f) == count;
    if (fclose(f)) ok = 0;
    if (!ok) unlink(path);
    return ok;
}
static int write_mosaic(const char *prefix, const Mosaic *m) {
    const char *suffixes[] = {".ppm", ".source-id.pgm", ".source-x.pgm", ".source-y.pgm"};
    const uint8_t *buffers[] = {m->rgb, m->ids, m->xs, m->ys};
    size_t count = (size_t)m->width * (size_t)m->height;
    size_t lengths[] = {3 * count, count, 2 * count, 2 * count};
    char names[4][1024];
    for (int i = 0; i < 4; ++i) {
        if (snprintf(names[i], sizeof names[i], "%s%s", prefix, suffixes[i]) >= (int)sizeof names[i]) return 0;
        /* Refuse all preexisting outputs before beginning a four-file write. */
        if (!access(names[i], F_OK)) return fprintf(stderr, "output exists: %s\n", names[i]), 0;
    }
    for (int i = 0; i < 4; ++i) {
        if (!write_exclusive(names[i], i ? "P5" : "P6", m->width, m->height,
                             i >= 2 ? 65535 : 255, buffers[i], lengths[i])) {
            for (int j = 0; j < i; ++j) unlink(names[j]);
            return fprintf(stderr, "failed to write output %s\n", names[i]), 0;
        }
    }
    return 1;
}
static int source_replay(const Plan *p, const Mosaic *m) {
    for (int y = 0; y < m->height; ++y) for (int x = 0; x < m->width; ++x) {
        size_t i = (size_t)y * (size_t)m->width + (size_t)x;
        if (!m->ids[i]) {
            if (m->xs[2*i] != 255 || m->xs[2*i+1] != 255 ||
                m->ys[2*i] != 255 || m->ys[2*i+1] != 255 ||
                m->rgb[3*i] != 232 || m->rgb[3*i+1] != 232 || m->rgb[3*i+2] != 232) return 0;
            continue;
        }
        const Photo *s = NULL;
        for (int k = 0; k < p->count; ++k) if (p->photos[k].id == m->ids[i]) s = &p->photos[k];
        if (!s) return 0;
        int sx = m->xs[2*i] * 256 + m->xs[2*i+1], sy = m->ys[2*i] * 256 + m->ys[2*i+1];
        if (sx >= s->image.width || sy >= s->image.height) return 0;
        if (memcmp(&m->rgb[3*i], &s->image.rgb[3*((size_t)sy*(size_t)s->image.width+(size_t)sx)], 3)) return 0;
    }
    return 1;
}
static int self_test(void) {
    Plan p = {0}; p.width = 6; p.height = 4; p.count = 2; p.join_count = 1;
    Photo *a = &p.photos[0], *b = &p.photos[1];
    a->id = 1; a->x1 = 4; a->y1 = 4; a->h[0] = a->h[4] = UNIT;
    b->id = 2; b->x0 = 2; b->x1 = 6; b->y1 = 4;
    b->h[0] = b->h[4] = UNIT; b->h[2] = -2 * UNIT;
    a->image.width = b->image.width = 4; a->image.height = b->image.height = 4;
    a->image.rgb = calloc(4 * 4, 3); b->image.rgb = calloc(4 * 4, 3);
    if (!a->image.rgb || !b->image.rgb) return 0;
    for (int i = 0; i < 16; ++i) { a->image.rgb[i*3] = (uint8_t)i; b->image.rgb[i*3] = (uint8_t)(100+i); }
    p.joins[0] = (Join){.first=1,.second=2,.axis=0,.cut=3,.gap=1};
    Mosaic m = {0}; int ok = render(&p, &m) && source_replay(&p, &m);
    if (ok) {
        size_t left = 1 * 6 + 1, gap = 1 * 6 + 3, right = 1 * 6 + 4;
        ok = m.ids[left] == 1 && m.ids[gap] == 0 && m.ids[right] == 2 &&
             m.rgb[3*left] == 5 && m.rgb[3*right] == 106;
        m.rgb[3*right] ^= 1;
        ok = ok && !source_replay(&p, &m); /* changed source sample is detected */
    }
    mosaic_free(&m);
    /* No implicit join is permitted. */
    p.join_count = 0; ok = ok && !render(&p, &m); mosaic_free(&m);
    /* Mesh displacement at the central node changes native sample, not its RGB. */
    p.count = 1; p.width = p.height = 5; a->x1 = a->y1 = 5;
    a->mesh_enabled = 1; a->mesh[1][1][0] = MESH_UNIT;
    int sx = -1, sy = -1;
    ok = ok && source_sample(a, 2, 2, &sx, &sy) == 1 && sx == 3 && sy == 2;
    a->mesh[1][1][0] = 32768;
    ok = ok && !warp_admitted(a); /* a foldover must not be silently flattened */
    a->mesh[1][1][0] = MESH_UNIT;
    a->h[6] = -(UNIT/2); /* zero at x=2 */
    ok = ok && source_sample(a, 2, 2, &sx, &sy) == -1;
    plan_free(&p);
    if (ok) puts("PASS: source replay, seam gutter, negative replay, missing join, mesh, foldover, pole");
    return ok;
}
int main(int argc, char **argv) {
    if (argc == 2 && !strcmp(argv[1], "--self-test")) return self_test() ? 0 : 1;
    if (argc != 3) {
        fprintf(stderr,"usage: paper-stitch PLAN.tsv OUTPUT_PREFIX | --self-test\n"); return 2;
    }
    Plan p = {0}; Mosaic mosaic = {0};
    int ok = read_plan(argv[1], &p);
    for (int i = 0; ok && i < p.count; ++i)
        if (!read_ppm(p.photos[i].path, &p.photos[i].image))
            { fprintf(stderr, "cannot decode P6 source: %s\n", p.photos[i].path); ok = 0; }
    if (ok) ok = render(&p, &mosaic);
    if (ok) ok = source_replay(&p, &mosaic);
    if (ok) ok = write_mosaic(argv[2], &mosaic);
    if (ok) printf("PASS: source-replayed provisional mosaic %d x %d (geometry NOT ACCEPTED)\n", p.width, p.height);
    mosaic_free(&mosaic); plan_free(&p);
    return ok ? 0 : 1;
}
