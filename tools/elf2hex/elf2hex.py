'''
File: bin2hex.py
Project: tools
Created Date: Thursday July 9th 2020
Author: Ronan (ronan.lashermes@inria.fr)
-----
Last Modified: Monday, 24th August 2020 2:20:33 pm
Modified By: Ronan (ronan.lashermes@inria.fr>)
-----
Copyright (c) 2020 INRIA
'''

import click
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import NoteSection, SymbolTableSection, Section
from elftools.elf.segments import Segment

@click.command()
@click.option('--input', help='Path to input file')
@click.option('--wide', default=16, help='Number of bytes per line')
@click.option('--output', default='f.hex', help='Path to output file')



def read_elf_file(input, wide, output):
    e = ELFFile(open(input, 'rb'))
    accumulator = bytearray()
    # for s in e.iter_sections():
    for seg in e.iter_segments():
        accumulator = extend_with_segment(accumulator, seg)

    whole_string = gen_string(accumulator, wide)
    # write to output file
    with open(output, "w") as hex_file:
        hex_file.write(whole_string)
    

def extend_with_segment(accumulator, segment):
    start_addr = segment['p_paddr']
    mem_size = segment['p_memsz']
    end_addr = start_addr + mem_size
    data = segment.data()
    file_size = len(data)
    end_copy_addr = start_addr + file_size
    

    # while len(accumulator) < end_addr:
        # accumulator += bytearray(1)
    accumulator += bytearray(end_addr - len(accumulator))

    # print("Accumulator len = %i, start_addr = 0x%x, end_addr = 0x%x" %(len(accumulator), start_addr, end_addr))
    # print("Data len = %i" %(len(data)))
    
    for add in range(start_addr, end_copy_addr):
        accumulator[add] = data[add-start_addr]

    for add in range(end_copy_addr, end_addr):
        accumulator[add] = 0
    
    return accumulator

def gen_string(byte_data, wide):
    out_string = ""
    counter = 1
    # print(type(byte_data))
    bd = bytes(byte_data)
    for b in bd:
        
        s = "%02x" % b
        if counter % wide == 0:
            out_string += s + '\n'
        else:
            out_string += s + ' '
        counter += 1

    out_string += '\n\n'
    return out_string

if __name__ == '__main__':
    read_elf_file()
    