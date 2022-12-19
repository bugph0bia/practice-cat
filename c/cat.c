#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


const char *HELP =
    "Usage: cat [OPTION]... [FILE]...\n"
    "Concatenate FILE(s) to standard output.\n"
    "\n"
    "With no FILE, or when FILE is -, read standard input.\n"
    "\n"
    "  -A, --show-all           equivalent to -vET\n"
    "  -b, --number-nonblank    number nonempty output lines, overrides -n\n"
    "  -e                       equivalent to -vE\n"
    "  -E, --show-ends          display $ at end of each line\n"
    "  -n, --number             number all output lines\n"
    "  -s, --squeeze-blank      suppress repeated empty output lines\n"
    "  -t                       equivalent to -vT\n"
    "  -T, --show-tabs          display TAB characters as ^I\n"
    "  -u                       (ignored)\n"
    "  -v, --show-nonprinting   use ^ and M- notation, except for LFD and TAB\n"
    "      --help     display this help and exit\n"
    "      --version  output version information and exit\n"
    "\n"
    "Examples:\n"
    "  cat f - g  Output f\'s contents, then standard input, then g\'s contents.\n"
    "  cat        Copy standard input to standard output.";

const char *VERSION =
    "cat (practice of c) v1.0\n"
    "Written by bugph0bia";


// arguments
typedef struct {
    // option flags
    bool b, E, n, s, T, u, v;
    // target files
    char *fnames[256];
} Args;

// print status
typedef struct {
    int lno;    // line no
    int lfrep;  // count of LF repetitions
} Status;


// parse arguments
void parse_args(Args *args, int argc, char *argv[]) {
    int fpos = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            puts(HELP);
            exit(0);
        }
        else if (strcmp(argv[i], "--version") == 0) {
            puts(VERSION);
            exit(0);
        }
        else if (strcmp(argv[i], "-A") == 0 || strcmp(argv[i], "--show-all") == 0) {
            args->v = args->E = args->T = true;
        }
        else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--number-nonblank") == 0) {
            args->b = true;
        }
        else if (strcmp(argv[i], "-e") == 0) {
            args->v = args->E = true;
        }
        else if (strcmp(argv[i], "-E") == 0 || strcmp(argv[i], "--show-ends") == 0) {
            args->E = true;
        }
        else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
            args->n = true;
        }
        else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--squeeze-blank") == 0) {
            args->s = true;
        }
        else if (strcmp(argv[i], "-t") == 0) {
            args->v = args->T = true;
        }
        else if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--show-tabs") == 0) {
            args->T = true;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--show-nonprinting") == 0) {
            args->v = true;
        }
        else if (strcmp(argv[i], "-u") == 0) {
            ;
        }
        else {
            args->fnames[fpos++] = argv[i];
        }
    }

    // override
    if (args->b) {
        args->n = false;
    }
    // stdin if no target file
    if (fpos == 0) {
        args->fnames[0] = "-";
    }
}

// convert and print character
void print_char(char ch, Args *args, Status *stat) {
    // -s
    // squeeze blank
    if (args->s && ch == '\n' && stat->lfrep >= 2) return;

    // -n, -b
    // print line number
    if ((stat->lno == 0 || stat->lfrep > 0) && (args->n || (args->b && ch != '\n'))) {
        printf("%6d\t", ++stat->lno);
    }

    // -E
    // add $ at EOL
    if (args->E && ch == '\n') {
        putchar('$');
    }

    // -T, -v
    // convert to ^ notation (only TAB)
    if (args->T && ch == '\t') {
        printf("^I");
    }
    else if (args->v && ch != '\t' && ch != '\n') {
        // add prefix M- notation
        if (ch & 0x80) {
            printf("M-");
        }
        char ch2 = ch & ~0x80;

        // convert to ^ notation
        if (ch2 >= 0x00 && ch2 <= 0x1F) {
            putchar('^');
            putchar(ch2 + '@');
        }
        else if (ch2 == 0x7F) {
            printf("^?");
        }
        else {
            putchar(ch2);
        }
    }
    else {
        putchar(ch);
    }

    // count repeat LF
    if (ch == '\n') stat->lfrep++;
    else stat->lfrep = 0;
}

// main
int main (int argc, char *argv[]) {
    // parse arguments
    Args args = {0};
    parse_args(&args, argc, argv);

    // loop target files
    Status stat = {0};
    for (int fi = 0; args.fnames[fi] != NULL; fi++) {
        // set target file pointer
        char *fname = args.fnames[fi];
        FILE *fp = NULL;
        if (strlen(fname) == 0 || strcmp(fname, "-") == 0) {
            fp = stdin;
        }
        else {
            if ((fp = fopen(fname, "r")) == NULL) {
                fputs("file open error", stderr);
                return 1;
            }
        }

        // print characters
        char ch;
        while (fread(&ch, 1, 1, fp) > 0) {
            print_char(ch, &args, &stat);
        }

        // file close
        if (fp && fp != stdin) {
            fclose(fp);
        }
    }
}
