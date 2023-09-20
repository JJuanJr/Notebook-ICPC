import subprocess

def run_command(command, input_data=None):
    process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    stdout, _ = process.communicate(input_data)
    return stdout.strip()

while True:
    testcase = run_command(["python3", "gen.py"])
    brute_output = run_command(["./brute"], testcase)
    main_output = run_command(["./main"], testcase)
    
    if brute_output != main_output:
        print("Testcase:\n", testcase)
        print("Output brute:\n", brute_output)
        print("Output sol:\n", main_output)
        break
