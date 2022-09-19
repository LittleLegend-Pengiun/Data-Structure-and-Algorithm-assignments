import subprocess
from pathlib import Path
from functools import reduce

class run_test:
    @classmethod
    def text_preprocessing(cls, text):
        new_text = [line for line in text.split('\n') if line.strip() != '']
        return reduce(lambda a, b: a + "\n" + b, new_text[1:], new_text[0])

    @classmethod
    def write_input(cls, str_in, num):
        file_name = "testcase/test" + str(num) + ".txt"
        with open(file_name, 'w') as f:
            f.write(str_in)
        
        return file_name
    
    @classmethod
    def run_solution(cls, file_in, num):
        file_name = "solution/sol" + str(num) + ".txt"
        with open(file_name, "w") as f:
            subprocess.run(["./main", file_in], stdout=f)
        
        return file_name
    
    @classmethod
    def check(cls, str_in, expect, num):
        str_in = cls.text_preprocessing(str_in)
        file1 = cls.write_input(str_in, num)
        file2 = cls.run_solution(file1, num)
        compare = Path(file2).read_text()
        return compare == expect