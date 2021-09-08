#! /usr/bin/python
import os
import sys
from subprocess import Popen, PIPE
import shlex
import difflib as dl
from rich.console import Console
from rich.table import Table

os.chdir(sys.argv[1] + "/func_tests/")
files = os.listdir(os.getcwd())
console = Console()


def match_name(index, word):
    return lambda name: name.split("_")[index] == word


def fand(f1, f2):
    return lambda *args: f1(*args) and f2(*args)


is_in = match_name(-1, "in.txt")
is_arg = match_name(-1, "args.txt")
is_out = match_name(-1, "out.txt")
is_pos = match_name(0, "pos")
is_neg = match_name(0, "neg")
has_args = any(filter(is_arg, files))
get_number = lambda name: name.split("_")[1]


def get_in_out_arg(pos_neg):
    filt = lambda ioa: list(sorted(filter(fand(ioa, pos_neg), files)))
    ins, outs, args = map(filt, [is_in, is_out, is_arg])
    if not args:
        args = [None for _ in ins]
    return ins, outs, args


def read_file(relpath):
    with open(f"./{relpath}", "r") as f:
        s = f.read()
    return s


def write_to_file(relpath, s):
    with open(f"./{relpath}", "w") as f:
        f.write(s)


def check(ins, outs, args, pos=True):

    fail_count = 0
    console.print(f"[bold] {'Positive' if pos else 'Negative'} tests [/bold]")
    table = Table(show_header=True, header_style="bold white")
    table.add_column("Name")
    table.add_column("Exit Code")
    table.add_column("Succeded")

    failed_table = Table(show_header=True, header_style="bold white")
    failed_table.add_column("Name")
    failed_table.add_column("Args")
    failed_table.add_column("Diff")
    failed_table.add_column("Exit Code")

    for in_path, out_path, arg_path in zip(ins, outs, args):
        if get_number(in_path) != get_number(out_path) or get_number(in_path) != get_number(arg_path):
            print("Something is wrong with your files! You need to have: n in, n out, n args.")
            print(f"You have: {len(ins)} ins, {len(outs)} outs and {len(args)} args")
            print(f"We have a mismatch zip iterating: {in_path} {out_path} {arg_path}")
            exit(1)

        failed = False
        diff = ""
        test_name = "_".join(in_path.split("_")[:2])
        
        a = []
        if arg_path:
            a = read_file(arg_path)
            a = shlex.split(a)
        i = read_file(in_path)

        o = read_file(out_path)

        process = Popen(["../main", *a], stdout=PIPE)
        (output, err) = process.communicate(input=str.encode(i))
        exit_code = process.wait()
        output = output.decode()
        
        output = ''.join(list(filter(lambda x: x != "\r", output)))
        o = ''.join(list(filter(lambda x: x != "\r", o)))

        if pos and exit_code != 0:
            failed = True
        if not pos and exit_code == 0:
            failed = True
        if output != o:
            failed = True
            for d in dl.unified_diff([o], [output]):
                diff += d
        if failed:
            failed_table.add_row(test_name, "".join(a), diff, f"{exit_code}")
            fail_count += 1
        
        table.add_row(test_name, f"{exit_code}", "❌" if failed else "✅")

    console.print(table)
    if fail_count > 0:
        console.print(f"[bold red]Tests failed:[/bold red] {fail_count}/{len(ins)}")
        console.print(failed_table)
    else:
        console.print("[bold green]All tests succeded![/bold green]")


def main():
    pos_in, pos_out, pos_arg = get_in_out_arg(is_pos)
    neg_in, neg_out, neg_arg = get_in_out_arg(is_neg)
    check(pos_in, pos_out, pos_arg)
    check(neg_in, neg_out, neg_arg, False)


if __name__ == "__main__":
    main()
