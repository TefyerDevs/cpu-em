

rom_size = 256

# bin 
bin_file = bytearray([0xea] * rom_size)

# mov rax, 60
bin_file[0x0F] = 0x58 # mov
bin_file[0x10] = 0x2F # address = rax
bin_file[0x11] = 0x3c # value = 60

# mov rdi, 0
bin_file[0x12] = 0x58 # mov
bin_file[0x13] = 0x1F # address = rdi
bin_file[0x14] = 0x00 # value = 0

#jumps after syscall
bin_file[0x15] = 0x43 # jmp
bin_file[0x16] = 0x19 # address = 0x19

# syscall
bin_file[0x18] = 0x4c # syscall


with open("rom.bin", 'wb') as file:
    file.write(bin_file)
