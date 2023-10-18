_vectors_start = 0x00100000;

ENTRY(_start)

MEMORY
{
	/* RAM(rwx): ORIGIN = 0x00100000, LENGTH = 64K */
	ROM(rwx):  ORIGIN = 0x70000000, LENGTH = 8K
}

SECTIONS
{
	.text :
	{
		obj/crt0.o(.text)
		*(.text)
	} >ROM

	.stack : ALIGN(4)
	{
		. += 256;
		. = ALIGN(LENGTH(ROM));
		_estack = .;
	} >ROM
}
