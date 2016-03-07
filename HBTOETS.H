/***
*       Toetsen.h
*       Keyboard scancodes.
*       Copyright (c) 1992 H.G.Burgstra.
*/

// Cursor verplaatsingstoetsen
#define K_UP            -72     // Uparrow, Ctrl-E
#define K_DOWN          -80     // Dnarrow, Ctrl-X
#define K_LEFT          -75     // Leftarrow, Ctrl-S
#define K_RIGHT         -77     // Rightarrow, Ctrl-D
#define K_HOME          -71     // Home, Ctrl-A
#define K_END           -79     // End, Ctrl-F
#define K_PGUP          -73     // PgUp, Ctrl-R
#define K_PGDN          -81     // PgDn, Ctrl-C
#define K_CTRL_LEFT    -115     // Ctrl-Leftarrow, Ctrl-Z
#define K_CTRL_RIGHT   -116     // Ctrl-Rightarrow, Ctrl-B
#define K_CTRL_HOME    -119     // Ctrl-Home, Ctrl-]
#define K_CTRL_END     -117     // Ctrl-End, Ctrl-W
#define K_CTRL_PGUP    -132     // Ctrl-PgUp, Ctrl-Hyphen
#define K_CTRL_PGDN    -118     // Ctrl-PgDn, Ctrl-^
#define K_CTRL_RET       10     // Ctrl-Return

#define K_ESC            27     // Esc, Ctrl-[
#define K_RETURN         13     // Return, Ctrl-M
#define K_ENTER          13     // Enter, Ctrl-M


// Editing keys
#define K_INS           -82     // Ins, Ctrl-V
#define K_DEL           -83     // Del, Ctrl-G
#define K_BS              8     // Backspace, Ctrl-H
#define K_CTRL_BS       127     // Ctrl-Backspace
#define K_TAB             9     // Tab, Ctrl-I
#define K_SH_TAB        -15     // Shift-Tab


// Control keys
#define K_CTRL_A        1       // Ctrl-A, Home
#define K_CTRL_B        2       // Ctrl-B, Ctrl-Rightarrow
#define K_CTRL_C        3       // Ctrl-C, PgDn, Ctrl-ScrollLock
#define K_CTRL_D        4       // Ctrl-D, Rightarrow
#define K_CTRL_E        5       // Ctrl-E, Uparrow
#define K_CTRL_F        6       // Ctrl-F, End
#define K_CTRL_G        7       // Ctrl-G, Del
#define K_CTRL_H        8       // Ctrl-H, Backspace
#define K_CTRL_I        9       // Ctrl-I, Tab
#define K_CTRL_J        10      // Ctrl-J
#define K_CTRL_K        11      // Ctrl-K
#define K_CTRL_L        12      // Ctrl-L
#define K_CTRL_M        13      // Ctrl-M, Return
#define K_CTRL_N        14      // Ctrl-N
#define K_CTRL_O        15      // Ctrl-O
#define K_CTRL_P        16      // Ctrl-P
#define K_CTRL_Q        17      // Ctrl-Q
#define K_CTRL_R        18      // Ctrl-R, PgUp
#define K_CTRL_S        19      // Ctrl-S, Leftarrow
#define K_CTRL_T        20      // Ctrl-T
#define K_CTRL_U        21      // Ctrl-U
#define K_CTRL_V        22      // Ctrl-V, Ins
#define K_CTRL_W        23      // Ctrl-W, Ctrl-End
#define K_CTRL_X        24      // Ctrl-X, Dnarrow
#define K_CTRL_Y        25      // Ctrl-Y
#define K_CTRL_Z        26      // Ctrl-Z, Ctrl-Leftarrow


