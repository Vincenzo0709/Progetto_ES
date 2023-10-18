all:
	make -C ram clean
	make -C ram
	cp ram/bin/ram.mem /mnt/c/Users/Giuseppe/Downloads/DICE/DICE.srcs/sources_1/imports/mem
	
	md5sum ram/bin/ram.bin | awk '{print $$1}' | ./util > rom/inc/img.h
	du -b ram/bin/ram.bin | awk '{print "\nsize_t len = "$$1";"}' >> rom/inc/img.h
	
	make -C rom clean
	make -C rom
	cp rom/bin/rom.mem /mnt/c/Users/Giuseppe/Downloads/DICE/DICE.srcs/sources_1/imports/mem

clean:
	make -C rom clean
	make -C ram clean

run:
	head -c $(SIZE) ram/bin/ram.bin > img.bin
	md5sum img.bin | awk '{print $$1}' | ./util > ram/inc/img.h
	du -b img.bin | awk '{print "\nsize_t len = "$$1";"}' >> ram/inc/img.h
	make
	/opt/riscv/bin/riscv64-unknown-elf-readelf -s ram/bin/ram.elf | \
		awk '/hashTrue|hash|cdi/ {print "p 0x"$$2" 16"} END {print "q"}' | make -C fpga run
	md5sum img.bin
	/opt/riscv/bin/riscv64-unknown-elf-readelf -s ram/bin/ram.elf | awk '/hashTrue|hash|cdi/'

.PHONY: all clean run
