#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <getopt.h>


const std::string HELP =
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

const std::string VERSION =
    "cat (practice of c) v1.0\n"
    "Written by bugph0bia";


// arguments
typedef struct {
    // option flags
    bool b, E, n, s, T, u, v;
    // target files
    std::vector<std::string> fnames;
} Args;

// print status
typedef struct {
    int lno;    // line no
    int lfrep;  // count of LF repetitions
} status;


// parse arguments
void parse_args(Args &args, const int argc, char *argv[]) {
    struct option longopts[] = {
        {"help",             no_argument, NULL, 'H'},
        {"version",          no_argument, NULL, 'V'},
        {"show-all",         no_argument, NULL, 'A'},
        {"number-nonblank",  no_argument, NULL, 'b'},
        {"show-ends",        no_argument, NULL, 'E'},
        {"number",           no_argument, NULL, 'n'},
        {"squeeze-blank",    no_argument, NULL, 's'},
        {"show-tabs",        no_argument, NULL, 'T'},
        {"show-nonprinting", no_argument, NULL, 'v'},
        {NULL,               0,           NULL, 0  },
    };
    int opt;
    while ((opt = getopt_long(argc, argv, "AbeEnstTvu", longopts, NULL)) != -1) {
        switch (opt) {
        case 'H':
            std::cout << HELP;
            std::exit(0);
        case 'V':
            std::cout << VERSION;
            std::exit(0);
        case 'A':
            args.v = args.E = args.T = true;
            break;
        case 'b':
            args.b = true;
            break;
        case 'e':
            args.v = args.E = true;
            break;
        case 'E':
            args.E = true;
            break;
        case 'n':
            args.n = true;
            break;
        case 's':
            args.s = true;
            break;
        case 't':
            args.v = args.T = true;
            break;
        case 'T':
            args.T = true;
            break;
        case 'v':
            args.v = true;
            break;
        case 'u':
            break;
        default:
            exit(1);
        }
    }
    // override
    if (args.b) {
        args.n = false;
    }

    for (int i = optind; i < argc; i++) {
        args.fnames.push_back(argv[i]);
    }
    // stdin if no target file
    if (args.fnames.empty()) {
        args.fnames.push_back("-");
    }
}

// convert and print character
void print_char(char ch, Args &args, status &stat) {
    // -s
    // squeeze blank
    if (args.s && ch == '\n' && stat.lfrep >= 2) return;

    // -n, -b
    // print line number
    if ((stat.lno == 0 || stat.lfrep > 0) && (args.n || (args.b && ch != '\n'))) {
        std::cout << std::setw(6) << ++stat.lno << "\t";
    }

    // -E
    // add $ at EOL
    if (args.E && ch == '\n') {
        std::cout << "$";
    }

    // -T, -v
    // convert to ^ notation (only TAB)
    if (args.T && ch == '\t') {
        std::cout << "^I";
    }
    else if (args.v && ch != '\t' && ch != '\n') {
        // add prefix M- notation
        if (ch & 0x80) {
            std::cout << "M-";
        }
        char ch2 = ch & ~0x80;

        // convert to ^ notation
        if (ch2 >= 0x00 && ch2 <= 0x1F) {
            ch2 += '@';
            std::cout << "^" << ch2;
        }
        else if (ch2 == 0x7F) {
            std::cout << "^?";
        }
        else {
            std::cout << ch2;
        }
    }
    else {
        std::cout << ch;
    }

    // count repeat LF
    if (ch == '\n') stat.lfrep++;
    else stat.lfrep = 0;
}

// main
int main (int argc, char *argv[]) {
    // parse arguments
    Args args = {0};
    parse_args(args, argc, argv);

    // loop target files
    status stat = {0};
    for (std::string &fname : args.fnames) {
        // set target file pointer
        std::unique_ptr<std::basic_istream<char>> ist;
        if (fname == "" || fname == "-") {
            ist.reset(&std::cin);
        }
        else {
            ist = std::make_unique<std::ifstream>(fname, std::ios::in | std::ios::binary);
            if (ist->fail()) {
                std::cerr << "file open error";
                return 1;
            }
        }

        // print characters
        char ch;
        for (;;) {
            ist->read(&ch, 1);
            if (ist->eof()) break;
            print_char(ch, args, stat);
        }

        // not close the stream if stream is stdin
        if (&*ist == &std::cin) {
            ist.release();
        }
    }
}