// Alt keys
#define K_ALT_A         -30     // Alt-A
#define K_ALT_B         -48     // Alt-B
#define K_ALT_C         -46     // Alt-C
#define K_ALT_D         -32     // Alt-D
#define K_ALT_E         -18     // Alt-E
#define K_ALT_F         -33     // Alt-F
#define K_ALT_G         -34     // Alt-G
#define K_ALT_H         -35     // Alt-H
#define K_ALT_I         -23     // Alt-I
#define K_ALT_J         -36     // Alt-J
#define K_ALT_K         -37     // Alt-K
#define K_ALT_L         -38     // Alt-L
#define K_ALT_M         -50     // Alt-M
#define K_ALT_N         -49     // Alt-N
#define K_ALT_O         -24     // Alt-O
#define K_ALT_P         -25     // Alt-P
#define K_ALT_Q         -16     // Alt-Q
#define K_ALT_R         -19     // Alt-R
#define K_ALT_S         -31     // Alt-S
#define K_ALT_T         -20     // Alt-T
#define K_ALT_U         -22     // Alt-U
#define K_ALT_V         -47     // Alt-V
#define K_ALT_W         -17     // Alt-W
#define K_ALT_X         -45     // Alt-X
#define K_ALT_Y         -21     // Alt-Y
#define K_ALT_Z         -44     // Alt-Z
#define K_ALT_1        -120     // Alt-1
#define K_ALT_2        -121     // Alt-2
#define K_ALT_3        -122     // Alt-3
#define K_ALT_4        -123     // Alt-4
#define K_ALT_5        -124     // Alt-5
#define K_ALT_6        -125     // Alt-6
#define K_ALT_7        -126     // Alt-7
#define K_ALT_8        -127     // Alt-8
#define K_ALT_9        -128     // Alt-9
#define K_ALT_0        -129     // Alt-0

// Function keys
#define K_F1            -59     // F1, Ctrl-\
#define K_F2            -60     // F2
#define K_F3            -61     // F3
#define K_F4            -62     // F4
#define K_F5            -63     // F5
#define K_F6            -64     // F6
#define K_F7            -65     // F7
#define K_F8            -66     // F8
#define K_F9            -67     // F9
#define K_F10           -68     // F10
#define K_F11          -133     // F11
#define K_F12          -134     // F12

// Control-function keys
#define K_CTRL_F1       -94     // Ctrl-F1
#define K_CTRL_F2       -95     // Ctrl-F2
#define K_CTRL_F3       -96     // Ctrl-F4
#define K_CTRL_F4       -97     // Ctrl-F3
#define K_CTRL_F5       -98     // Ctrl-F5
#define K_CTRL_F6       -99     // Ctrl-F6
#define K_CTRL_F7      -100     // Ctrl-F7
#define K_CTRL_F8      -101     // Ctrl-F8
#define K_CTRL_F9      -102     // Ctrl-F9
#define K_CTRL_F10     -103     // Ctrl-F10
#define K_CTRL_F11     -137     // Ctrl-F11
#define K_CTRL_F12     -138     // Ctrl-F12

// Alt-function keys
#define K_ALT_F1       -104     // Alt-F1
#define K_ALT_F2       -105     // Alt-F2
#define K_ALT_F3       -106     // Alt-F3
#define K_ALT_F4       -107     // Alt-F4
#define K_ALT_F5       -108     // Alt-F5
#define K_ALT_F6       -109     // Alt-F6
#define K_ALT_F7       -110     // Alt-F7
#define K_ALT_F8       -111     // Alt-F8
#define K_ALT_F9       -112     // Alt-F9
#define K_ALT_F10      -113     // Alt-F10
#define K_ALT_F11      -139     // Alt-F11
#define K_ALT_F12      -140     // Alt-F12

// Shift-function keys
#define K_SH_F1         -84     // Shift-F1
#define K_SH_F2         -85     // Shift-F2
#define K_SH_F3         -86     // Shift-F3
#define K_SH_F4         -87     // Shift-F4
#define K_SH_F5         -88     // Shift-F5
#define K_SH_F6         -89     // Shift-F6
#define K_SH_F7         -90     // Shift-F7
#define K_SH_F8         -91     // Shift-F8
#define K_SH_F9         -92     // Shift-F9
#define K_SH_F10        -93     // Shift-F10
#define K_SH_F11       -135     // Shift-F11
#define K_SH_F12       -136     // Shift-F12

