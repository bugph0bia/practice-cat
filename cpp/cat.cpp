#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


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
    int fpos = 0;
    for (int i = 1; i < argc; i++) {
        std::string cur_arg = argv[i];
        if (cur_arg == "--help") {
            std::cout << HELP << std::endl;
            std::exit(0);
        }
        else if (cur_arg == "--version") {
            std::cout << VERSION << std::endl;
            std::exit(0);
        }
        else if (cur_arg == "-A" || cur_arg == "--show-all") {
            args.v = args.E = args.T = true;
        }
        else if (cur_arg == "-b" || cur_arg == "--number-nonblank") {
            args.b = true;
        }
        else if (cur_arg == "-e") {
            args.v = args.E = true;
        }
        else if (cur_arg == "-E" || cur_arg == "--show-ends") {
            args.E = true;
        }
        else if (cur_arg == "-n" || cur_arg == "--number") {
            args.n = true;
        }
        else if (cur_arg == "-s" || cur_arg == "--squeeze-blank") {
            args.s = true;
        }
        else if (cur_arg == "-t") {
            args.v = args.T = true;
        }
        else if (cur_arg == "-T" || cur_arg == "--show-tabs") {
            args.T = true;
        }
        else if (cur_arg == "-v" || cur_arg == "--show-nonprinting") {
            args.v = true;
        }
        else if (cur_arg == "-u") {
            ;
        }
        else {
            args.fnames.push_back(cur_arg);
        }
    }

    // override
    if (args.b) {
        args.n = false;
    }
    // stdin if no target file
    if (fpos == 0) {
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
            std::cout << "^" << (ch2 + '@');
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
        std::unique_ptr<std::istream> fp;
        if (fname == "" || fname == "-") {
            fp = std::cin;
        }
        else {
            std::ifstream 
            if ((fp = fopen(fname, "r")) == NULL) {
                fputs("file open error", stderr);
                return 1;
            }
        }

        // print characters
        uint8_t ch;
        while (fread(&ch, 1, 1, fp) > 0) {
            print_char(ch, &args, &stat);
        }

        // file close
        if (fp && fp != stdin) {
            fclose(fp);
        }
    }
}
