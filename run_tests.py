from subprocess import Popen, PIPE
import openpyxl
from openpyxl import load_workbook
import os

tests = os.listdir("./tests")

local_s = "./local search.exe"
annealing = "./simulated annealing.exe"

workbook = load_workbook(filename="results.xlsx")
sheet = workbook.active

test_index = 3

for t in tests:    
    file_dir = "./tests/" + t + "\n"
    print(f"Test {test_index-2} / {len(tests)}: {t}")
    
    ls = Popen([local_s], stdout=PIPE, stdin=PIPE)
    ls.stdin.write(bytes(file_dir, 'UTF-8'))
    ls.stdin.flush()
    
    ls_res = int(ls.stdout.readline().strip())
    
    sa = Popen([annealing], stdout=PIPE, stdin=PIPE)
    sa.stdin.write(bytes(file_dir, 'UTF-8'))
    sa.stdin.flush()
    
    sa_results = sa.stdout.readline().strip().decode().split(' ')
    
    index_str = str(test_index)
    sheet["A"+index_str] = t
    
    sheet["C"+index_str] = ls_res
    
    sheet["E"+index_str] = float(sa_results[0])
    sheet["F"+index_str] = int(sa_results[1])
    sheet["G"+index_str] = int(sa_results[2])
    sheet["H"+index_str] = float(sa_results[3])
    
    test_index += 1

workbook.save("results.xlsx")
    