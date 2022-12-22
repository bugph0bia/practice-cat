from typing import Union
import sys
import argparse


HELP = 'Concatenate FILE(s) to standard output.'
VERSION = 'cat (practice of python) v1.0 / Written by bugph0bia'


class PrintChar:
    """print character class (Callable)"""

    def __init__(self, args: argparse.Namespace):
        """constructor"""
        self.args = args  # ccommandline arguments
        self.lno = 0  # line no
        self.lfrep = 0  # count of LF repetitions

    def __call__(self, code: int):
        """function object"""
        # -s
        # squeeze blank
        if self.args.s and code == ord('\n') and self.lfrep >= 2:
            return

        # -n, -b
        # print line number
        if ((self.lno == 0 or self.lfrep > 0)
            and (self.args.n or (self.args.b and code != ord('\n')))):
            self.lno += 1
            self.print(f'{self.lno:>6}\t')

        # -E
        # add $ at EOL
        if self.args.E and code == ord('\n'):
            self.print('$')

        # -T, -v
        # convert to ^ notation (only TAB)
        if self.args.T and code == ord('\t'):
            self.print('^I')
        elif self.args.v and code != ord('\t') and code != ord('\n'):
            # add prefix M- notation
            if code & 0b1000_0000:
                self.print('M-')
            code2 = code & ~0b1000_0000

            # convert to ^ notation
            if code2 >= 0x00 and code2 <= 0x1F:
                self.print('^')
                self.print(code2 + ord('@'))
            elif code2 == 0x7F:
                self.print('^?')
            else:
                self.print(code2)
        else:
            self.print(code)

        # count repeat LF
        if code == ord('\n'):
            self.lfrep += 1
        else:
            self.lfrep = 0

    @staticmethod
    def print(data: Union[int, str]):
        """print ascii code or string"""
        # convert to ascii bytes
        if isinstance(data, int):
            # ascii code
            bytes_data = data.to_bytes(1, 'little')
        else:
            # string
            bytes_data = data.encode('ascii')
        # print
        sys.stdout.buffer.write(bytes_data)


def main():
    """main"""
    # parse arguments
    parser = argparse.ArgumentParser(description=HELP)
    parser.add_argument('--version', action='version', version=VERSION)
    parser.add_argument('-A', '--show-all', action='store_true',
                        help='equivalent to -vET', dest='A')
    parser.add_argument('-b', '--number-nonblank', action='store_true',
                        help='number nonempty output lines, overrides -n', dest='b')
    parser.add_argument('-e', action='store_true',
                        help='equivalent to -vE', dest='e')
    parser.add_argument('-E', '--show-ends', action='store_true',
                        help='display $ at end of each line', dest='E')
    parser.add_argument('-n', '--number', action='store_true',
                        help='number all output lines', dest='n')
    parser.add_argument('-s', '--squeeze-blank', action='store_true',
                        help='suppress repeated empty output lines', dest='s')
    parser.add_argument('-t', action='store_true',
                        help='equivalent to -vT', dest='t')
    parser.add_argument('-T', '--show-tabs', action='store_true',
                        help='display TAB characters as ^I', dest='T')
    parser.add_argument('-u', action='store_true',
                        help='(ignored)', dest='u')
    parser.add_argument('-v', '--show-nonprinting', action='store_true',
                        help='use ^ and M- notation, except for LFD and TAB', dest='v')
    parser.add_argument('files', nargs='*',
                        help='with no FILE, or when FILE is -, read standard input')
    args = parser.parse_args()

    # complex
    if args.A:
        args.v = args.E = args.T = True
    if args.e:
        args.v = args.E = True
    if args.t:
        args.v = args.T = True
    # override
    if args.b:
        args.n = False

    # stdin if n
    fnames = args.files
    if not (fnames := args.files):
        fnames = ['-']

    print_char = PrintChar(args)

    # loop target files
    for fname in fnames:
        # set target file object
        if not fname or fname == '-':
            f = sys.stdin
        else:
            f = open(fname, 'rb')

        # print characters
        while (ch := f.read(1)):
            print_char(ord(ch))

        # file close
        if f != sys.stdin:
            f.close()


if __name__ == '__main__':
    main()

