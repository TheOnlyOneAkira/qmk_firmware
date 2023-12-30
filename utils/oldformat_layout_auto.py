# keyboard_layouts = {
# "sofle":[
#     [   0,    1,    2,    3,    4,    5, None, None, None, None,    6,    7,    8,    9,   10,   11],
#     [  12,   13,   14,   15,   16,   17, None, None, None, None,   18,   19,   20,   21,   22,   23],
#     [  24,   25,   26,   27,   28,   29, None, None, None, None,   30,   31,   32,   33,   34,   35],
#     [  36,   37,   38,   39,   40,   41,   42, None, None,   43,   44,   45,   46,   47,   48,   49],
#     [None, None,   50,   51,   52,   53,   54, None, None,   55,   56,   57,   58,   59, None, None]
# ]
# }
keyboard_layouts = {
"sofle":[
    [   0,    1,    2,    3,    4,    5, None, None, None, None,    6,    7,    8,    9,   10,   11],
    [  12,   13,   14,   15,   16,   17, None, None, None, None,   18,   19,   20,   21,   22,   23],
    [  24,   25,   26,   27,   28,   29, None, None, None, None,   30,   31,   32,   33,   34,   35],
    [  36,   37,   38,   39,   40,   41,   42, None, None,   43,   44,   45,   46,   47,   48,   49],
    [None, None,   50,   51,   52,   53,   54, None, None,   55,   56,   57,   58,   59, None, None]
]
}

empty = "    "


type = "sofle"
input_layout = """
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, C(G(KC_LEFT)), KC_NO, KC_NO, C(G(KC_RGHT)), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
"""

replace_layers = {
    0:"_BASE",
    1:"_SETTINGS",
    2:"_SYMBOLS",
    3:"_SHORTCUTS",
    4:"_NUMPAD",
    5:"_EXTRAS"
}


template = keyboard_layouts[type]
n_cols = len(template[0])

input_layout = input_layout.replace("  "," ").replace("\t","").replace("\n","")
for k, v in replace_layers.items():
    input_layout = input_layout.replace( "("+str(k), "("+v )
# input_layout = input_layout.replace("KC_TRNS", "_______")
# input_layout = input_layout.replace("KC_NO", "XXXXXXX")

split_layout = input_layout.split(", ")
transposed_template = [ [ split_layout[idx] if idx is not None else empty for idx in row  ] for row in template ]
cols_max_width = [ max([len(row[col_idx]) for row in transposed_template])+2 for col_idx in range(n_cols) ]


string = "LAYOUT(\n"


sep_line = "\t//"
for idx in range(n_cols):
    width = cols_max_width[idx]
    sep_line += "+" + "-" * width
sep_line += "+\n"


for row in transposed_template:
    keys = "\t   "
    for idx in range(n_cols):
        width = cols_max_width[idx]
        v = row[idx]
        end = "," if v != empty else " "
        diff = width - len(v)
        v = " "*(diff//2) + v + " "*(diff//2) + " "*(diff%2)
        keys += v+end
    keys += "\n"
    string += sep_line+keys
string = string[:-2]+"\n"
string += sep_line

last_comma_idx = string.rfind(",")
final_string = string[:last_comma_idx] + " " + string[last_comma_idx+1:]+"),"

print(final_string)

print("end")