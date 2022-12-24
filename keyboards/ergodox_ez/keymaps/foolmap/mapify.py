#!/usr/bin/env python3
import argparse
import os
import re

FN_KEY_REGEX = re.compile(r'(OSL|TG|OSM|MEH|HYPR|CAG)\((.*)\)')
LAYOUT_START_MATCHER = re.compile(r'\[([A-Z]+)\] = LAYOUT_ergodox\(')
MULTILINE_COMMENT_LINE = re.compile(r'^(/| )\*(/)?.*')

LAYERS = {
    'base': 'basic',
    'symb': 'symbol',
    'mdia': 'media',
}


def process_layout(layout, layout_name, index) -> str:
    layout_name = LAYERS.get(layout_name.lower(), layout_name)
    l = [abbrev(c, i) for i, c in enumerate(layout)]
    return f'''/* Keymap {index}: {layout_name.capitalize()} Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |{l[0]:<8}|{l[1]:^6}|{l[2]:^6}|{l[3]:^6}|{l[4]:^6}|{l[5]:^6}|{l[6]:^6}|           |{l[38]:^6}|{l[39]:^6}|{l[40]:^6}|{l[41]:^6}|{l[42]:^6}|{l[43]:^6}|{l[44]:>8}|
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |{l[7]:<8}|{l[8]:^6}|{l[9]:^6}|{l[10]:^6}|{l[11]:^6}|{l[12]:^6}|{l[13]:^6}|           |{l[45]:^6}|{l[46]:^6}|{l[47]:^6}|{l[48]:^6}|{l[49]:^6}|{l[50]:^6}|{l[51]:>8}|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |{l[14]:<8}|{l[15]:^6}|{l[16]:^6}|{l[17]:^6}|{l[18]:^6}|{l[19]:^6}|------|           |------|{l[52]:^6}|{l[53]:^6}|{l[54]:^6}|{l[55]:^6}|{l[56]:^6}|{l[57]:>8}|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |{l[20]:<8}|{l[21]:^6}|{l[22]:^6}|{l[23]:^6}|{l[24]:^6}|{l[25]:^6}|{l[26]:^6}|           |{l[58]:^6}|{l[59]:^6}|{l[60]:^6}|{l[61]:^6}|{l[62]:^6}|{l[63]:^6}|{l[64]:>8}|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |{l[27]:^6}|{l[28]:^6}|{l[29]:^6}|{l[30]:^6}|{l[31]:^6}|                                       |{l[65]:^6}|{l[66]:^6}|{l[67]:^6}|{l[68]:^6}|{l[69]:^6}|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |{l[32]:^6}|{l[33]:^6}|       |{l[70]:^6}|{l[71]:^6}|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |{l[35]:^6}|{l[36]:^6}|{l[34]:^6}|       |{l[72]:^6}|{l[74]:^6}|{l[75]:^6}|
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |{l[37]:^6}|       |{l[73]:^6}|      |      |
 *                                 `--------------------'       `--------------------'
 */
'''


def build_layout_maps(input_file):
    layout_keys_matcher = re.compile(r'\[[A-Z]+\] = LAYOUT_ergodox\((.*)\),')

    keymaps = {}
    paren_stack = None
    in_layout = False
    layout_name = None

    with open(input_file) as fd:
        layout = ''

        for l in fd:
            l = l.strip()

            if len(l) == 0 or l.startswith('//') or MULTILINE_COMMENT_LINE.match(l) is not None:
                continue

            if m := LAYOUT_START_MATCHER.match(l):
                layout_name = m.group(1)
                in_layout = True
            if not in_layout:
                continue

            for c in l:
                layout += c
                if c == '(':
                    if paren_stack is None:
                        paren_stack = []
                    paren_stack.append('(')
                elif c == ')':
                    if paren_stack is None:
                        raise Exception('Unbalanced parenthesis')
                    paren_stack.pop()
                elif paren_stack is not None and len(paren_stack) == 0:
                    in_layout = False
                    keymaps[layout_name] = layout
                    layout = ''
                    paren_stack = None

    layout_maps = {}
    for name, keymap in keymaps.items():
        if m := layout_keys_matcher.match(keymap):
            layout_keys = m.group(1)
            layout_maps[name] = ''.join(layout_keys.split(' ')).split(',')

    return layout_maps


