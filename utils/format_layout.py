import json
import os

keyboard_layouts = {}
list_layouts = [f for f in os.listdir("./layouts/") if f[-11:] == "layout.json"]
for layout in list_layouts:
    with open("./layouts/"+layout) as file:
        data = json.load(file)
        keyboard_layouts[layout[:-12]] = data
        file.close()

empty = str(input("choose spacer (leave empty for classic four spaces):"))
empty = empty if empty != "" else "    "

available_layouts = keyboard_layouts.keys()
print( "\n[" + ', '.join( [ str(k) for k in available_layouts ] ) + "]")
type_input_text = "please choose valid keyboard layout:\n"
type_layout = str(input(type_input_text))
while type_layout not in available_layouts:
    type_layout = (input(type_input_text))



input_layout = " "
while input_layout != "":
    input_layout = str(input("\nput layout here:"))
    # input_layout = """
    # KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, C(G(KC_LEFT)), KC_NO, KC_NO, C(G(KC_RGHT)), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
    # """

    replace_layers = {
        0:"_BASE",
        1:"_SETTINGS",
        2:"_SYMBOLS",
        3:"_SHORTCUTS",
        4:"_NUMPAD",
        5:"_EXTRAS"
    }


    template = keyboard_layouts[type_layout]
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