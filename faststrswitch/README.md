# Fast String Switch (FSS)

## Switch Table

The switch table consists of four parts:
- Header
- Array Table (AT)
- Index Table (IT)
- Partial String Table (PST)


### Header Table

The header table contains important data for indexing data entries.

Offset | Type  | Description
-------|-------|-----------------------
0000h  | u16   | Modulo Denominator
0002h  | u8    | Block Size (byte)
0003h  | u8    | Index Table Count
0004h  | u16   | Maximum String Length
0006h  | u16   | String Case Count
0008h  | u8    | Array Table Pointer Size (byte)
0009h  | u8    | PST Pointer Size (byte)

### Array Table
`Array Table` is the table of array that stores the pointer of `Index Table`.

**Array Table Entry**
Offset                            | Description
----------------------------------|----------------------------------------------------
$0$                               | Array Size in ($\lceil\log_{256}{D}\rceil$) byte(s)
$\lceil\log_{256}{D}\rceil(n+1)$  | Element #$n$

$S_{e}$: Array Table Element Size<br/>
$n$: Element Index starting from zero for each AT entry<br/>

`Array Table Pointer` differs from `Array Table Entry Element Index`.<br/>
`Array Table Pointer` points every $\lceil\log_{256}{D}\rceil$ bytes of data in Array Table. But `Array Table Entry Element Index`, starting from index 0 of its Table Entry, references the $n$ th element of `Array Table Entry`.

### Index Table

### Partial String Table

$D$: Modulo Denominator<br/>
$n$: Index Table Depth # (Starts from zero)<br/>
$N_{d}$: Total Index Table Depth Count<br/>
$N_{c}$: String Case Count

**Size of Non-final Index Table**
$$\lceil\log_{256}{D}\rceil D$$