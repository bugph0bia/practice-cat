package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
)

const help = `Usage: cat [OPTION]... [FILE]..
Concatenate FILE(s) to standard output.

With no FILE, or when FILE is -, read standard input.`

const example = `
Examples:
  cat f - g  Output f's contents, then standard input, then g's contents.
  cat        Copy standard input to standard output.`

const version = `cat (practice of c) v1.0
Written by bugph0bia`

// arguments
type Args struct {
	// option flags
	flagb, flagE, flagn, flags, flagT, flagu, flagv bool
	// target files
	fnames []string
}

// print status
type Status struct {
	// line no
	lno int
	// count of LF repetitions
	lfrep int
	// writer
	writer *bufio.Writer
}

// parse arguments
func parseArgs(args *Args) {
	// extend help message
	flag.CommandLine.Usage = func() {
		o := flag.CommandLine.Output()
		fmt.Fprintln(o, help)
		flag.PrintDefaults()
		fmt.Fprintln(o, example)
	}

	var flagversion, flagA, flage, flagt bool

	flag.BoolVar(&flagversion, "version", false, "output version information and exit")
	flag.BoolVar(&flagA, "A", false, "equivalent to -vET")
	flag.BoolVar(&args.flagb, "b", false, "number nonempty output lines, overrides -n")
	flag.BoolVar(&flage, "e", false, "equivalent to -vE")
	flag.BoolVar(&args.flagE, "E", false, "display $ at end of each line")
	flag.BoolVar(&args.flagn, "n", false, "number all output lines")
	flag.BoolVar(&args.flags, "s", false, "supress repeated empty output lines")
	flag.BoolVar(&flagt, "t", false, "equivalent to -vT")
	flag.BoolVar(&args.flagT, "T", false, "displa TAB characters as ^I")
	flag.BoolVar(&args.flagu, "u", false, "(ignored)")
	flag.BoolVar(&args.flagv, "v", false, "use ^ and M- notation, except for LFD and TAB")
	flag.Parse()

	// output varsion
	if flagversion {
		fmt.Println(version)
		os.Exit(0)
	}

	// override
	if args.flagb {
		args.flagn = false
	}
	// complex
	if flagA {
		args.flagv, args.flagE, args.flagT = true, true, true
	}
	if flage {
		args.flagv, args.flagE = true, true
	}
	if flagt {
		args.flagv, args.flagT = true, true
	}

	args.fnames = flag.Args()

	// stdin if no target file
	if len(args.fnames) == 0 {
		args.fnames = append(args.fnames, "-")
	}
}

// convert and print character
func printChar(ch byte, args *Args, stat *Status) {
	// -s
	// squeeze blank
	if args.flags && ch == '\n' && stat.lfrep >= 2 {
		return
	}

	// -n, -b
	if (stat.lno == 0 || stat.lfrep > 0) && (args.flagn || (args.flagb && ch != '\n')) {
		stat.lno++
		fmt.Fprintf(stat.writer, "%6d\t", stat.lno)
	}

	// -E
	// add $ at EOL
	if args.flagE && ch == '\n' {
		fmt.Fprint(stat.writer, "$")
	}

	// -T, -v
	// convert to ^ notation (only TAB)
	if args.flagT && ch == '\t' {
		fmt.Fprint(stat.writer, "^I")
	} else if args.flagv && ch != '\t' && ch != '\n' {
		if (ch & 0b1000_0000) != 0 {
			fmt.Fprint(stat.writer, "M-")
		}
		ch2 := ch &^ 0b1000_0000

		// convert to ^ notation
		if ch2 >= 0x00 && ch2 <= 0x1F {
			fmt.Fprint(stat.writer, "^")
			fmt.Fprintf(stat.writer, "%s", string([]byte{(ch2 + '@')}))
		} else if ch2 == 0x7F {
			fmt.Fprint(stat.writer, "^?")
		} else {
			fmt.Fprintf(stat.writer, "%s", string([]byte{ch2}))
		}
	} else {
		fmt.Fprintf(stat.writer, "%s", string([]byte{ch}))
	}

	// count repean LF
	if ch == '\n' {
		stat.lfrep++
	} else {
		stat.lfrep = 0
	}
}

func main() {
	// parse arguments
	var args Args
	parseArgs(&args)

	// loop target files
	var stat Status
	stat.writer = bufio.NewWriterSize(os.Stdout, 1024*1024)
	for _, fname := range args.fnames {
		var file *os.File
		if len(fname) == 0 || fname == "-" {
			file = os.Stdin
		} else {
			f, err := os.Open(fname)
			if err != nil {
				fmt.Fprintln(os.Stderr, "file open error")
				os.Exit(1)
			}
			defer f.Close()
			file = f
		}

		// print characters
		buff := make([]byte, 1)
		for {
			_, err := file.Read(buff)
			if err == io.EOF {
				break
			}
			if err != nil {
				fmt.Fprintln(os.Stderr, "file read error")
				os.Exit(1)
			}
			printChar(buff[0], &args, &stat)
		}
	}
	stat.writer.Flush()
}
