all : decrypt encrypt

decrypt : hacl
	gcc decrypt.c -o decrypt -I./hacl-star/dist/gcc-compatible -I./hacl-star/dist/karamel/include -I./hacl-star/dist/karamel/krmllib/dist/minimal ./hacl-star/dist/gcc-compatible/libevercrypt.a

encrypt : hacl
	gcc encrypt.c -o encrypt -I./hacl-star/dist/gcc-compatible -I./hacl-star/dist/karamel/include -I./hacl-star/dist/karamel/krmllib/dist/minimal ./hacl-star/dist/gcc-compatible/libevercrypt.a

hacl :
	cd hacl-star/dist/gcc-compatible/ && ./configure && make
