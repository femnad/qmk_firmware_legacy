#!/usr/bin/env python3
import argparse
from collections import defaultdict
from dataclasses import dataclass
import re
from typing import Dict, List
import yaml

BLANK_KEY = '_'
CANONICAL_BLANK = '_' * 7
DEFAULT_CONFIG_FILE = 'foolmap.yml'
DEFAULT_FUNCTIONS_FILE = 'fn.c'
DEFAULT_OUTPUT_FILE = 'keymap.c'
ENUM_INDENT = 2
INCLUDES = [
    '#include QMK_KEYBOARD_H',
    '#include "version.h"',
]
KEYMAP_DEFINITION = 'const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {'
LAYOUT_INDENT = 8
LAYOUT_MACRO = 'LAYOUT_moonlander'
MOD_REGEX = re.compile(r'([lr](alt|ctl|gui|sft))')
MULTI_KEY_REGEX = re.compile(r'(os[lm])\(([a-z]+)\)')
MODIFIED_KEY_REGEX = re.compile(r'([rl](alt|ctl|gui|sft)\()+([a-z_]+)+\)+')
NON_KC_KEYS = {
    'reset',
}
ONE_SHOT_LAYER_KEY = re.compile(r'osl\(([a-z]+)\)')
ONE_SHOT_MODIFIER_KEY = re.compile(r'osm\(([a-z]+)\)')
ROW_PADDINGS = {3: {5: 2}, 4: {5: 2}, 5: {0: -3, 3: -2, 5: 3}}
TABLE_PADDING = 2


@dataclass
class Config:
    layouts: Dict[str, List[str]]
    custom_keys: List[str]


def maybe_mod_prefix(key: str):
    mod_match = MOD_REGEX.match(key)
    if not mod_match:
        return key
    return f'mod_{mod_match.group(1)}'


@dataclass
class LayouterArgs:
    config_file: str
    functions_file: str
    output_file: str


