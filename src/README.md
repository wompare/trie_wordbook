This is an indexer for wordlists where each word is on separate lines in a text file. The path to the text file needs to be an argument on execution. The <-c> is optinal, and the program will default to asm. The syntax is (using the defaults in the Makefile):
```bash
program <-c> <path/to/text/file>
```

To assemble on 64-bit Linux systems, the gcc-multilib and glibc:i386 packages need to be installed. Note that the glibc:i386 package may not show up in your list if you are using a graphical packet manager such as Synaptic. On Debian based systems, the package can be installed with the following command:

```bash
sudo apt install glibc:i386
```

Compiling and running the program has been tested on the following systems:
- Raspberry Pi 3 Model B+ with Raspberry Pi OS
- Desktop computer, AMD Ryzen 5 1600X, with Ubuntu Mate 21.04
- Lenovo V155, AMD Ryzen 5 3500U, with Windows 10