def output_map(input_file):
    layout_maps = build_layout_maps(input_file)

    comment_line = re.compile(r'^(/| )\*(/)?.*')

    paren_stack = None
    in_layout = False
    is_comment = False
    layout_index = 0
    layout = None

    output_file = f'{input_file}.tmp'

    with open(input_file) as ifd, open(output_file, 'w') as ofd:
        for l in ifd:

            if comment_line.match(l):
                is_comment = True
                continue
            else:
                # If the previous line was a comment skip printing for this loop
                # as we're probably at the end of a multiline comment
                if is_comment:
                    is_comment = False
                    continue

            layout_start_match = LAYOUT_START_MATCHER.match(l)
            if layout_start_match is not None:
                layout_name = layout_start_match.group(1)
                in_layout = True
                layout = process_layout(layout_maps[layout_name], layout_name, layout_index)
                ofd.write(f'{layout}\n')
                layout_index += 1

            if in_layout:
                for c in l:
                    if not layout:
                        raise Exception('Layout is unknown')
                    layout += c
                    if c == '(':
                        if paren_stack is None:
                            paren_stack = []
                        paren_stack.append('(')
                    elif c == ')':
                        if paren_stack is None:
                            raise Exception('Unbalanced parenthesis')
                        paren_stack.pop()
                    elif paren_stack is not None and len(paren_stack) == 0:
                        in_layout = False
                        paren_stack = None

            ofd.write(l)

    os.rename(output_file, input_file)


def get_max_len(index):
    # Longer key, mostly on the edge.
    if index in [0, 7, 14, 20, 26, 57]:
        return 9
    return 6


SYMBOLS = {
    'QUOT': "'",
    'COMM': ',',
    'DOT': '.',
    'SCLN': ';',
    'EXLM': '!',
    'AT': '@',
    'HASH': '#',
    'DLR': '$',
    'PERC': '%',
    'CIRC': '^',
    'AMPR': '&',
    'ASTR': '*',
    'LCBR': '{',
    'RCBR': '}',
    'LPRN': '(',
    'RPRN': ')',
    'EQL': '=',
    'SLSH': '/',
    'MINS': '-',
    'UNDS': '_',
    'LBRC': '[',
    'RBRC': ']',
    'TILD': '~',
    'PIPE': '|',
    'GRV': '`',
    'BSLS': '\\',
    'PLUS': '+',
    'QK_BOOT': 'BOOT',
}

COMBINATIONS = {
    'MEH',
    'HYPR',
    'CAG',
}

FN_MAP = {
    'OSL': '@',
    'TG': '!',
    'OSM': '^',
}


def abbrev(k, index):
    max_len = get_max_len(index)

    if k in SYMBOLS:
        return SYMBOLS[k][:max_len]

    if k.startswith('KC_'):
        k = k[3:][:max_len]
        return SYMBOLS.get(k, k)

    if k.startswith('MOD_'):
        return k[4:][:max_len]

    if set(k) == {'_'}:
        return ''

    fn_key = FN_KEY_REGEX.match(k)
    if fn_key is None:
        return k[:max_len]

    fn, key = fn_key.groups()
    if '_' in key:
        _, _, key_full = key.partition('_')
        key = key_full.split('_')[-1]

    if fn in COMBINATIONS:
        return f'{fn}+{key}'

    fn = FN_MAP.get(fn, fn)
    return f'{fn}{key}'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--file', default='keymap.c')

    args = parser.parse_args()

    output_map(args.file)


if __name__ == '__main__':
    main()