class Layouter:
    def __init__(self, args: LayouterArgs):
        self.args = args
        self.config = self.read_config()

    def read_config(self) -> Config:
        with open(self.args.config_file) as f:
            config_dict = yaml.load(f, Loader=yaml.SafeLoader)
            return Config(**config_dict)

    def base_canonicalize(self, key: str):
        if key in NON_KC_KEYS:
            return key

        if key in self.config.custom_keys:
            return key

        if key == BLANK_KEY:
            return CANONICAL_BLANK

        if multi_key_match := MULTI_KEY_REGEX.match(key):
            fn, key = multi_key_match.groups()
            key = maybe_mod_prefix(key)
            return f'{fn}({key})'

        if modified_key_match := MODIFIED_KEY_REGEX.match(key):
            modified_key = modified_key_match.groups()[-1]
            return key.replace(modified_key, f'kc_{modified_key}')

        return f'kc_{key}'

    def canonicalize(self, key: str) -> str:
        return self.base_canonicalize(key).upper()

    def symbolize_modified_key(self, key: str) -> str:
        keys = re.split(r'\(|\)', key)
        keys = [k for k in keys if k]
        modifiers = [k[1] for k in keys[:-1]]
        combi = modifiers + [keys[-1]]
        return '-'.join(combi)

    def symbolize(self, key: str) -> str:
        if osl_key := ONE_SHOT_LAYER_KEY.match(key):
            layer = osl_key.group(1)
            return f'@{layer}'
        elif osm_key := ONE_SHOT_MODIFIER_KEY.match(key):
            modifier = osm_key.group(1)
            return f'^{modifier}'
        elif MODIFIED_KEY_REGEX.match(key):
            return self.symbolize_modified_key(key)
        return key

    def includes(self, output):
        for include in INCLUDES:
            output.write(f'{include}\n')
        output.write('\n')

    def definitions(self, output):
        for index, layout in enumerate(self.config.layouts.keys()):
            layout = layout.upper()
            output.write(f'#define {layout} {index}\n')
        output.write('\n')

    def custom_keycodes(self, output):
        output.write('enum custom_keycodes {\n')
        for index, keycode in enumerate(self.config.custom_keys):
            output.write(' ' * ENUM_INDENT)
            keycode = keycode.upper()
            output.write(keycode)
            if index == 0:
                output.write(' = ML_SAFE_RANGE')
            output.write(',\n')
        output.write('};\n\n')

    def get_layout_table(self, layout_tables: Dict[str, List[List[str]]]) -> str:
        col_widths = defaultdict(lambda: 0)
        padded_tables = {}

        output = ''

        for layout, rows in layout_tables.items():
            new_rows = []
            for row_index, row in enumerate(rows):
                new_row = []
                if row_index not in ROW_PADDINGS:
                    new_rows.append(row)
                    continue
                row_padding = ROW_PADDINGS[row_index]
                for col_index, col in enumerate(row):
                    if col_index not in row_padding:
                        new_row.append(col)
                        continue
                    col_padding = row_padding[col_index]
                    padding = ['' for _ in range(abs(col_padding))]
                    if col_padding > 0:
                        new_row.append(col)
                        new_row += padding
                    else:
                        new_row += padding
                        new_row.append(col)
                new_rows.append(new_row)
            padded_tables[layout] = new_rows

        for _, rows in padded_tables.items():
            for row in rows:
                for i, col in enumerate(row):
                    cur_col_len = len(col)
                    max_col_len = col_widths[i]
                    if cur_col_len > max_col_len:
                        col_widths[i] = cur_col_len

        num_layouts = len(padded_tables.keys())
        for layout_index, (layout, rows) in enumerate(padded_tables.items()):
            output += f'Layer: {layout.upper()}\n'
            for w in col_widths.values():
                output += '+'
                output += '-' * (w+TABLE_PADDING)
            output += '+\n'
            for row_index, row in enumerate(rows):
                col = ''
                for i, col in enumerate(row):
                    col_len = col_widths[i] + TABLE_PADDING
                    sep = '|' if col or row[i - 1] else ' '
                    output += sep
                    printed_col = col.upper().replace('_', '')
                    output += f'{printed_col:^{col_len}}'
                last_sep = '|' if col else ' '
                output += f'{last_sep}\n'
                col_i = 0
                for col_i, w in enumerate(col_widths.values()):
                    btm = '+' if row[col_i] or row[col_i - 1] else ' '
                    sep = '-' if row[col_i] else ' '
                    output += btm
                    output += sep * (w + TABLE_PADDING)
                last_bind = '+' if row[col_i] else ' '
                output += f'{last_bind}\n'
            if layout_index < num_layouts - 1:
                output += '\n'

        commented_output = []
        lines = output.split('\n')
        num_lines = len(lines)
        for i, line in enumerate(lines):
            line = line.rstrip()
            if i == 0:
                prefix = '/* '
            elif i == num_lines - 1:
                prefix = ' */\n'
            elif line:
                prefix = ' * '
            else:
                prefix = ' *'
            commented_output.append(f'{prefix}{line}')

        return '\n'.join(commented_output)

    def layouts(self, output):
        layouts = {}
        layout_table = {}
        col_widths = defaultdict(dict)

        for layout, keys in self.config.layouts.items():
            rows = []
            table_rows = []
            for row in keys:
                row = row.split()
                table_row = [self.symbolize(key) for key in row]
                table_rows.append(table_row)
                row = [self.canonicalize(key) for key in row]
                rows.append(row)
            layout_table[layout] = table_rows
            layouts[layout] = rows

        layout_table = self.get_layout_table(layout_table)
        output.write(layout_table)

        for layout, rows in layouts.items():
            for row in rows:
                for index, col in enumerate(row):
                    col_len = len(col)
                    if col_widths[layout].get(index, 0) < col_len:
                        col_widths[layout][index] = col_len

        output.write(f'{KEYMAP_DEFINITION}\n\n')

        num_layouts = len(layouts.keys())
        for layout_index, (layout, rows) in enumerate(layouts.items()):
            output.write(f'[{layout.upper()}] = {LAYOUT_MACRO}(\n')

            for row_index, row in enumerate(rows):
                output.write(' ' * LAYOUT_INDENT)
                num_rows = len(rows)
                num_cols = len(row)

                for index, col in enumerate(row):
                    suffix = ', ' if index < num_cols - 1 else ','
                    padding = col_widths[layout][index] + len(suffix)

                    if index == num_cols - 1:
                        padding = 0
                        if row_index == num_rows - 1:
                            suffix = ''

                    col = f'{col}{suffix}'
                    output.write(f'{col:<{padding}}')
                output.write('\n')

            output.write('),\n')

            if layout_index < num_layouts - 1:
                output.write('\n')

        output.write('};\n\n')

    def functions(self, output):
        with open(self.args.functions_file) as f:
            for l in f:
                output.write(l)

    def output(self):
        with open(self.args.output_file, 'w') as f:
            self.includes(f)
            self.definitions(f)
            self.custom_keycodes(f)
            self.layouts(f)
            self.functions(f)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', '--config_file', default=DEFAULT_CONFIG_FILE)
    parser.add_argument('-f', '--output_file', default=DEFAULT_OUTPUT_FILE)
    parser.add_argument('-n', '--functions_file', default=DEFAULT_FUNCTIONS_FILE)

    args = parser.parse_args()
    args = LayouterArgs(**args.__dict__)

    layouter = Layouter(args)
    layouter.output()


if __name__ == '__main__':
    main()
