Here is an example output of moo_parser, when invoked as:

    ./moo-booth -limit=1 00.MOO.gz

```
File MOO Chunk:
  Version: 1
  Test Count: 10000
  CPU type: 88

==== Test #0 (671 bytes) ====
Name: "add byte [ss:bp+di-64h], cl"
Initial CPU State:
  Registers:
    ax    = 52A1 (21153)
    bx    = E724 (59172)
    cx    = 81C8 (33224)
    dx    = F0F7 (61687)
    cs    = 31ED (12781)
    ss    = 1D03 (7427)
    ds    = 0258 (600)
    es    = CCC3 (52419)
    sp    = BF76 (49014)
    bp    = 2608 (9736)
    si    = CB21 (52001)
    di    = 2729 (10025)
    ip    = 02B6 (694)
    flags = F452 (62546)
  RAM entries: 5
    32186 = 00 (0)
    32187 = 4B (75)
    32188 = 9C (156)
    32189 = 90 (144)
    21CFD = 14 (20)
Final CPU State:
  Registers:
    ip    = 02B9 (697)
    flags = F482 (62594)
  RAM entries: 1
    21CFD = DC (220)
```
